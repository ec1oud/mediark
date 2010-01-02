#ifndef SHELLPLUGIN_H
#define SHELLPLUGIN_H

#include "plugin.h"

/**
	In contrast to a progressive plugin this one is decidedly retro:
	runs a program and sends its output to a plain text frame.
*/
class ShellPlugin : public Plugin
{
public:
    ShellPlugin();
};

#endif // SHELLPLUGIN_H
