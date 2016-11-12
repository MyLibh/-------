#include "Network.hpp"

#pragma comment(lib, "WS2_32.lib")

Network::Network()
{
	WSADATA wsData;

	if (FAILED(WSAStartup(MAKEWORD(2, 2), &wsData))) PostQuitMessage(WSAGetLastError());
}

Network::~Network()
{}

BOOL Network::initServerConnection()
{
	if ((server_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) return E_FAIL;

	
	ZeroMemory(&serverAddr_, sizeof(serverAddr_));

	serverAddr_.sin_family = AF_INET;
	serverAddr_.sin_addr.S_un.S_addr = inet_addr("127.0.0.0"); 
	serverAddr_.sin_port = htons(1234);

	return TRUE;
}

BOOL Network::connectServer()
{
	if(connect(server_, reinterpret_cast<sockaddr*>(&serverAddr_), sizeof(serverAddr_)) == SOCKET_ERROR) return E_FAIL;
   
	char buff[512] = "HELLO WORLD";
	if (send(server_, buff, 512, 0) == SOCKET_ERROR)  return E_FAIL;
	
	if (FAILED(recv(server_, buff, 512, 0))) return E_FAIL;

	CONST WORD LENGTH = 128;
	char ip[LENGTH] = "";
	char port[LENGTH / 4] = "";
	char num[16] = "";

	if (FAILED(recv(server_, ip, LENGTH, 0))) return E_FAIL;
	if (FAILED(recv(server_, port, LENGTH / 4, 0))) return E_FAIL;
	if (FAILED(recv(server_, num, 16, 0))) return E_FAIL;

	closesocket(server_);
	return TRUE;
}