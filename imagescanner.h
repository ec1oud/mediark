#ifndef IMAGESCANNER_H
#define IMAGESCANNER_H
#include <sane/sane.h>

#include <QObject>
#include <QImage>

class ImageScanner : public QObject
{
	Q_OBJECT
public:
	static ImageScanner* instance();
	QImage scan(QString mediaType);
	QStringList allScannerNames();
	QString scannerDev(int idx);

public slots:

signals:
	void progress(int val);
	void progressRange(int zero, int max);

private:
	ImageScanner();
	void setOptions(SANE_Handle dev, QString mediaType);
	void getOptions(SANE_Handle dev);

	QList<const SANE_Device*> m_allDevices;
	SANE_Handle m_scanner;
};

#endif // IMAGESCANNER_H
