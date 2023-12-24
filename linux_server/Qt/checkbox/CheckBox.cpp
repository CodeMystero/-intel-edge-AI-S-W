#include <QApplication>
#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QButtonGroup>

int main(int argc, char** argv){

	QApplication app(argc, argv);

	QWidget *widget = new QWidget(0);
	QButtonGroup *bg = new QButtonGroup(widget);

	QLabel *lb = new QLabel("selector",widget);
	lb->move(10, 10);

	QCheckBox *cb1 = new QCheckBox("Option &1", widget);
	cb1->move(10,30);
	bg->addButton(cb1, 1);

	QCheckBox *cb2 = new QCheckBox("Option &2", widget);
   cb2->move(10,50);
   bg->addButton(cb2, 2);

   QCheckBox *cb3 = new QCheckBox("Option &3", widget);
   cb3->move(10,70);
   bg->addButton(cb3, 3);

   QCheckBox *cb4 = new QCheckBox("Option &4", widget);
   cb4->move(10,90);
   bg->addButton(cb4, 4);

   bg->setExclusive(false);
   QObject::connect(bg, SIGNAL(buttonclicked(int)), lb, SLOT(setNum(int)));

   widget->resize(110, 140);
   widget->show();

   return app.exec();

}
