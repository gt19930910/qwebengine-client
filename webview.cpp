#include "webview.h"

WebView::WebView(QWidget *widget):QWebEngineView(widget)
{
    VcdLog4Qt::getInstance()->info("new webview");
    QIcon icon = QIcon(ICON_PATH);
    this->setWindowIcon(icon);
}

void WebView::closeEvent(QCloseEvent *event)
{
    QMessageBox mBox(QMessageBox::Information, tr("云端网络"), tr("是否确定退出？   "));
    QPushButton *btnYes = mBox.addButton(tr("确定"), QMessageBox::YesRole);
    QPushButton *btnNo = mBox.addButton(tr("取消"), QMessageBox::NoRole);

    QIcon icon = QIcon(ICON_PATH);
    mBox.setWindowIcon(icon);
    mBox.exec();

    if ((QPushButton*)mBox.clickedButton() == btnYes)
    {
        event->accept();
        VcdLog4Qt::getInstance()->info("==================application quit================");
        QApplication::quit();
    }

    if ((QPushButton*)mBox.clickedButton() == btnNo)
    {
        event->ignore();
    }
}
