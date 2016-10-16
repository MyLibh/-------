#pragma once

#include "Variables.hpp"
#include "Balls.hpp"

using namespace Gdiplus;

class ProgramManager 
{
private:
	

	VOID drawTable();
	VOID drawBalls() { balls_.draw(graphics_, pen_, font_, brush_); }
	VOID dump() { cout << hWnd_ << " " << hDC_ << " " << memDC_ << " " << memHbm_ << " " << oldHbm_ << endl; }

public:
	HWND hWnd_;
	HDC  hDC_;
	HDC  memDC_;
	HBITMAP memHbm_;
	HBITMAP oldHbm_;
	Graphics *graphics_;
	Pen *pen_;
	Font *font_;
	SolidBrush *brush_;
	Balls balls_;
	ProgramManager(HWND);
	~ProgramManager();

	BOOL drawAll();

	VOID setPenColor(Color color) { pen_->SetColor(color); }
	VOID setPenWidth(REAL width) { pen_->SetWidth(width); }
	VOID setBrushColor(Color color) { brush_->SetColor(color); }
};




