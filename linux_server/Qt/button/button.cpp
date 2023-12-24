#include <QApplication>
#include <QPushButton>
#include <QIcon>

int main(int argc, char **argv){
	
	QApplication app(argc, argv);

	QPushButton button("Click me");	
	button.resize(1000,1000);
	button.move(300,300);
	//QObject::connect(button, SIGNAL(clicked()),&app, SLOT(quit()));	
	QIcon icon(":/sumo.png");
	button.setIcon(icon);
	button.show();

	return app.exec();

}
