#include "ringsmapprogressbar.h"
#include "ringsmapprogressbarplugin.h"

#include <QtPlugin>

RingsMapProgressbarPlugin::RingsMapProgressbarPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void RingsMapProgressbarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool RingsMapProgressbarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *RingsMapProgressbarPlugin::createWidget(QWidget *parent)
{
    return new RingsMapProgressbar(parent);
}

QString RingsMapProgressbarPlugin::name() const
{
    return QLatin1String("RingsMapProgressbar");
}

QString RingsMapProgressbarPlugin::group() const
{
    return QLatin1String("");
}

QIcon RingsMapProgressbarPlugin::icon() const
{
    return QIcon();
}

QString RingsMapProgressbarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString RingsMapProgressbarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool RingsMapProgressbarPlugin::isContainer() const
{
    return false;
}

QString RingsMapProgressbarPlugin::domXml() const
{
    return QLatin1String("<widget class=\"RingsMapProgressbar\" name=\"ringsMapProgressbar\">\n</widget>\n");
}

QString RingsMapProgressbarPlugin::includeFile() const
{
    return QLatin1String("ringsmapprogressbar.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ringsmapprogressbarplugin, RingsMapProgressbarPlugin)
#endif // QT_VERSION < 0x050000
