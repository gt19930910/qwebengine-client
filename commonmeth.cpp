#include "commonmeth.h"

CommonMeth::CommonMeth()
{

}

QString CommonMeth::json_to_qstring(QJsonObject json)
{
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray1 = document.toJson(QJsonDocument::Compact);
    QString strJson(byteArray1);
    return strJson;
}

QString CommonMeth::url_decode(QString &data)
{
    QByteArray ba = data.toLocal8Bit();
    return QUrl::fromPercentEncoding(ba);
}

//    //此处将json转为QString
//    QJsonObject json;
//    json.insert("Name", "Qt");
//    json.insert("From", 1991);
//    json.insert("Cross Platform", true);
//    QJsonDocument document;
//    document.setObject(json);
//    QByteArray byteArray1 = document.toJson(QJsonDocument::Compact);
//    QString strJson(byteArray1);
//    qDebug() << strJson;

//    //此处将QString转QJsonObject并解析
//    QByteArray byteArray2 = strJson.toLocal8Bit().data();

//    QJsonParseError jsonError;
//    QJsonDocument doucment = QJsonDocument::fromJson(byteArray2, &jsonError);  // 转化为 JSON 文档
//    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
//        if (doucment.isObject()) { // JSON 文档为对象
//            QJsonObject object = doucment.object();  // 转化为对象
//            if (object.contains("Name")) {  // 包含指定的 key
//                QJsonValue value = object.value("Name");  // 获取指定 key 对应的 value
//                if (value.isString()) {  // 判断 value 是否为字符串
//                    QString strName = value.toString();  // 将 value 转化为字符串
//                    qDebug() << "Name : " << strName;
//                }
//            }
//            if (object.contains("From")) {
//                QJsonValue value = object.value("From");
//                if (value.isDouble()) {
//                    int nFrom = value.toVariant().toInt();
//                    qDebug() << "From : " << nFrom;
//                }
//            }
//            if (object.contains("Cross Platform")) {
//                QJsonValue value = object.value("Cross Platform");
//                if (value.isBool()) {
//                    bool bCrossPlatform = value.toBool();
//                    qDebug() << "CrossPlatform : " << bCrossPlatform;
//                }
//            }
//        }
//    }
