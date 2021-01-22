/*
 *********************************************************************************************************
 *
 *	 工具名称 : BinMergeTool
 *	 文件名称 : BinMergeToolDlg.cpp
 *	 版    本 : V1.0.0.1
 *	 修改记录 :
 *		 版本号       日期       作者    说明
 *		 v1.0.0.1    2021-01-22 veis    首发
 *
 *	 Copyright (C), 2021-2022, 博客园 https://www.cnblogs.com/veis/
 *
 *********************************************************************************************************
 */

// BinMergeToolDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "BinMergeTool.h"
#include "BinMergeToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBinMergeToolDlg 对话框
CBinMergeToolDlg::CBinMergeToolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BINMERGETOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBinMergeToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OFFSET_ADDR, m_addr);
	DDX_Control(pDX, IDC_APP_PATH, m_apppath);
	DDX_Control(pDX, IDC_LOADER_PATH, m_loaderpath);
	DDX_Control(pDX, IDC_PROGRESS, m_prog);
	DDX_Control(pDX, IDC_STATIC1, m_proc_value);
}

BEGIN_MESSAGE_MAP(CBinMergeToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOADERLOAD, &CBinMergeToolDlg::OnBnClickedLoaderload)
	ON_BN_CLICKED(IDC_APPLOAD, &CBinMergeToolDlg::OnBnClickedAppload)
	ON_BN_CLICKED(IDC_MERGE, &CBinMergeToolDlg::OnBnClickedMerge)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CBinMergeToolDlg 消息处理程序
