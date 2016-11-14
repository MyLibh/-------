#include "Server.hpp"

#pragma comment(lib, "Ws2_32.lib")

Network::Server::Server() :
	server_(),
	serverBind_(),
	started_(FALSE),
	closed_(FALSE)
{}

Network::Server::~Server() { if(!closed_) close(); }

BOOL Network::Server::start()
{
	if(started_) 
	{
		throw std::string("Server has already started. Do not start it again\n");
		return FALSE;
	}

	if(closed_) closed_ = !closed_;

	WSADATA wsaData = {};
	if (FAILED(WSAStartup(MAKEWORD(2, 2), &wsaData))) 
	{
		throw WSAGetLastError();
		return FALSE;
	}

	std::cout << "Starting server...\n";

	if ((server_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) 
	{
		throw WSAGetLastError();
		return FALSE;
	}

	ZeroMemory(&serverBind_, sizeof(serverBind_));
	serverBind_.sin_family			 = PF_INET;
	serverBind_.sin_addr.S_un.S_addr = htonl(INADDR_ANY);																
	serverBind_.sin_port			 = htons(1234);				

	if (bind(server_, reinterpret_cast<sockaddr*>(&serverBind_), sizeof(serverBind_)) == SOCKET_ERROR) 
	{
		throw WSAGetLastError();
		return FALSE;
	}

	if (FAILED(listen(server_, SOMAXCONN))) 
	{
		throw WSAGetLastError();
		return FALSE;
	}

	started_ = TRUE;

	std::cout << "Server started\n\n";

	return TRUE;
}

BOOL Network::Server::work()
{
	if(!started_ || closed_)
	{
		throw std::string("You did not start the server\n");
		return FALSE;
	}

	for(USHORT i = 0; !GetAsyncKeyState(VK_ESCAPE); i++)
	{
		try
		{
			if(i == 0 || i == 1) addNewClient(i);
			else if(i == 2) 
			{
				createPair();
				
				i = 0;
			}
			else throw std::string("value of 'i' is not allowed\n");
		}
		catch(INT error) { throw error; }
		catch(CONST std::string &error)	{ throw error; }
	}

	return FALSE;
}

BOOL Network::Server::close()
{
	if(!started_)
	{
		throw std::string("Do not close server if you did not start it!\n");
		return FALSE;
	}

	if(closed_) 
	{
		throw std::string("Server has already closed. Do not close it again\n");
		return FALSE;
	}

	std::cout << "Closing server...\n";

	closesocket(server_);

	//for(WORD i = 0; i < PAIR; i++) closesocket(client_[i]);
	
	closed_  = TRUE;
	started_ = FALSE;
	
	std::cout << "Server closed\n\n";

	return TRUE;
}

BOOL Network::Server::addNewClient(USHORT i)
{
	std::cout << "Waiting for the " << i + 1 << "...\n"; 

	USHORT tmp = (i == 0)? 1 : 0;

	ZeroMemory(&sockaddr_[i], sizeof(sockaddr_[i]));
	INT newLen = sizeof(sockaddr_[i]);

	if (FAILED(client_[tmp] = accept(server_, (sockaddr*)&sockaddr_[i], &newLen)))
	{
		throw std::string("Failed to connect " + std::to_string(i + 1) + std::to_string(WSAGetLastError()));
		return FALSE;
	}
	else 
	{
		std::cout << "New Client: " << i + 1 << "\n";
		std::cout << "Client IP: " << inet_ntoa(static_cast<in_addr>(sockaddr_[i].sin_addr)) << ", port: " << ntohs(sockaddr_[i].sin_port) << "\n\n";

		char buffer[MAX_BUFFER_LENGTH] = "";	
		if (FAILED(recv(client_[tmp], buffer, MAX_BUFFER_LENGTH, 0))) 
		{
			throw WSAGetLastError();
			return FALSE;
		}
		
		//cout << buffer << endl;
			
		if (send(client_[tmp], "CONNECTED, PLEASE WAIT", strlen("CONNECTED, PLEASE WAIT"), 0) == SOCKET_ERROR) 
		{
			throw WSAGetLastError();
			return FALSE;
		}
	}
	return TRUE;
}

BOOL Network::Server::createPair()
{
	std::cout << "Creating a pair...\n";


	try
	{
		std::string buffer("");

		sendPairInfo(buffer, 0, true);
		sendPairInfo(buffer, 0, false);
	}
	catch(CONST std::string &error) { throw error; }

	std::cout << "Pair created\n\n";
	std::cout << "Closing clients sockets...\n";
	
	for(USHORT i = 0; i < PAIR; i++) closesocket(client_[i]);

	std::cout << "Sockets closed\n\n\n";
	
	return TRUE;
}

BOOL Network::Server::sendPairInfo(std::string &buffer, USHORT i, BOOL first)
{
	USHORT tmp = (i == 0)? 1 : 0;

	if (FAILED(send(client_[i], const_cast<char*>(buffer.c_str()), buffer.length(), 0))) 
	{
		throw std::string("Failed to send 'ip': " + std::to_string(WSAGetLastError()) + "\n");
		return FALSE;
	}
	buffer = std::to_string(ntohs(sockaddr_[tmp].sin_port));
	if (FAILED(send(client_[i], const_cast<char*>(buffer.c_str()), buffer.length(), 0))) 
	{
		throw std::string("Failed to send 'port': " + std::to_string(WSAGetLastError()) + "\n");
		return FALSE;
	}
	buffer = std::to_string((first)? 1 : 2);
	if (FAILED(send(client_[i], const_cast<char*>(buffer.c_str()), buffer.length(), 0))) 
	{
		throw std::string("Failed to send 'first': " + std::to_string(WSAGetLastError()) + "\n");
		return FALSE;
	}

	return TRUE;
}