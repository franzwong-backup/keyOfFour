// DI.cpp: implementation of the CDI class.
//
//////////////////////////////////////////////////////////////////////

#include "..\include\DI.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDI::CDI()
{
	m_hWnd = 0;
	m_hInstance = 0;
	m_lpdi = 0;
	m_pDIMouseDevice = 0;
	m_pDIKeyboardDevice = 0;
	memset(keystate, 0, sizeof(unsigned char)*256);
}

CDI::~CDI()
{
	CleanUp();
}

bool CDI::Create(HWND hWnd, HINSTANCE hInstance, bool bMouse, bool bKeyboard)
{
	if (m_lpdi) { return false; }
	if (m_hWnd) { return false; }
	if (m_hInstance) { return false; }
	HRESULT hRet;
	//Create direct input object
	hRet = DirectInput8Create(GetModuleHandle(NULL), 0x0800, 
		IID_IDirectInput8, (void**)&m_lpdi, NULL);
	if ( FAILED(hRet) ) { return false; }
	bool bRet;
	//Create mouse device
	if (bMouse)
	{
		bRet = CreateMouse();
		if ( !bRet ) { return false; }
	}
	//Create keyboard device
	if (bKeyboard)
	{
		bRet = CreateKeyboard();
		if ( !bRet ) { return false; }
	}
	//Give the info of the window to CDI
	m_hWnd = hWnd;
	m_hInstance = hInstance;
	return true;
}

bool CDI::CreateMouse()
{
	HRESULT hRet;
	if (m_pDIMouseDevice) { return false; }
	hRet = m_lpdi->CreateDevice(GUID_SysMouse, &m_pDIMouseDevice, NULL);
	if ( FAILED( hRet ) ) { return false; }
	hRet = m_pDIMouseDevice->SetCooperativeLevel(m_hWnd, DISCL_BACKGROUND |
		DISCL_NONEXCLUSIVE);
	if ( FAILED( hRet ) ) { return false; }
	hRet = m_pDIMouseDevice->SetDataFormat(&c_dfDIMouse);
	if ( FAILED( hRet ) ) { return false; }
	if ( m_pDIMouseDevice )
	{
		hRet = m_pDIMouseDevice->Acquire();
		if ( FAILED(hRet) ) { return false; }
	}
	return true;
}

bool CDI::CreateKeyboard()
{
	HRESULT hRet;
	if (m_pDIKeyboardDevice) { return false; }
	hRet = m_lpdi->CreateDevice(GUID_SysKeyboard, &m_pDIKeyboardDevice, NULL);
	if ( FAILED( hRet ) ) { return false; }
	hRet = m_pDIKeyboardDevice->SetCooperativeLevel(m_hWnd, DISCL_BACKGROUND |
		DISCL_NONEXCLUSIVE);
	if ( FAILED( hRet ) ) { return false; }
	hRet = m_pDIKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	if ( FAILED( hRet ) ) { return false; }
	if ( m_pDIKeyboardDevice )
	{
		hRet = m_pDIKeyboardDevice->Acquire();
		if ( FAILED(hRet) ) { return false; }
	}
	return true;
}

void CDI::CleanUp()
{
	HRESULT hRet;
	//clean up mouse device
	if ( m_pDIMouseDevice )
	{  
		m_pDIMouseDevice->Unacquire();
		m_pDIMouseDevice->Release(); 
		m_pDIMouseDevice = 0; 
	}
	//clean up keyboard device
	if ( m_pDIKeyboardDevice )
	{ 
		m_pDIKeyboardDevice->Unacquire();
		m_pDIKeyboardDevice->Release(); 
		m_pDIKeyboardDevice = 0; 
	}
	//clean up direct input object
	if ( m_lpdi ) { m_lpdi->Release(); m_lpdi = 0; }	
	//Reset the handle of window and instance
	m_hWnd = 0;
	m_hInstance = 0;
}

bool CDI::GetDeviceState()
{
	HRESULT hRet;
	if ( m_pDIKeyboardDevice )
	{
		hRet = m_pDIKeyboardDevice->GetDeviceState( sizeof(unsigned char)*256,
			(LPVOID)keystate);
		if ( FAILED(hRet) ) { return false; }
	}
	if ( m_pDIMouseDevice )
	{
		hRet = m_pDIMouseDevice->GetDeviceState( sizeof(DIMOUSESTATE), 
			(LPVOID)&mouse_state );
		if ( FAILED(hRet) ) { return false; }
		m_absX += mouse_state.lX;
		m_absY += mouse_state.lY;		
	}
	return true;
}

bool CDI::IsKeydown(int iKey)
{
	if (!m_pDIKeyboardDevice) { return false; }
	return static_cast<bool>(keystate[iKey] & 0x80);
}

bool CDI::IsLMouseButtonDown()
{
	if (!m_pDIMouseDevice) { return false; }
	return static_cast<bool>(mouse_state.rgbButtons[0] & 0x80);
}

bool CDI::IsRMouseButtonDown()
{
	if (!m_pDIMouseDevice) { return false; }
	return static_cast<bool>(mouse_state.rgbButtons[1] & 0x80);
}
