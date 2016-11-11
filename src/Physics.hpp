#pragma once

#ifndef __PHYSICS_HPP_INCLUDED__
#define __PHYSICS_HPP_INCLUDED__

#include "Variables.hpp"
#include "Vector.hpp"

namespace Billiards 
{
	namespace physics
	{
		CONST vec CenterDugLuz[ColvoCenterDugLuz] =
		{ 
			vec(sizeX - sizestenaRIGHT + RDugLuz,            sizestenaUP + Ru + RDugLuz),
			vec(sizeX - sizestenaRIGHT + RDugLuz, sizeYpol + sizestenaUP - Ru - RDugLuz),
			vec(        sizestenaLEFT  - RDugLuz,            sizestenaUP + Ru + RDugLuz),
			vec(        sizestenaLEFT  - RDugLuz, sizeYpol + sizestenaUP - Ru - RDugLuz),
			vec(sizestenaLEFT + Ru + RDugLuz, sizeY - sizestenaDOWN + RDugLuz),
			vec(sizeXpol / 2 + sizestenaLEFT - RLuz - RDugLuz, sizeY - sizestenaDOWN + RDugLuz),
			vec(sizeXpol + sizestenaLEFT - Ru - RDugLuz, sizeY - sizestenaDOWN + RDugLuz),
			vec(sizeXpol / 2 + sizestenaLEFT + RLuz + RDugLuz, sizeY - sizestenaDOWN + RDugLuz),
			vec(sizestenaLEFT + Ru + RDugLuz,                        sizestenaUP - RDugLuz),
			vec(sizeXpol / 2 + sizestenaLEFT - RLuz - RDugLuz,            sizestenaUP - RDugLuz),
			vec(sizeXpol + sizestenaLEFT - Ru - RDugLuz,                  sizestenaUP - RDugLuz),
			vec(sizeXpol / 2 + sizestenaLEFT + RLuz + RDugLuz,            sizestenaUP - RDugLuz)
		};

		enum Ball
		{
			wrong      = -1,
			zero       =  0,
			thirst     =  1,
			second     =  2,
			third      =  3,
			fourth     =  4,
			fifth      =  5,
			sixth      =  6,
			seventh    =  7,
			eighth     =  8,
			nineth     =  9,
			tenth      = 10,
			eleventh   = 11,
			twelfth    = 12,
			thirteenth = 13,
			fourteenth = 14,
			fifteenth  = 15,
		};

		class Physics : private Uncopyable
		{
		private:
			vec    mouse_;
			//vec    auxilaryLine_;

			vec    ballPosition_[NUMBER_OF_BALLS];
			vec    ballSpeed_[NUMBER_OF_BALLS];
			BOOL   ballStatus_[NUMBER_OF_BALLS];

			WORD   ballScoredNumber_;
			double cueAngle_;

			VOID repulsion();
			VOID repulsionFrom();
			VOID moveBalls();
	
			VOID rotateCue(CONST POINT&);

		protected: 
			//inline CONST vec    &getMouse()             const;
			//inline CONST vec    &getAuxLine()           const;
 			inline CONST vec    &getBallPosition(WORD)  const;
			inline CONST vec    &getBallsPosition()     const;
			inline CONST vec    &getBallSpeed(WORD)     const;
			inline       BOOL    getBallStatus(WORD)    const;
			inline CONST BOOL   &getBallsStatus()       const;
			inline       double  getCueAngleInRadians() const;

			inline VOID setBallPosition(CONST vec&, WORD);
			inline VOID setBallSpeed(CONST vec&, WORD);
			inline VOID setBallStatus(BOOL, WORD);

			inline BOOL ballsStopped() const;
			inline VOID reset();			
				   VOID doPhysics(CONST POINT&, BOOL = TRUE);

		public:
			explicit Physics();
			~Physics();
		};
	};
};

#endif // __PHYSICS_HPP_INCLUDED__