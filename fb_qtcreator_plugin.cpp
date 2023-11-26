#include "fb_qtcreator_plugin.h"
#include "fb_qtcreator_pluginconstants.h"

#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/icontext.h>
#include <coreplugin/icore.h>

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QPlainTextEdit>

namespace fb_qtcreator_plugin::Internal {

fb_qtcreator_pluginPlugin::fb_qtcreator_pluginPlugin()
{
    // Create your members
}

fb_qtcreator_pluginPlugin::~fb_qtcreator_pluginPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

void fb_qtcreator_pluginPlugin::initialize()
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.

    // If you need access to command line arguments or to report errors, use the
    //    bool IPlugin::initialize(const QStringList &arguments, QString *errorString)
    // overload.

    auto moveByParagraphUpAction = new QAction(tr("Move the cursor up to the next empty line"), this);
    Core::Command *moveByParagraphUpCmd = Core::ActionManager::registerAction(moveByParagraphUpAction,
                                                             Constants::MOVE_BY_PARAGRAPH_UP_ACTION_ID,
                                                             Core::Context(
                                                                 Core::Constants::C_GLOBAL));
    moveByParagraphUpCmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Up")));
    connect(moveByParagraphUpAction, &QAction::triggered, this, [this]() {
        moveByParagraphAction(true);
    });

    auto moveByParagraphDownAction = new QAction(tr("Move the cursor down to the next empty line"), this);
    Core::Command *moveByParagraphDownCmd = Core::ActionManager::registerAction(moveByParagraphDownAction,
                                                                              Constants::MOVE_BY_PARAGRAPH_DOWN_ACTION_ID,
                                                                              Core::Context(
                                                                                  Core::Constants::C_GLOBAL));
    moveByParagraphDownCmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Down")));
    connect(moveByParagraphDownAction, &QAction::triggered, this, [this]() {
        moveByParagraphAction(false);
    });

    Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::MENU_ID);
    menu->menu()->setTitle(tr("fb_qtcreator_plugin"));
    menu->addAction(moveByParagraphUpCmd);
    menu->addAction(moveByParagraphDownCmd);
    Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);
}

void fb_qtcreator_pluginPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag fb_qtcreator_pluginPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

void fb_qtcreator_pluginPlugin::moveByParagraphAction(bool up)
{
    auto edit = qobject_cast<QPlainTextEdit *>(Core::ICore::currentContextWidget());
    if(edit) {
        QString line;
        auto cursor = edit->textCursor();
        do {
            cursor.clearSelection();
            cursor.movePosition(up ? QTextCursor::Up : QTextCursor::Down);
            cursor.select(QTextCursor::LineUnderCursor);
            line = cursor.selectedText();
            cursor.movePosition(up ? QTextCursor::StartOfLine : QTextCursor::EndOfLine);
        } while(!line.trimmed().isEmpty() && (up ? !cursor.atStart() : !cursor.atEnd()));
        cursor.clearSelection();
        edit->setTextCursor(cursor);
    }
}

} // namespace fb_qtcreator_plugin::Internal
