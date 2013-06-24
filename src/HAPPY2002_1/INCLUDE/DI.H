// DI.h: interface for the CDI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DI_H__740C4019_B64B_492C_B165_FFF83BF14F87__INCLUDED_)
#define AFX_DI_H__740C4019_B64B_492C_B165_FFF83BF14F87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <dinput.h>

class CDI  
{
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	LPDIRECTINPUT8 m_lpdi;
	LPDIRECTINPUTDEVICE8 m_pDIMouseDevice;
	LPDIRECTINPUTDEVICE8 m_pDIKeyboardDevice;

	bool CreateKeyboard();
	bool CreateMouse();

public:
	bool IsKeydown(int iKey);

	bool IsLMouseButtonDown();
	bool IsRMouseButtonDown();

	unsigned int m_absX;
	unsigned int m_absY;

	unsigned char keystate[256];
	DIMOUSESTATE mouse_state;

	bool Create(HWND hWnd, HINSTANCE hInstance, bool bMouse, bool bKeyboard);
	void CleanUp();
	bool GetDeviceState();
	CDI();
	virtual ~CDI();	
};

#endif // !defined(AFX_DI_H__740C4019_B64B_492C_B165_FFF83BF14F87__INCLUDED_)
