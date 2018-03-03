// TransferDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Transfer.h"
#include "TransferDlg.h"

#include <Tlhelp32.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_STR 256
/////////////////////////////////////////////////////////////////////////////
// CTransferDlg dialog

CTransferDlg::CTransferDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransferDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransferDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTransferDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransferDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTransferDlg, CDialog)
	//{{AFX_MSG_MAP(CTransferDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransferDlg message handlers

BOOL CTransferDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CenterWindow(GetDesktopWindow());	// center to the hpc screen

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}



void CTransferDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	HKEY hKey = NULL;  
	DWORD dwRet = 0;
	if(ERROR_SUCCESS == ::RegCreateKeyEx(HKEY_LOCAL_MACHINE, L"init", 0, L"",
										REG_OPTION_NON_VOLATILE,
										KEY_READ|KEY_WRITE,     
										NULL,            
										&hKey, &dwRet
										))
	{
		TCHAR *path = L"\\HardDisk\\Documents and Settings\\default\\TransferService.exe";
		::RegSetValueEx(hKey,L"Launch80",0,REG_SZ,(const BYTE*)path,(wcslen(path)+1)*sizeof(TCHAR));
		DWORD depend = 20;
		::RegSetValueEx(hKey,L"Depend80",0,REG_BINARY,(const BYTE*)&depend,2);
	}
	MessageBox(L"init Success");
}

void CTransferDlg::OnButton2() 
{
	//WinExec(L"TransferService.exe",SW_SHOW);
	//ShellExecute(NULL, L"open", L"TransferService.exe", NULL, NULL, SW_SHOWNORMAL); 
	//STARTUPINFO si;
	//memset(&si, 0, sizeof(STARTUPINFO));
	//si.cb = sizeof(STARTUPINFO);
	//si.dwFlags = STARTF_USESHOWWINDOW;
	//si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;
	if(CreateProcess(L"TransferService.exe",NULL,NULL,NULL,FALSE,0,NULL,NULL,NULL,&pi))
	{
		MessageBox(L"start Success");
	}
	return;
	SYSTEMTIME t;
	GetLocalTime(&t);
	CString strTime;
	strTime.Format(L"%4d%2d%2d", t.wYear, t.wMonth, t.wDay);  // 如果数字3将会显示成' 3'，不足两位时，前面以空格填充
	strTime.Replace(' ', '0');   // 将字符串中的空格用字符'0'来代替
	MessageBox(strTime); 
	return;
	// TODO: Add your control notification handler code here
	HKEY hKey = NULL;  
	DWORD dwRet = 0;
	if(ERROR_SUCCESS == ::RegCreateKeyEx(HKEY_LOCAL_MACHINE, L"Services\\transfer", 0, L"",
										REG_OPTION_NON_VOLATILE,
										KEY_READ|KEY_WRITE,     
										NULL,            
										&hKey, &dwRet
										))
	{
		//TCHAR *path = L"\\Program Files\\TransferService\\TransferService.dll";
		TCHAR *path = L"\\HardDisk\\Documents and Settings\\default\\TransferService.dll";
		::RegSetValueEx(hKey,L"Dll",0,REG_SZ,(const BYTE*)path,(wcslen(path)+1)*sizeof(TCHAR));
		DWORD order = 10,index=0,context=0,keep=1;
		::RegSetValueEx(hKey,L"Order",0,REG_DWORD,(const BYTE*)&order, sizeof(DWORD));
		TCHAR *prefix = L"TRS";
		::RegSetValueEx(hKey,L"Prefix",0,REG_SZ,(const BYTE*)prefix,(wcslen(prefix)+1)*sizeof(TCHAR));
		::RegSetValueEx(hKey,L"Index",0,REG_DWORD,(const BYTE*)&index, sizeof(DWORD));
		::RegSetValueEx(hKey,L"Context",0,REG_DWORD,(const BYTE*)&context, sizeof(DWORD));
		::RegSetValueEx(hKey,L"Keep",0,REG_DWORD,(const BYTE*)&keep, sizeof(DWORD));
	}
	//MessageBox(L"TransferService Success");
}

void CTransferDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	//ActivateService(L"transfer", 0);
	//MessageBox(L"ActivateService Success");
	LPCWSTR lpExistingFileName = L"TransferService.exe",lpNewFileName=L"\\HardDisk\\Documents and Settings\\default\\TransferService.exe";
	if(CopyFile(lpExistingFileName,lpNewFileName,TRUE))
	{
		MessageBox(L"CopyFile Success");
	}
	else
	{
		MessageBox(L"CopyFile error");
	}

}

void CTransferDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	HKEY hKey = NULL;  
	DWORD dwRet = 0;
	if(ERROR_SUCCESS == ::RegCreateKeyEx(HKEY_LOCAL_MACHINE, L"TransferService", 0, L"",
										REG_OPTION_NON_VOLATILE,
										KEY_READ|KEY_WRITE,     
										NULL,            
										&hKey, &dwRet
										))
	{
		SYSTEMTIME t;
		CMonthCalCtrl * pMonthCalendar = (CMonthCalCtrl*)GetDlgItem(IDC_MONTHCALENDAR1);
		pMonthCalendar->GetCurSel(&t);   // 获取选中项的日期
		
		DWORD year=t.wYear,month=t.wMonth,day=t.wDay;
		::RegSetValueEx(hKey,L"Year",0,REG_DWORD,(const BYTE*)&year, sizeof(DWORD));
		::RegSetValueEx(hKey,L"Month",0,REG_DWORD,(const BYTE*)&month, sizeof(DWORD));
		::RegSetValueEx(hKey,L"Day",0,REG_DWORD,(const BYTE*)&day, sizeof(DWORD));
		//CString strTime;
		//strTime.Format(L"%4d%2d%2d", sysTime.wYear, sysTime.wMonth, sysTime.wDay);  // 如果数字3将会显示成' 3'，不足两位时，前面以空格填充
		//strTime.Replace(' ', '0');   // 将字符串中的空格用字符'0'来代替
		//MessageBox(strTime); 

		//TCHAR *path = L"\\HardDisk\\Documents and Settings\\default\\TransferService.exe";
		//::RegSetValueEx(hKey,L"Launch80",0,REG_SZ,(const BYTE*)path,(wcslen(path)+1)*sizeof(TCHAR));
		//DWORD depend = 20;
		//::RegSetValueEx(hKey,L"Depend80",0,REG_BINARY,(const BYTE*)&depend,2);

		MessageBox(L"date Success");
	}
	

	
}

DWORD KillProcess( DWORD PID )
{
                HANDLE hApp ;
                DWORD ReturnValue = FALSE;
 
                hApp = OpenProcess(PROCESS_TERMINATE, FALSE, PID);
                if( hApp )
                {
                                if( !TerminateProcess( hApp, 999 ) )
                                                RETAILMSG( 1, (TEXT("KillApp: Failed to kill app, error %d\n"), GetLastError() ));
                                else
                                                ReturnValue = TRUE;
                }
                else
                                RETAILMSG( 1, (TEXT("KillApp: %X is not currently running\n"), PID ) );
 
                CloseHandle(hApp);
                return ReturnValue;
}

void CTransferDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	HWND hWnd = ::FindWindow(NULL,L"TransferService");
	if(!hWnd) return;
	DWORD dwPI;
	GetWindowThreadProcessId(hWnd, &dwPI);
	if(!dwPI) return;
	HANDLE handle = OpenProcess(0,FALSE,dwPI);
	TerminateProcess(handle,0);
	MessageBox(L"close Success");
}
