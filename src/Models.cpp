#include "Models.hpp"

namespace Billiards
{
	namespace models
	{
		Models::Models(HWND hWnd, CONST UPOINT &rWindowSize) :
			Graphics(hWnd, rWindowSize),
			Physics(),
			drawCue_(TRUE),
			drawMenu_(FALSE)			
		{
		}

		Models::~Models()
		{
		}

		inline VOID Models::setCueStatus(BOOL status) { drawCue_ = status; }

		inline VOID Models::setMenuStatus(BOOL status) { drawMenu_ = status; }

		VOID Models::doModels(CONST POINT &rMouse)
		{
			doPhysics(rMouse, drawCue_);
			//doGraphics(vec(), drawCue_, getCueAngleInRadians(), 15, drawMenu_);
		}
	};
};