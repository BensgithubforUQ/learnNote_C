#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsApplication1 w;
    w.show();
    
    return a.exec(); //�ý��̽���Ϣѭ������������һ��
}