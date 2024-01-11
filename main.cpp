//
// Created by Ivan Ugryumov on 03.01.2024.
//
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow win;
    win.show();

    return qApp->exec();
}
