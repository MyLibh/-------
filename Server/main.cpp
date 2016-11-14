#include "Server.hpp"

INT main()
{
	Network::Server server;

	try
	{
		server.start();

		server.work();

		server.close();
	}
	catch(INT error) { std::cout << "Error: " << error << std::endl; }
	catch(CONST std::string &error) { std::cout << error; }

	system("pause");

	return 0;
}

