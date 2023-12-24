#include <QApplication>
#include <QLCDNumber>

int main(int argc, char** argv){

	QApplication app(argc, argv);

	QWidget* widget = new QWidget(0);

	QLCDNumber *lcd1 = new QLCDNumber(widget);
	lcd1->setSegmentStyle(QLCDNumber::Flat);
	lcd1->display(2014);
	lcd1->move(10,10);

   QLCDNumber *lcd2 = new QLCDNumber(widget);
   lcd2->setSegmentStyle(QLCDNumber::Flat);
   lcd2->display(2015);
   lcd2->move(10,40);

   widget->resize(120,80);
   widget->show();

   return app.exec();

}
