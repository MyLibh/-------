#include "Variables.hpp"

class Profile : private Uncopyable
{
private:
	string name_;

public:
	Profile();
	~Profile();
};