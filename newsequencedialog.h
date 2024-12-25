#ifndef NEWSEQUENCEDIALOG_H
#define NEWSEQUENCEDIALOG_H

#include <QDialog>
#include <QFileInfo>

namespace Ui {
    class NewSequenceDialog;
}

class NewSequenceDialog : public QDialog {
    Q_OBJECT
public:
	NewSequenceDialog(QFileInfo basePath, QWidget *parent = 0);
    ~NewSequenceDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::NewSequenceDialog *m_ui;
	QFileInfo m_basePath;

private slots:
	void on_selectFolderButton_clicked();
 void on_buttonBox_accepted();
 void on_imageFormatBox_currentIndexChanged(QString );
 void on_sourceDriveBox_currentIndexChanged(QString );
 void on_archiveFolderEdit_textChanged(QString );
};

#endif // NEWSEQUENCEDIALOG_H
