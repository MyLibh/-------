#include "Config.hpp"

Config::Config()
{
	setDefaults();

	ifstream config("../src/Billiards.cfg");

	if (config.is_open())
	{
		string line;
		while (getline(config, line))
		{
			vector<string> tokens;
			istringstream iss(line);
			copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));

			if (tokens.size() == 3) properties_[tokens[0]] = tokens[2];
			else if (tokens.size() == 1 && 
				tokens[0] != "[PROJECT]" && 
				tokens[0] != "[WINDOW]" && 
				tokens[0] != "[TEXTURES]") properties_[tokens[0]] = "";		
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

VOID Config::setDefaults()
{
	
}

VOID Config::createLog()
{
	ofstream log("../src/Config.log");

	if (log.is_open())
	{
		log << "Бильярд " << __VERSION__ << " by " << __AUTHOR__ << " Copyright (C) 2016" << endl;
		log << "Дата построения: " << __DATE__ << " - " << __TIME__ << endl;
		log << "Программа использует следующий конфиг:" << endl << endl;

		for each (pair<string, string> pair in properties_)
		{
			if (pair.second != "") log << pair.first << " = " << pair.second << endl;
			else log << pair.first << endl;
		}		
	}

	log.close();
}


