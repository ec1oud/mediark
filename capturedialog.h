#ifndef CAPTUREDIALOG_H
#define CAPTUREDIALOG_H

#include <QDialog>
#include "imagescanner.h"

namespace Ui {
    class CaptureDialog;
}

class CaptureDialog : public QDialog {
    Q_OBJECT

public:
    CaptureDialog(QWidget *parent = 0);
    ~CaptureDialog();

public slots:
	void imageScanned(QImage img);
	void diskCaptured();

protected:
    void changeEvent(QEvent *e);
	void showEvent(QShowEvent* event);
	void update();

private:
    Ui::CaptureDialog *m_ui;
	ImageScanner* m_scanner;
	QImage m_scannedImage;

private slots:
	void on_scanSequenceTo_valueChanged(int );
 void on_scanSequenceFrom_valueChanged(int );
 void on_mediaTypes_currentIndexChanged(QString );
 void on_scanSequenceNumber_valueChanged(int );
	void on_captureSequenceNumber_valueChanged(int );
	void on_captureButton_clicked();
	void on_scanButton_clicked();
};

#endif // CAPTUREDIALOG_H
