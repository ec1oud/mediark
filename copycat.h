#ifndef COPYCAT_H
#define COPYCAT_H

#include <QObject>
#include <QProgressBar>
#include <QThread>
#include "plugin.h"

/**
	A really talented cat who can learn how to copy media in any way you like
	(if provided instructions in the form of a Plugin).
*/
class CopyCat : public QThread
{
public:
	static CopyCat* instance();
	Plugin* selectPlugin(QString name);
	Plugin* currentPlugin() { return m_currentPlugin; }
	QStringList allPlugins();
	QFileInfo devicePath() { return m_devicePath; }
	void setDevicePath(QFileInfo dp);
	int nextSequenceNumber() { return m_currentPlugin->nextSequenceNumber(); }
	void setNextSequenceNumber(int v);
	/**
		Go kitty go
	*/
	void go(QProgressBar* progressBar, QImage scannedImage);

protected:
	void run();

private:
	CopyCat();
	QMap<QString, Plugin*> plugins;
	Plugin* m_currentPlugin;
	QFileInfo m_devicePath;
//	QImage m_image;
};

#endif // COPYCAT_H
