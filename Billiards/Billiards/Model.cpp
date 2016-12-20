#include "stdafx.h"
#include "Model.hpp"

namespace Billiards
{
	namespace model
	{
		Model::Model(HWND hWnd, CONST UPOINT &rWindowSize) :
			graphics_(hWnd, rWindowSize),
			physics_(),
			drawCue_(TRUE),
			drawMenu_(FALSE)			
		{
		}

		Model::~Model()
		{
		}

		inline VOID Model::setCueStatus(BOOL status) { drawCue_ = status; }

		inline VOID Model::setMenuStatus(BOOL status) { drawMenu_ = status; }

		VOID Model::doModel(/*CONST POINT & rMouse*/)
		{
			physics_.doPhysics(POINT(), drawCue_);
			graphics_.doGraphics(physics_.ballPosition_, drawCue_, 0, 15, drawMenu_);
		}
	};
};