#include "networking.h"

Networking::Networking(int port)
{
	this->port = port;
}

//Host on a port and wait for a connection
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

//Connect using an IP address and a port
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

//Send data via the socket
bool Networking::sendData(std::string data)
{
	if(socket.send(data.c_str(), strlen(data.c_str())) != sf::Socket::Done)
	{
		std::cout << "Failure sending data\n";
		return false;
	}
	
	return true;
}

//Receive data from the socket. This function is blocking.
std::string Networking::receiveData()
{
	char data[100];
	std::size_t received;
	if (socket.receive(data, 100, received) != sf::Socket::Done)
	{
		std::cout << "Failure receiving data\n";
		return "";
	}
	
	std::string dataString = std::string(data);
	dataString = dataString.substr(0, received);
	
	return std::string(dataString);
}

//Disconnect
void Networking::disconnect()
{
	socket.disconnect();
}