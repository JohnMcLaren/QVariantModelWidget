#pragma once

#include <QFrame>
#include <QLayout>
#include <QScreen>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>
#include "../qvarianttablewidget.h"
#include "../qvarianttreewidget.h"

class Window : public QFrame
{
	Q_OBJECT

public:
	Window(const int width, const int height)
	{
		setGeometry(QRect(screen()->size().width() / 3, screen()->size().height() / 3, width, height));
	}

	QVariantTreeWidget treeTest;
	QVariantTableWidget tableTest;

	//bool bClose =false;

private:

protected:
	//void closeEvent(QCloseEvent *event) { bClose =true; };
};
