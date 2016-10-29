#include "Textures.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

//==============================================================================================================

Textures::Textures()
{
	background_ = new Image(WAYS[TEXTURES::background].c_str());
	table_      = new Image(WAYS[TEXTURES::table].c_str());
	cue_        = new Image(WAYS[TEXTURES::cue].c_str());
	menu_       = new Image(WAYS[TEXTURES::menu].c_str());

	for(size_t i = 0; i < NUMBER_OF_BALLS; i++) balls_[i] = new Image(WAYS[i].c_str());	
}

Textures::~Textures()
{
	delete(background_);
	delete(table_);
	delete(cue_);
	delete(menu_);

	for(size_t i = 0; i < NUMBER_OF_BALLS; i++) delete(balls_[i]);
}

