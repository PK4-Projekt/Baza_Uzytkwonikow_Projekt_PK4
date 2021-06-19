//
// Created by snaf on 30.04.2021.
//

#ifndef UNTITLED1_MESSAGE_H
#define UNTITLED1_MESSAGE_H


#include <QMessageBox>

class Message {
public:
    static void warning(const QString& message) {
        QMessageBox msgWarning;
        msgWarning.setText(message);
        msgWarning.setIcon(QMessageBox::Warning);
        msgWarning.setWindowTitle("Ostrzeżenie");
        msgWarning.exec();
    }

    static void info(const QString& message) {
        QMessageBox msgWarning;
        msgWarning.setText(message);
        msgWarning.setIcon(QMessageBox::Information);
        msgWarning.setWindowTitle("Informacja");
        msgWarning.exec();
    }
};


#endif //UNTITLED1_MESSAGE_H
