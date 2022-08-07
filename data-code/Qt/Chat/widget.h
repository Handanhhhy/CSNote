#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>
#include <QColor>
#include <QTextCharFormat>

namespace Ui {
class Widget;
}
class TcpServer;

enum MessageType
{Message,NewParticipant,ParticipantLeft,FileName,Refuse};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void processPendingDatagrams();
    void on_sendPushButton_clicked();
    void getFileName(QString);
    void currenFromatChanged(const QTextCharFormat &format);
    void on_sendTool_clicked();

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_sizeComboBox_currentIndexChanged(const QString &arg1);

    void on_blodTool_clicked(bool checked);

    void on_italicTool_clicked(bool checked);

    void on_underlineTool_clicked(bool checked);

    void on_colorTool_clicked();

    void on_saveTool_clicked();

    void on_clearTool_clicked();

    void on_exitPushButton_clicked();

protected:
    void newParticipant(QString userName,QString localHostName,QString ipAddress);
    void participantLeft(QString userName,QString localHostName,QString time);
    void sendMessage(MessageType type,QString serverAddress = " ");
    void hasPendingFile(QString userName,QString serverAddress,QString clientAddress,QString fileName);
    QString getUername();
    QString getIp();
    QString getMessage();
    bool saveFile(const QString fileName);
    void Widget::closeEvent(QCloseEvent *e);
private:
    Ui::Widget *ui;
    QUdpSocket *udpSocket;
    qint16 port;
    QString fileName;
    TcpServer *server;
    QColor color;
};

#endif // WIDGET_H
