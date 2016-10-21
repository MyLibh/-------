#pragma once

#include "Variables.hpp"
#include "Balls.hpp"
#include "Cue.hpp"

using namespace Gdiplus;

class ProgramManager
{
private:
	HWND        hWnd_;
	HDC         memDC_;
	HBITMAP     memHbm_;
	HBITMAP     oldHbm_;
	HINSTANCE   hInstance_;

	Graphics   *graphics_;
	Pen        *pen_;
	Font       *font_;
	SolidBrush *brush_;

	Balls       balls_;
	Cue         cue_;

	UPOINT      window_; // Улучшить название

	//Так можно делать???
	VOID reInitGraphics() { delete(graphics_); graphics_ = new Graphics(memDC_); }
	VOID reInitPen(Color color = Color::Yellow, REAL width = 10) { delete(pen_); pen_ = new Pen(color, width); }
	VOID reInitFont(const WCHAR *font = L"Times New Roman", REAL size = 25, INT style = 0, Unit unit = Unit::UnitPoint) { delete(font_); font_ = new Font(font, size, style, unit); }
	VOID reInitBrush(Color color = Color::Black) { delete(brush_); brush_ = new SolidBrush(color); }

public:
	ProgramManager();
	~ProgramManager();
	
	VOID dump() const { cout << "memDC: " << memDC_ << ", memHbm: " << memHbm_ << ", oldHbm: " << oldHbm_ << ", hInst: " << hInstance_ << endl
							 << "hWnd: " << hWnd_  /*<<", title: " << title_ << ", wndClassName: " << wndClassName_ */<< endl 
							 << "graphics: " << graphics_ << ", pen: " << pen_ << ", font: " << font_ << ", brush: " << brush_ << endl << endl; }

	HDC       getMemDC()       const { return memDC_; }
	HBITMAP   getMemHbm()      const { return memHbm_; }
	HBITMAP   getOldHbm()      const { return oldHbm_; }
	HWND      getHWND()		   const { return hWnd_; }
	HINSTANCE getHINSTANCE()   const { return hInstance_; }
	//WCHAR     getTitle() const { return *title_; }
	//WCHAR     getWndClassName() const { return *wndClassName_; }
	Color     getPenColor()    const { Color *retColor = NULL; pen_->GetColor(retColor); return *retColor; }
	REAL      getPenWidth()    const { return pen_->GetWidth(); }
	UPOINT    getMemDCWindow() const { return window_; }
	//Стандартные функции для шрифта

	VOID setMemDC(HDC hDC)                 { memDC_     = hDC; }
	VOID setMemHbm(HBITMAP memHbm)         { memHbm_    = memHbm; }
	VOID setOldHbm(HBITMAP oldHbm)         { oldHbm_    = oldHbm; }
	VOID setHWND(HWND hWnd)                { hWnd_      = hWnd; }
	VOID setHINSTANCE(HINSTANCE hInstance) { hInstance_ = hInstance; }
	VOID setMemDCWindow(RECT rect)         { window_ = rect; }
	VOID setCuePosition(LPARAM lParam)          { cue_.setPosition(lParam); }          
	//VOID setPenColor(Color color) { pen_->SetColor(color); }
	//VOID setPenWidth(REAL width) { pen_->SetWidth(width); }

	VOID loadTitle(WCHAR *title_)               { LoadStringW(hInstance_, IDS_APP_TITLE, title_, MAX_LOADSTRING); }
	VOID loadWndClassName(WCHAR *wndClassName_) { LoadStringW(hInstance_, IDC_BILLIARDS, wndClassName_, MAX_LOADSTRING);}
	VOID loadBufferIntoCanvas(HDC canvas)       { BitBlt(canvas, 0, 0, window_.width, window_.height, memDC_, 0, 0, SRCCOPY); }

	VOID initDubbleBuffering(HDC hDC);
	VOID clearDubbleBuffering();

	VOID drawTable();
	VOID drawCue() { cue_.draw(graphics_); }
	VOID moveCue() { cue_.rotate(); }
	VOID drawBalls() { balls_.draw(graphics_, pen_, font_, brush_); }
	VOID moveBalls() { balls_.move(); }

	BOOL stopBalls() const { if(balls_.stopped()) graphics_->DrawString(L"EZ WIN", strlen("EZ WIN"), font_, PointF(10, 10), brush_); return balls_.stopped(); }
};
