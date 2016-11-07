#include "Textures.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

//=============================================================================================================================

Textures::Textures() :
	pBackground_(nullptr),//new Image(WAYS[Texture::background].c_str())),
	pTable_(new Image(WAYS[Texture::table].c_str())),
	pCue_(new Image(WAYS[Texture::cue].c_str())),
	pMenu_(new Image(WAYS[Texture::menu].c_str()))
	//pBalls_()
{
	for(size_t i = 0; i < NUMBER_OF_BALLS; i++) pBalls_[i] = new Image(WAYS[i].c_str());	
}

Textures::Textures(CONST Config &config)
{
	pBackground_ = new Image(config.getWString("background").c_str());
	pTable_ = new Image(config.getWString("table").c_str());
	pCue_ = new Image(config.getWString("cue").c_str());
	pMenu_ = new Image(config.getWString("menu").c_str());
}

Textures::~Textures()
{
	delete(pBackground_);
	delete(pTable_);
	delete(pCue_);
	delete(pMenu_);

	for(size_t i = 0; i < NUMBER_OF_BALLS; i++) delete(pBalls_[i]);
}

