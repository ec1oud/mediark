#include "newsequencedialog.h"
#include "ui_newsequencedialog.h"
#include "copycat.h"

NewSequenceDialog::NewSequenceDialog(QFileInfo basePath, QWidget *parent) :
    QDialog(parent),
	m_ui(new Ui::NewSequenceDialog),
	m_basePath(basePath)
{
    m_ui->setupUi(this);
	m_ui->errorLabel->setVisible(false);
	m_ui->imageFormatBox->addItems(CopyCat::instance()->allPlugins());
	m_ui->sourceDriveBox->addItem(CopyCat::instance()->devicePath().absoluteFilePath());
	/// @todo populate choices with all the removable drives via HAL (DBus)
	/// http://indhubharathi.wordpress.com/2008/08/17/listing-all-removable-devices-in-linux/
}

NewSequenceDialog::~NewSequenceDialog()
{
    delete m_ui;
}

void NewSequenceDialog::changeEvent(QEvent *e)
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

void NewSequenceDialog::on_archiveFolderEdit_textChanged(QString txt)
{
	/// @todo validate it
	QFileInfo newDir(m_basePath.absoluteFilePath() + "/" + txt);
	m_ui->directoryPathLabel->setText(newDir.absoluteFilePath());
}

void NewSequenceDialog::on_sourceDriveBox_currentIndexChanged(QString dev)
{
//	CopyCat::instance()->setDevicePath(QFileInfo(dev));
}

void NewSequenceDialog::on_imageFormatBox_currentIndexChanged(QString name)
{
	CopyCat::instance()->selectPlugin(name);
}

void NewSequenceDialog::on_buttonBox_accepted()
{
	CopyCat::instance()->setDevicePath(QFileInfo(m_ui->sourceDriveBox->currentText()));
	CopyCat::instance()->currentPlugin()->
			setPathAndSequenceStart(m_ui->directoryPathLabel->text());
}
