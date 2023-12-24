#include <QApplication>
#include <QWidget>
#include <QRadioButton>
#include <QButtonGroup>

int main(int argc, char** argv){


	QApplication app(argc, argv);

	QWidget *widget = new QWidget(0);
	QButtonGroup *bg = new QButtonGroup(widget);

	QRadioButton *rb1 = new QRadioButton("Option &1", widget);
	rb1->move(10,10);
	bg->addButton(rb1);

	QRadioButton *rb2 = new QRadioButton("Option &2", widget);
   rb2->move(10,30);
   bg->addButton(rb2);

   QRadioButton *rb3 = new QRadioButton("Option &3", widget);
   rb3->move(10,50);
   bg->addButton(rb3);

   QRadioButton *rb4 = new QRadioButton("Option &4", widget);
   rb4->move(10,70);
   bg->addButton(rb4);

   QRadioButton *rb5 = new QRadioButton("Option &5", widget);
   rb5->move(10,90);
   bg->addButton(rb5);

   widget->resize(140, 130);
   widget->show();
   
	return app.exec();
}
