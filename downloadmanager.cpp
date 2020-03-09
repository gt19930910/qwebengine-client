#include "downloadmanager.h"

DownloadManager::DownloadManager(QWebEngineDownloadItem *download, QObject *parent)
    : download(download)
    , QObject(parent)
    , m_comMeth(new CommonMeth())
{
    VcdLog4Qt::getInstance()->info("new download manager");
    if (download) {
        QString path = m_comMeth->url_decode(download->path());
        VcdLog4Qt::getInstance()->info("download path:" + path);

        dfile.setFile(path);
        durl = download->url();
    }
    init();
}

void DownloadManager::init()
{
    if (download) {
        VcdLog4Qt::getInstance()->info("bind download state");
        connect(download.data(), SIGNAL(downloadProgress(qint64,qint64)),
                this, SLOT(downloadProgress(qint64,qint64)));
        connect(download.data(), SIGNAL(finished()),
                this, SLOT(finished()));
    }
    get_file_name();
}

bool DownloadManager::get_file_name(bool promptForFileName)
{

/*
    QSettings settings;
    settings.beginGroup(QLatin1String("downloadmanager"));//downloadmanager这是一个组，可以防止字段名相同
    //获取桌面路径(最后是没有/的) C:/Users/gt/Desktop
    QString defaultLocation = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    if (dfile.absoluteDir().exists())//如果dfile里面的绝对路径存在的话，C:/Users/gt/Downloads
        defaultLocation = dfile.absolutePath();//将defaultLocation从桌面路径变成dfile里面的路径(最后不带/)
    //这句话是读取setting里面的downloadmanager组的downloadDirectory字段的值，存储到defaultLocation里面，返回值给到downloadDirectory
    QString downloadDirectory = settings.value(QLatin1String("downloadDirectory"), defaultLocation).toString();
    if (!downloadDirectory.isEmpty())//如果downloadDirectory存在的话，给他后面加一个/
        downloadDirectory += QLatin1Char('/');

    //初始化一个QFileInfo,给路径和文件的绝对路径，初始化完之后文件的绝对路径会改成前面的路径
    QString defaultFileName = QFileInfo(downloadDirectory, dfile.fileName()).absoluteFilePath();

    QString fileName = defaultFileName;
    dfile.setFile(fileName);

    if (download && download->state() == QWebEngineDownloadItem::DownloadRequested)
        download->setPath(dfile.absoluteFilePath());
*/

    QString defaultLocation = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    if (!defaultLocation.isEmpty())//如果downloadDirectory存在的话，给他后面加一个/
        defaultLocation += QLatin1Char('/');
    QString defaultFileName = QFileInfo(defaultLocation, dfile.fileName()).absoluteFilePath();
    QString fileName = defaultFileName;
    dfile.setFile(fileName);

    if (download && download->state() == QWebEngineDownloadItem::DownloadRequested)
        download->setPath(dfile.absoluteFilePath());
    VcdLog4Qt::getInstance()->info("set download file path:" + dfile.absoluteFilePath());

    return true;
}

void DownloadManager::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    m_bytesReceived = bytesReceived;
    if (bytesTotal == -1) {
        //progressBar->setValue(0);
        //progressBar->setMaximum(0);
    } else {
        //progressBar->setValue(bytesReceived);
        //progressBar->setMaximum(bytesTotal);
    }
    emit progress_callback(m_bytesReceived, bytesTotal, this);
}

void DownloadManager::finished()
{
    if (download) {
        QWebEngineDownloadItem::DownloadState state = download->state();
        bool interrupted = false;

        switch (state) {
        case QWebEngineDownloadItem::DownloadRequested: // Fall-through.
        case QWebEngineDownloadItem::DownloadInProgress:
            Q_UNREACHABLE();
            break;
        case QWebEngineDownloadItem::DownloadCompleted:
            break;
        case QWebEngineDownloadItem::DownloadCancelled:
            interrupted = true;
            break;
        case QWebEngineDownloadItem::DownloadInterrupted:
            interrupted = true;
            break;
        }

        if (interrupted) {
            return;
        }
    }
    emit finish_callback(m_bytesReceived, this);
}
