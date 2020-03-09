#ifndef COMMONMETH_H
#define COMMONMETH_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>
#include <QUrl>
#include "vcdlog4qt.h"

#define ICON_PATH "C://qt-pro/icon/icon.ico"
//#define DEFAULT_CONN_URL "http://219.83.160.145:8080"
#define DEFAULT_CONN_URL "https://blog.csdn.net/FlayHigherGT"
//#define DEFAULT_CONN_URL "appstore.verycloud.cn:8080"
//#define DEFAULT_CONN_URL "http://219.83.160.146:5476/"
//#define DEFAULT_CONN_URL "http://192.168.170.231:8084/test"

enum js_cmd {
  SHOWFOLDER
};

class CommonMeth
{
public:
    CommonMeth();
    QString json_to_qstring(QJsonObject json);
    QString url_decode(QString &data);
};

#endif // COMMONMETH_H
