#ifndef JSCONTEXT_H
#define JSCONTEXT_H

#include <QObject>
#include <QWebEnginePage>
#include <QString>
#include "vcdlog4qt.h"

class JsContext : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString someattribute MEMBER m_someattribute NOTIFY someattributeChanged)

public:
    explicit JsContext(QObject *parent = 0);
    void sendMsg(QWebEnginePage* page, const QString& msg);

private:
    QString m_someattribute;

signals:
    void recvdMsg(const QString& msg);
    void someattributeChanged(const QString &attr);

public slots:
    void onMsg(const QString& msg);
    void setsomeattribute(QString attr);

};

#endif // JSCONTEXT_H
