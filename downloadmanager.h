#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H
#include <QWebEngineDownloadItem>
#include <QtCore/QFileInfo>
#include <QtCore/QSettings>
#include <QStandardPaths>
#include <QUrl>
#include <QDir>
#include <QObject>
#include <QDebug>

#include "vcdlog4qt.h"
#include "commonmeth.h"

class DownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit DownloadManager(QWebEngineDownloadItem *download, QObject *parent = 0);
    void init();
    bool get_file_name(bool promptForFileName = false);

    QScopedPointer<QWebEngineDownloadItem> download;
    QUrl durl;
    QFileInfo dfile;

signals:
    void finish_callback(qint64 recvTotal, DownloadManager *pthis);
    void progress_callback(qint64 byteRecved, qint64 recvTotal, DownloadManager *pthis);

private slots:
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void finished();

private:
    CommonMeth *m_comMeth;
    qint64 m_bytesReceived;
};

#endif // DOWNLOADMANAGER_H
