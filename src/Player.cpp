#include "Player.hpp"

GameInfo::GameInfo() :
	turn(Turns::None), // -1 - in; 1 - inShot | same to 2
	scoredEight(FALSE),
	scoredWrong(FALSE),
	scoredZero(FALSE),
	first(TRUE),
	drawCue(TRUE),
	firstScore(FALSE),
	scored(FALSE),
	ballType2(BallType::NoType),
	wrongBall(Balls::Ball::wrong)
{}

GameInfo::~GameInfo()
{}

VOID GameInfo::restart()
{
	turn        = Turns::None;

	scoredEight = FALSE;
	scoredWrong = FALSE;
	scoredZero  = FALSE;
	first       = TRUE;
	drawCue     = TRUE;
	firstScore  = FALSE;
	scored      = FALSE;

	ballType2   = BallType::NoType;
	wrongBall   = Balls::Ball::wrong;
}
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

Player::Player(CONST BOOL &rFirst, CONST wstring &rName /* = "ÊÎÌÏÜÞÒÅÐ" */) :
	name_(rName),
	score_(0),
	ballType_(BallType::NoType),
	first_(rFirst),
	//tmpBallsStatus_(),
	//tmpBallsPos_(),
	copied_(FALSE)
{
	memset(tmpBallsStatus_, FALSE, sizeof(tmpBallsStatus_));
	memset(tmpBallsPos_, 0, sizeof(tmpBallsPos_));
}

Player::Player(CONST string &rName, CONST Player &rPlayer)
{
	setName(rName);
	score_    = rPlayer.getScore();
	ballType_ = rPlayer.getType();
	first_    = rPlayer.getFirst();
	copied_   = FALSE;

	memset(tmpBallsStatus_, FALSE, sizeof(tmpBallsStatus_));
	memset(tmpBallsPos_, 0, sizeof(tmpBallsPos_));
}

Player::~Player()
{}

VOID Player::turn(ProgramManager &rProgramManager, GameInfo &rGameInfo)
{
	if(rGameInfo.first == first_)
	{
		if(rGameInfo.scoredEight) rProgramManager.endGame(name_ + L" âûèãðàë ñî ñ÷¸òîì: " + getScoreWStr());
		else if(rGameInfo.scoredZero)
		{ 
			rGameInfo.scoredZero = FALSE;
			rGameInfo.drawCue    = FALSE;
			rGameInfo.turn       = Turns::SetZeroPos;

			rProgramManager.updateZero();
		}
		else if(rGameInfo.scoredWrong)
		{
			rGameInfo.scoredWrong = FALSE;
			rGameInfo.drawCue     = FALSE;
			rGameInfo.turn        = Turns::SetPos;
		}

		if(!copied_) 
		{
			memcpy(tmpBallsStatus_, rProgramManager.getScored(), sizeof(tmpBallsStatus_));
			memcpy(tmpBallsPos_, rProgramManager.getPoints(), sizeof(tmpBallsPos_));

			copied_ = !copied_;
		}

		if(rGameInfo.turn == Turns::SetZeroPos)
		{ 
			rProgramManager.setBallCoords(rProgramManager.getMousePos());

			rProgramManager.work(textToDraw(), PointF(0, 0), static_cast<ARGB>(Color::LightGreen), FALSE);

			if(Key(VK_END)) 
			{
				rGameInfo.turn = Turns::Blow;

				rGameInfo.drawCue = TRUE;
			}
		}
		else if(rGameInfo.turn == Turns::SetPos)
		{
			rProgramManager.setBallCoords(rProgramManager.getMousePos(), rGameInfo.wrongBall);
			rProgramManager.work(textToDraw(), PointF(0, 0), static_cast<ARGB>(Color::LightGreen), FALSE);
			
			if(Key(VK_END)) 
			{
				rGameInfo.turn = Turns::Blow;

				rGameInfo.drawCue = TRUE;
			}
		}
		else if(rGameInfo.turn == Turns::Blow) 
		{	
			if(Key(VK_SPACE))
			{
				POINT cursor = { 0, 0 };
				GetCursorPos(&cursor);		

				rProgramManager.nextMove();
				rGameInfo.turn = Turns::Step;
			}
			else rProgramManager.work(textToDraw());
		}
		else if(rGameInfo.turn == Turns::Step)
		{
			if(!rProgramManager.stopBalls()) rProgramManager.work(textToDraw());
			else
			{
				updateScore(checkScored(rProgramManager, rGameInfo));
				if(!checkPoints(rProgramManager)) if(score_ != 0) score_--;
				resetValues();
				rGameInfo.resetToNext(); 
			}		
		}
	}
	else rProgramManager.work(textToDraw(), PointF(static_cast<REAL>(rProgramManager.getMemDCWindow().width - 6 * sizestenaRIGHT), 0), static_cast<ARGB>(Color::Red), rGameInfo.drawCue);
}

