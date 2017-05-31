#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QTcpSocket>

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
private slots:
	void parseBuffer(QTcpSocket *socket);
	void newConnection();
	void socketReadyRead();
	//void newConnection();
	//void processMessage(QString message);
};

#endif // CORE_H
