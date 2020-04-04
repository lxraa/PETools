
// PEtoolsDlg.h: 头文件
//

#pragma once
#include "LPEFile.h"

// CPEtoolsDlg 对话框
class CPEtoolsDlg : public CDialogEx
{
// 构造
public:
	CPEtoolsDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CPEtoolsDlg();
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PETOOLS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit file_path;
	LPEFile *pefile;
	CEdit typeInfo;
private:
	BOOL setInformation();
public:
	CEdit pe_entry;
	CEdit pe_section_number;
	CEdit pe_base_address;
	CEdit pe_image_size;
	CEdit pe_mem_align;
	CEdit pe_file_align;
	CEdit pe_base_code;
	CEdit pe_base_data;
};
