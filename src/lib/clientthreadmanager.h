#ifndef CLIENTTHREADMANAGER_H
#define CLIENTTHREADMANAGER_H

#include <QObject>
#include <QMap>
#include <QVector>

namespace CacheConnect
{
class Client;
class ClientInformation;

/**
 * @brief Manages every client instance on different thread
 * @author Shashwat Dixit <shashwatdixit124@gmail.com>
 */
class ClientThreadManager : public QObject
{
	Q_OBJECT
public:
	/**
	 * @brief Constructor
	 */
	explicit ClientThreadManager(QObject* parent = nullptr);
	/**
	 * @brief Destructor
	 */
	~ClientThreadManager();

Q_SIGNALS:
	/**
	 * @brief emitted when a new client is registered
	 * @param ci Information of the Client Registered
	 */
	void clientAdded(ClientInformation ci);

	/**
	 * @brief emitted when new text message is sent (or recieved)
	 * @param id of client associated with the message
	 * @param msg text message
	 */
	void messageAdded(qint16 id,QString msg);

	/**
	 * @brief emitted when a client is removed
	 * @param id of client removed
	 */
	void clientRemoved(qint16 id);

public Q_SLOTS:
	/**
	 * @brief adds Client to the client list
	 * @param client Client to add
	 */
	void clientCreated(Client* client);

	/**
	 * @brief sends the clientAdded signal if client has recieved information
	 * @param ci Information of Client to add
	 */
	void addClient(ClientInformation ci);

	/**
	 * @brief emits messageAdded signal
	 * @param id of client associated with the message
	 * @param msg text message
	 */
	void messageRecieved(qint16 id,QString msg);

	/**
	 * @brief closes the connection for client specified
	 * @param client Client for which Connection is closed
	 */
	void closeConnection(Client* client);

	/**
	 * @brief removes every client in client list
	 */
	void removeAllClients();

	/**
	 * @brief removes a specific client
	 * called using signal from Client
	 */
	void removeClient();

	/**
	 * @brief sends text message to a Client
	 * @param id for a Client to send text message
	 * @param msg text message to send
	 */
	void sendToClient(qint16 id, QString msg);

protected:
	/**
	 * @brief map of all registered clients
	 */
	QMap<qint16,Client*> m_clientList;

	/**
	 * @brief map of clients that are not registered
	 * i.e. map of Client that have not accepted details yet
	 */
	QVector<Client*> m_clientInQueue;

	/**
	 * @brief adds Client to List of not registered Client
	 * adds Client to m_clientInQueue
	 */
	void addToPending(Client* client);

	/**
	 * @brief to check if a client is registered or not
	 * @param client Client to check registered or not
	 * @return true if client is registered, false otherwise
	 */
	bool isPending(Client* client);

	/**
	 * @brief removes client provided
	 * @param client Client to remove from m_clientInQueue
	 */
	void removeIfPending(Client* client);

};

}

#endif
