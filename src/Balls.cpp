#include "Balls.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

Balls::Balls() : 
	numScored_(0)
{
	points_[Ball::zero]       = vec(sizestenaLEFT + sizeXpol / 4                        , sizestenaUP + sizeYpol / 2             );
	points_[Ball::thirst]     = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 2 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 2 * RShari);
	points_[Ball::second]     = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 2 * RShari);
	points_[Ball::third]      = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 3 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 1 * RShari);
	points_[Ball::fourth]     = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 2 * RShari);
	points_[Ball::fifth]      = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 4 * RShari);
	points_[Ball::sixth]      = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 3 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 3 * RShari);
	points_[Ball::seventh]    = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 1 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 1 * RShari);
	points_[Ball::eighth]     = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 2 * cor3 * RShari, sizestenaUP + sizeYpol / 2             );
	points_[Ball::nineth]     = vec(sizestenaLEFT + sizeXpol * 3 / 4                  , sizestenaUP + sizeYpol / 2             );
	points_[Ball::tenth]      = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 3 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 1 * RShari);
	points_[Ball::eleventh]   = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 4 * RShari);
	points_[Ball::twelfth]    = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 1 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 1 * RShari);
	points_[Ball::thirteenth] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2             );
	points_[Ball::fourteenth] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 3 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 3 * RShari);
	points_[Ball::fifteenth]  = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 2 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 2 * RShari);

	memset(&speeds_,0, sizeof(speeds_));
	memset(&scored_, FALSE, sizeof(scored_));
}

Balls::~Balls()
{}

BOOL Balls::stopped() const
{
	for (size_t i = 0; i < NUMBER_OF_BALLS; i++) if (speeds_[i].getL() != 0) return false;

	return true;
}

VOID Balls::repulsion()
{
	for  (size_t i = 0; i < NUMBER_OF_BALLS - 1; i++)
	{
		for (size_t j = i + 1; j < NUMBER_OF_BALLS; j++)
		{
			if ((pow(points_[i].getX() - points_[j].getX(), 2) + pow(points_[i].getY() - points_[j].getY(), 2) <= 4 * RShari * RShari)
				&& (pow(points_[i].getX() - points_[j].getX(), 2) + pow(points_[i].getY() - points_[j].getY(), 2))        //надо сделать чтобы после синкосов они удалялись
				>= (pow((points_[i].getX() + speeds_[i].getX()) - (points_[j].getX() + speeds_[j].getX()), 2) + pow((points_[i].getY() + speeds_[i].getY()) - (points_[j].getY() + speeds_[j].getY()), 2)))
			{

				double tmp_xi = 0, tmp_yi = 0;
				double tmp_xj = 0, tmp_yj = 0;

				double ug = 10000000;
				double phi = M_PI_4;
				if (points_[i].getX() != points_[j].getX())
				{
					ug = (points_[i].getY() - points_[j].getY()) / (points_[i].getX() - points_[j].getX());

					phi = atan(ug);
				}

				double vx_j = ( speeds_[i].getX() * cos(phi) + speeds_[i].getY() * sin(phi));
				double vy_i = (-speeds_[i].getX() * sin(phi) + speeds_[i].getY() * cos(phi));

				double vx_i = ( speeds_[j].getX() * cos(phi) + speeds_[j].getY() * sin(phi));
				double vy_j = (-speeds_[j].getX() * sin(phi) + speeds_[j].getY() * cos(phi));

				tmp_xi = ( vx_i * cos(-phi) + vy_i * sin(-phi));
				tmp_yi = (-vx_i * sin(-phi) + vy_i * cos(-phi));

				tmp_xj = ( vx_j * cos(-phi) + vy_j * sin(-phi));
				tmp_yj = (-vx_j * sin(-phi) + vy_j * cos(-phi));

				//double slg_car = 0;
				//double slg_new = 0;

				if (sqrt(pow(points_[i].getX() - points_[j].getX(), 2) + pow(points_[i].getY() - points_[j].getY(), 2))
					>= sqrt(pow((points_[i].getX() + 25 * tmp_xi) - (points_[j].getX() + 25 * tmp_xj), 2) + pow((points_[i].getY() + 25 * tmp_yi) - (points_[j].getY() + 25 * tmp_yj), 2)))
				{
					//slg_car = sqrt(pow(t[i].x - t[j].x, 2) + pow(t[i].y - t[j].y, 2));

					//slg_new = sqrt(pow((t[i].x + 25*clgxi) - (t[j].x + 25*clgxj), 2) + pow((t[i].y + 25*clgyi) - (t[j].y + 25*clgyj), 2));
				}
				else
				{
					speeds_[j].setX(tmp_xj);
					speeds_[j].setY(tmp_yj);

					speeds_[i].setX(tmp_xi);
					speeds_[i].setY(tmp_yi);
				}

			}
		}
	}

}

