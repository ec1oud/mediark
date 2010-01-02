#include "capturedialog.h"
#include "ui_capturedialog.h"
#include "settings.h"
#include "copycat.h"
#include "plugin.h"
#include <QDebug>

CaptureDialog::CaptureDialog(QWidget *parent) :
    QDialog(parent),
	m_ui(new Ui::CaptureDialog),
	m_scanner(ImageScanner::instance())
{
    m_ui->setupUi(this);
	foreach(QString mt, Settings::instance()->allMediaTypes())
		m_ui->mediaTypes->addItem(mt);
	connect(m_scanner, SIGNAL(progressRange(int,int)),
			m_ui->scanProgressBar, SLOT(setRange(int,int)));
	connect(m_scanner, SIGNAL(progress(int)),
			m_ui->scanProgressBar, SLOT(setValue(int)));
	connect(m_scanner, SIGNAL(done(QImage)),
			this, SLOT(imageScanned(QImage)));
}

CaptureDialog::~CaptureDialog()
{
    delete m_ui;
}

void CaptureDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void CaptureDialog::imageScanned(QImage img)
{
	m_scannedImage = img;
	m_ui->scanImageLabel->setPixmap(QPixmap::fromImage(m_scannedImage));
}

void CaptureDialog::showEvent(QShowEvent* event)
{
	m_ui->scannerDevLabel->setText(Settings::instance()->chosenScanner());
	m_ui->scanProgressBar->setValue(0);
	m_ui->captureProgressBar->setValue(0);
	m_ui->scanImageLabel->setText("Disk\nImage");
	m_ui->captureImageLabel->setText("Disk\nImage");
	m_ui->captureSequenceNumber->setValue(CopyCat::instance()->nextSequenceNumber());
	update();
}

void CaptureDialog::on_scanButton_clicked()
{
//	QRectF scanArea = Settings::instance()->scanGeometry(m_ui->mediaTypes->currentText());
//	qDebug() << "scan area: " << scanArea;
	m_scanner->scan(m_ui->mediaTypes->currentText());
}

void CaptureDialog::on_captureButton_clicked()
{
	m_ui->captureImageLabel->setPixmap(QPixmap::fromImage(m_scannedImage));
	m_ui->scanImageLabel->setText("Disk\nImage");
	CopyCat::instance()->go(m_ui->captureProgressBar, m_scannedImage);
	CaptureDialog::update();
	m_ui->captureImageLabel->setText("Disk\nImage");
}

void CaptureDialog::update()
{
	m_ui->captureDataLabel->setText(QString("%1 -> %2")
		.arg(CopyCat::instance()->devicePath().absoluteFilePath())
		.arg(CopyCat::instance()->currentPlugin()->nextImageOutput().absoluteFilePath()));
}

void CaptureDialog::on_scanSequenceNumber_valueChanged(int val)
{
	update();
}

void CaptureDialog::on_captureSequenceNumber_valueChanged(int val)
{
	CopyCat::instance()->setNextSequenceNumber(val);
	update();
}
