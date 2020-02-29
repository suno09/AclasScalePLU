// Demo.cpp : Defines the entry point for the application.
//

#include "stdafx.H"
#include "resource.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
int					TestPBusDrv();

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DEMO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_DEMO);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_DEMO);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_DEMO;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
                case IDM_TEST:
					TestPBusDrv();
					MessageBox(NULL,"Test OK!","Test",0);
					break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

typedef struct{
				char*	Name;	
				long	LFCode;	
				char*	Code;	
				long	BarCode;	
				long	UnitPrice;	
				long	WeightUnit;
				long	Deptment;	
				double	Tare;	
				long	ShlefTime;	
				long	PackageType;
				double	PackageWeight;
				long	Tolerance;
				char	Message1;
				char	Reserved;
				short	Reserved1;
				char	Message2;
				char	Reserved2;
				char	MultiLabel;
				char	Rebate;
				long	Account;
				}TPLU;
typedef TPLU* PPLU;
typedef TPLU TPLUCluster[4];
typedef TPLUCluster* PPLUCluster;
typedef long THotkeyTable[84];
typedef THotkeyTable* PHotkeyTable;

typedef int (CALLBACK* LPFNPBusConnect)(char *,char *,int,char *,int);
typedef int (CALLBACK* LPFNPBusDisConnect)(int);
typedef int (CALLBACK* LPFNPBusTransferPLUCluster)(PPLUCluster);
typedef int (CALLBACK* LPFNPBusTransferHotkey)(PHotkeyTable,int);
typedef int (CALLBACK* LPFNPBusPLUToStr)(PPLU,char *);
typedef int (CALLBACK* LPFNPBusStrToPLU)(char *,PPLU);


int TestPBusDrv()
{
  HINSTANCE hDLL;               // Handle to DLL
  LPFNPBusConnect PBusConnect;
  LPFNPBusDisConnect PBusDisConnect;
  LPFNPBusTransferPLUCluster PBusTransferPLUCluster;
  LPFNPBusTransferHotkey PBusTransferHotkey;
  LPFNPBusPLUToStr PBusPLUToStr;
  LPFNPBusStrToPLU PBusStrToPLU;
  long ReturnVal;
  TPLU PLU;
  TPLUCluster PLUCluster;
  THotkeyTable HotkeyTable;
  char Str[256];
  char PLUName[256];
  char PLUCode[256];
  ReturnVal=0;


  hDLL = LoadLibrary("PBusDrv.DLL");
  if (hDLL != NULL)
  {
    PBusConnect=(LPFNPBusConnect)GetProcAddress(hDLL,"PBusConnect");
	PBusDisConnect=(LPFNPBusDisConnect)GetProcAddress(hDLL,"PBusDisConnect");
	PBusTransferPLUCluster=(LPFNPBusTransferPLUCluster)GetProcAddress(hDLL,"PBusTransferPLUCluster");
	PBusTransferHotkey=(LPFNPBusTransferHotkey)GetProcAddress(hDLL,"PBusTransferHotkey");
	PBusPLUToStr=(LPFNPBusPLUToStr)GetProcAddress(hDLL,"PBusPLUToStr");
	PBusStrToPLU=(LPFNPBusStrToPLU)GetProcAddress(hDLL,"PBusStrToPLU");
    // Init
	memset(&PLU,0,sizeof(PLU));
	memset(&PLUCluster,0,sizeof(PLUCluster));
	memset(HotkeyTable,0,sizeof(HotkeyTable));
	PLU.Name="��Ǵ�ײ�";
	PLU.LFCode=12345;
	PLU.UnitPrice=8888888;
	PLUCluster[0]=PLU;
	HotkeyTable[0]=12345;
    //test PBusPLUToStr
	memset(Str,0,256);
	ReturnVal=PBusPLUToStr(&PLU,Str);
	//test PBusStrToPLU
	memset(&PLU,0,sizeof(PLU));
	PLU.Name=PLUName;
	PLU.Code=PLUCode;
	ReturnVal=PBusStrToPLU(Str,&PLU);
	//Connect
    ReturnVal=PBusConnect(".\\lfzk.dat",".\\system.cfg",1234,"COM1",0);//��ʹ��ʵ�ʵĳӺż��˿�
	//Transfer one PLU
    ReturnVal=PBusTransferPLUCluster(&PLUCluster);
	//Transfer Hotkey
    ReturnVal=PBusTransferHotkey(&HotkeyTable,0);
	//DisConnect
    ReturnVal=PBusDisConnect(1234); //��ʹ��ʵ�ʵĳӺ�
  }
  return ReturnVal;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
