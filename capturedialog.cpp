#include "capturedialog.h"
#include "ui_capturedialog.h"
#include "settings.h"
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

void CaptureDialog::showEvent(QShowEvent* event)
{
	m_ui->scannerDevLabel->setText(Settings::instance()->chosenScanner());
	m_ui->scanProgressBar->setValue(0);
	m_ui->captureProgressBar->setValue(0);
	m_ui->scanImageLabel->setText("Disk\nImage");
	m_ui->captureImageLabel->setText("Disk\nImage");
}

void CaptureDialog::on_scanButton_clicked()
{
//	QRectF scanArea = Settings::instance()->scanGeometry(m_ui->mediaTypes->currentText());
//	qDebug() << "scan area: " << scanArea;
	QImage img = m_scanner->scan(m_ui->mediaTypes->currentText());
	m_ui->scanImageLabel->setPixmap(QPixmap::fromImage(img));
}
