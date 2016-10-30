#pragma once

#include "Variables.hpp"
#include "Balls.hpp"
#include "Cue.hpp"
#include "Textures.hpp"
#include "Menu.hpp"

using namespace Gdiplus;

class ProgramManager final
{
private:
	HWND        hWnd_;
	HDC         memDC_;
	HBITMAP     memHbm_;
	HBITMAP     oldHbm_;
	HINSTANCE   hInstance_;
	WCHAR       title_[MAX_LOADSTRING];
	WCHAR       wndClassName_[MAX_LOADSTRING];

	Graphics   *graphics_;
	Pen        *pen_;
	Font       *font_;
	SolidBrush *brush_;

	Textures    *textures_;
	Button      exit_;
	Mouse       mouse_;
	Balls       balls_;
	Cue         cue_;
	Menu        menu_;
	
	UPOINT      window_; // Улучшить название(размеры memDC)

	VOID reInitGraphics() { delete(graphics_); graphics_ = new Graphics(memDC_); }
	VOID reInitTextures() { delete(textures_); textures_ = new Textures(); }
	VOID reInitPen(Color color = Color::Yellow, REAL width = 10) { delete(pen_); pen_ = new Pen(color, width); }
	VOID reInitFont(const WCHAR *font = L"Times New Roman", REAL size = 25, INT style = 0, Unit unit = Unit::UnitPoint) { delete(font_); font_ = new Font(font, size, style, unit); }
	VOID reInitBrush(Color color = Color::Black) { delete(brush_); brush_ = new SolidBrush(color); }

public:
	ProgramManager();
	//ProgramManager(const ProgramManager&);
	~ProgramManager();
	
	//ProgramManager& operator=(ProgramManager&) { $b PAUSE return *this; }

	VOID dump() const { cout << "memDC: " << memDC_ << ", memHbm: " << memHbm_ << ", oldHbm: " << oldHbm_ << ", hInst: " << hInstance_ << endl
							 << "hWnd: " << hWnd_ <<", title: " << title_ << ", wndClassName: " << wndClassName_ << endl 
							 << "graphics: " << graphics_ << ", pen: " << &pen_ << ", font: " << font_ << ", brush: " << &brush_ << endl
							 << endl << endl; }

	inline HDC       getMemDC()       const { return memDC_; }
	inline HBITMAP   getMemHbm()      const { return memHbm_; }
	inline HBITMAP   getOldHbm()      const { return oldHbm_; }
	inline HWND      getHWND()		  const { return hWnd_; }
	inline HINSTANCE getHINSTANCE()   const { return hInstance_; }
	inline Color     getPenColor()    const { Color *retColor = NULL; pen_->GetColor(retColor); return *retColor; }
	inline REAL      getPenWidth()    const { return pen_->GetWidth(); }
	inline UPOINT    getMemDCWindow() const { return window_; }

	inline CONST WCHAR *getTitle()        const { return title_; }
	inline CONST WCHAR *getWndClassName() const { return wndClassName_; }
	//Стандартные функции для шрифта

	inline VOID setMemDC(HDC hDC)                   { memDC_     = hDC; }
	inline VOID setMemHbm(HBITMAP memHbm)           { memHbm_    = memHbm; }
	inline VOID setOldHbm(HBITMAP oldHbm)           { oldHbm_    = oldHbm; }
	inline VOID setHWND(HWND hWnd)                  { hWnd_      = hWnd; }
	inline VOID setHINSTANCE(HINSTANCE hInstance)   { hInstance_ = hInstance; }
	inline VOID setMemDCWindow(RECT rect)           { window_ = rect; }
	inline VOID setMouse(LPARAM lParam, int button) { mouse_.update(lParam, button); }  
	inline VOID setPenColor(Color color)            { pen_->SetColor(color); }
	inline VOID setPenWidth(REAL width)             { pen_->SetWidth(width); }
	//Стандартные функции для шрифта
	inline VOID setBrushColor(Color color = Color::Black) { brush_->SetColor(color); }

	inline CONST VOID loadBackgroundIntoCanvas(HDC canvas) const { graphics_->DrawImage(textures_->getBackgroundTexture(), RectF(0, 0, static_cast<REAL>(window_.width), static_cast<REAL>(window_.height))); }
	inline CONST VOID loadBufferIntoCanvas(HDC canvas)     const { BitBlt(canvas, 0, 0, window_.width, window_.height, memDC_, 0, 0, SRCCOPY); }

	VOID initManager();
	VOID initDubbleBuffering(HDC);
	VOID clearDubbleBuffering();

	VOID drawTable() const; // { graphics->DrawImage(textures_->getTableTexture(), RectF());); } 
	inline VOID drawCue()   const { cue_.draw(graphics_, pen_, textures_->getCueTexture()); }
	inline VOID drawMenu()  const { menu_.draw(graphics_, textures_->getMenuTexture(), window_, pen_, brush_, font_); }
	inline VOID drawBalls() const { balls_.draw(graphics_, textures_->getBallsTexture()); }
	inline VOID drawExit()  const { exit_.draw(graphics_, pen_, brush_, font_); }

	inline VOID moveCue() { cue_.rotate(balls_.getBitokCoords(), mouse_); } 
	inline VOID moveBalls() { balls_.move(); }
	

    VOID onPAINT(); 
	VOID work();

	inline BOOL stopBalls() const { if(balls_.stopped()) graphics_->DrawString(L"EZ WIN", strlen("EZ WIN"), font_, PointF(10, 10), brush_); return balls_.stopped(); }
};
