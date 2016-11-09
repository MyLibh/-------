#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

/*
SOCKET sConnect;
SOCKET *connections;
SOCKET sListen;

int ClientCount = 0;
	setlocale(LC_ALL, "russian");

	WSAData data;
	WORD socketVersion = MAKEWORD(2, 2);
	int res;
	if((res = WSAStartup(socketVersion, &data)) != 0) return -1;

	struct addrinfo hints;
	struct addrinfo *result;

	connections = (SOCKET*)calloc(64, sizeof(SOCKET));
	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	getaddrinfo(NULL, "7770", &hints, &result);

	sListen = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	bind(sListen, result->ai_addr, result->ai_addrlen);
	listen(sListen, SOMAXCONN);

	freeaddrinfo(result);

	cout << "Starting server...";
	char connect[] = "Connect...;;;;5";
	for(;; Sleep(75))
	{
		if(sConnect = accept(sListen, NULL, NULL))
		{
			cout << "Client connect..." << endl;
			connections[ClientCount] = sConnect;
			send(connections[ClientCount], connect, strlen(connect), NULL);
			ClientCount++;
			//CreateThread();
		}
	}
*/

#define		MAX_CONN	10
#define		MSG_LEN		128

int main()
{
	cout << "Starting server..." << endl;	

	SOCKET server;
	sockaddr_in	serverBind;
	
	SOCKET client1;
	SOCKET client2;
	sockaddr_in	player1;
	sockaddr_in	player2;

	int new_len = 0;

	WSADATA wsData;
	if (FAILED(WSAStartup(MAKEWORD(2, 2), &wsData))) return E_FAIL;
	
	if ((server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) return E_FAIL;

	ZeroMemory(&serverBind, sizeof(serverBind));
	serverBind.sin_family			= PF_INET;
	serverBind.sin_addr.S_un.S_addr	= htonl(INADDR_ANY);																
	serverBind.sin_port				= htons(1234);				

	if (bind(server, reinterpret_cast<sockaddr*>(&serverBind), sizeof(serverBind)) == SOCKET_ERROR) return E_FAIL;

	if (FAILED(listen(server, SOMAXCONN))) return E_FAIL;
		
	cout << "Server started" << endl;

	for (size_t i = 0; !GetAsyncKeyState(27); i++)
	{
		if(i == 0)
		{
			cout << "Waiting for the 1" << endl;
			ZeroMemory(&player1, sizeof(player1));
			new_len = sizeof(player1);

			if (FAILED(client1 = accept(server, (sockaddr*)&player1, &new_len)))
			{
				printf ("\n Accept failed on %d", i + 1);
				return E_FAIL;
			}
			else 
			{
				printf ("New Client... Number %d\n", i + 1);
				printf ("Client IP %s, Client Port %d\n", inet_ntoa((in_addr)player1.sin_addr), ntohs(player1.sin_port));

				char buffer[512] = "";	
				if (FAILED(recv(client1, buffer, 512, 0))) return E_FAIL;
		
				cout << buffer << endl;
			
				if (send(client1, "CONNECTED, PLEASE WAIT", strlen("CONNECTED, PLEASE WAIT"), 0) == SOCKET_ERROR) return E_FAIL;
			}	
		}
		else if(i == 1)
		{
			cout << "Waiting for the 2" << endl;
			ZeroMemory(&player2, sizeof(player2));
			new_len = sizeof(player2);

			if (FAILED(client2 = accept(server, (sockaddr*)&player2, &new_len)))
			{
				printf ("\n Accept failed on %d", i + 1);
				return E_FAIL;
			}
			else 
			{
				printf ("New Client... Number %d\n", i + 1);
				printf ("Client IP %s, Client Port %d\n", inet_ntoa((in_addr)player2.sin_addr), ntohs(player2.sin_port));

				char buffer[512] = "";	
				if (FAILED(recv(client2, buffer, 512, 0))) return E_FAIL;
		
				cout << buffer << endl;
			
				if (send(client2, "CONNECTED, PLEASE WAIT", strlen("CONNECTED, PLEASE WAIT"), 0) == SOCKET_ERROR) return E_FAIL;
			}	
		}
		else if(i == 2)
		{
			cout << "Creating a pair" << endl;
			i = -1;

			string buffer(inet_ntoa((in_addr)player2.sin_addr));
			if (FAILED(send(client1, const_cast<char*>(buffer.c_str()), buffer.length(), 0))) return E_FAIL;
			buffer = to_string(ntohs(player2.sin_port));
			if (FAILED(send(client1, const_cast<char*>(buffer.c_str()), buffer.length(), 0))) return E_FAIL;
			buffer = to_string(1);
			if (FAILED(send(client1, const_cast<char*>(buffer.c_str()), buffer.length(), 0))) return E_FAIL;

			buffer = inet_ntoa((in_addr)player1.sin_addr);
			if (FAILED(send(client2, const_cast<char*>(buffer.c_str()), buffer.length(), 0))) return E_FAIL;
			buffer = to_string(ntohs(player1.sin_port));
			if (FAILED(send(client2, const_cast<char*>(buffer.c_str()), buffer.length(), 0))) return E_FAIL;
			buffer = to_string(2);
			if (FAILED(send(client2, const_cast<char*>(buffer.c_str()), buffer.length(), 0))) return E_FAIL;

			closesocket(client1);
			closesocket(client2);
			cout << "closed" << endl;
		}	
	}

	cout << "Closing server..." << endl;
	closesocket(server);

	cout << "Server closed" << endl;

	return 0;
}
