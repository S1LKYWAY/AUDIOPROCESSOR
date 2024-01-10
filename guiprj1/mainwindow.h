// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void loadWavFile(const QString &filePath);
    void drawWaveforms(const QVector<QVector<qint16>> &audioData);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QVector<qint16>> audioData;
    bool wavFileLoaded;
};

#endif // MAINWINDOW_H