VOID Balls::repulsionFrom()
{
	for (size_t i = 0; i < NUMBER_OF_BALLS - 1; i++)
	{
		for (size_t j = 0; j < ColvoCenterDugLuz; j++)
		{
			if ((pow(points_[i].getX() - CenterDugLuz[j].getX(), 2) + pow(points_[i].getY() - CenterDugLuz[j].getY(), 2) <= (RShari + RDugLuz) * (RShari + RDugLuz))
				&& (pow(points_[i].getX() - CenterDugLuz[j].getX(), 2) + pow(points_[i].getY() - CenterDugLuz[j].getY(), 2))        //надо сделать чтобы после синкосов они уддалялись
				>= (pow((points_[i].getX() + speeds_[i].getX()) - (CenterDugLuz[j].getX()), 2) + pow((points_[i].getY() + speeds_[i].getY()) - (CenterDugLuz[j].getY()), 2)))
			{

				double tmp_xi = 0;
				double tmp_yi = 0;
				//double clgxj = 0;
				//double clgyj = 0;

				double ug = 10000000;
				double phi = M_PI_4;
				if (points_[i].getX() != CenterDugLuz[j].getX())
				{
					ug = (points_[i].getY() - CenterDugLuz[j].getY()) / (points_[i].getX() - CenterDugLuz[j].getX());

					phi = atan(ug);
				}

				double vx_i = -(speeds_[i].getX() * cos(phi) + speeds_[i].getY() * sin(phi));
				double vy_i = (-speeds_[i].getX() * sin(phi) + speeds_[i].getY() * cos(phi));

				tmp_xi = ( vx_i * cos(-phi) + vy_i * sin(-phi));
				tmp_yi = (-vx_i * sin(-phi) + vy_i * cos(-phi));
				 
				if (sqrt(pow(points_[i].getX() - CenterDugLuz[j].getX(), 2) + pow(points_[i].getY() - CenterDugLuz[j].getY(), 2))
					>= sqrt(pow((points_[i].getX() + 25 * tmp_xi) - (CenterDugLuz[j].getX()), 2) + pow((points_[i].getY() + 25 * tmp_yi) - (CenterDugLuz[j].getY()), 2)))
				{
				}
				else
				{
					speeds_[i].setX(tmp_xi);
					speeds_[i].setY(tmp_yi);
				}

			}
		}
	}
}

