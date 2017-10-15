#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    port = new QSerialPort;
    ui->textEditRX->setReadOnly(1);
    statusRS232 = new QLabel(tr("Status : <font color=red>Desconectado</font>"));
    statusBar()->addPermanentWidget(statusRS232);
    confPort = new DialogConfigPort(this);
    ui->pushButtonEnviar->setEnabled(0);
}

MainWindow::~MainWindow()
{
    delete ui;
    if(port->isOpen()) port->close();
    delete port;
}

void MainWindow::closeEvent()
{
    if(port->isOpen())
        port->close();
}

void MainWindow::readRxData(void)
{
char c;
QString RxBuffer;
while(port->getChar(&c) == true)
    {
    RxBuffer += c ;
    }
    ui->textEditRX->insertPlainText(RxBuffer);
}

void MainWindow::on_pushButtonLimparRX_clicked()
{
    ui->textEditRX->clear();
}

void MainWindow::on_pushButtonLimparTX_clicked()
{
    ui->textEditTX->clear();
}

void MainWindow::on_actionSalvar_RX_triggered()
{
QByteArray f = ui->textEditRX->toPlainText().toUtf8();
salvar(f);
}

void MainWindow::on_actionSalvar_TX_triggered()
{
QByteArray f = ui->textEditTX->toPlainText().toUtf8();
salvar(f);
}

void MainWindow::salvar(QByteArray f)
{
QString myFilePath;
myFilePath  =  QFileDialog::getSaveFileName(this, tr("Salvar arquivo como..."),
QDir::homePath(), tr("Arquivo *.txt") );
    if(!myFilePath.isEmpty())
    {
    QFile  file(myFilePath);
    if  (file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
    file.write(f);
    statusBar()->showMessage(tr("Arquivo salvo com sucesso."),  3000);
    }
    }
}

void MainWindow::on_action_Sair_triggered()
{
    close();
}

void MainWindow::on_action_Configurar_Porta_triggered()
{
    confPort->show();
}

void MainWindow::on_action_Conectar_triggered()
{
    port->setPortName(confPort->confsPort);
    bool stus = port->open(QIODevice::ReadWrite);
     if (!stus)
         QMessageBox::critical(this, tr("Erro ao abrir"),
                               tr("Esta porta nao pode ser aberta"), 0, 0, 1);
     else
     {
        switch (confPort->confsPortIndex[0])
        {
        case 0: port->setBaudRate(QSerialPort::Baud1200); break;
        case 1: port->setBaudRate(QSerialPort::Baud2400); break;
        case 2: port->setBaudRate(QSerialPort::Baud4800); break;
        case 3: port->setBaudRate(QSerialPort::Baud9600); break;
        case 4: port->setBaudRate(QSerialPort::Baud19200); break;
        case 5: port->setBaudRate(QSerialPort::Baud38400); break;
        case 6: port->setBaudRate(QSerialPort::Baud57600); break;
        case 7: port->setBaudRate(QSerialPort::Baud115200); break;
        default : port->setBaudRate(QSerialPort::Baud1200);
        }
        switch (confPort->confsPortIndex[1])
        {
        case 0: port->setDataBits(QSerialPort::Data5); break;
        case 1: port->setDataBits(QSerialPort::Data6); break;
        case 2: port->setDataBits(QSerialPort::Data7); break;
        case 3: port->setDataBits(QSerialPort::Data8); break;
        default: port->setDataBits(QSerialPort::Data8);
        }
        switch (confPort->confsPortIndex[2])
        {
        case 0: port->setStopBits(QSerialPort::OneStop); break;
        case 1: port->setStopBits(QSerialPort::OneAndHalfStop); break;
        case 2: port->setStopBits(QSerialPort::TwoStop); break;
        default: port->setStopBits(QSerialPort::OneStop);
        }
        switch (confPort->confsPortIndex[3])
        {
        case 0: port->setParity(QSerialPort::NoParity); break;
        case 1: port->setParity(QSerialPort::EvenParity); break;
        case 2: port->setParity(QSerialPort::OddParity); break;
        case 3: port->setParity(QSerialPort::MarkParity); break;
        case 4: port->setParity(QSerialPort::SpaceParity); break;
        default: port->setParity(QSerialPort::NoParity);
        }
        switch (confPort->confsPortIndex[4])
        {
        case 0: port->setFlowControl(QSerialPort::NoFlowControl); break;
        case 1: port->setFlowControl(QSerialPort::HardwareControl); break;
        case 2: port->setFlowControl(QSerialPort::SoftwareControl); break;
        default: port->setFlowControl(QSerialPort::NoFlowControl);
        }

        connect(port, SIGNAL(readyRead(void)), this, SLOT(readRxData(void))) ;
        ui->action_Desconectar->setEnabled(1);
        ui->action_Conectar->setDisabled(1);
        ui->action_Configurar_Porta->setDisabled(1);
        statusRS232->setText(tr("Status : <font color=blue>Conectado</font>"));
        ui->pushButtonEnviar->setEnabled(true);
     }
}

void MainWindow::on_action_Desconectar_triggered()
{
    if(port->isOpen()) port->close();
    disconnect(port, SIGNAL(readyRead()), 0, 0);
    ui->action_Desconectar->setDisabled(1);
    ui->action_Conectar->setEnabled(1);
    ui->action_Configurar_Porta->setEnabled(1);
    statusRS232->setText(tr("Status : <font color=red>Desconectado</font>"));
    ui->pushButtonEnviar->setEnabled(false);
}

void MainWindow::on_pushButtonEnviar_clicked()
{
    int i;
    QByteArray ch = ui->textEditTX->toPlainText().toUtf8();
    if(ui->radioButtonChar->isChecked()) port->putChar(ch[0]);
    else 
    for(i=0; i<ch.length(); i++) port->putChar(ch[i]);
}

void MainWindow::on_actionSobre_triggered()
{
    QMessageBox::about(this, tr("RS232Term 0.11"),
                        tr("<B>RS232Term</B><BR>"
                        "autor: Roberto O. D. Valle<br>email: "
                        "<a href='mailto:mtester@mtester.com.br'>mtester@mtester.com.br</a><br> "
                        "home:<a href='url:http://www.mtester.com.br'>www.mtester.com.br</a>"));
}

