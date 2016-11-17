#pragma once 

#include "Variables.hpp"

class Network : private Uncopyable
{
private:
	SOCKET server_;
	SOCKET client_;
	SOCKET opponent_;
	sockaddr_in serverAddr_;

	BOOL initServerConnection();
	
public:
	BOOL connectServer();
	BOOL getOpponentInfo();
	BOOL sentInfoToOpponent();

public:
	explicit Network();
	~Network();
};

/*
	//=======================================================================================
	
	SOCKET server;
	WSADATA wsData;

	if (FAILED(WSAStartup(MAKEWORD(2, 2), &wsData))) return E_FAIL;
	
	if ((server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) return E_FAIL;

	sockaddr_in s_addrs;
	ZeroMemory(&s_addrs, sizeof(s_addrs));

	s_addrs.sin_family = AF_INET;
	s_addrs.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); 
	s_addrs.sin_port = htons(1234);

	if (connect(server, reinterpret_cast<sockaddr*>(&s_addrs), sizeof(s_addrs)) == SOCKET_ERROR) return E_FAIL;
   
	char buff[512] = "HELLO WORLD";
	if (send(server, buff, 512, 0) == SOCKET_ERROR)  return E_FAIL;
	
	if (FAILED(recv(server, buff, 512, 0))) return E_FAIL;

	CONST WORD LENGTH = 128;
	char ip[LENGTH] = "";
	char port[LENGTH / 4] = "";
	char num[16] = "";

	if (FAILED(recv(server, ip, LENGTH, 0))) return E_FAIL;
	if (FAILED(recv(server, port, LENGTH / 4, 0))) return E_FAIL;
	if (FAILED(recv(server, num, 16, 0))) return E_FAIL;

	closesocket(server);
	//==================================

	char buff2[512] = "HELLO WORLD2";
	if (atoi(num) == 1) 
	{
		cout << "AMA HEAR";
		SOCKET player2socs;
		if ((player2socs = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) return -1;

		sockaddr_in s_addrp2s;
		ZeroMemory(&s_addrp2s, sizeof(s_addrp2s));

		s_addrp2s.sin_family = AF_INET;
		s_addrp2s.sin_addr.S_un.S_addr = inet_addr(ip); 
		s_addrp2s.sin_port = htons(static_cast<u_short>(atoi(port)));
	
		if (connect(player2socs, reinterpret_cast<sockaddr*>(&s_addrp2s), sizeof(s_addrp2s)) == SOCKET_ERROR) return -2;
   
		if (send(player2socs, buff2, 512, 0) == SOCKET_ERROR)  return -3;
		closesocket(player2socs);
	}
	else 
	{
		cout << "AMA NOT HEAR";
		SOCKET player2socr;
		if ((player2socr = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) return -4;

		sockaddr_in s_addrp2r;
		ZeroMemory(&s_addrp2r, sizeof(s_addrp2r));

		s_addrp2r.sin_family			= PF_INET;
		s_addrp2r.sin_addr.S_un.S_addr	= htonl(INADDR_ANY);																
		s_addrp2r.sin_port				= htons(static_cast<u_short>(atoi(port)));

		if (bind(player2socr, reinterpret_cast<sockaddr*>(&s_addrp2r), sizeof(s_addrp2r)) == SOCKET_ERROR) return -5;
		if (FAILED(listen(player2socr, SOMAXCONN))) return -6;

		SOCKET player2socs;
		sockaddr_in player2socsaddr;

		ZeroMemory(&player2socsaddr, sizeof(player2socsaddr));
		int new_len = sizeof(player2socsaddr);

		if (FAILED(player2socs = accept(player2socr, (sockaddr*)&player2socsaddr, &new_len))) return -7;		
		else {if (FAILED(recv(player2socs, buff2, 512, 0))) return -8;}

		closesocket(player2socs);
		closesocket(player2socr);
		cout << buff2;		
	}

	
	//==============================================================================================
	*/