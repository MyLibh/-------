#include "Variables.hpp"

#pragma once 

using namespace Gdiplus;

class Textures
{
private:
	Image *background_;
	Image *table_;
	Image *cue_;
	

public:      
    Image *balls_[NUMBER_OF_BALLS];

	Textures();
	~Textures();

	VOID loadTextures();
	//VOID loadFromConfig(WCHAR*);

	Image *getBackgroundTexture() const { return background_; }
	Image *getCueTexture()        const { return cue_; }
	Image *getTableTexture()      const { return table_; }
	//Image *getBallTexture(size_t index) const { return ball_[index]; }
};