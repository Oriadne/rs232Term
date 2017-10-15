#ifndef DIALOGCONFIGPORT_H
#define DIALOGCONFIGPORT_H

#include <QDialog>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QSettings>

namespace Ui {
class DialogConfigPort;
}

class DialogConfigPort : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogConfigPort(QWidget *parent = 0);
    ~DialogConfigPort();
    QString confsPort;
    int confsPortIndex[5];
private slots:
    void on_pushButtonCancel_clicked();
    void on_pushButtonOk_clicked();
    void updateConfs();

private:
    Ui::DialogConfigPort *ui;
    void writeSettings();
    void readSettings();
};

#endif // DIALOGCONFIGPORT_H
