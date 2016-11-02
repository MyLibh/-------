#pragma once

#include "Variables.hpp"

enum BallType
{
	Zero    = 0,
	Solid   = 1,
	Striped = 2
};

class Player final
{
private:
	string   name_;
	WORD     score_;
	BOOL     first_;
	BallType ballType_;

public:
	Player(string, BOOL, BallType);
	~Player();

	inline VOID updateScore(WORD score) { score_ += score; }

	BOOL checkScored(BOOL scored_[]);
};

