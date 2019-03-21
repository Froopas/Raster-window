////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define WIN32_LEAN_AND_MEAN


//////////////
// INCLUDES //
//////////////
#include <windows.h>

#include "Controller.h"

#include "Renderer.h"

class Renderer;
class Game;
class Controller;

////////////////////////////////////////////////////////////////////////////////
// Class name: SystemClass
////////////////////////////////////////////////////////////////////////////////
class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	Controller* m_controller;
	Renderer* m_renderer;
	Game* m_game;

	bool FULL_SCREEN = false;

};


static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


static SystemClass* ApplicationHandle = 0;

#endif