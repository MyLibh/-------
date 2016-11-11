#include "Physics.hpp"

namespace Billiards
{
	namespace physics
	{
		Physics::Physics() :
			mouse_()
		{ reset(); }

		Physics::~Physics()
		{
		}

		VOID Physics::repulsion()
		{
			for (size_t i = 0; i < NUMBER_OF_BALLS - 1; i++)
			{
				for (size_t j = i + 1; j < NUMBER_OF_BALLS; j++)
				{
					if ((pow(ballPosition_[i].getX() - ballPosition_[j].getX(), 2) + pow(ballPosition_[i].getY() - ballPosition_[j].getY(), 2) <= 4 * RShari * RShari)
						&& (pow(ballPosition_[i].getX() - ballPosition_[j].getX(), 2) + pow(ballPosition_[i].getY() - ballPosition_[j].getY(), 2))       
						>= (pow((ballPosition_[i].getX() + ballSpeed_[i].getX()) - (ballPosition_[j].getX() + ballSpeed_[j].getX()), 2) + pow((ballPosition_[i].getY() + ballSpeed_[i].getY()) - (ballPosition_[j].getY() + ballSpeed_[j].getY()), 2)))
					{

						double tmp_xi = 0, tmp_yi = 0;
						double tmp_xj = 0, tmp_yj = 0;

						double ug = 10000000;
						double phi = M_PI_4;
						if (ballPosition_[i].getX() != ballPosition_[j].getX())
						{
							ug = (ballPosition_[i].getY() - ballPosition_[j].getY()) / (ballPosition_[i].getX() - ballPosition_[j].getX());

							phi = atan(ug);
						}

						double vx_j = ( ballSpeed_[i].getX() * cos(phi) + ballSpeed_[i].getY() * sin(phi));
						double vy_i = (-ballSpeed_[i].getX() * sin(phi) + ballSpeed_[i].getY() * cos(phi));

						double vx_i = ( ballSpeed_[j].getX() * cos(phi) + ballSpeed_[j].getY() * sin(phi));
						double vy_j = (-ballSpeed_[j].getX() * sin(phi) + ballSpeed_[j].getY() * cos(phi));

						tmp_xi = ( vx_i * cos(-phi) + vy_i * sin(-phi));
						tmp_yi = (-vx_i * sin(-phi) + vy_i * cos(-phi));

						tmp_xj = ( vx_j * cos(-phi) + vy_j * sin(-phi));
						tmp_yj = (-vx_j * sin(-phi) + vy_j * cos(-phi));

						if (sqrt(pow(ballPosition_[i].getX() - ballPosition_[j].getX(), 2) + pow(ballPosition_[i].getY() - ballPosition_[j].getY(), 2))
							>= sqrt(pow((ballPosition_[i].getX() + 25 * tmp_xi) - (ballPosition_[j].getX() + 25 * tmp_xj), 2) + pow((ballPosition_[i].getY() + 25 * tmp_yi) - (ballPosition_[j].getY() + 25 * tmp_yj), 2)))
						{
							//slg_car = sqrt(pow(t[i].x - t[j].x, 2) + pow(t[i].y - t[j].y, 2));

							//slg_new = sqrt(pow((t[i].x + 25*clgxi) - (t[j].x + 25*clgxj), 2) + pow((t[i].y + 25*clgyi) - (t[j].y + 25*clgyj), 2));
						}
						else
						{
							ballSpeed_[j].setX(tmp_xj);
							ballSpeed_[j].setY(tmp_yj);

							ballSpeed_[i].setX(tmp_xi);
							ballSpeed_[i].setY(tmp_yi);
						}

					}
				}
			}
		}

		VOID Physics::repulsionFrom()
		{
			for (size_t i = 0; i < NUMBER_OF_BALLS - 1; i++)
			{
				for (size_t j = 0; j < ColvoCenterDugLuz; j++)
				{
					if ((pow(ballPosition_[i].getX() - CenterDugLuz[j].getX(), 2) + pow(ballPosition_[i].getY() - CenterDugLuz[j].getY(), 2) <= (RShari + RDugLuz) * (RShari + RDugLuz))
						&& (pow(ballPosition_[i].getX() - CenterDugLuz[j].getX(), 2) + pow(ballPosition_[i].getY() - CenterDugLuz[j].getY(), 2))     
						>= (pow((ballPosition_[i].getX() + ballSpeed_[i].getX()) - (CenterDugLuz[j].getX()), 2) + pow((ballPosition_[i].getY() + ballSpeed_[i].getY()) - (CenterDugLuz[j].getY()), 2)))
					{

						double tmp_xi = 0;
						double tmp_yi = 0;

						double ug = 10000000;
						double phi = M_PI_4;
						if (ballPosition_[i].getX() != CenterDugLuz[j].getX())
						{
							ug = (ballPosition_[i].getY() - CenterDugLuz[j].getY()) / (ballPosition_[i].getX() - CenterDugLuz[j].getX());

							phi = atan(ug);
						}

						double vx_i = -(ballSpeed_[i].getX() * cos(phi) + ballSpeed_[i].getY() * sin(phi));
						double vy_i = (-ballSpeed_[i].getX() * sin(phi) + ballSpeed_[i].getY() * cos(phi));

						tmp_xi = ( vx_i * cos(-phi) + vy_i * sin(-phi));
						tmp_yi = (-vx_i * sin(-phi) + vy_i * cos(-phi));
				 
						if (sqrt(pow(ballPosition_[i].getX() - CenterDugLuz[j].getX(), 2) + pow(ballPosition_[i].getY() - CenterDugLuz[j].getY(), 2))
							>= sqrt(pow((ballPosition_[i].getX() + 25 * tmp_xi) - (CenterDugLuz[j].getX()), 2) + pow((ballPosition_[i].getY() + 25 * tmp_yi) - (CenterDugLuz[j].getY()), 2)))
						{
						}
						else
						{
							ballSpeed_[i].setX(tmp_xi);
							ballSpeed_[i].setY(tmp_yi);
						}

					}
				}
			}
		}

