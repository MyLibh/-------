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
	
	BallType ballType_;

	inline VOID updateScore(WORD score) { score_ += score; }

protected:
	BOOL tmpBalls_[NUMBER_OF_BALLS];
	BOOL copied_;

	WORD checkScored(CONST BOOL[]);
	VOID resetValues(TURN&);

	Player &operator=(Player&);
	Player operator!();

public:
	Player(string = "КОМПЬЮТЕР", BallType = static_cast<BallType>(rand() % 2 + 1)); 
	Player(string, Player&); // Второй игрок
	~Player();

	inline string getName() const { return name_; }
	inline WORD getScore() const { return score_; }
	inline BallType getBallType() const { return ballType_; }

	inline VOID setName(string name) { name_ = name; }
	
	VOID turn(ProgramManager&, TURN&, Turns);
	inline wstring textToDraw() const;
};

extern Player player1;
extern Player player2;