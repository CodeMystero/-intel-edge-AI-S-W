#include <QApplication>
#include <QLineEdit>
#include <QMessageBox>
#include <wiringPi.h>

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    if (wiringPiSetupGpio() == -1) {
        QMessageBox::critical(nullptr, "Error", "Failed to initialize wiringPi.");
        return 1;
    }

    pinMode(21, OUTPUT);

    QLineEdit* LE = new QLineEdit(0);
    LE->setEchoMode(QLineEdit::Normal);

    // QLineEdit Enter slot connection
    QObject::connect(LE, &QLineEdit::returnPressed, [&]() {
        // QLineEdit stinrg import
        QString userInput = LE->text();

        if (userInput.toLower() == "on") {
            digitalWrite(21, HIGH);
            QMessageBox::information(nullptr, "User Input", "You pressed Enter (LED ON): " + userInput);
        } else if (userInput.toLower() == "off") {
            digitalWrite(21, LOW);
            QMessageBox::information(nullptr, "User Input", "You pressed Enter (LED OFF): " + userInput);
        } else {
            QMessageBox::warning(nullptr, "Invalid Input", "Unsupported command: " + userInput);
        }

        LE->clear();
    });

    LE->show();
    return app.exec();
}
