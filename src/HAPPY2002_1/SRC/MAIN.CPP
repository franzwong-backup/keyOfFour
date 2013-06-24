//-----------------------------------------------------------------------------
//Includes
//-----------------------------------------------------------------------------
#include <windows.h>
#include <mmsystem.h>
#include <ctime>
#include <string>
#include "..\include\DD.h"
#include "..\include\DI.h"
#include "..\include\DS.h"

#include "..\include\OpeningScene.h"
#include "..\include\MenuScene.h"
#include "..\include\MapScene.h"
#include "..\include\BattleScene.h"

#include "..\include\MainChar.h"
#include "..\include\resource.h"

//#define WINDOW_MODE 1
//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------
const int WIN_WIDTH = 640, WIN_HEIGHT = 480; // Dimensions of the window
HINSTANCE MainInstance = NULL;
HWND MainHwnd = NULL;
const char szWinName[] = "The Key of Four";
DWORD dwCurrent = 0, dwLast = 0;

const unsigned int OPENING = 0;
const unsigned int MAINMENU = 1;
const unsigned int MAP = 2;
const unsigned int MENU = 3;
const unsigned int BATTLE = 4;
const unsigned int GETKEY = 5;
const unsigned int ENDING = 6;

unsigned int g_imode = OPENING;
int WINDOW_MODE = 0;
bool g_bMinimized = false;

COpeningScene *g_pOpeningScene = 0;
CMenuScene *g_pMenuScene = 0;
CMapScene *g_pMapScene = 0;
CBattleScene *g_pBattleScene = 0;

CMainChar g_MainChar;

CDD dd;
CDI di;

