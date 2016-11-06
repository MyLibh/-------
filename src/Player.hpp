#pragma once

#include "Variables.hpp"
#include "ProgramManager.hpp"

typedef int TURN;

enum Turns
{
	None       = 0,
	Blow       = 1,
	Step       = 2,
	SetZeroPos = 3,
	SetPos     = 4
};

enum BallType
{
	NoType  = -1,
	Zero    =  0,

	Solid   =  1,
	Striped =  2
};

class GameInfo
{
private:
	GameInfo(CONST GameInfo&) {}
	GameInfo& operator=(CONST GameInfo&) {}

public:
	Turns turn;
	BOOL  scoredEight;
	BOOL  scoredWrong;
	BOOL  scoredZero;
	BOOL  touchNobody;
	BOOL  first;
	BOOL  drawCue;
	BOOL  firstScore;

	BallType    ballType2;
	Balls::Ball wrongBall;

	explicit GameInfo();
	~GameInfo();

	inline VOID dump() const { cout << __FUNCTION__ << endl; 
							     cout << "Step: " << turn << ", nine: " << scoredEight << ", wrong: " << scoredWrong <<
									 ", zero: " << scoredZero << ", nbdy:" << touchNobody << endl << endl; }

	VOID resetToNext() { dump(); turn = Turns::Blow; first = !first; dump(); }
};

BallType getBallType(Balls::Ball);

class Player final
{
private:
	wstring  name_;
	WORD     score_;
	BallType ballType_;
	BOOL     first_;

	inline VOID updateScore(CONST WORD &rScore) { score_ += rScore; }

protected:
	BOOL tmpBalls_[NUMBER_OF_BALLS];
	BOOL copied_;

	WORD checkScored(ProgramManager&, GameInfo&);
	inline VOID resetValues() { copied_ = !copied_; }

	inline string getScoreStr()   const { return to_string(score_); }
	inline wstring getScoreWStr() const { return to_wstring(score_); }

	inline VOID reset() { score_ = 0; }

	Player& operator=(CONST Player&);
	Player operator!();

public:
	Player(CONST BOOL&, CONST wstring& = L"ÊÎÌÏÜÞÒÅÐ"); 
	Player(CONST string&, CONST Player&); // Âòîðîé èãðîê
	~Player();

	inline CONST wstring  &getName()  const { return name_; }
	inline CONST WORD     &getScore() const { return score_; }
	inline CONST BallType &getType()  const { return ballType_; }
	inline CONST BOOL     &getFirst() const { return first_; }

	inline VOID setName(CONST string &rName) { wstring_convert<codecvt_utf8_utf16<WCHAR>> converter; name_ = converter.from_bytes(rName); }
	
	VOID turn(ProgramManager&, GameInfo&);

	inline wstring textToDraw() const { return wstring(name_ + L": " + to_wstring(score_)); }
};

extern Player player1;
extern Player player2;