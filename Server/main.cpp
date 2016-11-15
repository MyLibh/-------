#include "Server.hpp"

typedef unsigned UNSIGNED;

INT main()
{
	Network::Server server;

	srand(static_cast<UNSIGNED>(time(NULL)));

	try
	{
		server.start();

		server.work();

		server.close();
	}
	catch(INT error) { std::cout << "WSAError: " << error << std::endl; }
	catch(CONST std::string &error) { std::cout << error; }

	system("pause");

	return 0;
}

