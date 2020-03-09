#ifndef VCDLOG4QT_H
#define VCDLOG4QT_H

#include <QDEBUG>

#include "logmanager.h"
#include "propertyconfigurator.h"

#define LOG4QT_PATH "C://qt-pro/etc/QtLog4Qt.conf"

class VcdLog4Qt
{
public:

    static VcdLog4Qt* getInstance()
    {
        if (m_pInstance == NULL)
            m_pInstance = new VcdLog4Qt(LOG4QT_PATH, "LOGF");
        return m_pInstance;
    }

    void info(const QString &msg) {
        m_log->info(msg.toStdString().c_str());
        qDebug() << msg;
    }

private:
    Log4Qt::Logger *m_log;
    static VcdLog4Qt* m_pInstance;

    VcdLog4Qt(const QString &path, const QString &name) {
        set_log_path(path);
        set_log_name(name);
    }

    void set_log_path(const QString &path) {
        Log4Qt::PropertyConfigurator::configure(path);
    }

    void set_log_name(const QString &name) {
        m_log = Log4Qt::Logger::logger(name);
    }
};

#endif // VCDLOG4QT_H
