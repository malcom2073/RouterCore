#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QTcpSocket>
#include "packetizer.h"

//class QWebSocketServer;
class QTcpServer;

class Core : public QObject
{
	Q_OBJECT
public:
	Core();
private:
	//QWebSocketServer *m_pWebSocketServer;
	QTcpServer *m_tcpServer;
	QMap<QTcpSocket*,QByteArray> m_bufferMap;
	QMap<QTcpSocket*,Packetizer*> packetizerMap;
	QMap<QString,QMap<QString,QVariant> > dataMap;
	QList<QTcpSocket*> m_debugSocketList;
	void sendDebugMessage(QString message);
private slots:
	void newPacket(QObject *identifier,QByteArray packet);
	void parseBuffer(QTcpSocket *socket);
	void newConnection();
	void socketReadyRead();
	//void newConnection();
	//void processMessage(QString message);
};

#endif // CORE_H
