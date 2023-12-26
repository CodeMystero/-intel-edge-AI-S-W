#include <QApplication>
#include <QWidget>
#include <wiringPi.h>
#include <QPushButton>
#include <QPixmap>
#include <softPwm.h>
#include <QDial>
#include <QLabel>

const int led = 21;

int main(int argc, char** argv){

	wiringPiSetupGpio();
	pinMode(led, OUTPUT);

	softPwmCreate(20, 0, 100);

	QApplication app(argc, argv);

	QPixmap buttonImage("/home/pi/work/finalprj/sumo.png");
	QSize newSize(100,110);
	QPixmap scaledImage = buttonImage.scaled(newSize, Qt::KeepAspectRatio);

	QWidget window;
	window.setGeometry(100,100,300,400);


	QDial *pwmDial = new QDial(&window);
	pwmDial->setNotchesVisible(true);
	pwmDial->setRange(0,100);
	pwmDial->setWrapping(true);

   QPushButton *quitButton = new QPushButton("Quit", &window);
   QPushButton *toggleLEDButton = new QPushButton(&window);

	pwmDial->resize(100,100);
	pwmDial->move(50,250);
   
	quitButton->resize(100, 50);
   quitButton->move(50, 50);

   toggleLEDButton->resize(100, 50);
   toggleLEDButton->move(50, 120);

	toggleLEDButton->setIcon(scaledImage);
	toggleLEDButton->setIconSize(newSize);
	toggleLEDButton->setFixedSize(newSize);

	/*
  	toggleLEDButton->setStyleSheet("QPushButton {"
					"border-radius: 30px;"
					"background-color: #3498db;"
					"color: white;"
					"}"
					"QPushButton:hover{"
					"background-color: #e74c3c;"
					"}");

	*/
   window.setWindowTitle("Yeah I am doing shitt");

    
   QObject::connect(quitButton, SIGNAL(clicked()), &app, SLOT(quit()));

  
	QObject::connect(toggleLEDButton, &QPushButton::clicked, [=]() {
        digitalWrite(led, !digitalRead(led));
    });

	QObject::connect(pwmDial, &QDial::valueChanged, [=](int value){

							softPwmWrite(20,value);
						//	label->setNum(value);

						 });

    window.show();

	 return app.exec();
	

}
