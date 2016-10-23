#include "Balls.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

Balls::Balls()
{
	golled = 0;

	//t[ 0] = vec(300, 100);
	t[ 0] = vec(sizestenaLEFT + sizeXpol / 4                        , sizestenaUP + sizeYpol / 2             );
	t[ 1] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 2 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 2 * RShari);
	t[ 2] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 2 * RShari);
	t[ 3] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 3 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 1 * RShari);
	t[ 4] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 2 * RShari);
	t[ 5] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 4 * RShari);
	t[ 6] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 3 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 3 * RShari);
	t[ 7] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 1 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 1 * RShari);
	t[ 8] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 2 * cor3 * RShari, sizestenaUP + sizeYpol / 2             );
	t[ 9] = vec(sizestenaLEFT + sizeXpol * 3 / 4                  , sizestenaUP + sizeYpol / 2             );
	t[10] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 3 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 1 * RShari);
	t[11] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 4 * RShari);
	t[12] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 1 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 1 * RShari);
	t[13] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 4 * cor3 * RShari, sizestenaUP + sizeYpol / 2             );
	t[14] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 3 * cor3 * RShari, sizestenaUP + sizeYpol / 2 + 3 * RShari);
	t[15] = vec(sizestenaLEFT + sizeXpol * 3 / 4 + 2 * cor3 * RShari, sizestenaUP + sizeYpol / 2 - 2 * RShari);

	for (size_t i = 1; i < NUMBER_OF_BALLS; i++) v[i] = vec(0, 0);
	//v[0] = vec(5, -3.7);
	//v[0] = vec(15, 1.7);
	//v[0] = vec(15, -4.2);
	//v[0] = vec(5, -3.74);
	v[0] = vec(19, 1);
}

Balls::~Balls()
{}

BOOL Balls::stopped() const
{
	for (size_t i = 0; i < NUMBER_OF_BALLS; i++) if (v[i].getL() != 0) return false;

	return true;
}

