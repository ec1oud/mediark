#include "devicefinder.h"

DeviceFinder::DeviceFinder() :
	hal("org.freedesktop.Hal.Manager", "/Manager", QDBusConnection::sessionBus(), this)
{
	QDBusPendingReply<QStringList> ret = hal.GetAllDevices();
	ret.waitForFinished();
	if (ret.isError())
		qDebug() << ret.error();
	else
	{
		foreach(QString drive, ret.value())
			qDebug() << drive;
	}
}
