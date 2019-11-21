#include "GenAlgorithm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GenAlgorithm w;
	w.show();
	return a.exec();
}
	