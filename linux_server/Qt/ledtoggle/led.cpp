#include <QApplication>
#include <QWidget>
#include <wiringPi.h>
#include <QPushButton>
#include <QPixmap>
const int led = 21;

int main(int argc, char** argv){

	wiringPiSetupGpio();
	pinMode(led, OUTPUT);

	QApplication app(argc, argv);

	QPixmap buttonImage("/home/pi/work/ledtoggle/led.png");
	QSize newSize(100,120);
	QPixmap scaledImage = buttonImage.scaled(newSize, Qt::KeepAspectRatio);

	QWidget window;
	window.setGeometry(100,100,200,280);
	

   QPushButton *quitButton = new QPushButton("Quit", &window);
   QPushButton *toggleLEDButton = new QPushButton(&window);

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
    window.setWindowTitle("Button Example");

    
    QObject::connect(quitButton, SIGNAL(clicked()), &app, SLOT(quit()));

  
    QObject::connect(toggleLEDButton, &QPushButton::clicked, [=]() {
        digitalWrite(led, !digitalRead(led));
    });

    window.show();

	 return app.exec();
	

}
