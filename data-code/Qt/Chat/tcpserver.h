#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QDialog>
#include <QtNetwork>
#include <QTimer>
#include <QFileDialog>

namespace Ui {
class TcpServer;
}

class TcpServer : public QDialog
{
    Q_OBJECT

public:
    explicit TcpServer(QWidget *parent = nullptr);
    ~TcpServer();
    void initServer();
    void refused();
protected:
    void closeEvent(QCloseEvent *);
protected slots:
    void sendMessage();
    void updateClientProgess(qint64 numBytes);
private slots:
    void on_serverOpenButton_clicked();
    void on_serverSendButton_clicked();
    void on_serverCloseButton_clicked();

signals:
    void sendFile(QString);
private:
    Ui::TcpServer *ui;
    QTcpServer *tcpserver;
    QTcpSocket *clienConnection;
    qint16 port;
    qint64 payloadSize;
    qint64 totalSize;
    qint64 byteWiritten;
    qint64 byteToWrite;
    QString fileName;
    QString theFileName;
    QFile *localFile;
    QByteArray outBlock;
    QTime time;
};

#endif // TCPSERVER_H
