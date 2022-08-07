#include "widget.h"
#include "ui_widget.h"
#include <QHostInfo>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QNetworkInterface>
#include <QProcess>
#include "tcpserver.h"
#include <QFileDialog>
#include "tcpclient.h"
#include <QColorDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    udpSocket = new QUdpSocket(this);
    port = 8150;
    udpSocket->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    connect(udpSocket,&QUdpSocket::readyRead,this,&Widget::processPendingDatagrams);
    sendMessage(NewParticipant);

    server = new TcpServer(this);
    connect(server,&TcpServer::sendFile,this,&Widget::getFileName);

    connect(ui->messageTextEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat)),
            this, SLOT(currentFormatChanged(const QTextCharFormat)));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::sendMessage(MessageType type, QString serverAddress)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    QString localhostname = QHostInfo::localHostName();
    QString address = getIp();
    out<<type<<getUername()<<localhostname;
    switch(type){
    case Message:
        if(ui->messageTextEdit->toPlainText()==" "){
            QMessageBox::warning(0,tr("warning"),tr("Sending information cannot be empty"),QMessageBox::Ok);
            return;
        }
        out<<address<<getMessage();
        ui->messageBrowser->verticalScrollBar()
                ->setValue(ui->messageBrowser->verticalScrollBar()->maximum());
        break;
    case NewParticipant:
        out<<address;
        break;
    case ParticipantLeft:
        break;
    case FileName:
    { int row = ui->userTableWidget->currentRow();
        QString clientAddress = ui->userTableWidget->item(row,2)->text();
        out<<address<<clientAddress<<fileName;}
        break;
    case Refuse:
        out<<address;
        break;
    }
    udpSocket->writeDatagram(data,data.length(),QHostAddress::Broadcast,port);
}

void Widget::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(),datagram.size());
        QDataStream in(&datagram,QIODevice::ReadOnly);
        int messageType;
        in>>messageType;
        QString userName,localhostname,ipAddress,message;
        QString time = QDateTime::currentDateTime().toString("yyyy-mm-dd hh:mm:ss");
        switch (messageType) {
        case Message:
            in>>userName>>localhostname>>ipAddress>>message;
            ui->messageBrowser->setTextColor(Qt::blue);
            ui->messageBrowser->setCurrentFont(QFont("Times New Roman",12));
            ui->messageBrowser->append("["+userName+"]"+time);
            ui->messageBrowser->append(message);
            break;
        case NewParticipant:
            in>>userName>>localhostname>>ipAddress;
            newParticipant(userName,localhostname,ipAddress);
            break;
        case ParticipantLeft:
            in>>userName>>localhostname>>ipAddress;
            participantLeft(userName,localhostname,ipAddress);
            break;
        case FileName: {
            in >> userName >> localhostname >> ipAddress;
            QString clientAddress, fileName;
            in >> clientAddress >> fileName;
            hasPendingFile(userName, ipAddress, clientAddress, fileName);
            break;
        }
        case Refuse: {
            in >> userName >> localhostname;
            QString serverAddress;
            in >> serverAddress;
            QString ipAddress = getIp();

            if(ipAddress == serverAddress)
            {
                server->refused();
            }
            break;
        }
        }
    }
}

void Widget::newParticipant(QString userName, QString localHostName, QString ipAddress)
{
    bool isEmpty = ui->userTableWidget->findItems(localHostName,Qt::MatchExactly).isEmpty();
    if(isEmpty){
        QTableWidgetItem *usename = new QTableWidgetItem(userName);
        QTableWidgetItem *localhostName = new QTableWidgetItem(localHostName);
        QTableWidgetItem *ipaddress = new QTableWidgetItem(ipAddress);

        ui->userTableWidget->insertRow(0);
        ui->userTableWidget->setItem(0,0,usename);
        ui->userTableWidget->setItem(0,1,localhostName);
        ui->userTableWidget->setItem(0,2,ipaddress);

        ui->messageBrowser->setTextColor(Qt::gray);
        ui->messageBrowser->setCurrentFont(QFont("Times New Roman",10));
        ui->messageBrowser->append(QString("%1 在线").arg(userName));

        ui->userNumLabel->setText(tr("当前在线人数:%1").arg(ui->userTableWidget->rowCount()));

        sendMessage(NewParticipant);
    }
}

void Widget::participantLeft(QString userName, QString localHostName, QString time)
{
    int rowNum = ui->userTableWidget->findItems(localHostName,Qt::MatchExactly).first()->row();
    ui->userTableWidget->removeRow(rowNum);
    ui->messageBrowser->setTextColor(Qt::gray);
    ui->messageBrowser->setCurrentFont(QFont("Times New Roman",10));
    ui->messageBrowser->append(QString("%1 于 %2 离开").arg(userName).arg(time));

    ui->userNumLabel->setText(tr("当前在线人数:%1").arg(ui->userTableWidget->rowCount()));
}

QString Widget::getIp()
{
    //一个主机上可能有多个ip地址 包括ipv4和ipv6
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach(QHostAddress a,list){
        if(a.protocol()==QAbstractSocket::IPv4Protocol){
            return a.toString();
        }
    }
}

