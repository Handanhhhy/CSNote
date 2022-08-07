#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QMessageBox>

TcpClient::TcpClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    totalSize = 0;
    byteReceived = 0;
    fileNameSize = 0;
    tcpClient = new QTcpSocket(this);
    port = 8150;
    connect(tcpClient,&QTcpSocket::readyRead,this,&TcpClient::readMessage);
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));

}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch(socketError)
    {
    case QAbstractSocket::RemoteHostClosedError : break;
    default : qDebug() << tcpClient->errorString();
    }
}

void TcpClient::setFileName(QString fileName)
{
    localFile = new QFile(fileName);
}

void TcpClient::setHostAddress(QHostAddress address)
{
    hostAddress = address;
    newConnect();
}

void TcpClient::newConnect()
{
    blockSize = 0;
    tcpClient->abort();
    tcpClient->connectToHost(hostAddress,port);
    time.start();
}

void TcpClient::readMessage()
{
    QDataStream in(tcpClient);
    in.setVersion(QDataStream::Qt_5_12);
    float useTime = time.elapsed();
    if(byteReceived<=sizeof(qint64)*2){
        if((tcpClient->bytesAvailable()>=sizeof (qint64)*2
            &&fileNameSize==0)){
            in>>totalSize>>fileNameSize;
            byteReceived+=sizeof(qint64)*2;
        }
        if(tcpClient->bytesAvailable()>=fileNameSize&&fileNameSize!=0){
            in>>fileName;
            byteReceived+=fileNameSize;
            if(!localFile->open(QFile::WriteOnly)){
                QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件 %1:\n%2.")
                                     .arg(fileName).arg(localFile->errorString()));
                return;
            }else {
                return;
            }
        }
    }
    if (byteReceived < totalSize) {
        byteReceived += tcpClient->bytesAvailable();
        inBlock = tcpClient->readAll();
        localFile->write(inBlock);
        inBlock.resize(0);
    }
    ui->clientProgressBar->setMaximum(totalSize);
    ui->clientProgressBar->setValue(byteReceived);

    double speed = byteReceived / useTime;
    ui->label->setText(tr("has accepted %1MB (%2MB/s) "
                          "\n total size%3MB useTime:%4 second\n need times：%5 second")
                       .arg(byteReceived / (1024*1024))
                       .arg(speed*1000/(1024*1024),0,'f',2)
                       .arg(totalSize / (1024 * 1024))
                       .arg(useTime/1000,0,'f',0)
                       .arg(totalSize/speed/1000 - useTime/1000,0,'f',0));

    if(byteReceived == totalSize)
    {
        localFile->close();
        tcpClient->close();
        ui->label->setText(tr("接收文件 %1 完毕")
                           .arg(fileName));
    }
}

void TcpClient::on_clientCanclePushButton_clicked()
{
    tcpClient->abort();
    if(localFile->isOpen()){
        localFile->close();
    }
}

void TcpClient::on_clientClosePushButton_clicked()
{
    tcpClient->abort();
    if(localFile->isOpen()){
        localFile->close();
    }
    close();
}

void TcpClient::closeEvent(QCloseEvent *)
{
    on_clientClosePushButton_clicked();
}
