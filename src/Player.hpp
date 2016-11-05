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

struct GameInfo
{
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
							     cout << "Step: " << turn << ", 9: " << scoredEight << ", -: " << scoredWrong <<
									 ", 0: " << scoredZero << ", nbdy:" << touchNobody << endl << endl; }

	VOID resetToNext() { turn = Turns::Blow; first = !first; }
};

BallType getBallType(Balls::Ball);

class Player final
{
private:
	//Player(CONST Player&) {}

	wstring   name_;
	WORD     score_;
	BallType ballType_;
	BOOL     first_;

	inline VOID updateScore(WORD score) { score_ += score; }

protected:
	BOOL tmpBalls_[NUMBER_OF_BALLS];
	BOOL copied_;

	WORD checkScored(ProgramManager&, GameInfo&);
	inline VOID resetValues() { copied_ = !copied_; }

	inline string getScoreStr() const { return to_string(score_); }
	inline wstring getScoreWStr() const { return to_wstring(score_); }
	inline VOID reset() { score_ = 0; }

	Player &operator=(Player&);
	Player operator!();

public:
	Player(BOOL, wstring = L"ÊÎÌÏÜÞÒÅÐ"); 
	Player(string, Player&); // Âòîðîé èãðîê
	~Player();

	inline wstring getName() const { return name_; }
	inline WORD getScore() const { return score_; }
	inline BallType getType() const { return ballType_; }

	inline VOID setName(string name) { wstring_convert<codecvt_utf8_utf16<WCHAR>> converter; CHAR text[10] = ""; name_ = converter.from_bytes(name); }
	
	VOID turn(ProgramManager&, GameInfo&);

	inline wstring textToDraw() const { return wstring(name_ + L": " + to_wstring(score_)); }
};

extern Player player1;
extern Player player2;