#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include "settings.h"

#define STR_ORGANIZATION "Electron Cloud"
#define STR_PRODUCT "MediArk"

#define SETTING_GROUP_MAIN "main"
#define SETTING_GROUP_SESSION "session"
#define SETTING_GROUP_OPEN_FILES "open-files"
#define SETTING_GROUP_RECENT_FILES "recent-files"
#define SETTING_RECENT_FILES_LIMIT "recentFilesLimit"
#define SETTING_GROUP_SCAN_GEOMETRY "scan-geometry"
#define SETTING_GROUP_SCAN_MATRIX "scan-matrix"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define RECORD_SIZE_BYTES 1024

#endif // COMMON_H
