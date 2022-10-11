#include "MyOwnButton.h"
#include <QDebug>

MyOwnButton::MyOwnButton(QWidget *parent = 0)
	: QPushButton(parent)
{
	qDebug() << "MyOwnButton class construct...";
}

MyOwnButton::~MyOwnButton()
{
	qDebug() << "MyOwnButton class destruct...";
}
