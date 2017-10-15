#include "dialogconfigport.h"
#include "ui_dialogconfigport.h"

DialogConfigPort::DialogConfigPort(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfigPort)
{
    ui->setupUi(this);
    foreach (const QSerialPortInfo &infoPort, QSerialPortInfo::availablePorts())
    {
        ui->comboBoxPorta->addItem(infoPort.portName());
    }
    readSettings();
    updateConfs();
}

DialogConfigPort::~DialogConfigPort()
{
    delete ui;
}

void DialogConfigPort::on_pushButtonCancel_clicked()
{
    this->hide();
}

void DialogConfigPort::on_pushButtonOk_clicked()
{
    updateConfs();
    writeSettings();
    this->hide();
}

void DialogConfigPort::updateConfs()
{
    confsPort = (ui->comboBoxPorta->currentText());
    confsPortIndex[0] = ui->comboBoxBaudRate->currentIndex();
    confsPortIndex[1] = ui->comboBoxDataBits->currentIndex();
    confsPortIndex[2] = ui->comboBoxStopBits->currentIndex();
    confsPortIndex[3] = ui->comboBoxParity->currentIndex();
    confsPortIndex[4] = ui->comboBoxFlowControl->currentIndex();
}

void DialogConfigPort::writeSettings()
{
    QSettings settings("rs232Term", "rs232Term");
    settings.setValue("Bauds", (confsPortIndex[0]));
    settings.setValue("DataBits", (confsPortIndex[1]));
    settings.setValue("Parity", (confsPortIndex[2]));
    settings.setValue("StopBits", (confsPortIndex[3]));
    settings.setValue("FlowControl", (confsPortIndex[4]));
}

void DialogConfigPort::readSettings()
{
    QSettings settings("rs232Term", "rs232Term");
    ui->comboBoxBaudRate->setCurrentIndex(settings.value("Bauds", 3).value<int>());
    ui->comboBoxDataBits->setCurrentIndex(settings.value("DataBits", 3).value<int>());
    ui->comboBoxParity->setCurrentIndex(settings.value("Parity", 0).value<int>());
    ui->comboBoxStopBits->setCurrentIndex(settings.value("StopBits", 0).value<int>());
    ui->comboBoxFlowControl->setCurrentIndex(settings.value("FlowControl", 0).value<int>());
}