std::string g_strCurrentDir;
//-----------------------------------------------------------------------------
// Function
//-----------------------------------------------------------------------------
HRESULT WinInit();
bool UpdateFrame();
void CleanUp();
bool Operation();
bool Map_Init();
bool Battle_Init(unsigned int iMapID);
bool Battle_CleanUp();
//-----------------------------------------------------------------------------
// The window's message handler.
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (msg)
	{
	case WM_KEYUP:
		if (wParam == VK_ESCAPE)
		{
			PostMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		CleanUp();
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		hdc = BeginPaint(MainHwnd,&ps);
		EndPaint(MainHwnd,&ps);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
    break;

	}
	return 0;
}


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{

	if (FAILED(WinInit()))
	{
		MessageBox( MainHwnd, TEXT("Window init failed.")
                    TEXT("The program will now exit."), szWinName, 
                    MB_ICONERROR | MB_OK );
        return FALSE;
	}

	//Rand Init
	srand(time(0));

	if ( MessageBox(MainHwnd, "Do you want windowed mode? ( If you want better graphics, please press no. )", 
		"Question", MB_YESNO) == IDYES)
	{
		WINDOW_MODE = 1;
	}
	else
	{
		WINDOW_MODE = 0;
	}

	bool bRet;
	//Create DX
	if (WINDOW_MODE == 0) 
	{
		bRet = dd.Create(MainHwnd, hInst, 640, 480, 16);
	}
	else
	{
		bRet = dd.CreateWindowMode(MainHwnd, hInst, 640, 480);
	}

	if ( !bRet )
	{
		MessageBox(MainHwnd, "Error in Creating DX", "Error", MB_OK|MB_ICONERROR);
		CleanUp();
		return FALSE;
	}
			
	//Create DI
	bRet = di.Create(MainHwnd, MainInstance, true, true);
	if ( !bRet )
	{
		MessageBox(MainHwnd, "Error in Creating DI", "Error", MB_OK|MB_ICONERROR);
		CleanUp();
		return FALSE;
	}

	char strBuffer[1024];
	GetCurrentDirectory(1024, strBuffer);

	g_strCurrentDir = strBuffer;

	//Init Opening Scene
	if ( !g_pOpeningScene )
	{
		g_pOpeningScene = new COpeningScene(&dd, MainHwnd, MainInstance);
		
		bRet = g_pOpeningScene->Init(".\\scene\\opening.txt");
		if ( !bRet )
		{
			MessageBox(MainHwnd, "Error in Init Opening Scene", "Error", MB_OK|MB_ICONERROR); 
			CleanUp();
			return FALSE;
		}
	}

	try
	{	
		ShowWindow(MainHwnd, SW_SHOWDEFAULT);
		UpdateWindow(MainHwnd);
		
		MSG msg;

		for (;;)
		{
			if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) )
			{
				if (msg.message == WM_QUIT)
					break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				//if ( IsIconic(MainHwnd) ) 
				//{
					dwCurrent = GetTickCount();
					//Get input device state
					bRet = di.GetDeviceState();
					if ( !bRet )
					{
						MessageBox(MainHwnd, "Error in Getting Device State",
							"Error", MB_OK|MB_ICONERROR); 
						break;
					}
					
					if ( dwCurrent - dwLast > 150 )
					{
						//Game operation part
						bRet = Operation();
						if ( !bRet )
						{
							MessageBox(MainHwnd, "Error in game operation", "Error", 
								MB_OK|MB_ICONERROR); 
							break;
						}
						//Update frame
						bRet = UpdateFrame();
						if ( !bRet )
						{
							MessageBox(MainHwnd, "Error in Updating Frame", "Error", 
								MB_OK|MB_ICONERROR); 
							break;
						}

						dwLast = GetTickCount();
					}
				//}
			}

		}
	}
	catch (HRESULT)
	{
		// An unexpected error has occurred.
	}
	CleanUp();
	return 0;
}
//CS_CLASSDC
HRESULT WinInit()
{
	WNDCLASSEX wc = {
		sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, MsgProc, 0L, 0L, 
		GetModuleHandle(NULL), 
		LoadIcon(NULL, MAKEINTRESOURCE(IDI_GAMEICON)),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)GetStockObject(BLACK_BRUSH), NULL, 
		szWinName, NULL
	};
	if( RegisterClassEx( &wc ) == 0 )
        return E_FAIL;

	int ScreenWidth		= GetSystemMetrics(SM_CXSCREEN);
	int ScreenHeight	= GetSystemMetrics(SM_CYSCREEN);

	HWND hWnd = 0;
	if (WINDOW_MODE == 0)
	{
		//Full screen
		hWnd = CreateWindow(szWinName, szWinName,
			WS_POPUP, 
			0, 0, ScreenWidth, ScreenHeight,
			0, 0, wc.hInstance, 0);
	}
	else
	{
		//Window mode
		hWnd = CreateWindow(szWinName, szWinName,
			WS_POPUP,
			0, 0, ScreenWidth, ScreenHeight,
			0, 0, wc.hInstance, 0);
	}

	if (hWnd == NULL)
		return E_FAIL;
	MainHwnd = hWnd;
	MainInstance = wc.hInstance;
	CoInitialize(NULL);
	return S_OK;
}

bool UpdateFrame()
{
	bool bRet = true;
	//Clean the back buffer
	dd.ClearBackBuffer();
	//Draw
	switch (g_imode)
	{
		case OPENING:
			if ( g_pOpeningScene )
			{ bRet = g_pOpeningScene->Draw(); }
			break;
		case MAINMENU:
			if ( g_pMenuScene )
			{ bRet = g_pMenuScene->Draw(); }
		case MAP:
			if ( g_pMapScene )
			{ bRet = g_pMapScene->Draw();}
		case BATTLE:
			if ( g_pBattleScene )
			{ bRet = g_pBattleScene->Draw(); }
	}
	if ( !bRet )
		return false;

	//Flip surface
	if (WINDOW_MODE == 0)
	{ bRet = dd.FlipSurface(); }
	else
	{ bRet = dd.BltBackToPri(); }
	if ( !bRet ) { return false; }

	return true;
}

