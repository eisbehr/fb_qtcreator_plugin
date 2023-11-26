#pragma once

#include <qglobal.h>

#if defined(FB_QTCREATOR_PLUGIN_LIBRARY)
#define FB_QTCREATOR_PLUGIN_EXPORT Q_DECL_EXPORT
#else
#define FB_QTCREATOR_PLUGIN_EXPORT Q_DECL_IMPORT
#endif
