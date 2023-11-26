#pragma once

#include "fb_qtcreator_plugin_global.h"

#include <extensionsystem/iplugin.h>

namespace fb_qtcreator_plugin::Internal {

class fb_qtcreator_pluginPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "fb_qtcreator_plugin.json")

public:
    fb_qtcreator_pluginPlugin();
    ~fb_qtcreator_pluginPlugin() override;

    void initialize() override;
    void extensionsInitialized() override;
    ShutdownFlag aboutToShutdown() override;

private:
    void moveByParagraphAction(bool up);
};

} // namespace fb_qtcreator_plugin::Internal
