#include "fonts.h"

Fonts::Fonts(){

    int fontId = QFontDatabase::addApplicationFont(":fonts/BigBlueTerm437NerdFont-Regular.ttf");
    if (fontId == -1) {
        // Fehlerbehandlung: Schriftart konnte nicht geladen werden
        qWarning() << "Konnte die Schriftart nicht laden!";
    }

    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);

    this->setFamily(fontFamily);
}

