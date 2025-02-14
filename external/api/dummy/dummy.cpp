#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>       // read(), write(), close()
#include <errno.h>  
#include <sys/time.h>     // FD_SET, FD_ZERO, FD_ISSET, select()
#include <arpa/inet.h>    // inet_ntoa()
#include "dummy.h"
#include "../src_winterface/winterface.h"

#define MAX 1000
#define SA struct sockaddr
#define MAX_CLIENTS 30

extern BUF net_buf;
extern int new_argc;
extern char **netw_argv;

// Struktur für einen Client
typedef struct {
    int fd;       // File Descriptor des Clients
    WINT netw;    // Netzwerkschnittstelle aus deiner winterface-Bibliothek
    int active;   // Kennzeichen, ob der Slot belegt ist (1 = aktiv, 0 = frei)
} client_t;

void *thread_server(void *p)
{
    int PORT = *(int *)p;
    char msg[256];
    int speed = 0;
    
    // Setze den Message-String anhand des Ports
    if (PORT == TRAIN_PORT_Y) {
        sprintf(msg, "TRAIN_Y");
    } else if (PORT == TRAIN_PORT_B) {
        sprintf(msg, "TRAIN_B");
    } else if (PORT == MB_PORT) {
        sprintf(msg, "MAINBOARD");
    } else {
        sprintf(msg, "UNKNOWN");
    }

    int sockfd, newfd, max_sd, activity, i;
    socklen_t len;
    struct sockaddr_in servaddr, cli;

    // Befehlsarray initialisieren
    CMD cmd_arr[CMD_ARR_ENTRYS];
    cmd_arr_init(cmd_arr);

    // Erstelle den Listening-Socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("%s socket creation failed...\n", msg);
        exit(EXIT_FAILURE);
    } else {
        printf("%s Socket successfully created..\n", msg);
    }
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0) {
        printf("%s socket bind failed...\n", msg);
        exit(EXIT_FAILURE);
    } else {
        printf("%s Socket successfully binded..\n", msg);
    }

    if (listen(sockfd, 5) != 0) {
        printf("%s Listen failed...\n", msg);
        exit(EXIT_FAILURE);
    } else {
        printf("%s Server listening...\n", msg);
    }
    
    // Array für die Client-Verbindungen
    client_t clients[MAX_CLIENTS];
    for (i = 0; i < MAX_CLIENTS; i++) {
        clients[i].fd = 0;
        clients[i].active = 0;
    }
    
    fd_set readfds;
    
    while (1) {
        // Setze das fd_set zurück
        FD_ZERO(&readfds);
        // Füge den Listening-Socket hinzu
        FD_SET(sockfd, &readfds);
        max_sd = sockfd;
        
        // Füge alle aktiven Client-Sockets zum fd_set hinzu
        for (i = 0; i < MAX_CLIENTS; i++) {
            int sd = clients[i].fd;
            if (sd > 0)
                FD_SET(sd, &readfds);
            if (sd > max_sd)
                max_sd = sd;
        }
        
        // Blockiere, bis auf einen der Sockets Daten warten (keine Timeout-Angabe)
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if (activity < 0 && errno != EINTR) {
            perror("select error");
            continue;
        }
        
        // Neue Verbindung eingetroffen?
        if (FD_ISSET(sockfd, &readfds)) {
            len = sizeof(cli);
            newfd = accept(sockfd, (SA *)&cli, &len);
            if (newfd < 0) {
                perror("accept error");
                continue;
            }
            printf("%s: Neue Verbindung, socket fd: %d, IP: %s, Port: %d\n",
                   msg, newfd, inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));
                   
            // Füge den neuen Client in das Array ein
            for (i = 0; i < MAX_CLIENTS; i++) {
                if (clients[i].fd == 0) {
                    clients[i].fd = newfd;
                    clients[i].active = 1;
                    netw_init(&clients[i].netw, newfd);
                    printf("%s: Neuer Client wurde an Index %d hinzugefügt.\n", msg, i);
                    break;
                }
            }
            if (i == MAX_CLIENTS) {
                printf("%s: Maximale Anzahl Clients erreicht. Verbindung wird abgelehnt.\n", msg);
                close(newfd);
            }
        }
        
        // Prüfe alle aktiven Client-Sockets auf eingehende Daten
        for (i = 0; i < MAX_CLIENTS; i++) {
            int sd = clients[i].fd;
            if (sd > 0 && FD_ISSET(sd, &readfds)) {
                // Verwende netw_recv() zum Auslesen. Geht die Verbindung verloren, liefert netw_recv() 0 zurück.
                if (netw_recv(&clients[i].netw)) {
                    printf("%s: Daten von Socket %d empfangen.\n", msg, sd);
                    int id = netw_handle_message(&clients[i].netw, cmd_arr);
                    if (id == TCP_SPEED) {
                        speed = 1;
                    }
                    if (id == REPORT_SPEED) {
                        printf("%s: Sende Speed-Antwort...\n", msg);
                        char buf[16];
                        sprintf(buf, "%d", speed);
                        write(sd, buf, 16);
                    }
                } else {
                    // Verbindung wurde geschlossen – Socket freigeben
                    printf("%s: Client auf Socket %d hat die Verbindung beendet.\n", msg, sd);
                    close(sd);
                    clients[i].fd = 0;
                    clients[i].active = 0;
                }
            }
        }
    }
    
    // Dieser Teil wird aufgrund der Endlosschleife nicht erreicht
    close(sockfd);
    return NULL;
}
