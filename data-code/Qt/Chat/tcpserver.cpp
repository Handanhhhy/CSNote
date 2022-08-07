#include "tcpserver.h"
#include "ui_tcpserver.h"
#include <QMessageBox>

TcpServer::TcpServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    tcpserver = new QTcpServer(this);
    port = 8150;
    connect(tcpserver,&QTcpServer::newConnection,this,&TcpServer::sendMessage);
    initServer();
}

TcpServer::~TcpServer()
{
    delete ui;
}

void TcpServer::initServer()
{
     payloadSize = 64*1032;
     totalSize = 0;
     byteWiritten = 0;
     byteToWrite = 0;
     ui->label->setText(tr("请选择要传送的文件"));
     ui->serverSendButton->setEnabled(false);
     ui->serverOpenButton->setEnabled(true);
     ui->progressBar->reset();
     tcpserver->close();
}

void TcpServer::sendMessage()
{
    ui->serverSendButton->setEnabled(false);
    clienConnection = tcpserver->nextPendingConnection();
    connect(clienConnection,SIGNAL(bytesWritten(qint64)),
            this,SLOT(updateClientProgess(qint64)));
    ui->label->setText(tr("开始传输文件:%1").arg(fileName));
    localFile = new QFile(fileName);
    if(!localFile->open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件:%1 \n %2")
                             .arg(fileName).arg(localFile->errorString()));
    }
    totalSize = localFile->size();
    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_12);
    time.start();
    QString curFile = fileName.right(fileName.size()-fileName.lastIndexOf('/')-1);
    sendOut<<qint64(0)<<qint64(0)<<curFile;
    totalSize+=outBlock.size();
    ui->progressBar->setMaximum(totalSize);
    sendOut.device()->seek(0);
    sendOut<<totalSize<<qint64(outBlock.size()-sizeof (qint64)*2);
    byteToWrite = totalSize - clienConnection->write(outBlock);
    outBlock.resize(0);
}

void TcpServer::updateClientProgess(qint64 numBytes)
{
    qApp->processEvents();//用于传输大文件是界面不会被冻结
    byteWiritten+=numBytes;
    if(byteToWrite>0){
        outBlock = localFile->read(qMin(byteToWrite,payloadSize));
        byteToWrite-=(int)clienConnection->write(outBlock);
        outBlock.resize(0);
    }else{
        localFile->close();
    }
    ui->progressBar->setValue(byteWiritten);
    float useTime = time.elapsed();
    double speed = byteWiritten/useTime;
    ui->label->setText(tr("Has been sent %1 MB (%2 MB/s)"
                          "\n TotalSize %3 Mb UsedTime%4 second "
                          "\n Estimated time remaining:%5 second")
                       .arg(byteWiritten/(1024*1024))
                       .arg(speed*1000/(1024*1024),0,'f',2)
                       .arg(totalSize/(1024*1024))
                       .arg(useTime/1000,0,'f',2)
                       .arg(totalSize/speed/1000-useTime/1000,0,'f',0));

    if(byteWiritten==totalSize){
        localFile->close();
        tcpserver->close();
        ui->label->setText(tr("发送文件%1成功").arg(fileName));
    }
}

void TcpServer::on_serverOpenButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this);
    if(!fileName.isEmpty()){
        theFileName = fileName.right(fileName.size()-fileName.lastIndexOf('/')-1);
        ui->label->setText(tr("要发送的文件为:%1").arg(theFileName));
        ui->serverSendButton->setEnabled(true);
        ui->serverOpenButton->setEnabled(false);

    }
}

void TcpServer::on_serverSendButton_clicked()
{
    if(!tcpserver->listen(QHostAddress::AnyIPv4,port)){
        close();
        return;
    }
    ui->label->setText(tr("等待对方接受...."));
    emit sendFile(theFileName);
}

void TcpServer::on_serverCloseButton_clicked()
{
    if(tcpserver->isListening()){
        tcpserver->close();
        if(localFile->isOpen()){
            localFile->close();
            clienConnection->abort();//关闭套接字，并丢弃数据
        }
    }
    close();
}

void TcpServer::refused()
{
    tcpserver->close();
    ui->label->setText(tr("对方拒绝接收!"));
}

void TcpServer::closeEvent(QCloseEvent *)
{
    on_serverCloseButton_clicked();
}
