#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include "dialogconfigport.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent();

private:
    Ui::MainWindow *ui;
    QSerialPort *port;
    void salvar(QByteArray f);
    QLabel *statusRS232;
    DialogConfigPort *confPort;


private slots:
    void on_actionSobre_triggered();
    void on_pushButtonEnviar_clicked();
    void on_action_Desconectar_triggered();
    void readRxData();
    void on_action_Conectar_triggered();
    void on_action_Configurar_Porta_triggered();
    void on_action_Sair_triggered();
    void on_actionSalvar_TX_triggered();
    void on_actionSalvar_RX_triggered();
    void on_pushButtonLimparTX_clicked();
    void on_pushButtonLimparRX_clicked();
};

#endif // MAINWINDOW_H