		VOID Physics::moveBalls()
		{
		}

		VOID Physics::rotateCue(CONST POINT &rMouse)
		{
			mouse_.setX(rMouse.x);
			mouse_.setY(rMouse.y);

			cueAngle_ = (mouse_ - ballPosition_[0]).toDegrees();
		}

		inline CONST vec& Physics::getBallPosition(WORD index) const
		{
			if(index >= NUMBER_OF_BALLS) throw __FUNCTION__;
			else return ballPosition_[index];
		}

		inline CONST vec& Physics::getBallsPosition() const { return *ballPosition_; }

		inline CONST vec& Physics::getBallSpeed(WORD index) const
		{
			if(index >= NUMBER_OF_BALLS) throw __FUNCTION__;
			else return ballSpeed_[index];
		}

		inline BOOL Physics::getBallStatus(WORD index) const
		{
			if(index >= NUMBER_OF_BALLS) throw __FUNCTION__;
			else return ballStatus_[index];
		}

		inline CONST BOOL& Physics::getBallsStatus() const { return *ballStatus_; }

		inline double Physics::getCueAngleInRadians() const { return cueAngle_ * M_PI / 180; }

		inline VOID Physics::setBallPosition(CONST vec &rNewPosition, WORD index) 
		{ 
			if(index >= NUMBER_OF_BALLS) throw __FUNCTION__;
			else ballPosition_[index] = rNewPosition; 
		}

		inline VOID Physics::setBallSpeed(CONST vec &rNewSpeed, WORD index) 
		{ 
			if(index >= NUMBER_OF_BALLS) throw __FUNCTION__;
			else ballSpeed_[index] = rNewSpeed; 
		}

		inline VOID Physics::setBallStatus(BOOL newStatus, WORD index) 
		{ 
			if(index >= NUMBER_OF_BALLS) throw __FUNCTION__;
			else ballStatus_[index] = newStatus; 
		}

		inline BOOL Physics::ballsStopped() const
		{
			for (size_t i = 0; i < NUMBER_OF_BALLS; i++) 
				if (ballSpeed_[i].getL() != 0) return FALSE;

			return TRUE;
		}

		inline VOID Physics::reset()
		{
			ballPosition_[Ball::zero]       = vec(sizestenaLEFT + sizeXpol / 4                        , sizestenaUP + sizeYpol / 2             );
			ballPosition_[Ball::thirst]     = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 2 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 2 * RShari);
			ballPosition_[Ball::second]     = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 2 * RShari);
			ballPosition_[Ball::third]      = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 3 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 1 * RShari);
			ballPosition_[Ball::fourth]     = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 2 * RShari);
			ballPosition_[Ball::fifth]      = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 4 * RShari);
			ballPosition_[Ball::sixth]      = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 3 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 3 * RShari);
			ballPosition_[Ball::seventh]    = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 1 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 1 * RShari);
			ballPosition_[Ball::eighth]     = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 2 * cor3 * RShari, sizestenaUP + sizeYpol / 2             );
			ballPosition_[Ball::nineth]     = vec(sizestenaLEFT + sizeXpol * 3 / 4                  , sizestenaUP + sizeYpol / 2             );
			ballPosition_[Ball::tenth]      = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 3 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 1 * RShari);
			ballPosition_[Ball::eleventh]   = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 4 * RShari);
			ballPosition_[Ball::twelfth]    = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 1 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 1 * RShari);
			ballPosition_[Ball::thirteenth] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2             );
			ballPosition_[Ball::fourteenth] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 3 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 3 * RShari);
			ballPosition_[Ball::fifteenth]  = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 2 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 2 * RShari);

			memset(&ballSpeed_, 0, sizeof(ballSpeed_));
			memset(&ballStatus_, FALSE, sizeof(ballStatus_));

			ballScoredNumber_ = 0;
			cueAngle_         = 0;
		}

		VOID Physics::doPhysics(CONST POINT &rMouse, BOOL cueEnable /* = TRUE */)
		{
			moveBalls();
			if(cueEnable) rotateCue(rMouse);
		}
	};
};