//
// Created by Ivan Ugryumov on 03.01.2024.
//
#include "MainWindow.h"
#include "MetalWidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    auto *metalWgt = new MetalWidget();
    setCentralWidget(metalWgt);

    metalWgt->initView();
    setMinimumSize(600, 400);
}