VOID Balls::restart()
{
	numScored_ = 0;

	points_[Ball::zero]       = vec(sizestenaLEFT + sizeXpol / 4                        , sizestenaUP + sizeYpol / 2             );
	points_[Ball::thirst]     = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 2 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 2 * RShari);
	points_[Ball::second]     = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 2 * RShari);
	points_[Ball::third]      = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 3 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 1 * RShari);
	points_[Ball::fourth]     = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 2 * RShari);
	points_[Ball::fifth]      = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 4 * RShari);
	points_[Ball::sixth]      = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 3 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 3 * RShari);
	points_[Ball::seventh]    = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 1 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 1 * RShari);
	points_[Ball::eighth]     = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 2 * cor3 * RShari, sizestenaUP + sizeYpol / 2             );
	points_[Ball::nineth]     = vec(sizestenaLEFT + sizeXpol * 3 / 4                  , sizestenaUP + sizeYpol / 2             );
	points_[Ball::tenth]      = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 3 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 1 * RShari);
	points_[Ball::eleventh]   = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 4 * RShari);
	points_[Ball::twelfth]    = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 1 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 1 * RShari);
	points_[Ball::thirteenth] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2             );
	points_[Ball::fourteenth] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 3 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 3 * RShari);
	points_[Ball::fifteenth]  = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 2 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 2 * RShari);

	memset(&speeds_,0, sizeof(speeds_));
	memset(&scored_, FALSE, sizeof(scored_));
}

