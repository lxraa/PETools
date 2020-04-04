
// PEtoolsDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "PEtools.h"
#include "PEtoolsDlg.h"
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


// CPEtoolsDlg 对话框



CPEtoolsDlg::CPEtoolsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PETOOLS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CPEtoolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, file_path);
	DDX_Control(pDX, IDC_EDIT10, typeInfo);
	DDX_Control(pDX, IDC_EDIT2, pe_entry);
	DDX_Control(pDX, IDC_EDIT3, pe_section_number);
	DDX_Control(pDX, IDC_EDIT4, pe_base_address);
	DDX_Control(pDX, IDC_EDIT5, pe_image_size);
	DDX_Control(pDX, IDC_EDIT6, pe_mem_align);
	DDX_Control(pDX, IDC_EDIT7, pe_file_align);
	DDX_Control(pDX, IDC_EDIT8, pe_base_code);
	DDX_Control(pDX, IDC_EDIT9, pe_base_data);
}

BEGIN_MESSAGE_MAP(CPEtoolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPEtoolsDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON1, &CPEtoolsDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPEtoolsDlg 消息处理程序

BOOL CPEtoolsDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPEtoolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPEtoolsDlg::OnPaint()
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
HCURSOR CPEtoolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CPEtoolsDlg::setInformation() {
	INT type = pefile->type;
	CString t, entry, section_number, base_address, image_size, mem_align, file_align, base_code, base_data;

	
	t.Format(TEXT("%d位"), type);
	typeInfo.SetWindowTextW(t);

	if (type == 32){
		//程序入口
		entry.Format(TEXT("%p"), pefile->nt_headers32->OptionalHeader.AddressOfEntryPoint);
		pe_entry.SetWindowTextW(entry);
		//区块数目
		section_number.Format(TEXT("%d"), pefile->nt_headers32->FileHeader.NumberOfSections);
		pe_section_number.SetWindowTextW(section_number);
		//镜像基址
		base_address.Format(TEXT("%p"), pefile->nt_headers32->OptionalHeader.ImageBase);
		pe_base_address.SetWindowTextW(base_address);
		//镜像大小
		image_size.Format(TEXT("%p"), pefile->nt_headers32->OptionalHeader.SizeOfImage);
		pe_image_size.SetWindowTextW(image_size);
		//内存对齐
		mem_align.Format(TEXT(""));
		pe_mem_align.SetWindowTextW(mem_align);
		//文件对齐
		file_align.Format(TEXT(""));
		pe_file_align.SetWindowTextW(file_align);
		//代码基址
		base_code.Format(TEXT(""));
		pe_base_code.SetWindowTextW(base_code);
		//数据基址
		base_data.Format(TEXT(""));
		pe_base_data.SetWindowTextW(base_data);

	}
	
	return TRUE;
}


void CPEtoolsDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog file(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.dll)|*.dll|Describe Files (*.exe)|*.exe|All Files (*.*)|*.*||"), NULL);
	if (file.DoModal() != IDOK) {
		MessageBox(TEXT("error"));
		return;
		
	}
	file_path.SetWindowTextW(file.GetPathName());
	this->pefile = new LPEFile(file.GetPathName());
	/*CString s;
	s.Format(TEXT("%p %d %p %p"), pefile->first_section_table, pefile->section_number, pefile->nt_headers32, pefile->nt_headers64);
	MessageBox(s);*/
	setInformation();
	return;
}

CPEtoolsDlg::~CPEtoolsDlg() {
	if (this->pefile != NULL) {
		delete this->pefile;
	}
}