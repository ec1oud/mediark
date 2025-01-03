#include "preferencesdialog.h"
#include "settings.h"
#include "ui_preferencesdialog.h"
#include "imagescanner.h"
#include "copycat.h"
#include <QDebug>

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::PreferencesDialog)
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
}

PreferencesDialog::~PreferencesDialog()
{
    delete m_ui;
}

void PreferencesDialog::changeEvent(QEvent *e)
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

void PreferencesDialog::showEvent(QShowEvent* /*event*/)
{
	/// @todo thread this
	foreach (QString scanner, ImageScanner::instance()->allScannerNames())
		m_ui->scannerBox->addItem(scanner);
	m_ui->captureMethodBox->addItems(CopyCat::instance()->allPlugins());
}

void PreferencesDialog::on_scannerBox_currentIndexChanged(int index)
{
	Settings::instance()->chosenScanner(ImageScanner::instance()->scannerDev(index));
}

void PreferencesDialog::on_tl_x_edit_editingFinished()
{
	Settings* settings = Settings::instance();
	QString mediaType = m_ui->mediaTypes->currentText();
	QRectF rect = settings->scanGeometry(mediaType);
	bool ok = false;
	rect.setLeft(m_ui->tl_x_edit->text().toDouble(&ok));
	if (ok)
	{
		settings->setScanGeometry(mediaType, rect);
		updateDimensionLabels(rect);
	}
}

void PreferencesDialog::on_tl_y_edit_editingFinished()
{
	Settings* settings = Settings::instance();
	QString mediaType = m_ui->mediaTypes->currentText();
	QRectF rect = settings->scanGeometry(mediaType);
	bool ok = false;
	rect.setTop(m_ui->tl_y_edit->text().toDouble(&ok));
	if (ok)
	{
		settings->setScanGeometry(mediaType, rect);
		updateDimensionLabels(rect);
	}
}

void PreferencesDialog::on_br_x_edit_editingFinished()
{
	Settings* settings = Settings::instance();
	QString mediaType = m_ui->mediaTypes->currentText();
	QRectF rect = settings->scanGeometry(mediaType);
	bool ok = false;
	rect.setRight(m_ui->br_x_edit->text().toDouble(&ok));
	if (ok)
	{
		settings->setScanGeometry(mediaType, rect);
		updateDimensionLabels(rect);
	}
}

void PreferencesDialog::on_br_y_edit_editingFinished()
{
	Settings* settings = Settings::instance();
	QString mediaType = m_ui->mediaTypes->currentText();
	QRectF rect = settings->scanGeometry(mediaType);
	bool ok = false;
	rect.setBottom(m_ui->br_y_edit->text().toDouble(&ok));
	if (ok)
	{
		settings->setScanGeometry(mediaType, rect);
		updateDimensionLabels(rect);
	}
}

void PreferencesDialog::on_resolutionEdit_editingFinished()
{
	bool ok = false;
	int val =  m_ui->resolutionEdit->text().toInt(&ok);
	if (ok)
		Settings::instance()->setInt("main", "resolution", val);
}

void PreferencesDialog::on_mediaTypes_currentIndexChanged(QString mediaType)
{
	QRectF rect = Settings::instance()->scanGeometry(mediaType);
//	qDebug() << rect;
//	qDebug() << "br_x" << QString::number(rect.right());
	m_ui->tl_x_edit->setText(QString::number(rect.left()));
	m_ui->tl_y_edit->setText(QString::number(rect.top()));
	m_ui->br_x_edit->setText(QString::number(rect.right()));
	m_ui->br_y_edit->setText(QString::number(rect.bottom()));
	QSize matrixDims = Settings::instance()->matrixDims(mediaType);
	m_ui->matrixColumns->setValue(matrixDims.width());
	m_ui->matrixRows->setValue(matrixDims.height());
	updateDimensionLabels(rect);
}

void PreferencesDialog::updateDimensionLabels(QRectF rect)
{
	m_ui->widthLabel->setText(QString::number(rect.width()));
	m_ui->heightLabel->setText(QString::number(rect.height()));
}

void PreferencesDialog::on_matrixColumns_valueChanged(int)
{
	Settings::instance()->setMatrixDims(m_ui->mediaTypes->currentText(),
		QSize(m_ui->matrixColumns->value(), m_ui->matrixRows->value()));
}

void PreferencesDialog::on_matrixRows_valueChanged(int)
{
	Settings::instance()->setMatrixDims(m_ui->mediaTypes->currentText(),
		QSize(m_ui->matrixColumns->value(), m_ui->matrixRows->value()));
}
