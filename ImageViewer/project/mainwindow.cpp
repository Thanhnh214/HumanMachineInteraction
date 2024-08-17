#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!imagePath.isEmpty()) {
        QImage image(imagePath);
        if (image.isNull()) {
            qDebug() << "Invalid image file";
        } else {
            ui->imageLabel->setPixmap(QPixmap::fromImage(image));
        }
    }
}

void MainWindow::on_ocrButton_clicked()
{
    if (!imagePath.isEmpty()) {
        QString recognizedText = performOCR(imagePath);
        ui->textEdit->setPlainText(recognizedText);
    }
}

QString MainWindow::performOCR(const QString &imagePath)
{
    tesseract::TessBaseAPI api;
    if (api.Init(nullptr, "eng")) {
        qDebug() << "Could not initialize Tesseract.";
        return QString();
    }

    Pix *image = pixRead(imagePath.toUtf8().constData());
    api.SetImage(image);
    char *text = api.GetUTF8Text();
    QString recognizedText = QString::fromUtf8(text);

    api.End();
    delete[] text;
    pixDestroy(&image);

    return recognizedText;
}
