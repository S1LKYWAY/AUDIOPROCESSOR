// main.cpp
#include "mainwindow.h"
#include <QApplication>
#include <QFileDialog>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Open .wav File", QString(), "Wave Files (*.wav)");

    if (!filePath.isEmpty()) {
        mainWindow.loadWavFile(filePath);
        mainWindow.show();
    }

    return app.exec();
}