void CleanUp()
{
	//Clean up scene
	if ( g_pOpeningScene ) { delete g_pOpeningScene; g_pOpeningScene = 0; } //Opening
	if ( g_pMenuScene ) { delete g_pMenuScene; g_pMenuScene = 0; }	//Menu
	if ( g_pMapScene ) { delete g_pMapScene; g_pMapScene = 0; }	//Map
	if ( g_pBattleScene ) { delete g_pBattleScene; g_pBattleScene = 0; }	//Map
	//Clean up direct input
	di.CleanUp();
	//Clean up direct draw
	dd.CleanUp();
	// Clean up everything and exit the app
	UnregisterClass(szWinName, MainInstance);
	CoUninitialize();
}

bool Operation()
{
	bool bRet;
	switch (g_imode)
	{
		case OPENING: //Opening mode
			if ( g_pOpeningScene )
			{
				if ( ( di.IsKeydown(DIK_SPACE) ) || ( di.IsKeydown(DIK_UP) ) )
				{
					g_pOpeningScene->addFrameNum();
				}

				if ( (  di.IsLMouseButtonDown()) || ( di.IsKeydown(DIK_RETURN) ) 
					|| ( g_pOpeningScene->getFrameNum() > 149) )
				{
					//End opening scene
					if ( g_pOpeningScene )
						{ delete g_pOpeningScene; g_pOpeningScene = 0; }
					//Create menu scene
					if ( !g_pMenuScene ) //Check if the menu exist
					{	
						//If not exist , create it
						g_pMenuScene = new CMenuScene(&dd, MainHwnd, MainInstance);
						bRet = g_pMenuScene->Init(".\\scene\\menu.txt");
						if ( !bRet )
						{
							MessageBox(MainHwnd, "Error in Init Menu Scene",
								"Error", MB_OK|MB_ICONERROR); 
							return false;
						}
						g_imode = MAINMENU;
					}
					else
						return false;	//Error occur				
				}
				if ( g_pOpeningScene )
				{
					bRet = g_pOpeningScene->CheckAndLoop();
					if ( !bRet ) { return false; }
					bRet = g_pOpeningScene->Operate();
					if ( !bRet ) { return false; }
				}
			}
			break;
		case MAINMENU: //Main Menu mode
			if ( g_pMenuScene )
			{
				switch ( g_pMenuScene->getCursorPos() )
				{
				case 0:
						if ( di.IsKeydown(DIK_DOWN) )
						{
							g_pMenuScene->moveCursorDown(); //Set the cursor to lower option
							g_pMenuScene->PlayAnvilSound();
						}
						if ( di.IsKeydown(DIK_RETURN) || di.IsLMouseButtonDown() ) //If user presses enter for start game
						{
							bRet = Map_Init();
							if ( !bRet ) { return false; }
						}
					break;
				case 1:
						if ( di.IsKeydown(DIK_UP) )
						{
							g_pMenuScene->moveCursorUp(); //Set the cursor to higher option
							g_pMenuScene->PlayAnvilSound();
						}
						if ( di.IsKeydown(DIK_RETURN) ) //If user presses enter for exit
						{
							//Exit game
							PostMessage(MainHwnd, WM_CLOSE, 0, 0);
						}
					break;
				}
				if ( g_pMenuScene )
				{
					bRet = g_pMenuScene->CheckAndLoop();
					if ( !bRet ) { return false; }
				}
			}
			break;
		case MAP:
			{
				bool bMove = false;
				//Detect keyboard input
				if ( di.IsKeydown(DIK_UP) || di.IsKeydown(DIK_W) )
				{
					if ( !bMove )
					{
						g_MainChar.MoveUp(g_pMapScene);
						bMove = true;
					}
				}
				if ( di.IsKeydown(DIK_DOWN) || di.IsKeydown(DIK_S) )
				{
					if ( !bMove )
					{
						g_MainChar.MoveDown(g_pMapScene);
						bMove = true;
					}
				}
				if ( di.IsKeydown(DIK_LEFT) || di.IsKeydown(DIK_A) )
				{
					if ( !bMove )
					{
						g_MainChar.MoveLeft(g_pMapScene);
						bMove = true;
					}
				}
				if ( di.IsKeydown(DIK_RIGHT) || di.IsKeydown(DIK_D) )
				{
					if ( !bMove )
					{
						g_MainChar.MoveRight(g_pMapScene);
						bMove = true;
					}
				}
				if ( bMove )
				{
					int BattleRand = rand() % 30;
					if ( BattleRand == 20 )
					{
						unsigned int iMapID = g_pMapScene->getCurrentMap()->getMapID();
						bRet = Battle_Init(iMapID);
						if ( !bRet ) { return false; }
					}					
				}
				if ( g_pMapScene )
				{
					bRet = g_pMapScene->CheckAndLoop();
					if ( !bRet ) { return false; }
				}
			}
			break;
		case BATTLE:
			{
				bool bMove = false;
				if ( di.IsKeydown(DIK_UP) )
				{
					g_pBattleScene->LightMagic();
					bMove = true;
				}
				if ( di.IsKeydown(DIK_DOWN) )
				{
					g_pBattleScene->DarkMagic();
					bMove = true;
				}				
				if ( di.IsKeydown(DIK_RETURN) )
				{
					Battle_CleanUp();
					bMove = true;
				}
				if ( g_pBattleScene )
				{
					bRet = g_pBattleScene->CheckAndLoop();
					if ( !bRet ) { return false; }
				}
			}
			break;
		default:
			return false;
			break;
	}
	return true;
}