BOOL CBinMergeToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_FileExtend = _T("bin");
	m_prog.SetRange32(0, 4096);
	m_prog.SetPos(0);
	m_prog.SetBarColor(RGB(0, 0, 255));
	m_proc_value.SetWindowText(_T("0%"));
	m_addr.SetWindowText(_T("4000"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBinMergeToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBinMergeToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBinMergeToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CBinMergeToolDlg::OnBnClickedLoaderload()
{
	// TODO: 在此添加控件通知处理程序代码
	OpenFileDlg(m_loaderfilepath, m_loadername);
	m_loaderpath.SetWindowText(m_loaderfilepath);
}

void CBinMergeToolDlg::OnBnClickedAppload()
{
	// TODO: 在此添加控件通知处理程序代码
	OpenFileDlg(m_appfilepath, m_appname);
	m_apppath.SetWindowText(m_appfilepath);
}

void CBinMergeToolDlg::OnBnClickedMerge()
{
	// TODO: 在此添加控件通知处理程序代码
	CString outputFileName;
	// m_FileExtend = m_outputtype.GetCheck() ? _T("bin") : _T("hex");
	outputFileName.Format(_T("%s(%s).%s"), m_appname.GetBuffer(), m_loadername.GetBuffer(), m_FileExtend.GetBuffer());

	m_addr.GetWindowText(m_OffsetAddr);
	StrAddrToHex(m_OffsetAddr, m_app_addr);

	CFileDialog SavefileDlg(FALSE, m_FileExtend, outputFileName, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Binary Files (*.bin)|*.bin|"));
	if (SavefileDlg.DoModal() == IDOK)
	{
		CString path = SavefileDlg.GetPathName();
		CombinFile(m_loaderfilepath, m_appfilepath, path, m_app_addr);
		m_app_addr = 0;
	}
}

void CBinMergeToolDlg::OpenFileDlg(CString& filepath, CString& filename)
{
	// TODO: 在此处添加实现代码.
	static TCHAR BASED_CODE szFilter[] = 
		_T("Binary Files (*.bin)|*.bin|")
		_T("Hex Files (*.hex)|*.hex|");

	CFileDialog OpenfileDlg(TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter, NULL, 0, TRUE);

	if (OpenfileDlg.DoModal() == IDOK)
	{
		filepath = OpenfileDlg.GetPathName(); // 包含路径和扩展名
		filename = OpenfileDlg.GetFileTitle(); // 不含扩展名和路径
	}
}

BOOL CBinMergeToolDlg::CombinFile(CString loader_path, CString app_path, CString output_path, unsigned long offset_addr)
{
	CFile fp_loader, fp_app, fp_dest;
	TCHAR szError[1024];
	CFileException ex;

	if (!fp_loader.Open(loader_path,
		CFile::modeRead, &ex))
	{
		ex.GetErrorMessage(szError, 1024);
		_tprintf_s(_T("Couldn't open source file: %1024s"), szError);
		MessageBox(szError, _T("错误提示"), MB_ICONERROR);
		return FALSE;
	}

	if (!fp_app.Open(app_path,
		CFile::modeRead, &ex))
	{
		ex.GetErrorMessage(szError, 1024);
		_tprintf_s(_T("Couldn't open source file: %1024s"), szError);
		MessageBox(szError, _T("错误提示"), MB_ICONERROR);
		return FALSE;
	}

	if (!fp_dest.Open(output_path,
		CFile::modeCreate | CFile::modeWrite, &ex))
	{
		ex.GetErrorMessage(szError, 1024);
		_tprintf_s(_T("Couldn't open source file: %1024s"), szError);
		MessageBox(szError, _T("错误提示"), MB_ICONERROR);
		return FALSE;
	}

	DWORD loader_size = (DWORD)fp_loader.GetLength();
	DWORD app_size = (DWORD)fp_app.GetLength();

	if (loader_size > offset_addr)
		return FALSE;

	int nPos = 0;
	int max_range = offset_addr + app_size;
	CString curValue;
	m_prog.SetRange32(0, max_range);
	m_prog.SetPos(nPos);

	BYTE* pbuf = new BYTE[loader_size];

	if (NULL != pbuf)
	{
		// 写入loader
		fp_loader.Read(pbuf, loader_size);
		fp_dest.Write(pbuf, loader_size);
		nPos += loader_size;
		m_prog.SetPos(nPos);
		curValue.Format(_T("%d%%"), nPos * 100 / max_range);
		m_proc_value.SetWindowText(curValue);

		// 写入剩余字节为0XFF
		unsigned char ch = 0xff;
		for (size_t i = 0; i < offset_addr - loader_size; i++)
			fp_dest.Write(&ch, 1);

		nPos += offset_addr - loader_size;
		m_prog.SetPos(nPos);
		curValue.Format(_T("%d%%"), nPos * 100 / max_range);
		m_proc_value.SetWindowText(curValue);

		// 写入APP
		delete []pbuf;
		pbuf = new BYTE[app_size];
		if (pbuf != NULL)
		{
			fp_app.Read(pbuf, app_size);
			fp_dest.Write(pbuf, app_size);
			delete[]pbuf;

			nPos += app_size;
			m_prog.SetPos(nPos);
			curValue.Format(_T("%d%%"), nPos * 100 / max_range);
			m_proc_value.SetWindowText(curValue);
		}
	}
	fp_loader.Close();
	fp_app.Close();
	fp_dest.Close();

	Sleep(1000);
	m_prog.SetPos(0);
	m_proc_value.SetWindowText(_T("完成"));

	return TRUE;
}

BOOL CBinMergeToolDlg::StrAddrToHex(CString strAddr, DWORD& p_addr)
{
	if (strAddr.IsEmpty())
		return FALSE;

	const TCHAR hex[] = _T("0123456789ABCDEF");

	int len = strAddr.GetLength();
	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < 16; j++) 
		{
			if (strAddr.GetAt(i) == hex[j])
			{
				p_addr = (p_addr << 4) | j;
				break;
			}
		}
	}
	return TRUE;
}

void CBinMergeToolDlg::OnCancel()
{
}

void CBinMergeToolDlg::OnOK()
{
}

void CBinMergeToolDlg::OnClose()
{
	CDialogEx::OnCancel();
}
