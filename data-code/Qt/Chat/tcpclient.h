#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QDialog>
#include <QFile>
#include <QtNetwork>

namespace Ui {
class TcpClient;
}

class TcpClient : public QDialog
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = nullptr);
    ~TcpClient();
   void setFileName(QString fileName);
   void setHostAddress(QHostAddress address);
   void newConnect();
protected:
   void closeEvent(QCloseEvent *);
protected slots:
    void readMessage();
    void displayError(QAbstractSocket::SocketError);
private slots:
    void on_clientCanclePushButton_clicked();
    void on_clientClosePushButton_clicked();

private:
    Ui::TcpClient *ui;
    QTcpSocket *tcpClient;
    qint16 blockSize;
    QHostAddress hostAddress;
    qint16 port;

    QFile *localFile;
    qint64 totalSize;
    qint64 byteReceived;
    qint64 byteToreceive;
    qint64 fileNameSize;
    QString fileName;
    QByteArray inBlock;
    QTime time;
};

#endif // TCPCLIENT_H
