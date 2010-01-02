#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"
#include "newsequencedialog.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	archiveDir(Settings::instance()->stringOrDefault(SETTING_GROUP_SESSION, "archiveDir", "."))
{
    ui->setupUi(this);
	refreshArchives();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshArchives()
{
	/// @todo show icons or something
	setWindowTitle(QString("%1: %2").arg(STR_PRODUCT).arg(archiveDir.absoluteFilePath()));
}

void MainWindow::on_actionAdd_media_triggered()
{
	captureDialog.show();
}

void MainWindow::on_actionPreferences_triggered()
{
	preferencesDialog.show();
}

void MainWindow::on_actionOpen_archive_dir_triggered()
{
	QString dir = QFileDialog::getExistingDirectory(
			this, "Choose a location to store sets of disk images",
			archiveDir.absoluteFilePath(), QFileDialog::ShowDirsOnly);
	Settings::instance()->setString(SETTING_GROUP_SESSION, "archiveDir", dir);
	archiveDir = QFileInfo(dir);
	refreshArchives();
}

void MainWindow::on_actionNew_sequence_triggered()
{
	NewSequenceDialog dlg(archiveDir);
	dlg.exec();
}
