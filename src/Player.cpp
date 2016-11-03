#include "Player.hpp"

Player::Player(string name /* = "ÊÎÌÏÜÞÒÅÐ" */) :
	name_(name),
	lose_(FALSE),
	score_(0),
	ballType_(BallType::Zero),
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

BOOL Player::turn(ProgramManager &programManager, TURN &is, Turns turn, BOOL lose)
{
	if(lose) programManager.endGame(name_ + " âûèãðàë ñî ñ÷¸òîì: " + getScoreStr());
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
			updateScore(checkScored(programManager));
			resetValues(is);
		}
	}
	else if(is == turn) 
	{	
		if(Key(32))
		{
			POINT cursor = { 0, 0 };
			GetCursorPos(&cursor);		

			programManager.nextMove();
			is = -is;
		}
		else programManager.work(textToDraw(), PointF(0, 0), Color::LightGreen);
	}
	else programManager.work(textToDraw(), PointF(0, 100), Color::Red);

	return lose_;
}

VOID Player::resetValues(TURN &is)
{
	copied_ = !copied_;
	is = (is == Turns::FirstStep)? Turns::SecondBlow : Turns::FirstBlow;
}

WORD Player::checkScored(ProgramManager &programManager)
{
	WORD ret_val = 0;
	for(size_t i = 0; i < NUMBER_OF_BALLS; i++)
		if(tmpBalls_[i] != programManager.getScored()[i])
		{
			if(i == Balls::Ball::zero)
			{
			}
			else if(i == Balls::Ball::eighth)
			{
				lose_ = true;
				score_ = 0;

				return FALSE;
			}
			else ret_val++;
		}
	
	return ret_val;
}

Player & Player::operator=(Player &player)
{
	name_     = player.getName();
	score_    = player.getScore();
	ballType_ = player.getBallType();

	lose_   = FALSE;
	copied_ = FALSE;
	memset(tmpBalls_, FALSE, sizeof(tmpBalls_));

	return *this;
}

Player Player::operator!()
{
	return Player(name_);
}

inline wstring Player::textToDraw() const
{
	  wstring_convert<codecvt_utf8_utf16<WCHAR>> converter; 
	  
	  CHAR text[10] = "";
	  string tmp = name_ + ": " + _itoa(score_, text, 10);

	  return wstring(converter.from_bytes(tmp)); 
}