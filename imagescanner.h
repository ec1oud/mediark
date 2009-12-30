#ifndef IMAGESCANNER_H
#define IMAGESCANNER_H
#include <sane/sane.h>

#include <QObject>
#include <QImage>
#include <QThread>

class ImageScanner : public QThread
{
	Q_OBJECT
public:
	static ImageScanner* instance();
	void scan(QString mediaType);
	QStringList allScannerNames();
	QString scannerDev(int idx);

public slots:

signals:
	void progress(int val);
	void progressRange(int zero, int max);
	void done(QImage img);

protected:
	void run();

private:
	ImageScanner();
	void setOptions(SANE_Handle dev, QString mediaType);
	void getOptions(SANE_Handle dev);

	QList<const SANE_Device*> m_allDevices;
	SANE_Handle m_scanner;
	QString m_mediaType;
//	QImage m_scannedImage;
};

#endif // IMAGESCANNER_H
