#ifndef NETWORKING_H
#define NETWORKING_H

#include <SFML/Network.hpp>
#include <iostream>

class Networking
{
private:
	int port;
	int status;
	sf::TcpListener listener;
	sf::TcpSocket socket;
public:
	Networking() {};
	Networking(int port);
	bool host();
	bool connect(std::string ip);
	bool sendData(std::string data);
	std::string receiveData();
	void disconnect();
};

#endif /* NETWORKING_H */