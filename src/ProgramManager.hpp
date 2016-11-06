#pragma once

#include "Variables.hpp"
#include "Balls.hpp"
#include "Cue.hpp"
#include "Textures.hpp"
#include "Menu.hpp"
#include "Keyboard.hpp"
#include "Config.hpp"
#include "Exceptions.hpp"
 
using namespace Gdiplus;

//=============================================================================================================================

class ProgramManager final : private Menu, private Balls, private Cue, private Mouse
{
private:
	static CONST SIZE_T MAX_LOADSTRING = 64;

	HWND        hWnd_;
	HDC         memDC_;
	HBITMAP     memHbm_;
	HBITMAP     oldHbm_;
	HINSTANCE   hInstance_;
	WCHAR       title_[MAX_LOADSTRING];
	WCHAR       wndClassName_[MAX_LOADSTRING];

	Graphics   *pGraphics_;
	Pen        *pPen_;
	Font       *pFont_;
	SolidBrush *pBrush_;

	Textures   *pTextures_;
	Button      exit_;
	//Config      config_;
	
	UPOINT      window_; // Улучшить название(размеры memDC)

	wstring anotherPlayerText_;
	PointF  anotherPlayerPoint_;
	Color   anotherPlayerColor_;

	ProgramManager(CONST ProgramManager&) {}
	ProgramManager& operator=(CONST ProgramManager&) {}

	inline string HWND2STRING() const { char text[32] = ""; ; return string(_itoa(reinterpret_cast<INT>(hWnd_), text, 10)); }
	inline string HINSTANCE2STRING() const { char text[32] = ""; ; return string(_itoa(reinterpret_cast<INT>(hInstance_), text, 10)); }

	inline CONST VOID loadBackgroundIntoCanvas(HDC canvas) const { pGraphics_->DrawImage(&pTextures_->getBackgroundTexture(), RectF(0, 0, static_cast<REAL>(window_.width), static_cast<REAL>(window_.height))); }
	inline CONST VOID loadBufferIntoCanvas(HDC canvas)     const { BitBlt(canvas, 0, 0, window_.width, window_.height, memDC_, 0, 0, SRCCOPY); }

	VOID initDubbleBuffering(HDC);
	VOID clearDubbleBuffering();

	VOID drawTable() const; // { graphics->DrawImage(textures_->getTableTexture(), RectF());); } 
	inline VOID drawCue()   const { if(Balls::stopped()) Cue::draw(pGraphics_, *pPen_, pTextures_->getCueTexture()); }
	inline VOID drawMenu()  const { Menu::draw(pGraphics_, pTextures_->getMenuTexture(), window_, *pPen_, *pBrush_, *pFont_); }
	inline VOID drawBalls() const { Balls::draw(pGraphics_, pTextures_->getBallsTexture()); }
	inline VOID drawExit()  const { exit_.draw(pGraphics_, *pPen_, *pBrush_, *pFont_); }

	inline VOID moveCue() { if(Balls::stopped()) Cue::rotate(Balls::getBallCoords(Balls::Ball::zero), Mouse::getCoords()); } 
	inline VOID moveBalls() { Balls::move(); }
	
	inline MenuActions menuProcedure(POINT mouse, INT16 button) { return Menu::procedure(mouse, button); }

public:
	explicit ProgramManager(HWND, HINSTANCE);
	~ProgramManager();
	
	inline VOID dump() const { cout << "memDC: " << memDC_ << ", memHbm: " << memHbm_ << ", oldHbm: " << oldHbm_ << ", hInst: " << hInstance_ << endl
							        << "hWnd: " << hWnd_ <<", title: " << title_ << ", wndClassName: " << wndClassName_ << endl << endl; }

	inline HDC       getMemDC()       const { return memDC_; }
	inline HBITMAP   getMemHbm()      const { return memHbm_; }
	inline HBITMAP   getOldHbm()      const { return oldHbm_; }
	inline HWND      getHWND()		  const { return hWnd_; }
	inline HINSTANCE getHINSTANCE()   const { return hInstance_; }
	inline Color     getPenColor()    const { Color *retColor = NULL; pPen_->GetColor(retColor); return *retColor; }
	inline REAL      getPenWidth()    const { return pPen_->GetWidth(); }
	inline UPOINT    getMemDCWindow() const { return window_; }
	inline POINT     getMousePos()    const { return Mouse::getCoords(); }
	//Стандартные функции для шрифта
	inline CONST WCHAR *getTitle()        const { return title_; }
	inline CONST WCHAR *getWndClassName() const { return wndClassName_; }
	inline CONST BOOL  *getScored() const { return Balls::getScored(); }
	

	VOID setDefaults();
	inline VOID updateZero() { Balls::setBallStatus(); }

	inline VOID setMemDC(HDC hDC)                   { memDC_     = hDC; }
	inline VOID setMemHbm(HBITMAP memHbm)           { memHbm_    = memHbm; }
	inline VOID setOldHbm(HBITMAP oldHbm)           { oldHbm_    = oldHbm; }
	inline VOID setHWND(HWND hWnd)                  { hWnd_      = hWnd; }
	inline VOID setHINSTANCE(HINSTANCE hInstance)   { hInstance_ = hInstance; }
	inline VOID setMemDCWindow(RECT rect)           { window_ = rect; }
	inline VOID setMouse(LPARAM lParam, int button) { Mouse::update(lParam, button); }
	//Стандартные функции для шрифта 
	inline VOID setPenColor(Color color = Color::Yellow)  { pPen_->SetColor(color); }
	inline VOID setPenWidth(REAL width = 10)              { pPen_->SetWidth(width); }	
	inline VOID setBrushColor(Color color = Color::Black) { pBrush_->SetColor(color); }
	inline VOID setBallCoords(POINT coords, size_t index = 0) { Balls::setBallCoords(coords, index); }

    VOID onPAINT(); 
	VOID work(CONST wstring&, CONST PointF& = PointF(0, 0), CONST Color& = Color::LightGreen, CONST BOOL& = TRUE);
	VOID endGame(wstring winnerMsg){ MessageBox(hWnd_, winnerMsg.c_str(), L"ИГРА ОКОНЧЕНА", MB_OK | MB_ICONINFORMATION); Menu::activate(); }
	inline VOID nextMove() { Balls::nextMove(15, Cue::getAngleInRadians()); }

	inline BOOL stopBalls() const { return Balls::stopped(); }
};
