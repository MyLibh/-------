#pragma once

#include "Variables.hpp"
#include "ProgramManager.hpp"

typedef int TURN;

enum Turns
{
	FirstBlow =  1,
	FirstStep = -1,

	SecondBlow =  2,
	SecondStep = -2
};

enum BallType
{
	Zero    =  0,

	Solid   =  1,
	Striped = -1
};

class Player final
{
private:
	//Player(CONST Player&) {}

	string   name_;
	WORD     score_;
	BOOL     lose_;
	BallType ballType_;

	inline VOID updateScore(WORD score) { score_ += score; }

protected:
	BOOL tmpBalls_[NUMBER_OF_BALLS];
	BOOL copied_;

	WORD checkScored(ProgramManager&);
	VOID resetValues(TURN&);

	inline string getScoreStr() const { CHAR text[10] = ""; return string(_itoa(score_, text, 10)); }
	inline VOID reset() { score_ = 0; lose_ = FALSE; }

	Player &operator=(Player&);
	Player operator!();

public:
	Player(string = "КОМПЬЮТЕР"); 
	Player(string, Player&); // Второй игрок
	~Player();

	inline string getName() const { return name_; }
	inline WORD getScore() const { return score_; }
	inline BallType getBallType() const { return ballType_; }

	inline VOID setName(string name) { name_ = name; }
	
	BOOL turn(ProgramManager&, TURN&, Turns, BOOL);
	inline wstring textToDraw() const;
};

extern Player player1;
extern Player player2;