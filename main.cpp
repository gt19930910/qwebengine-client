#include "mainwindow.h"
#include <QApplication>

#include "commonmeth.h"
#include "log4qt.h"

int main(int argc, char *argv[])
{
    //支持高分屏
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    VcdLog4Qt::getInstance()->info("==================== client start ==================");

    MainWindow w;

    QIcon icon = QIcon(ICON_PATH);
    w.setWindowIcon(icon);

//    w.show();

    return a.exec();
}
