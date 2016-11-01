#include "Config.hpp"

Config::Config()
{
	properties_["Background"] = "";

	ifstream config("Billiards.cfg");

	if (config.is_open())
	{
		string line;
		while (getline(config, line))
		{
			vector<string> tokens;
			istringstream iss(line);
			copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));

			if (tokens.size() == 3 && tokens[0][0])
			{
				properties_[tokens[0]] = tokens[2];
			}
			else if (tokens.size() == 1)
			{
				properties_[tokens[0]] = "";
			}
		}
	}
	else createLog();

	config.close();
}

Config::~Config()
{
	createLog();

	properties_.clear();
}

VOID Config::createLog()
{
	ofstream log("Billiards.cfg");

	if (log.is_open())
	{
		log << "Build Date: " << __DATE__ << " - " << __TIME__ << endl;

		for each (pair<string, string> pair in properties_)
		{
			if (pair.second != "")
			{
				log << pair.first << " = " << pair.second << endl;
			}
			else
			{
				log << pair.first << endl;
			}
		}
	}

	log.close();
}


