#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openButton_clicked();
    void on_ocrButton_clicked();

private:
    Ui::MainWindow *ui;
    QString imagePath;

    QString performOCR(const QString &imagePath);
};

#endif // MAINWINDOW_H
