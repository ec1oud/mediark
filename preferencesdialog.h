#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QtGui/QDialog>

namespace Ui {
    class PreferencesDialog;
}

class PreferencesDialog : public QDialog {
    Q_OBJECT
public:
    PreferencesDialog(QWidget *parent = 0);
    ~PreferencesDialog();

protected:
    void changeEvent(QEvent *e);
	void showEvent(QShowEvent* event);
	void updateDimensionLabels(QRectF rect);

private:
    Ui::PreferencesDialog *m_ui;

private slots:
	void on_resolutionEdit_editingFinished();
 void on_mediaTypes_currentIndexChanged(QString );
	void on_tl_x_edit_editingFinished();
	void on_tl_y_edit_editingFinished();
	void on_br_x_edit_editingFinished();
	void on_br_y_edit_editingFinished();
	void on_scannerBox_currentIndexChanged(int index);
};

#endif // PREFERENCESDIALOG_H
