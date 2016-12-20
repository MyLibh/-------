#pragma once

#ifndef __MODELS_HPP_INCLUDED__
#define __MODELS_HPP_INCLUDED__

#include "stdafx.h"
#include "Graphics.hpp"
#include "Physics.hpp"

namespace Billiards
{
	namespace model
	{
		class Model : private Uncopyable
		{
		private:
			BOOL drawCue_;
			BOOL drawMenu_;

			physics::Physics   physics_;
			graphics::Graphics graphics_;

		protected: 
			inline VOID setCueStatus(BOOL);
			inline VOID setMenuStatus(BOOL);
			
		public:
			explicit Model(HWND, CONST UPOINT&);
			~Model();
			
			VOID doModel(/*CONST POINT&*/);
		};
	};
};

#endif // __MODELS_HPP_INCLUDED__