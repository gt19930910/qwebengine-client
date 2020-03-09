#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWebEngineView>
#include <QCloseEvent>
#include <QApplication>
#include <QMessageBox>
#include <QIcon>

#include "commonmeth.h"

class WebView : public QWebEngineView
{
    Q_OBJECT

public:
    WebView(QWidget *widget = 0);
    void closeEvent(QCloseEvent *event);
};

#endif // WEBVIEW_H
