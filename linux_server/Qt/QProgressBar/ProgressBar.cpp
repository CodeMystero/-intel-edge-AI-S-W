#include <QApplication>
#include <QProgressBar>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char** argv){

	QApplication app(argc, argv);

	QWidget window;
	QVBoxLayout layout(&window);

	QProgressBar *pb = new QProgressBar();
	//pb->setOrientation(Qt::Vertical);
	pb->setRange(0,100);
	pb->setValue(0);
	pb->setFormat("%v floors");
	pb->setAlignment(Qt::AlignLeft);

	
	layout.addWidget(pb);


	QTimer timer;
	QObject::connect(&timer, &QTimer::timeout, [=](){
						  	int currentValue = pb->value();
						  	if(currentValue < pb->maximum()){
						  		pb->setValue(currentValue + 1);
							}else{
								pb->setValue(0);
							}
							});

	timer.start(1000);

	pb->setFixedSize(400,400);
	pb->move(100,100);	

	window.show();

	return app.exec();

}


