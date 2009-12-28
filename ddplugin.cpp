#include "ddplugin.h"
#include <QApplication>
#include <QMessageBox>

DDPlugin::DDPlugin() : Plugin()
{
}

void DDPlugin::start(QFileInfo device)
{
	QFileInfo destFile = nextImageOutput();
	QFile dev(device.absoluteFilePath());
	if (!dev.open(QIODevice::ReadOnly))
	{
		QMessageBox::critical(QApplication::activeWindow(), tr(STR_PRODUCT),
			tr("Failed to open %1").arg(device.absoluteFilePath()));
		return;
	}
	QFile dest(destFile.absoluteFilePath());
	if (!dest.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		QMessageBox::critical(QApplication::activeWindow(), tr(STR_PRODUCT),
			tr("Failed to open %1").arg(destFile.absoluteFilePath()));
		return;
	}

	// 1k at a time (sweet disk-drive)
	QByteArray buf(RECORD_SIZE_BYTES, 0);
	qint64 volumeSize = dev.size();
	emit totalRecords(0, volumeSize / RECORD_SIZE_BYTES);
	qint64 recordLen = dev.read(buf.data(), 1024);
	int recordIdx = 0;
	while (recordLen > 1)
	{
		dest.write(buf.constData(), recordLen);
		emit recordsCopied(++recordIdx);
		recordLen = dev.read(buf.data(), 1024);
	}
	emit totalRecords(0, 100);
	emit recordsCopied(100);
	dev.close();
}