bool Map_Init()
{
	bool bRet;
	
	//End menu scene
	if ( g_pMenuScene )
		{ delete g_pMenuScene; g_pMenuScene = 0; }
	//Create menu scene
	if ( !g_pMapScene ) //Check if the menu exist
	{	
		//If not exist , create it
		g_pMapScene = new CMapScene(&dd, MainHwnd, MainInstance);
		bRet = g_pMapScene->Init(".\\scene\\map.txt");
		g_MainChar.setCurrentMap(g_pMapScene->getMapByID(0));
		g_pMapScene->setMainCharPtr(&g_MainChar);
		g_pMapScene->setCurrentMap(g_pMapScene->getMapByID(0));
		if ( !bRet )
		{
			MessageBox(MainHwnd, "Error in Init Map Scene",
				"Error", MB_OK|MB_ICONERROR); 
			return false;
		}
		g_imode = MAP;								
	}
	else
		{ return false;	}//Error occur

	return true;
}

bool Battle_Init(unsigned int iMapID)
{
	g_imode = BATTLE;
	//ds.CleanUp();
	g_pMapScene->StopMusic();
	//Create Battle Scene
	if ( g_pBattleScene )
		return false;
	else
	{
		bool bRet;
		g_pBattleScene = new CBattleScene(&dd, MainHwnd, MainInstance);
		//g_pBattleScene->setBoss();
		bRet = g_pBattleScene->Init(".\\scene\\battle.txt");
		if ( !bRet )
		{
			MessageBox(MainHwnd, "Error in Init Battle Scene",
				"Error", MB_OK|MB_ICONERROR); 
			return false;
		}
		g_pBattleScene->setBackgroundPic(iMapID);
	}
	return true;
}

bool Battle_CleanUp()
{
	//End battle scene
	if ( g_pBattleScene )
		{ delete g_pBattleScene; g_pBattleScene = 0; }
	g_imode = MAP;
	bool bRet;
	if ( g_pMapScene )
	{
		bRet = g_pMapScene->PlayMusic();
		if ( !bRet ) { return false; }
	}
	return true;
}
