#pragma once

#ifndef __MODELS_HPP_INCLUDED__
#define __MODELS_HPP_INCLUDED__

#include "Variables.hpp"
#include "Graphics.hpp"
#include "Physics.hpp"

namespace Billiards
{
	namespace models
	{
		class Models : private graphics::Graphics, private physics::Physics
		{
		private:
			BOOL drawCue_;
			BOOL drawMenu_;

		protected: 
			inline VOID setCueStatus(BOOL);
			inline VOID setMenuStatus(BOOL);
			
		public:
			explicit Models(HWND, CONST UPOINT&);
			~Models();VOID doModels(CONST POINT&);
		};
	};
};

#endif // __MODELS_HPP_INCLUDED__