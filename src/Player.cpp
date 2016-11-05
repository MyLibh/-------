#include "Player.hpp"

GameInfo::GameInfo() :
	turn(Turns::None), // -1 - in; 1 - inShot | same to 2
	scoredEight(FALSE),
	scoredWrong(FALSE),
	scoredZero(FALSE),
	touchNobody(FALSE),
	first(TRUE),
	drawCue(TRUE),
	firstScore(FALSE),
	ballType2(BallType::NoType),
	wrongBall(Balls::Ball::wrong)
{}

GameInfo::~GameInfo()
{}

//=========================================================================================

BallType getBallType(Balls::Ball ball)
{
	switch(ball)
	{
	case 0:
		return BallType::Zero;

	case 1: case 2: case 3: case 4:
		case 5: case 6: case 7: case 8:
			return BallType::Solid;

	case 9: case 10: case 11: case 12:
		case 13: case 14: case 15: 
			return BallType::Striped;

		default: return BallType::NoType; // PostQuitMessage(-9999);
	}
}

//=========================================================================================
Player::Player(BOOL first, wstring name /* = "ÊÎÌÏÜÞÒÅÐ" */) :
	name_(name),
	score_(0),
	ballType_(BallType::NoType),
	first_(first),
	copied_(FALSE)
{
	//setName(name);
	memset(tmpBalls_, FALSE, sizeof(tmpBalls_));
}

Player::Player(string name, Player &first)
{
	*this = !first;
	//setName(name);
}

Player::~Player()
{}

VOID Player::turn(ProgramManager &programManager, GameInfo &gameInfo)
{
	if(gameInfo.first == first_)
	{
		if(gameInfo.scoredEight) programManager.endGame(name_ + L" âûèãðàë ñî ñ÷¸òîì: " + getScoreWStr());
		if(gameInfo.scoredZero)
		{
			gameInfo.scoredZero = FALSE;
			gameInfo.drawCue    = FALSE;
			gameInfo.turn       = Turns::SetZeroPos;
		}
		if(gameInfo.scoredWrong)
		{
			gameInfo.scoredWrong = FALSE;
			gameInfo.drawCue     = FALSE;
			gameInfo.turn        = Turns::SetPos;
		}

		if(!copied_) 
		{
			memcpy(tmpBalls_, programManager.getScored(), sizeof(tmpBalls_));

			copied_ = !copied_;
		}

		if(gameInfo.turn == Turns::SetZeroPos)
		{
			programManager.setBallCoords(programManager.getMousePos(), gameInfo.wrongBall);
			programManager.work(textToDraw(), PointF(0, 0), Color::LightGreen, FALSE);

			if(Key(VK_END)) 
			{
				gameInfo.turn = Turns::Blow;

				gameInfo.drawCue = TRUE;
			}
		}
		else if(gameInfo.turn == Turns::SetPos)
		{
			programManager.setBallCoords(programManager.getMousePos());
			programManager.work(textToDraw(), PointF(0, 0), Color::LightGreen, FALSE);

			if(Key(VK_END)) 
			{
				gameInfo.turn = Turns::Blow;

				gameInfo.drawCue = TRUE;
			}
		}
		else if(gameInfo.turn == Turns::Blow) 
		{	
			if(Key(VK_SPACE))
			{
				POINT cursor = { 0, 0 };
				GetCursorPos(&cursor);		

				programManager.nextMove();
				gameInfo.turn = Turns::Step;
			}
			else programManager.work(textToDraw());
		}
		else if(gameInfo.turn == Turns::Step)
		{
			if(!programManager.stopBalls()) programManager.work(textToDraw());
			else
			{
				updateScore(checkScored(programManager, gameInfo));
				resetValues();
				gameInfo.resetToNext();
			}		
		}
	}
	else programManager.work(textToDraw(), PointF(0, 100), Color::Red, gameInfo.drawCue);
}

WORD Player::checkScored(ProgramManager &programManager, GameInfo &gameInfo)
{
	WORD ret_val = 0;
	for(size_t i = 0; i < NUMBER_OF_BALLS; i++)
		if(tmpBalls_[i] != programManager.getScored()[i])
		{
			BallType ballType = getBallType(static_cast<Balls::Ball>(i));
			
			if(!gameInfo.firstScore && ballType != BallType::Zero) 
			{
				gameInfo.firstScore = !gameInfo.firstScore;
				ballType_ = ballType;

				gameInfo.ballType2 = (ballType_ == BallType::Solid)? BallType::Striped : BallType::Solid;
			}
			else if(ballType_ == BallType::NoType) ballType_ = gameInfo.ballType2;
				 
			switch(ballType)
			{
			case BallType::Zero:
				gameInfo.scoredZero = TRUE;
				if(score_ != 0) score_--;
				break;
			case BallType::Solid: 
				if(i == Balls::Ball::eighth)
				{
					gameInfo.scoredEight = TRUE;
					score_ = 0;

					return FALSE;
				}
				else
				{
					if(ballType_ == BallType::Solid) ret_val++;
					else 
					{
						gameInfo.scoredWrong = TRUE;
						if(score_ != 0) score_--;
					}
				}
				break;
			case BallType::Striped: 
				if(ballType_ == BallType::Solid) ret_val++;
				else 
				{
					gameInfo.scoredWrong = TRUE;
					gameInfo.wrongBall = static_cast<Balls::Ball>(i);
					if(score_ != 0) score_--;
				}
				break;
			default: PostQuitMessage(-999);
			}			
		}
	
	return ret_val;
}

Player & Player::operator=(Player &player)
{
	name_     = player.getName();
	score_    = player.getScore();
	ballType_ = player.getType();

	first_  = first_;
	copied_ = FALSE;

	memset(tmpBalls_, FALSE, sizeof(tmpBalls_));

	return *this;
}

Player Player::operator!()
{
	return Player(!first_);
}
