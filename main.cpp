#include <QApplication>
#include <QTranslator>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QTranslator qtTranslator;
	qtTranslator.load("qt_" + QLocale::system().name());
	a.installTranslator(&qtTranslator);

	QTranslator appTranslator;
	appTranslator.load("QCodeCounter_" + QLocale::system().name());
	a.installTranslator(&appTranslator);

	MainWindow w;
	w.show();

	return a.exec();
}
