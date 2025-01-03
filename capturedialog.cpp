#include "capturedialog.h"
#include "ui_capturedialog.h"
#include "settings.h"
#include "copycat.h"
#include "plugin.h"
#include <QDebug>
#include <QDir>

CaptureDialog::CaptureDialog(QWidget *parent) :
    QDialog(parent),
	m_ui(new Ui::CaptureDialog),
	m_scanner(ImageScanner::instance())
{
    m_ui->setupUi(this);
	int idx = 0;
	int chosenIdx = 0;
	QString chosenType = Settings::instance()->stringOrDefault(SETTING_GROUP_SESSION, "media-type", "");
	foreach(QString mt, Settings::instance()->allMediaTypes())
	{
		m_ui->mediaTypes->addItem(mt);
		if (chosenType == mt)
			chosenIdx = idx;
		++idx;
	}
	m_ui->mediaTypes->setCurrentIndex(chosenIdx);
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

void CaptureDialog::diskCaptured()
{
	m_ui->captureSequenceNumber->setValue(m_ui->captureSequenceNumber->value() + 1);
	disconnect(CopyCat::instance()->currentPlugin(), SIGNAL(done(bool)), this, NULL);
}

void CaptureDialog::showEvent(QShowEvent* /*event*/)
{
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
	m_scanner->setSequence(m_ui->scanSequenceFrom->value(), m_ui->scanSequenceTo->value() + 1);
	m_scanner->scan(m_ui->mediaTypes->currentText());
}

void CaptureDialog::on_captureButton_clicked()
{
	m_ui->captureImageLabel->setPixmap(QPixmap::fromImage(m_scannedImage));
//	m_ui->scanImageLabel->setText("Disk\nImage");
	connect(CopyCat::instance()->currentPlugin(), SIGNAL(done(bool)),
			this, SLOT(diskCaptured()));
	CopyCat::instance()->go(m_ui->captureProgressBar, m_scannedImage);
	CaptureDialog::update();
//	m_ui->captureImageLabel->setText("Disk\nImage");
}

void CaptureDialog::update()
{
	m_ui->scanPathLabel->setText(QString("%1 -> %2")
		.arg(Settings::instance()->chosenScanner())
		.arg(m_scanner->nextImageOutput().absoluteFilePath()));
	m_ui->captureDataLabel->setText(QString("%1 -> %2")
		.arg(CopyCat::instance()->devicePath().absoluteFilePath())
		.arg(CopyCat::instance()->currentPlugin()->nextImageOutput().absoluteFilePath()));
	QFileInfo graphicFi = CopyCat::instance()->currentPlugin()->nextImageOutput();
	graphicFi = QFileInfo(graphicFi.dir(), graphicFi.baseName() + ".jpg");
	if (graphicFi.exists())
	{
		QPixmap pm(graphicFi.absoluteFilePath());
		m_ui->captureImageLabel->setPixmap(pm);
	}
	else
		m_ui->captureImageLabel->setText("No\nImage");
}

void CaptureDialog::on_scanSequenceNumber_valueChanged(int)
{
	update();
}

void CaptureDialog::on_captureSequenceNumber_valueChanged(int val)
{
	CopyCat::instance()->setNextSequenceNumber(val);
	update();
}

void CaptureDialog::on_mediaTypes_currentIndexChanged(QString mediaType)
{
	QSize matrixDims = Settings::instance()->matrixDims(mediaType);
	m_ui->scanSequenceTo->setValue(m_ui->scanSequenceFrom->value() +
								   matrixDims.width() * matrixDims.height() - 1);
	Settings::instance()->setString(SETTING_GROUP_SESSION, "media-type", mediaType);
}

void CaptureDialog::on_scanSequenceFrom_valueChanged(int )
{
	QSize matrixDims = Settings::instance()->matrixDims(m_ui->mediaTypes->currentText());
	m_scanner->setSequence(m_ui->scanSequenceFrom->value(), m_ui->scanSequenceTo->value() + 1);
	m_ui->scanSequenceTo->setValue(m_ui->scanSequenceFrom->value() +
								   matrixDims.width() * matrixDims.height() - 1);
	m_ui->scanSequenceTo->setMinimum(m_ui->scanSequenceFrom->value());
	update();
}

void CaptureDialog::on_scanSequenceTo_valueChanged(int )
{
	m_scanner->setSequence(m_ui->scanSequenceFrom->value(), m_ui->scanSequenceTo->value() + 1);
	update();
}
