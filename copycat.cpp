#include "copycat.h"
#include "ddplugin.h"
#include <QDir>

CopyCat::CopyCat()
{
	DDPlugin* ddp = new DDPlugin();
	plugins.insert(ddp->name(), ddp);
	/// @todo use preferences
	m_currentPlugin = ddp;
	m_devicePath = Settings::instance()->stringOrDefault(
			"session", "captureDevice", "/dev/fd0");
}

CopyCat* CopyCat::instance()
{
	static CopyCat* self = new CopyCat();
	return self;
}

Plugin* CopyCat::selectPlugin(QString name)
{
	m_currentPlugin = plugins[name];
	return m_currentPlugin;
}

void CopyCat::setDevicePath(QFileInfo dp)
{
	m_devicePath = dp;
	Settings::instance()->setString("session", "captureDevice", dp.absoluteFilePath());
}

QStringList CopyCat::allPlugins()
{
	return plugins.keys();
}

void CopyCat::go(QProgressBar* progressBar, QImage scannedImage)
{
	m_image = scannedImage;
	Plugin* impl = CopyCat::instance()->currentPlugin();
	connect(impl, SIGNAL(totalRecords(int, int)),
			progressBar, SLOT(setRange(int,int)));
	connect(impl, SIGNAL(recordsCopied(int)),
			progressBar, SLOT(setValue(int)));
	start();

	/// @todo disconnect signals when done
}

void CopyCat::run()
{
	Plugin* impl = CopyCat::instance()->currentPlugin();
	QFileInfo diskImagePath = impl->nextImageOutput();
	QFileInfo scannedImagePath(diskImagePath.dir(), diskImagePath.baseName() + ".jpg");
	m_image.save(scannedImagePath.absoluteFilePath());
	impl->start(devicePath());
}