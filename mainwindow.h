#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
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
    Ui::MainWindow *ui;
	CaptureDialog captureDialog;
	PreferencesDialog preferencesDialog;

private slots:
	void on_actionPreferences_triggered();
	void on_actionAdd_media_triggered();
};

#endif // MAINWINDOW_H
