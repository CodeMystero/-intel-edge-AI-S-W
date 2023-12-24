#include <QApplication>
#include <QSpinBox>

int main(int argc, char** argv){

	QApplication app(argc, argv);

	QSpinBox *sb = new QSpinBox();
	sb->setRange(0,10);
	sb->setValue(5);
	sb->setWrapping(true);
	sb->setSpecialValueText("Value");
	sb->show();

	return app.exec();
}