VOID Player::restart()
{
	score_    = 0;
	ballType_ = BallType::NoType;
	copied_   = FALSE;

	memset(tmpBallsStatus_, FALSE, sizeof(tmpBallsStatus_));
	memset(tmpBallsPos_, 0, sizeof(tmpBallsPos_));
}

WORD Player::checkScored(ProgramManager &rProgramManager, GameInfo &rGameInfo)
{
	WORD ret_val = 0;
	for(size_t i = 0; i < NUMBER_OF_BALLS; i++)
		if(tmpBallsStatus_[i] != rProgramManager.getScored()[i])
		{
			BallType ballType = getBallType(static_cast<Balls::Ball>(i));
			
			if(!rGameInfo.firstScore && ballType != BallType::Zero) 
			{
				rGameInfo.firstScore = !rGameInfo.firstScore;
				ballType_ = ballType;

				rGameInfo.ballType2 = (ballType_ == BallType::Solid)? BallType::Striped : BallType::Solid;
			}
			else if(ballType_ == BallType::NoType && rGameInfo.firstScore) ballType_ = rGameInfo.ballType2;
				 
			switch(ballType)
			{
			case BallType::Zero:
				rProgramManager.updateZero();
				rGameInfo.scoredZero = TRUE;
				if(score_ != 0) score_--;
				break;
			case BallType::Solid: 
				if(i == Balls::Ball::eighth)
				{
					rGameInfo.scoredEight = TRUE;
					score_ = 0;

					return FALSE;
				}
				else
				{
					if(ballType_ == BallType::Solid) 
					{
						rGameInfo.scored = TRUE;
						ret_val++;
					}
					else 
					{
						rGameInfo.scoredWrong = TRUE;
						rGameInfo.wrongBall = static_cast<Balls::Ball>(i);
						if(score_ != 0) score_--;
					}
				}
				break;
			case BallType::Striped: 
				if(ballType_ == BallType::Striped) ret_val++;
				else 
				{
					rGameInfo.scoredWrong = TRUE;
					rGameInfo.wrongBall = static_cast<Balls::Ball>(i);
					if(score_ != 0) score_--;
				}
				break;
			default: PostQuitMessage(-999);
			}			
		}
	
	return ret_val;
}

BOOL Player::checkPoints(CONST ProgramManager &rProgramManager)
{
	for(size_t i = 1; i < NUMBER_OF_BALLS; i++)
		if(tmpBallsPos_[i] != rProgramManager.getPoints()[i]) return TRUE;

	return FALSE;
}

Player& Player::operator=(CONST Player &rPlayer)
{
	name_     = rPlayer.getName();
	score_    = rPlayer.getScore();
	ballType_ = rPlayer.getType();
	first_    = rPlayer.getFirst();
	copied_   = FALSE;

	memset(tmpBallsStatus_, FALSE, sizeof(tmpBallsStatus_));
	memset(tmpBallsPos_, FALSE, sizeof(tmpBallsPos_));

	return *this;
}

Player Player::operator!()
{
	return Player(!first_);
}
