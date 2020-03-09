#include "jscontext.h"

JsContext::JsContext(QObject *parent) : QObject(parent) {
    VcdLog4Qt::getInstance()->info("new jscontext");
}

void JsContext::sendMsg(QWebEnginePage* page, const QString& msg)
{
    page->runJavaScript(QString("recvMessage('%1');").arg(msg));
}

void JsContext::onMsg(const QString &msg)
{
    emit recvdMsg(msg);
}

void JsContext::setsomeattribute(QString attr)
{
    m_someattribute = attr;
    emit someattributeChanged(m_someattribute);
}
