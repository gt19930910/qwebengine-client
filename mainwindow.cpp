#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_commonMeth(new CommonMeth()),
    m_currUrl(DEFAULT_CONN_URL)
{
    ui->setupUi(this);

    VcdLog4Qt::getInstance()->info("DEFAULT_LOG4QT_CONFIG_PATH:" + QString(LOG4QT_PATH));
    VcdLog4Qt::getInstance()->info("DEFAULT_CONN_URL:" + QString(DEFAULT_CONN_URL));
    VcdLog4Qt::getInstance()->info("DEFAULT_ICON_PATH:" + QString(ICON_PATH));

    web_prepare();
    web_show();
}

MainWindow::~MainWindow()
{
    if (m_jsContext)
        delete m_jsContext;
    if (m_webChannel)
        delete m_webChannel;
    if (m_webPage)
        delete m_webPage;
    if (m_webView)
        delete m_webView;
    if (m_commonMeth)
        delete m_commonMeth;

    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox mBox(QMessageBox::Information, tr("云端网络"), tr("是否确定退出？   "));
    QPushButton *btnYes = mBox.addButton(tr("确定"), QMessageBox::YesRole);
    QPushButton *btnNo = mBox.addButton(tr("取消"), QMessageBox::NoRole);

    QIcon icon = QIcon(ICON_PATH);
    mBox.setWindowIcon(icon);
    mBox.exec();

    if ((QPushButton*)mBox.clickedButton() == btnYes) {
        event->accept();
        VcdLog4Qt::getInstance()->info("==================application quit================");
        QApplication::quit();
    }

    if ((QPushButton*)mBox.clickedButton() == btnNo)
        event->ignore();
}

void MainWindow::web_prepare()
{
    //WebView *webView = new WebView(this->ui->widget);
    WebView *webView = new WebView();
    webView->setWindowTitle("云端网络 AppStore");
    webView->setContextMenuPolicy(Qt::NoContextMenu);

    JsContext *jsContext = new JsContext(this);
    QWebChannel *webChannel = new QWebChannel();
    Webpage *webPage = new Webpage();
    webChannel->registerObject("context", jsContext);
    webPage->setWebChannel(webChannel);

    connect(jsContext, &JsContext::recvdMsg, this, [this](const QString &msg) {
        VcdLog4Qt::getInstance()->info("bind jscontext recv slot");
        this->get_js_data(msg);
    });

    //绑定下载信号,只能接收到当前页面下载内容
    connect(webPage->profile(), SIGNAL(downloadRequested(QWebEngineDownloadItem*)),
            this, SLOT(downloadRequested(QWebEngineDownloadItem*)));
    VcdLog4Qt::getInstance()->info("bind webpage downloadrequested slot");

    connect(webPage, SIGNAL(loadProgress(int)), this, SLOT(html_load_progress(int)));
    connect(webPage, SIGNAL(loadFinished(bool)), this, SLOT(html_load_finished(bool)));

    m_webView = webView;
    m_webPage = webPage;
    m_jsContext = jsContext;
    m_webChannel = webChannel;
}

void MainWindow::html_load_progress(int progress)
{
    VcdLog4Qt::getInstance()->info(QString::number(progress));
}

void MainWindow::html_load_finished(bool success)
{
    if (success)
        VcdLog4Qt::getInstance()->info("load success");
    else
        VcdLog4Qt::getInstance()->info("load failed");
}


void MainWindow::web_show()
{
    VcdLog4Qt::getInstance()->info("current url:" + m_currUrl);
    m_webView->setPage(m_webPage);
    m_webView->setUrl(QUrl(m_currUrl));
    VcdLog4Qt::getInstance()->info("webview size:1200x810");
    m_webView->resize(1200, 810);
    //m_webView->setWindowTitle(m_currUrl);
    m_webView->show();
}

void MainWindow::downloadRequested(QWebEngineDownloadItem* download)
{
    VcdLog4Qt::getInstance()->info("downloadRequested emited");
//    if (download->savePageFormat() != QWebEngineDownloadItem::UnknownSaveFormat) {
//        SavePageDialog dlg(this, download->savePageFormat(), download->path());
//        if (dlg.exec() != SavePageDialog::Accepted)
//            return;
//        download->setSavePageFormat(dlg.pageFormat());
//        download->setPath(dlg.filePath());
//    }
    DownloadManager *manager = new DownloadManager(download);
    connect(manager, &DownloadManager::finish_callback, this, [this](qint64 recvTotal, DownloadManager *manager) {
        this->download_finish(recvTotal, manager);
    });
    connect(manager, &DownloadManager::progress_callback, this, [this](qint64 byteRecved, qint64 recvTotal, DownloadManager *manager) {
        this->download_progress(byteRecved, recvTotal, manager);
    });
    download->accept();
}

void MainWindow::download_finish(qint64 recvTotal, DownloadManager *manager)
{
    VcdLog4Qt::getInstance()->info("manager id:" + QString::number(manager->download->id()) + " download finish");
    VcdLog4Qt::getInstance()->info("received data:" + QString::number(recvTotal));
    VcdLog4Qt::getInstance()->info("url path:" + manager->durl.path());
    VcdLog4Qt::getInstance()->info("url host:" + manager->durl.host());
    VcdLog4Qt::getInstance()->info("download file path:" + manager->dfile.absoluteFilePath());

    QJsonObject json;
    json.insert("host", manager->durl.host());
    json.insert("path", manager->durl.path());
    json.insert("current", recvTotal);
    json.insert("total", recvTotal);
    json.insert("finished", true);
    m_jsContext->setsomeattribute(m_commonMeth->json_to_qstring(json));

    manager->deleteLater();
}

void MainWindow::download_progress(qint64 byteRecved, qint64 recvTotal, DownloadManager *manager)
{
    //VcdLog4Qt::getInstance()->info(QString("manager id ") + QString::number(manager->download->id()) + " download data:" + QString::number(byteRecved) + "   total:" + QString::number(recvTotal));

    QJsonObject json;
    json.insert("host", manager->durl.host());
    json.insert("path", manager->durl.path());
    json.insert("current", byteRecved);
    json.insert("total", recvTotal);
    json.insert("finished", false);
    m_jsContext->setsomeattribute(m_commonMeth->json_to_qstring(json));
}

void MainWindow::open_desktop()
{
    VcdLog4Qt::getInstance()->info("open desktop");
    QString defaultLocation = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QDesktopServices::openUrl(QUrl(defaultLocation));
}

bool MainWindow::parse_js_cmd(QString &action)
{
    bool action_ok = true;
    VcdLog4Qt::getInstance()->info("parser_js_cmd:action name=" + action);

    open_desktop();

//    switch (action.toStdString()) {

//        case SHOWFOLDER:
//            open_desktop();
//            break;
//        default:
//            action_ok = false;
//            break;
//    }
    return action_ok;
}

bool MainWindow::get_js_data(const QString &data)
{
    QString d = data;
    VcdLog4Qt::getInstance()->info("get js data:" + d);

    QByteArray byteArray = d.toLocal8Bit().data();

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
        if (doucment.isObject()) { // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("action")) {  // 包含指定的 key
                QJsonValue value = object.value("action");  // 获取指定 key 对应的 value
                if (value.isString()) {  // 判断 value 是否为字符串
                    QString action = value.toString();  // 将 value 转化为字符串
                    if (!parse_js_cmd(action)) {
                        VcdLog4Qt::getInstance()->info("js action name is unknowned");
                        return false;
                    } else {
                        return true;
                    }
                }
            }
        }
    }
    VcdLog4Qt::getInstance()->info("parse js json failed");
    return false;
}
