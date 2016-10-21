#include "Balls.hpp"

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

INT Whatshar(int num)
{
	switch (num)
	{
	case 0: 
		return 1;
	case 1: case 2: case 3: case 4: case 5: case 6: case 7: 
		return 3;
	case 8: 
		return 2;
	case 9: case 10: case 11: case 12: case 13: case 14: case 15: 
		return 4;
	default: 
		return 0;
	}
}

//=============================================

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
	
	image_ = new Image(L"../src/Images/8.jpg");
	/*for(size_t i = 0; i < NUMBER_OF_BALLS; i++)
	{
		//char text[32] = "";
		//sprintf_s(text, "../src/Images/%d.jpg", i);
		//std::wstring pathToFile[32] = {(wstring)("../src/Images/" + "8" + ".")}; //i вместо 8
		image_[i] = new Image(L"../src/Images/8.jpg");	
	}*/
}

BOOL Balls::stopped() const
{
	for (size_t i = 0; i < NUMBER_OF_BALLS; i++) if (v[i].l != 0) return false;

	return true;
}

VOID Balls::repulsion()
{
	for  (size_t i = 0; i < NUMBER_OF_BALLS - 1; i++)
	{
		for (size_t j = i + 1; j < NUMBER_OF_BALLS; j++)
		{
			if ((pow(t[i].x - t[j].x, 2) + pow(t[i].y - t[j].y, 2) <= 4 * RShari * RShari)
				&& (pow(t[i].x - t[j].x, 2) + pow(t[i].y - t[j].y, 2))        //надо сделать чтобы после синкосов они удалялись
				>= (pow((t[i].x + v[i].x) - (t[j].x + v[j].x), 2) + pow((t[i].y + v[i].y) - (t[j].y + v[j].y), 2)))
			{

				double tmp_xi = 0, tmp_yi = 0;
				double tmp_xj = 0, tmp_yj = 0;

				double ug = 10000000;
				double phi = M_PI_4;
				if (t[i].x != t[j].x)
				{
					ug = (t[i].y - t[j].y) / (t[i].x - t[j].x);

					phi = atan(ug);
				}

				double vx_j = ( v[i].x * cos(phi) + v[i].y * sin(phi));
				double vy_i = (-v[i].x * sin(phi) + v[i].y * cos(phi));

				double vx_i = ( v[j].x * cos(phi) + v[j].y * sin(phi));
				double vy_j = (-v[j].x * sin(phi) + v[j].y * cos(phi));

				tmp_xi = ( vx_i * cos(-phi) + vy_i * sin(-phi));
				tmp_yi = (-vx_i * sin(-phi) + vy_i * cos(-phi));

				tmp_xj = ( vx_j * cos(-phi) + vy_j * sin(-phi));
				tmp_yj = (-vx_j * sin(-phi) + vy_j * cos(-phi));

				//double slg_car = 0;
				//double slg_new = 0;

				if (sqrt(pow(t[i].x - t[j].x, 2) + pow(t[i].y - t[j].y, 2))
					>= sqrt(pow((t[i].x + 25 * tmp_xi) - (t[j].x + 25 * tmp_xj), 2) + pow((t[i].y + 25 * tmp_yi) - (t[j].y + 25 * tmp_yj), 2)))
				{
					//slg_car = sqrt(pow(t[i].x - t[j].x, 2) + pow(t[i].y - t[j].y, 2));

					//slg_new = sqrt(pow((t[i].x + 25*clgxi) - (t[j].x + 25*clgxj), 2) + pow((t[i].y + 25*clgyi) - (t[j].y + 25*clgyj), 2));
				}
				else
				{
					v[j].x = tmp_xj;
					v[j].y = tmp_yj;
					v[i].x = tmp_xi;
					v[i].y = tmp_yi;
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
			if ((pow(t[i].x - CenterDugLuz[j].x, 2) + pow(t[i].y - CenterDugLuz[j].y, 2) <= (RShari + RDugLuz)*(RShari + RDugLuz))
				&& (pow(t[i].x - CenterDugLuz[j].x, 2) + pow(t[i].y - CenterDugLuz[j].y, 2))        //надо сделать чтобы после синкосов они уддалялись
				>= (pow((t[i].x + v[i].x) - (CenterDugLuz[j].x), 2) + pow((t[i].y + v[i].y) - (CenterDugLuz[j].y), 2)))
			{

				double tmp_xi = 0;
				double tmp_yi = 0;
				//double clgxj = 0;
				//double clgyj = 0;

				double ug = 10000000;
				double phi = M_PI_4;
				if (t[i].x != CenterDugLuz[j].x)
				{
					ug = (t[i].y - CenterDugLuz[j].y) / (t[i].x - CenterDugLuz[j].x);

					phi = atan(ug);
				}

				double vx_i = -(v[i].x*cos(phi) + v[i].y*sin(phi));
				double vy_i = (-v[i].x*sin(phi) + v[i].y*cos(phi));

				tmp_xi = ( vx_i * cos(-phi) + vy_i * sin(-phi));
				tmp_yi = (-vx_i * sin(-phi) + vy_i * cos(-phi));
				 
				if (sqrt(pow(t[i].x - CenterDugLuz[j].x, 2) + pow(t[i].y - CenterDugLuz[j].y, 2))
					>= sqrt(pow((t[i].x + 25 * tmp_xi) - (CenterDugLuz[j].x), 2) + pow((t[i].y + 25 * tmp_yi) - (CenterDugLuz[j].y), 2)))
				{
				}
				else
				{
					v[i].x = tmp_xi;
					v[i].y = tmp_yi;
				}

			}
		}
	}
}

VOID Balls::draw(Graphics *graphics, Pen *pen, Font *font, SolidBrush *brush) const
{
	for (size_t i = 0; i < NUMBER_OF_BALLS; i++)
	{
		switch (Whatshar(i))
		{
		case 1: pen->SetColor(Color::White); break;
		case 2: pen->SetColor(Color::Black); break;
		case 3: pen->SetColor(Color::Red);   break;
		case 4: pen->SetColor(Color::Blue);  break;

		default:                             break;
		}
		graphics->DrawEllipse(pen, static_cast<INT>(t[i].x - RShari / 2), static_cast<INT>(t[i].y - RShari / 2), RShari, RShari); 
		//graphics->DrawImage(image_, static_cast<INT>(t[i].x - RShari), static_cast<INT>(t[i].y - RShari), RShari, RShari);
		//cout << image_;
		//graphics->DrawImage(new Image(L"../src/Images/8.jpg"), static_cast<INT>(t[i].x - RShari / 2), static_cast<INT>(t[i].y - RShari / 2), RShari, RShari);

		char text[3] = "";
		sprintf_s(text, "%d", i);
		//const size_t length = strlen(text);
		//WCHAR *buffer = new WCHAR[length + 1];
		//buffer[length] = 0;
		//mbstowcs(buffer, text, length);

		brush->SetColor(Color::Black);
		//graphics->DrawString(buffer, length, font, PointF(static_cast<REAL>(t[i].x - RShari / 2), static_cast<REAL>(t[i].y - RShari / 2)), brush);
		graphics->DrawString(reinterpret_cast<const WCHAR*>(text), strlen(text), font, PointF(static_cast<REAL>(t[i].x - RShari / 2), static_cast<REAL>(t[i].y - RShari / 2)), brush);
		//delete(buffer);
	}
}

VOID Balls::move()
{
	int nat = 0;
	
	while (nat < NUMBER_OF_BALLS)
	{
		t[nat].x = t[nat].x + v[nat].x;

		if (t[nat].x >= sizeX - RShari - sizestenaRIGHT && t[nat].x <= sizeX - RShari - sizestenaRIGHT + 2 * RDugLuz &&
			(((t[nat].y > sizestenaUP + (Ru + RDugLuz)) && (t[nat].y < sizestenaUP + sizeYpol - (Ru + RDugLuz)))/* ||
																												(( t[nat].y < sizestenaUP + sizeYpol - (RLuz + RDugLuz)) && (t[nat].y > sizestenaUP + sizeYpol/2 + (RLuz + RDugLuz)))*/))
		{
			t[nat].x = sizeX - RShari - sizestenaRIGHT;
			v[nat].x = -v[nat].x;
		}
		
		if (t[nat].x <= RShari + sizestenaLEFT && t[nat].x >= RShari + sizestenaLEFT - 2 * RDugLuz &&
			(((t[nat].y > sizestenaUP + (Ru + RDugLuz)) && (t[nat].y < sizestenaUP + sizeYpol - (Ru + RDugLuz))))) // || (( t[nat].y < sizestenaUP + sizeYpol - (RLuz + RDugLuz)) && (t[nat].y > sizestenaUP + sizeYpol/2 + (RLuz + RDugLuz)))))
		{
			t[nat].x = RShari + sizestenaLEFT;
			v[nat].x = -v[nat].x;
		}

		t[nat].y = t[nat].y + v[nat].y;

		if (t[nat].y >= sizeY - RShari - sizestenaDOWN && t[nat].y <= sizeY - RShari - sizestenaDOWN + 2 * RDugLuz &&
			(((t[nat].x > sizestenaLEFT + (Ru + RDugLuz)) && (t[nat].x < sizestenaLEFT + sizeXpol / 2 - (RLuz + RDugLuz))) ||
			((t[nat].x < sizestenaLEFT + sizeXpol - (Ru + RDugLuz)) && (t[nat].x > sizestenaLEFT + sizeXpol / 2 + (RLuz + RDugLuz)))))
		{
			t[nat].y = sizeY - RShari - sizestenaDOWN;
			v[nat].y = -v[nat].y;
		}

		if (t[nat].y <= RShari + sizestenaUP && t[nat].y >= RShari + sizestenaUP - 2 * RDugLuz &&
			(((t[nat].x > sizestenaLEFT + (Ru + RDugLuz)) && (t[nat].x < sizestenaLEFT + sizeXpol / 2 - (RLuz + RDugLuz))) ||
			((t[nat].x < sizestenaLEFT + sizeXpol - (Ru + RDugLuz)) && (t[nat].x > sizestenaLEFT + sizeXpol / 2 + (RLuz + RDugLuz)))))
		{
			t[nat].y = RShari + sizestenaUP;
			v[nat].y = -v[nat].y;
		}

		v[nat].setLK();

		if (fabs(v[nat].l) >= 0.004) v[nat] -= 0.004;
		else v[nat] = vec(0, 0);

		//{   проверки попадания в лузы

		if ((t[nat].x - sizestenaLEFT + RDugLuz)*(t[nat].x - sizestenaLEFT + RDugLuz) +
			(t[nat].y - sizestenaUP + RDugLuz)*(t[nat].y - sizestenaUP + RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			t[nat] = vec(golled * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			v[nat] = vec(0, 0);
			golled++;
		}

		if ((t[nat].y - sizeY + sizestenaDOWN - RDugLuz)*(t[nat].y - sizeY + sizestenaDOWN - RDugLuz) +
			(t[nat].x - sizestenaLEFT + RDugLuz)*(t[nat].x - sizestenaLEFT + RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			t[nat] = vec(golled * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			v[nat] = vec(0, 0);
			golled++;
		}

		if ((t[nat].y - sizeY + sizestenaDOWN - RDugLuz)*(t[nat].y - sizeY + sizestenaDOWN - RDugLuz) +
			(t[nat].x - sizeX + sizestenaRIGHT - RDugLuz)*(t[nat].x - sizeX + sizestenaRIGHT - RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			t[nat] = vec(golled * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			v[nat] = vec(0, 0);
			golled++;
		}

		if ((t[nat].y - sizestenaUP + RDugLuz)*(t[nat].y - sizestenaUP + RDugLuz) +
			(t[nat].x - sizeX + sizestenaRIGHT - RDugLuz)*(t[nat].x - sizeX + sizestenaRIGHT - RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			t[nat] = vec(golled * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			v[nat] = vec(0, 0);
			golled++;
		}

		if ((t[nat].x - sizestenaLEFT - sizeXpol / 2)*(t[nat].x - sizestenaLEFT - sizeXpol / 2) +
			(t[nat].y + sizestenaDOWN - sizeY - RDugLuz)*(t[nat].y + sizestenaDOWN - sizeY - RDugLuz) <= (RLuz + 1)*(RLuz + 1))
		{
			t[nat] = vec(golled * 2 * (RShari + 1) + sizestenaLEFT * 2, sizestenaUP / 2 - 3);
			v[nat] = vec(0, 0);
			golled++;
		}

		if ((t[nat].x - sizestenaLEFT - sizeXpol / 2) * (t[nat].x - sizestenaLEFT - sizeXpol / 2) +
			(t[nat].y - sizestenaUP + RDugLuz) * (t[nat].y - sizestenaUP + RDugLuz) <= (RLuz + 1)*(RLuz + 1))
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