VOID Balls::move()
{
	int nat = 0;
	
	while (nat < NUMBER_OF_BALLS)
	{
		points_[nat].setX(points_[nat].getX() + speeds_[nat].getX());

		if (points_[nat].getX() >= sizeX - RShari - sizestenaRIGHT && points_[nat].getX() <= sizeX - RShari - sizestenaRIGHT + 2 * RDugLuz &&
			(((points_[nat].getY() > sizestenaUP + (Ru + RDugLuz)) && (points_[nat].getY() < sizestenaUP + sizeYpol - (Ru + RDugLuz)))/* ||
																												(( t[nat].y < sizestenaUP + sizeYpol - (RLuz + RDugLuz)) && (t[nat].y > sizestenaUP + sizeYpol/2 + (RLuz + RDugLuz)))*/))
		{
			points_[nat].setX(sizeX - RShari - sizestenaRIGHT);
			speeds_[nat].setX(-speeds_[nat].getX());
		}
		
		if (points_[nat].getX() <= RShari + sizestenaLEFT && points_[nat].getX() >= RShari + sizestenaLEFT - 2 * RDugLuz &&
			(((points_[nat].getY() > sizestenaUP + (Ru + RDugLuz)) && (points_[nat].getY() < sizestenaUP + sizeYpol - (Ru + RDugLuz))))) // || (( t[nat].y < sizestenaUP + sizeYpol - (RLuz + RDugLuz)) && (t[nat].y > sizestenaUP + sizeYpol/2 + (RLuz + RDugLuz)))))
		{
			points_[nat].setX(RShari + sizestenaLEFT);
			speeds_[nat].setX(-speeds_[nat].getX());
		}

		points_[nat].setY(points_[nat].getY() + speeds_[nat].getY());

		if (points_[nat].getY() >= sizeY - RShari - sizestenaDOWN && points_[nat].getY() <= sizeY - RShari - sizestenaDOWN + 2 * RDugLuz &&
			(((points_[nat].getX() > sizestenaLEFT + (Ru + RDugLuz)) && (points_[nat].getX() < sizestenaLEFT + sizeXpol / 2 - (RLuz + RDugLuz))) ||
			((points_[nat].getX() < sizestenaLEFT + sizeXpol - (Ru + RDugLuz)) && (points_[nat].getX() > sizestenaLEFT + sizeXpol / 2 + (RLuz + RDugLuz)))))
		{
			points_[nat].setY(sizeY - RShari - sizestenaDOWN);
			speeds_[nat].setY(-speeds_[nat].getY());
		}

		if (points_[nat].getY() <= RShari + sizestenaUP && points_[nat].getY() >= RShari + sizestenaUP - 2 * RDugLuz &&
			(((points_[nat].getX() > sizestenaLEFT + (Ru + RDugLuz)) && (points_[nat].getX() < sizestenaLEFT + sizeXpol / 2 - (RLuz + RDugLuz))) ||
			((points_[nat].getX() < sizestenaLEFT + sizeXpol - (Ru + RDugLuz)) && (points_[nat].getX() > sizestenaLEFT + sizeXpol / 2 + (RLuz + RDugLuz)))))
		{
			points_[nat].setY(RShari + sizestenaUP);
			speeds_[nat].setY(-speeds_[nat].getY());
		}

		speeds_[nat].setLK();

		if (fabs(speeds_[nat].getL()) >= 0.08) speeds_[nat] -= 0.08;
		else speeds_[nat] = vec(0, 0);

		//{   проверки попадания в лузы

		if ((points_[nat].getX() - sizestenaLEFT + RDugLuz) * (points_[nat].getX() - sizestenaLEFT + RDugLuz) +
			(points_[nat].getY() - sizestenaUP + RDugLuz) * (points_[nat].getY() - sizestenaUP + RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			points_[nat] = vec(numScored_ * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			speeds_[nat] = vec(0, 0);
			numScored_++;
			scored_[nat] = TRUE;
		}

		if ((points_[nat].getY() - sizeY + sizestenaDOWN - RDugLuz) * (points_[nat].getY() - sizeY + sizestenaDOWN - RDugLuz) +
			(points_[nat].getX() - sizestenaLEFT + RDugLuz) * (points_[nat].getX() - sizestenaLEFT + RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			points_[nat] = vec(numScored_ * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			speeds_[nat] = vec(0, 0);
			numScored_++;
			scored_[nat] = TRUE;
		}

		if ((points_[nat].getY() - sizeY + sizestenaDOWN - RDugLuz) * (points_[nat].getY() - sizeY + sizestenaDOWN - RDugLuz) +
			(points_[nat].getX() - sizeX + sizestenaRIGHT - RDugLuz) * (points_[nat].getX() - sizeX + sizestenaRIGHT - RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			points_[nat] = vec(numScored_ * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			speeds_[nat] = vec(0, 0);
			numScored_++;
			scored_[nat] = TRUE;
		}

		if ((points_[nat].getY() - sizestenaUP + RDugLuz) * (points_[nat].getY() - sizestenaUP + RDugLuz) +
			(points_[nat].getX() - sizeX + sizestenaRIGHT - RDugLuz) * (points_[nat].getX() - sizeX + sizestenaRIGHT - RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			points_[nat] = vec(numScored_ * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			speeds_[nat] = vec(0, 0);
			numScored_++;
			scored_[nat] = TRUE;
		}

		if ((points_[nat].getX() - sizestenaLEFT - sizeXpol / 2) * (points_[nat].getX() - sizestenaLEFT - sizeXpol / 2) +
			(points_[nat].getY() + sizestenaDOWN - sizeY - RDugLuz) * (points_[nat].getY() + sizestenaDOWN - sizeY - RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			points_[nat] = vec(numScored_ * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			speeds_[nat] = vec(0, 0);
			numScored_++;
			scored_[nat] = TRUE;
		}

		if ((points_[nat].getX() - sizestenaLEFT - sizeXpol / 2) * (points_[nat].getX() - sizestenaLEFT - sizeXpol / 2) +
			(points_[nat].getY() - sizestenaUP + RDugLuz) * (points_[nat].getY()- sizestenaUP + RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			points_[nat] = vec(numScored_ * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			speeds_[nat] = vec(0, 0);
			numScored_++;
			scored_[nat] = TRUE;
		}
		
		//}
		nat++;
	}

	if(scored_[0]) numScored_--;
	if(scored_[8]) numScored_--;

	repulsionFrom();
	repulsion();
}

VOID Balls::draw(Graphics *graphics, Image *images[]) const
{ 
	ImageAttributes imAttr;
	imAttr.SetColorKey(COLOR_KEY, COLOR_KEY);
	for(size_t i = 0; i < NUMBER_OF_BALLS; i++)
		graphics->DrawImage(images[i], Rect(static_cast<INT>(points_[i].getX()) - RShari, static_cast<INT>(points_[i].getY()) - RShari, 2 * RShari, 2 * RShari), 0, 0, 2 * RShari, 2 * RShari, Unit::UnitPixel, &imAttr, 0); 
}


