#pragma once

#pragma warning(push, 4)

#include <WinSock2.h>
#include <WS2tcpip.h> 
#include <iostream>
#include <string>
#include <ctime>

#pragma warning(pop)

#ifndef __SERVER_HPP_INCLUDED__
#define __SERVER_HPP_INCLUDED__

namespace Network
{
	CONST USHORT STD_PORT = 1234;

	class Server final
	{
	private:
		static CONST WORD PAIR = 2;
		static CONST WORD MAX_BUFFER_LENGTH = 64;

		SOCKET      server_;
		SOCKET      client_[PAIR];

		sockaddr_in serverBind_;
		sockaddr_in sockaddr_[PAIR];

		BOOL        started_;
		BOOL        closed_;

		Server(CONST Server&);
		Server& operator=(CONST Server&);

		BOOL addNewClient(USHORT);
		BOOL createPair();
		BOOL sendPairInfo(std::string&, USHORT, BOOL);

	public:
		explicit Server();
		~Server();

		BOOL start();
		BOOL work();
		BOOL close();
	};
};

#endif // __SERVER_HPP_INCLUDED__