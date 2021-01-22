
// BinMergeToolDlg.h: 头文件
//

#pragma once

// CBinMergeToolDlg 对话框
class CBinMergeToolDlg : public CDialogEx
{
// 构造
public:
	CBinMergeToolDlg(CWnd* pParent = nullptr);	// 标准构造函数
	enum OutputType {
		HEXDEC = 0, // 暂不支持
		BINARY
	};

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BINMERGETOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	CString m_appfilepath, m_appname; // APP全路径、APP文件名
	CString m_loaderfilepath, m_loadername; // Loader全路径、Loader文件名
	CString m_FileExtend; // 输出文件后缀
	CString m_OffsetAddr; // APP地址偏移
	DWORD m_app_addr; // APP地址

	CStatic m_proc_value; // 进度条数值显示
	CEdit m_addr; // APP地址
	CEdit m_apppath; // APP文件路径
	CEdit m_loaderpath; // Loader路径
	CProgressCtrl m_prog; // 进度条

	// 自定义函数
	void OpenFileDlg(CString& filepath, CString& filename);
	BOOL CombinFile(CString loader_path, CString app_path, CString output_path, unsigned long offset_addr);
	BOOL StrAddrToHex(CString strAddr, DWORD& p_addr);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedLoaderload();
	afx_msg void OnBnClickedAppload();
	afx_msg void OnClose();
	afx_msg void OnBnClickedMerge();
public:

};
