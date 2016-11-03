#include "Player.hpp"

Player::Player(string name /* = "КОМПЬЮТЕР" */, BallType type /* = rand() % 2 + 1*/) :
	name_(name),
	score_(0),
	ballType_(type),
	copied_(FALSE)
{
	memset(tmpBalls_, FALSE, sizeof(tmpBalls_));
}

Player::Player(string name, Player &first)
{
	*this = !first;
	setName(name);
}

Player::~Player()
{}

VOID Player::turn(ProgramManager &programManager, TURN &is, Turns turn)
{
	if(turn < 0) turn = static_cast<Turns>(abs(turn));

	if(!copied_) 
	{
		memcpy(tmpBalls_, programManager.getScored(), sizeof(tmpBalls_));

		copied_ = !copied_;
	}

	if(is == -turn)
	{
		if(!programManager.stopBalls()) programManager.work(textToDraw(), PointF(0, 0), Color::LightGreen);
		else
		{
			updateScore(checkScored(programManager.getScored()));
			resetValues(is);
		}
	}
	else if(is == turn) 
	{	
		if(Key(32))
		{
			POINT cursor = { 0, 0 };
			GetCursorPos(&cursor);		

			//programManager.moveCue();
			programManager.nextMove();
			is = -is;
		}
		else programManager.work(textToDraw(), PointF(0, 0), Color::LightGreen);
	}
	else programManager.work(textToDraw(), PointF(0, 100), Color::Red);
}

VOID Player::resetValues(TURN &is)
{
	copied_ = !copied_;
	is = (is == Turns::FirstStep)? Turns::SecondBlow : Turns::FirstBlow;
}

WORD Player::checkScored(CONST BOOL following[])
{
	WORD ret_val = 0;
	for(size_t i = 0; i < NUMBER_OF_BALLS; i++)
		if(tmpBalls_[i] != following[i])
		{
			ret_val++;
			//Проверки забития не того
		}
	
	return ret_val;
}

Player & Player::operator=(Player &player)
{
	name_ = player.getName();
	score_ = player.getScore();
	ballType_ = player.getBallType();

	copied_ = FALSE;
	memset(tmpBalls_, FALSE, sizeof(tmpBalls_));

	return *this;
}

Player Player::operator!()
{
	return Player(name_, static_cast<BallType>(-ballType_));
}

inline wstring Player::textToDraw() const
{
	  wstring_convert<codecvt_utf8_utf16<WCHAR>> converter; 
	  
	  CHAR text[10] = "";
	  string tmp = name_ + ": " + _itoa(score_, text, 10);

	  return wstring(converter.from_bytes(tmp)); 
}