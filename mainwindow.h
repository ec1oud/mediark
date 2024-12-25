#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include "capturedialog.h"
#include "preferencesdialog.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
	void refreshArchives();

private:
    Ui::MainWindow *ui;
	CaptureDialog captureDialog;
	PreferencesDialog preferencesDialog;
	QFileInfo archiveDir;

private slots:
	void on_actionNew_sequence_triggered();
	void on_actionOpen_archive_dir_triggered();
	void on_actionPreferences_triggered();
	void on_actionAdd_media_triggered();
};

#endif // MAINWINDOW_H