VOID Balls::repulsion()
{
	for  (size_t i = 0; i < NUMBER_OF_BALLS - 1; i++)
	{
		for (size_t j = i + 1; j < NUMBER_OF_BALLS; j++)
		{
			if ((pow(t[i].getX() - t[j].getX(), 2) + pow(t[i].getY() - t[j].getY(), 2) <= 4 * RShari * RShari)
				&& (pow(t[i].getX() - t[j].getX(), 2) + pow(t[i].getY() - t[j].getY(), 2))        //надо сделать чтобы после синкосов они удалялись
				>= (pow((t[i].getX() + v[i].getX()) - (t[j].getX() + v[j].getX()), 2) + pow((t[i].getY() + v[i].getY()) - (t[j].getY() + v[j].getY()), 2)))
			{

				double tmp_xi = 0, tmp_yi = 0;
				double tmp_xj = 0, tmp_yj = 0;

				double ug = 10000000;
				double phi = M_PI_4;
				if (t[i].getX() != t[j].getX())
				{
					ug = (t[i].getY() - t[j].getY()) / (t[i].getX() - t[j].getX());

					phi = atan(ug);
				}

				double vx_j = ( v[i].getX() * cos(phi) + v[i].getY() * sin(phi));
				double vy_i = (-v[i].getX() * sin(phi) + v[i].getY() * cos(phi));

				double vx_i = ( v[j].getX() * cos(phi) + v[j].getY() * sin(phi));
				double vy_j = (-v[j].getX() * sin(phi) + v[j].getY() * cos(phi));

				tmp_xi = ( vx_i * cos(-phi) + vy_i * sin(-phi));
				tmp_yi = (-vx_i * sin(-phi) + vy_i * cos(-phi));

				tmp_xj = ( vx_j * cos(-phi) + vy_j * sin(-phi));
				tmp_yj = (-vx_j * sin(-phi) + vy_j * cos(-phi));

				//double slg_car = 0;
				//double slg_new = 0;

				if (sqrt(pow(t[i].getX() - t[j].getX(), 2) + pow(t[i].getY() - t[j].getY(), 2))
					>= sqrt(pow((t[i].getX() + 25 * tmp_xi) - (t[j].getX() + 25 * tmp_xj), 2) + pow((t[i].getY() + 25 * tmp_yi) - (t[j].getY() + 25 * tmp_yj), 2)))
				{
					//slg_car = sqrt(pow(t[i].x - t[j].x, 2) + pow(t[i].y - t[j].y, 2));

					//slg_new = sqrt(pow((t[i].x + 25*clgxi) - (t[j].x + 25*clgxj), 2) + pow((t[i].y + 25*clgyi) - (t[j].y + 25*clgyj), 2));
				}
				else
				{
					v[j].setX(tmp_xj);
					v[j].setY(tmp_yj);

					v[i].setX(tmp_xi);
					v[i].setY(tmp_yi);
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
			if ((pow(t[i].getX() - CenterDugLuz[j].getX(), 2) + pow(t[i].getY() - CenterDugLuz[j].getY(), 2) <= (RShari + RDugLuz)*(RShari + RDugLuz))
				&& (pow(t[i].getX() - CenterDugLuz[j].getX(), 2) + pow(t[i].getY() - CenterDugLuz[j].getY(), 2))        //надо сделать чтобы после синкосов они уддалялись
				>= (pow((t[i].getX() + v[i].getX()) - (CenterDugLuz[j].getX()), 2) + pow((t[i].getY() + v[i].getY()) - (CenterDugLuz[j].getY()), 2)))
			{

				double tmp_xi = 0;
				double tmp_yi = 0;
				//double clgxj = 0;
				//double clgyj = 0;

				double ug = 10000000;
				double phi = M_PI_4;
				if (t[i].getX() != CenterDugLuz[j].getX())
				{
					ug = (t[i].getY() - CenterDugLuz[j].getY()) / (t[i].getX() - CenterDugLuz[j].getX());

					phi = atan(ug);
				}

				double vx_i = -(v[i].getX() * cos(phi) + v[i].getY() * sin(phi));
				double vy_i = (-v[i].getX() * sin(phi) + v[i].getY() * cos(phi));

				tmp_xi = ( vx_i * cos(-phi) + vy_i * sin(-phi));
				tmp_yi = (-vx_i * sin(-phi) + vy_i * cos(-phi));
				 
				if (sqrt(pow(t[i].getX() - CenterDugLuz[j].getX(), 2) + pow(t[i].getY() - CenterDugLuz[j].getY(), 2))
					>= sqrt(pow((t[i].getX() + 25 * tmp_xi) - (CenterDugLuz[j].getX()), 2) + pow((t[i].getY() + 25 * tmp_yi) - (CenterDugLuz[j].getY()), 2)))
				{
				}
				else
				{
					v[i].setX(tmp_xi);
					v[i].setY(tmp_yi);
				}

			}
		}
	}
}

VOID Balls::move()
{
	int nat = 0;
	
	while (nat < NUMBER_OF_BALLS)
	{
		t[nat].setX(t[nat].getX() + v[nat].getX());

		if (t[nat].getX() >= sizeX - RShari - sizestenaRIGHT && t[nat].getX() <= sizeX - RShari - sizestenaRIGHT + 2 * RDugLuz &&
			(((t[nat].getY() > sizestenaUP + (Ru + RDugLuz)) && (t[nat].getY() < sizestenaUP + sizeYpol - (Ru + RDugLuz)))/* ||
																												(( t[nat].y < sizestenaUP + sizeYpol - (RLuz + RDugLuz)) && (t[nat].y > sizestenaUP + sizeYpol/2 + (RLuz + RDugLuz)))*/))
		{
			t[nat].setX(sizeX - RShari - sizestenaRIGHT);
			v[nat].setX(-v[nat].getX());
		}
		
		if (t[nat].getX() <= RShari + sizestenaLEFT && t[nat].getX() >= RShari + sizestenaLEFT - 2 * RDugLuz &&
			(((t[nat].getY() > sizestenaUP + (Ru + RDugLuz)) && (t[nat].getY() < sizestenaUP + sizeYpol - (Ru + RDugLuz))))) // || (( t[nat].y < sizestenaUP + sizeYpol - (RLuz + RDugLuz)) && (t[nat].y > sizestenaUP + sizeYpol/2 + (RLuz + RDugLuz)))))
		{
			t[nat].setX(RShari + sizestenaLEFT);
			v[nat].setX(-v[nat].getX());
		}

		t[nat].setY(t[nat].getY() + v[nat].getY());

		if (t[nat].getY() >= sizeY - RShari - sizestenaDOWN && t[nat].getY() <= sizeY - RShari - sizestenaDOWN + 2 * RDugLuz &&
			(((t[nat].getX() > sizestenaLEFT + (Ru + RDugLuz)) && (t[nat].getX() < sizestenaLEFT + sizeXpol / 2 - (RLuz + RDugLuz))) ||
			((t[nat].getX() < sizestenaLEFT + sizeXpol - (Ru + RDugLuz)) && (t[nat].getX() > sizestenaLEFT + sizeXpol / 2 + (RLuz + RDugLuz)))))
		{
			t[nat].setY(sizeY - RShari - sizestenaDOWN);
			v[nat].setY(-v[nat].getY());
		}

		if (t[nat].getY() <= RShari + sizestenaUP && t[nat].getY() >= RShari + sizestenaUP - 2 * RDugLuz &&
			(((t[nat].getX() > sizestenaLEFT + (Ru + RDugLuz)) && (t[nat].getX() < sizestenaLEFT + sizeXpol / 2 - (RLuz + RDugLuz))) ||
			((t[nat].getX() < sizestenaLEFT + sizeXpol - (Ru + RDugLuz)) && (t[nat].getX() > sizestenaLEFT + sizeXpol / 2 + (RLuz + RDugLuz)))))
		{
			t[nat].setY(RShari + sizestenaUP);
			v[nat].setY(-v[nat].getY());
		}

		v[nat].setLK();

		if (fabs(v[nat].getL()) >= 0.004) v[nat] -= 0.004;
		else v[nat] = vec(0, 0);

		//{   проверки попадания в лузы

		if ((t[nat].getX() - sizestenaLEFT + RDugLuz)*(t[nat].getX() - sizestenaLEFT + RDugLuz) +
			(t[nat].getY() - sizestenaUP + RDugLuz) * (t[nat].getY() - sizestenaUP + RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			t[nat] = vec(golled * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			v[nat] = vec(0, 0);
			golled++;
		}

		if ((t[nat].getY() - sizeY + sizestenaDOWN - RDugLuz) * (t[nat].getY() - sizeY + sizestenaDOWN - RDugLuz) +
			(t[nat].getX() - sizestenaLEFT + RDugLuz) * (t[nat].getX() - sizestenaLEFT + RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			t[nat] = vec(golled * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			v[nat] = vec(0, 0);
			golled++;
		}

		if ((t[nat].getY() - sizeY + sizestenaDOWN - RDugLuz) * (t[nat].getY() - sizeY + sizestenaDOWN - RDugLuz) +
			(t[nat].getX() - sizeX + sizestenaRIGHT - RDugLuz) * (t[nat].getX() - sizeX + sizestenaRIGHT - RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			t[nat] = vec(golled * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			v[nat] = vec(0, 0);
			golled++;
		}

		if ((t[nat].getY() - sizestenaUP + RDugLuz) * (t[nat].getY() - sizestenaUP + RDugLuz) +
			(t[nat].getX() - sizeX + sizestenaRIGHT - RDugLuz) * (t[nat].getX() - sizeX + sizestenaRIGHT - RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			t[nat] = vec(golled * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			v[nat] = vec(0, 0);
			golled++;
		}

		if ((t[nat].getX() - sizestenaLEFT - sizeXpol / 2) * (t[nat].getX() - sizestenaLEFT - sizeXpol / 2) +
			(t[nat].getY() + sizestenaDOWN - sizeY - RDugLuz) * (t[nat].getY() + sizestenaDOWN - sizeY - RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			t[nat] = vec(golled * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			v[nat] = vec(0, 0);
			golled++;
		}

		if ((t[nat].getX() - sizestenaLEFT - sizeXpol / 2) * (t[nat].getX() - sizestenaLEFT - sizeXpol / 2) +
			(t[nat].getY() - sizestenaUP + RDugLuz) * (t[nat].getY()- sizestenaUP + RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			t[nat] = vec(golled * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			v[nat] = vec(0, 0);
			golled++;
		}
		
		//}


		nat++;
	}

	repulsionFrom();
	repulsion();
}

VOID Balls::draw(Gdiplus::Graphics *graphics, Gdiplus::Image *image, size_t index) 
{ 
	ImageAttributes imAttr;
	imAttr.SetColorKey(COLOR_KEY, COLOR_KEY);
	graphics->DrawImage(image, Rect(static_cast<INT>(t[index].getX()) - RShari, static_cast<INT>(t[index].getY()) - RShari, 2 * RShari, 2 * RShari), 0, 0, 2 * RShari, 2 * RShari, Unit::UnitPixel, &imAttr, 0); 
}



