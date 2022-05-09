#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QStatusBar>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>
#include <QTableWidget>
#include <QHeaderView>


#include <QSlider>
#define TASKMAX 8
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _firmata(new QFirmata(this)),
      _firstDigitalPinIndex(2),
       ui (new Ui::MainWindow)
{
    ui->setupUi(this);



    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(onConnectButtonClicked()));
    connect(ui->discButton, SIGNAL(clicked()), this, SLOT(onDisconnectButtonClicked()));

    connect(_firmata, SIGNAL(firmwareVersionReceived(int, int)), this, SLOT(onFirmwareVersionReceived(int,int)));
    connect(_firmata, SIGNAL(firmwareNameReceived(QString)), this, SLOT(onFirmwareNameReceived(QString)));
    connect(_firmata, SIGNAL(initialized(int,int,QString)), this, SLOT(onInitialized(int,int,QString)));
    connect(_firmata, SIGNAL(digitalPinChanged(int)), this, SLOT(onDigitalPinChanged(int)));
    connect(_firmata, SIGNAL(analogPinChanged(int)), this, SLOT(onAnalogPinChanged(int)));
    connect(_firmata, SIGNAL(sysExReceived(QVector<unsigned char>)), this, SLOT(onSysExReceived(QVector<unsigned char>)));
    Flag = false;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_connectButton_4_clicked()));

}

MainWindow::~MainWindow()
{

}

void MainWindow::onConnectButtonClicked()
{
    if(_firmata->openSoc(ui->Address->text(), ui->portTcp->value()))
    {
        statusBar()->showMessage(tr("[Notice] Successfully opened connection"), 5000);

        _firmata->sendDigitalPinMode(6, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(7, ARD_INPUT);
        _firmata->sendDigitalPinMode(8, ARD_INPUT);
        _firmata->sendDigitalPinMode(9, ARD_OUTPUT);

        _firmata->sendDigitalPinMode(13, ARD_OUTPUT);

    }
    else
    {
        statusBar()->showMessage(tr("[Error] Could not open connection"), 5000);
    }
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(ping()));
    timer->start(100);
}

void MainWindow::onDisconnectButtonClicked()
{
    statusBar()->showMessage(tr("[Notice] Successfully closed connection"), 5000);
    _firmata->close();
    MainWindow::close();
}

void MainWindow::onFirmwareVersionReceived(const int majorVersion, const int minorVersion)
{
    qDebug()<<"major"<<majorVersion<<"minor"<<minorVersion;
}
void MainWindow::onFirmwareNameReceived(QString firmwareName)
{
    qDebug()<<"firmware name"<<firmwareName;
}
void MainWindow::onInitialized(const int majorVersion, const int minorVersion, QString firmwareName)
{
    qDebug()<<"firmate initialized"<<majorVersion<<minorVersion<<firmwareName;
    statusBar()->showMessage(tr("initialized"), 5000);

    QString statusText = QString::number(majorVersion)+"."+QString::number(minorVersion);
   /* _firmata->sendDigitalPinMode(9, ARD_OUTPUT);
    _firmata->sendDigitalPinMode(6, ARD_OUTPUT);
    _firmata->sendDigitalPinMode(8, ARD_INPUT);
    _firmata->sendDigitalPinMode(7, ARD_INPUT);
    _firmata->sendDigitalPinReporting(8, ARD_INPUT);
    _firmata->sendDigitalPinReporting(7, ARD_INPUT);*/
    _firmata->sendAnalogPinReporting(0, ARD_ANALOG);

}
void MainWindow::onDigitalPinChanged(int pin)
{
    qDebug()<<"digital pin"<<pin<<"changed. new value"<<_firmata->getDigital(pin);

}

void MainWindow::onAnalogPinChanged(int pin)
{
        if(pin == 0)
        {
            qDebug()<<"analog pin"<<pin<<"changed. new value"<<_firmata->getAnalog(pin);
            int value =_firmata->getAnalog(pin);
            Distance=(6762.0/((value)-9.0))-4.0;
           ui->lcdNumber_3->display(Distance);
        }
}
void MainWindow::onSysExReceived(QVector<unsigned char> message)
{
    QString str;
    QVector<unsigned char>::iterator it;
    unsigned char buffer, address;

    qDebug()<<"sysExReceived"<<message;
    it = message.begin();
    address = *it;
    it++; // skip the first byte, which is the string command
    while( it != message.end() ) {
            buffer = *it;
            it++;
//            buffer += *it;// << 7;
//            it++;
            str+=QChar(buffer);
    }
    if (address == SONAR_DATA+0x00){
        ui->lcdNumber->display(str);
        readstr1=str.toInt();

 }
    else if (address == SONAR_DATA+0x01){
        ui->lcdNumber_2->display(str);
        readstr2=str.toInt();

}

}

void MainWindow::onStringReceived(const QString message)
{
    qDebug()<<"StringReceived"<<message;

}

void MainWindow::onAnalogPinReportinChange(unsigned int pin, bool value)
{
    qDebug()<<"analog pin reporting"<<pin<<"changed. new value"<<value;

    if(value)
    {
        _firmata->sendAnalogPinReporting(pin, ARD_ANALOG);
    }
    else
    {
        _firmata->sendAnalogPinReporting(pin, ARD_OFF);
    }
}

void MainWindow::onDigitalPinModeChange(unsigned int pin, int mode)
{
    switch(mode)
    {
        //none
    case 0: _firmata->sendDigitalPinReporting(pin, ARD_OFF);
        break;
    case 1: _firmata->sendDigitalPinMode(pin, ARD_INPUT); _firmata->sendDigitalPinReporting(pin, ARD_ON);
        break;
    case 2: _firmata->sendDigitalPinReporting(pin, ARD_OFF); _firmata->sendDigitalPinMode(pin, ARD_OUTPUT);
        break;
    case 3: _firmata->sendDigitalPinReporting(pin, ARD_OFF); _firmata->sendDigitalPinMode(pin, ARD_PWM);
        break;
    default:
        break;
    }

}

void MainWindow::on_connectButton_4_clicked()
{
  Flag = !Flag;
  if(Flag)
   _firmata->sendDigital(13,ARD_ON);
  else
   _firmata->sendDigital(13,ARD_OFF);
}


void MainWindow::on_pushButton_2_clicked()
{

    _firmata->sendSysEx(SONAR_CONFIG,{0});
}

void MainWindow::ping()
{
        _firmata->sendSysEx(SONAR_CONFIG,{0});
        _firmata->sendSysEx(SONAR_CONFIG,{1});
}
void MainWindow::on_pushButton_3_clicked()
{
    _firmata->sendSysEx(SONAR_CONFIG,{1});
}

void MainWindow::on_pushButton_4_clicked()
{
    int value =_firmata->getAnalog(0);
   ui->lcdNumber_3->display((6762.0/((value)-9.0))-4.0);
}


