// mainwindow.cpp
#include "mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QDataStream>
#include <QPainter>
#include <QDebug>
#include <cmath> // Include cmath for log2 function

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), wavFileLoaded(false) {
    // Initialize any necessary settings for the MainWindow
}

double calculateEntropy(const QVector<QVector<qint16>> &audioData) {
    QVector<qint16> allSamples;
    for (const auto &channelData : audioData) {
        allSamples.append(channelData);
    }

    QHash<qint16, int> sampleCounts;
    for (const qint16 sample : allSamples) {
        sampleCounts[sample]++;
    }

    double entropy = 0.0;
    const int totalSamples = allSamples.size();
    for (const auto &count : sampleCounts) {
        double probability = static_cast<double>(count) / totalSamples;
        entropy -= probability * log2(probability);
    }

    return entropy;
}

void MainWindow::loadWavFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error opening file";
        return;
    }

    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::LittleEndian);

    // Read and validate the header
    qint32 chunkID;
    qint32 fileSize;
    qint32 format;
    qint32 subchunk1ID;
    qint32 subchunk1Size;
    qint16 audioFormat;
    qint16 numChannels;
    qint32 sampleRate;
    qint32 byteRate;
    qint16 blockAlign;
    qint16 bitsPerSample;
    qint32 subchunk2ID;
    qint32 subchunk2Size;

    stream >> chunkID >> fileSize >> format;
    stream >> subchunk1ID >> subchunk1Size >> audioFormat >> numChannels;
    stream >> sampleRate >> byteRate >> blockAlign >> bitsPerSample;
    stream >> subchunk2ID >> subchunk2Size;

    qDebug() << "Read header successfully";
    qDebug() << "audioFormat:" << audioFormat;
    qDebug() << "numChannels:" << numChannels;

    if (audioFormat != 1 || numChannels != 2) {
        qDebug() << "Unsupported audio format or number of channels";
        file.close();
        return;
    }

    const int bytesPerSample = bitsPerSample / 8;
    const int numSamples = subchunk2Size / (numChannels * bytesPerSample);

    audioData.resize(numChannels);
    for (int channel = 0; channel < numChannels; ++channel) {
        audioData[channel].resize(numSamples);
        for (int i = 0; i < numSamples; ++i) {
            qint16 sample;
            stream >> sample;
            audioData[channel][i] = sample;
        }
    }

    file.close();
    wavFileLoaded = true;

    double entropy = calculateEntropy(audioData);
    qDebug() << "Entropy:" << entropy;

    update();  // Trigger a repaint
}

void MainWindow::drawWaveforms(const QVector<QVector<qint16>> &audioData) {
    const int margin = 20;
    const int height = this->height() - 2 * margin;
    const int width = this->width() - 2 * margin;

    for (int channel = 0; channel < audioData.size(); ++channel) {
        QVector<qint16> data = audioData[channel];
        double scaleFactor = height / static_cast<double>(SHRT_MAX);
        QVector<QPointF> points;

        for (int i = 0; i < data.size(); ++i) {
            double x = margin + (i * width / static_cast<double>(data.size()));
            double y = height / 2 - data[i] * scaleFactor;
            points.append(QPointF(x, y));
        }

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        if (!points.isEmpty()) {
            painter.drawPolyline(points);
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    if (wavFileLoaded) {
        drawWaveforms(audioData);
    }
}


