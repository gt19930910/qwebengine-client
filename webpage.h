#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <QWebEnginePage>

#include "vcdlog4qt.h"

class Webpage : public QWebEnginePage
{
    Q_OBJECT
public:
    Webpage();
};

#endif // WEBPAGE_H
