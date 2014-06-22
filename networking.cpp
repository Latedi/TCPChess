#include "networking.h"

Networking::Networking(int port)
{
	this->port = port;
}

bool Networking::host()
{
	if (listener.listen(port) != sf::Socket::Done)
	{
		std::cout << "Could not listen on port " << port << std::endl;
		return false;
	}
	
	std::cout << "Waiting for connection...\n";
	if (listener.accept(socket) != sf::Socket::Done)
	{
		return false;
	}
	
	std::cout << "A client connected from " << socket.getRemoteAddress() << ". Starting game.\n";
	return true;
}

bool Networking::connect(std::string ip)
{
	if (socket.connect(ip, port) != sf::Socket::Done)
	{
		std::cout << "Failed to connect to host at " << ip << std::endl;
		return false;
	}
	
	std::cout << "Connected to host at " << ip << std::endl;
	return true;
}

bool Networking::sendData(std::string data)
{
	if(socket.send(data.c_str(), data.length()) != sf::Socket::Done)
	{
		std::cout << "Failure sending data\n";
		return false;
	}
	
	return true;
}

std::string Networking::receiveData()
{
	char data[100];
	std::size_t received;
	if (socket.receive(data, 100, received) != sf::Socket::Done)
	{
		std::cout << "Failure receiving data\n";
		return "";
	}
	
	return std::string(data);
}

void Networking::disconnect()
{
	socket.disconnect();
}