#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsApplication1 w;
    w.show();
    
    return a.exec(); //让进程进消息循环，阻塞在这一行
}
