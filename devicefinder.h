#ifndef DEVICEFINDER_H
#define DEVICEFINDER_H

#include <QObject>
#include <QtDBus>
#include "hal_manager_interface.h"

/**
	Uses HAL via DBus to discover all removable devices.
*/
class DeviceFinder : public QObject
{
public:
    DeviceFinder();

private:
	HALManagerInterface hal;
};

#endif // DEVICEFINDER_H
