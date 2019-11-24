#ifndef NDICOMM_H
#define NDICOMM_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QThread>
#include <QVector3D>
#include <QList>

namespace Ui {
    class NdiComm;
}

class NdiCommProc;

class NdiComm : public QWidget
{
    Q_OBJECT
public:
    explicit NdiComm(QWidget *parent = nullptr);
    ~NdiComm();

    friend class NdiCommProc; //Declare friend class NdiCommProc

    void initPort(); //refresh serial ports

    QList<QVector3D> markers; //storage for coordinates of markers

private:
    Ui::NdiComm *ui;
    NdiCommProc *ndiCommProc;
	NdiComm *ndiComm;
    QThread *ndiThread;
//    QSerialPort serialPort; //Serial port
    
    bool isPortOpened;
    bool isStarted;

    QSerialPort::Parity getParity(QString text);
    QSerialPort::DataBits getDataBits(QString text);
    QSerialPort::StopBits getStopBits(QString text);
    QSerialPort::FlowControl getFlowCtrl(QString text);

    QTimer *timer;

    void printThread(QString front); //Test for thread

public:
    //Use to read and write on serialPort.
//    inline void write(QByteArray ba) {if(isPortOpened) ndiCommProc->serialPort.write(ba);}
//    inline bool waitForReadyRead(int msecs) {return serialPort.waitForReadyRead(msecs);}
//    inline QByteArray readAll(){return serialPort.readAll();}
//    inline void clear() { serialPort.clear(); }

signals:
    void serialOpened(); //serial port open signal
    void serialClosed(); //serial port close signal
    void initFinished(QString);
    void dataReady(QList<QVector3D>);

public slots:
    void recvProc();

private slots:
    void on_refreshButton_clicked();
    void on_openCloseButton_clicked();
    void on_startButton_clicked();

protected:
    void changeEvent(QEvent *event);
};


class NdiCommProc : public QObject
{
    Q_OBJECT
public:
    explicit NdiCommProc(QObject *parent = nullptr);
    ~NdiCommProc();
    float q;
    const char *msg;

    QByteArray requestData;
    QString strDisplay;

    QByteArray requestData1;

    QByteArray recvbuf;

    bool isRunning;

    QSerialPort serialPort;

signals:
    void initFinished(QString);
    void dataReady(QList<QVector3D>);

public slots:
    void ndiCommStart(); //start to communicate with Ndi

    void printThread(QString front);
    void data_read(); //FOR SU SHUN

    void get_data(); // Get data from NDI BY Yang Luo

private:
    void initsensor(); //FOR SU SHUN
    bool datawrong=false;
    int ConvertHexQString(QString ch, int i, int j);
    float Hex_To_Decimal(unsigned char * Byte);
    template<typename T> T getNum(const char* p);
};

#endif // NDICOMM_H
