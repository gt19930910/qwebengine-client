#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebChannel>
#include <QWebEngineProfile>
#include <QDebug>
#include <QCloseEvent>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>
#include <QDesktopServices>

#include "jscontext.h"
#include "vcdlog4qt.h"
#include "webview.h"
#include "webpage.h"
#include "downloadmanager.h"
#include "softinfo.h"
#include "commonmeth.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void web_show();
    bool get_js_data(const QString &data);
    bool parse_js_cmd(QString &action);
    void open_desktop();
    void web_prepare();
    void download_finish(qint64 recvTotal, DownloadManager *manager);
    void download_progress(qint64 byteRecved, qint64 recvTotal, DownloadManager *manager);
    void closeEvent(QCloseEvent *event);

private slots:
    void downloadRequested(QWebEngineDownloadItem* download);
    void html_load_progress(int progress);
    void html_load_finished(bool success);

private:
    Ui::MainWindow *ui;
    WebView *m_webView;
    Webpage *m_webPage;
    QWebChannel *m_webChannel;
    JsContext *m_jsContext;
    CommonMeth *m_commonMeth;
    QString m_currUrl;
};

#endif // MAINWINDOW_H
