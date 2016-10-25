#include "Textures.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

//==============================================================================================================

Textures::Textures()
{
	background_ = new Image(L"../src/Images/Background.jpg");
	table_      = nullptr;
	cue_        = new Image(L"../src/Images/Cue.png");

	for(size_t i = 0; i < NUMBER_OF_BALLS; i++)
	{
		WCHAR wstr[MAX_LOADSTRING] = L"";
		swprintf(wstr, L"../src/Images/%d.png", i);

		balls_[i] = new Image(wstr);
	}
}

Textures::~Textures()
{
	delete(background_);
	delete(table_);
	delete(cue_);

	for(size_t i = 0; i < NUMBER_OF_BALLS; i++) delete(balls_[i]);
}

VOID Textures::loadTextures()
{
	background_ = new Image(L"../src/Images/Background.jpg");
	table_      = nullptr;
	cue_        = new Image(L"../src/Images/Cue.png");

	for(size_t i = 0; i < NUMBER_OF_BALLS; i++)
	{
		WCHAR wstr[MAX_LOADSTRING] = L"";
		swprintf(wstr, L"../src/Images/%d.png", i);

		balls_[i] = new Image(wstr);
	}
}
