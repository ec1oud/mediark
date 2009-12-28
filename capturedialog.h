#ifndef CAPTUREDIALOG_H
#define CAPTUREDIALOG_H

#include <QtGui/QDialog>
#include "imagescanner.h"

namespace Ui {
    class CaptureDialog;
}

class CaptureDialog : public QDialog {
    Q_OBJECT
public:
    CaptureDialog(QWidget *parent = 0);
    ~CaptureDialog();

protected:
    void changeEvent(QEvent *e);
	void showEvent(QShowEvent* event);
	void update();

private:
    Ui::CaptureDialog *m_ui;
	ImageScanner* m_scanner;
	QImage m_scannedImage;

private slots:
	void on_captureButton_clicked();
	void on_scanButton_clicked();
};

#endif // CAPTUREDIALOG_H
