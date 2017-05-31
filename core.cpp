#include "core.h"
//#include <QWebSocketServer>
//#include <QWebSocket>
#include <QTcpServer>
#include <QTcpSocket>

#include <QDebug>
#include "cbor.h"

Core::Core()
{
	qDebug() << "Core Lives!";
/*	m_pWebSocketServer = new QWebSocketServer("",QWebSocketServer::NonSecureMode,this);
	if (m_pWebSocketServer->listen(QHostAddress::Any, 5001))
	{
		if (!connect(m_pWebSocketServer, SIGNAL(newConnection()),this, SLOT(newConnection())))
		{
			qDebug() << "Unable to connect!";
		}
	}
	else
	{
		qDebug() << "Unable to open listener";
	}*/

	m_tcpServer = new QTcpServer(this);
	m_tcpServer->listen(QHostAddress::Any,5001);
	connect(m_tcpServer,SIGNAL(newConnection()),this,SLOT(newConnection()));
}
void Core::newConnection()
{
	qDebug() << "Incoming connection";
	QTcpSocket *socket = m_tcpServer->nextPendingConnection();
	m_bufferMap.insert(socket,QByteArray());
	connect(socket,SIGNAL(readyRead()),this,SLOT(socketReadyRead()));
}
void Core::socketReadyRead()
{
	QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
	if (!socket)
	{
		return;
	}
	m_bufferMap[socket].append(socket->readAll());
	parseBuffer(socket);

}
void Core::parseBuffer(QTcpSocket *socket)
{
	if (m_bufferMap[socket].size() > 3)
	{
		//Big enough to contain byte + size
		if (static_cast<unsigned char>(m_bufferMap[socket].at(0)) != 0xAA)
		{
			qDebug() << "Error! Invalid packet!";
			qDebug() << QString::number(m_bufferMap[socket].at(0),16);
			exit(-1);
		}
		uint16_t size = (((unsigned char)m_bufferMap[socket].at(1)) << 8) + ((unsigned char)m_bufferMap[socket].at(2));
		if (m_bufferMap[socket].size() >= size+5)
		{
			//We have a full packet
			QByteArray packet = m_bufferMap[socket].mid(0,size+5);
			QVariant packetvariant = CBOR::unpack(packet.mid(3,size));
			m_bufferMap[socket].remove(0,size+5);
		}

	}
}

/*void Core::processMessage(QString message)
{
	qDebug() << "Message;" << message;
}

void Core::newConnection()
{
	qDebug() << "new Connection";
	QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();
qDebug() << "new Connections";

	connect(pSocket, &QWebSocket::textMessageReceived, this, &Core::processMessage);
	qDebug() << "new ConnectiowW";
//	printf("onNewConnection");

//	m_clients << pSocket;
}
*/
