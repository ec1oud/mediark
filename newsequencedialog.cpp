#include <QFileDialog>
#include "newsequencedialog.h"
#include "ui_newsequencedialog.h"
#include "copycat.h"
#include "devicefinder.h"

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
//	DeviceFinder finder;
	m_ui->directoryPathLabel->setText(m_basePath.absoluteFilePath() + "/?");
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
	if (newDir.exists())
		m_ui->explanationLabel->setText("Existing directory to be continued:");
	else
		m_ui->explanationLabel->setText("New directory to be created:");
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
	QFileInfo fi(m_ui->directoryPathLabel->text());
	int highest = -1;
	if (fi.exists())
	{
		qDebug() << "looking for existing images in" << fi.absoluteFilePath();
		QStringList filters;
		filters << "*.dd" << "*.iso";
        QRegularExpression sequenceExtractor("\\D+(\\d+)\\D*");
		QDir dir(fi.absoluteFilePath());
		foreach (QString e, dir.entryList(filters))
		{
            QRegularExpressionMatch match = sequenceExtractor.match(e);
            if (match.hasCaptured(1))
			{
				bool ok = false;
                int idx = match.captured(1).toInt(&ok);
//				qDebug() << e << ":" << idx;
				if (ok && idx > highest)
					highest = idx;
			}
		}
		qDebug("highest sequence number found: %d", highest);
	}
	else
	{
		qDebug("doesn't exist, creating");
		fi.dir().mkdir(fi.fileName());
	}
	CopyCat::instance()->setDevicePath(QFileInfo(m_ui->sourceDriveBox->currentText()));
	CopyCat::instance()->currentPlugin()->
            setPathAndSequenceStart(QFileInfo(m_ui->directoryPathLabel->text()), highest + 1);
}

void NewSequenceDialog::on_selectFolderButton_clicked()
{
	qDebug() << "opening from" << m_basePath.absoluteFilePath();
	QString fn = QFileDialog::getExistingDirectory(this,
	   tr("Select existing sequence for continuation"), m_basePath.absoluteFilePath());
	QFileInfo fi(fn);
	m_ui->archiveFolderEdit->setText(fi.baseName());
	m_ui->explanationLabel->setText("Existing directory to be continued:");
}
