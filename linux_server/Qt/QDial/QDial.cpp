#include <QApplication>
#include <QDial>
#include <wiringPi.h>
#include <softPwm.h>
#include <QLabel>
#include <QVBoxLayout>
int main(int argc, char** argv){

	QApplication app(argc, argv);

	wiringPiSetupGpio();
	softPwmCreate(21, 0, 100);
	//pinMode(21,PWM_OUTPUT);

	QWidget window;
	QVBoxLayout layout(&window);

	QDial *dl = new QDial();
	dl->setNotchesVisible(true);
	//dl->setNotchTarget(10);
	dl->setRange(0,100);
	dl->setWrapping(true);

	QLabel *label = new QLabel("0");
	label->setAlignment(Qt::AlignCenter);


	QObject::connect(dl, &QDial::valueChanged, [=](int value){
							softPwmWrite(21, value);
							label->setNum(value);
						});

	layout.addWidget(dl);
	layout.addWidget(label);

	window.show();
	return app.exec();
}
