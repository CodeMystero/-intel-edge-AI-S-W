#include <QApplication>
#include <QWidget>
#include <stdio.h>
#include <wiringPi.h>
#include <QPushButton>

const int led = 21;

int main(int argc, char *argv[]) {

    wiringPiSetupGpio();
    pinMode(led, OUTPUT);

    QApplication app(argc, argv);
    QWidget window;

    QPushButton *button = new QPushButton("Quit",0);

    digitalWrite(led, 0);

    button->resize(200, 200);
    button->move(300,300);
    window.setWindowTitle("Why no button");
    QObject::connect(button, SIGNAL(clicked()), &app, SLOT(quit()));
    
    button->show();

    return app.exec();

}