QString Widget::getUername()
{
    QStringList envVariables;
    envVariables<<"USERNAME.*"<<"USER.*"<<"USERDOMAIN.*"<<"HOSTNAME.*"<<"DOMAINNAME.*";
    QStringList enviroment = QProcess::systemEnvironment();
    foreach(QString string,envVariables){
        int index = enviroment.indexOf(QRegExp(string));
        if(index!=-1){
            QStringList stringlist = enviroment.at(index).split('=');
            if(stringlist.size()==2){
                return stringlist.at(1);
                break;
            }
        }
    }
    return "UN KNOW";
}

QString Widget::getMessage()
{
    QString msg = ui->messageTextEdit->toHtml();
    ui->messageTextEdit->clear();
    ui->messageTextEdit->setFocus();
    return msg;
}

void Widget::on_sendPushButton_clicked()
{
    sendMessage(Message);
}

void Widget::getFileName(QString name)
{
    fileName = name;
    sendMessage(FileName);
}

void Widget::on_sendTool_clicked()
{
    if(ui->userTableWidget->selectedItems().isEmpty()){
        QMessageBox::warning(0, tr("Choose user"),
                             tr("Please select the user to transfer from the user list first!"), QMessageBox::Ok);
        return;
    }
    server->show();
    server->initServer();
}

void Widget::hasPendingFile(QString userName, QString serverAddress, QString clientAddress, QString fileName)
{
    QString ipAddress = getIp();
    if(ipAddress == clientAddress)
    {
        int btn = QMessageBox::information(this,tr("Accept file"),
                                           tr("The file from %1(%2)：%3,Whether to receive?")
                                           .arg(userName).arg(serverAddress).arg(fileName),
                                           QMessageBox::Yes,QMessageBox::No);
        if (btn == QMessageBox::Yes) {
            QString name = QFileDialog::getSaveFileName(0,tr("保存文件"),fileName);
            if(!name.isEmpty())
            {
                TcpClient *client = new TcpClient(this);
                client->setFileName(name);
                client->setHostAddress(QHostAddress(serverAddress));
                client->show();
            }
        } else {
            sendMessage(Refuse, serverAddress);
        }
    }
}

//改变字体
void Widget::on_fontComboBox_currentFontChanged(const QFont &f)
{
    ui->messageTextEdit->setFont(f);
    ui->messageTextEdit->setFocus();
}

void Widget::on_sizeComboBox_currentIndexChanged(const QString &arg1)
{
    ui->messageTextEdit->setFontPointSize(arg1.toDouble());
    ui->messageTextEdit->setFocus();
}

void Widget::on_blodTool_clicked(bool checked)
{
    if(checked){
        ui->messageTextEdit->setFontWeight(QFont::Bold);
    }else{
        ui->messageTextEdit->setFontWeight(QFont::Normal);
    }
    ui->messageTextEdit->setFocus();
}

void Widget::on_italicTool_clicked(bool checked)
{
    ui->messageTextEdit->setFontItalic(checked);
    ui->messageTextEdit->setFocus();
}

void Widget::on_underlineTool_clicked(bool checked)
{
    ui->messageTextEdit->setFontUnderline(checked);
    ui->messageTextEdit->setFocus();
}



void Widget::on_colorTool_clicked()
{
    color = QColorDialog::getColor(color,this);
    if(color.isValid()){
        ui->messageTextEdit->setTextColor(color);
        ui->messageTextEdit->setFocus();
    }
}

void Widget::currenFromatChanged(const QTextCharFormat &format)
{
    ui->fontComboBox->setCurrentFont(format.font());
    if(format.fontPointSize()<9){
        ui->sizeComboBox->setCurrentIndex(3);
    }else{
        ui->sizeComboBox->setCurrentIndex(ui->sizeComboBox
                                          ->findText(QString::number(
                                                         format.fontPointSize())));
    }
    ui->blodTool->setChecked(format.font().bold());
    ui->italicTool->setChecked(format.font().italic());
    ui->underlineTool->setChecked(format.font().underline());
    color = format.foreground().color();
}



void Widget::on_saveTool_clicked()
{
    if(ui->messageBrowser->document()->isEmpty()){
        QMessageBox::warning(this,tr("警告"),tr("聊天记录为空不能保存"),QMessageBox::Ok);
    }else{
        QString fileName = QFileDialog::getSaveFileName(this,tr("保存聊天记录"),
                                                        tr("聊天记录"),tr("文本(*.txt);ALL File(*.*)"));
        if(!fileName.isEmpty()){
            saveFile(fileName);
        }
    }
}

bool Widget::saveFile(const QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QFile::Text)){
        QMessageBox::warning(this, tr("保存文件"),
                                   tr("无法保存文件 %1:\n %2").arg(fileName)
                                   .arg(file.errorString()));
              return false;
    }
    QTextStream out(&file);
    out<<ui->messageBrowser->toPlainText();
    return true;
}


void Widget::on_clearTool_clicked()
{
   ui->messageBrowser->clear();
}

void Widget::on_exitPushButton_clicked()
{
    close();
}

void Widget::closeEvent(QCloseEvent *e)
{
    sendMessage(ParticipantLeft);
    QWidget::closeEvent(e);
}
