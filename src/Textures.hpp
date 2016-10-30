#include "Variables.hpp"

#pragma once 

using namespace Gdiplus;

class Textures final
{
private:
	Image *background_;
	Image *table_;
	Image *cue_;
	Image *menu_;
	Image *balls_[NUMBER_OF_BALLS];

public:      
	Textures();
	Textures(ifstream);
	~Textures();

	inline Image *getBackgroundTexture() const { return background_; }
	inline Image *getCueTexture()        const { return cue_; }
	inline Image *getTableTexture()      const { return table_; }
	inline Image *getMenuTexture()       const { return menu_; }

	inline Image **getBallsTexture()  { return reinterpret_cast<Image**>(balls_); }
};