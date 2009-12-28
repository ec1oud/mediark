#ifndef DDPLUGIN_H
#define DDPLUGIN_H

#include "plugin.h"

class DDPlugin : public Plugin
{
	Q_OBJECT
	
public:
    DDPlugin();
	virtual QString name() { return "Internal DD (record copier)"; }
	virtual void start(QFileInfo device);
	virtual QString fileExt() { return "dd"; }
};

#endif // DDPLUGIN_H
