#include "stdafx.h"
#include "LFile.h"


BOOL LFile::init() {
	return TRUE;
}
BOOL LFile::load() {
	return TRUE;
}

BOOL LFile::load(CString path) {
	this->h_file = CreateFile(path, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (this->h_file == INVALID_HANDLE_VALUE) {
		outputMsg();
		return FALSE;
	}
	this->h_file_mapping = CreateFileMapping(this->h_file, NULL, PAGE_READWRITE, 0, 0x4000000, NULL);
	if (this->h_file_mapping == NULL) {
		outputMsg();
		return FALSE;
	}
	outputMsg(TEXT("加载文件成功"));
	return TRUE;
}

BOOL LFile::unload() {
	return TRUE;
}

BOOL LFile::outputMsg(LPCTSTR m) {
	MessageBox(NULL, m, TEXT("1"), MB_OK);
	return TRUE;
}
BOOL LFile::outputMsg(CString m) {
	MessageBox(NULL, m, TEXT("1"), MB_OK);
	return TRUE;
}

BOOL LFile::outputMsg(DWORD number){
	CString s;
	s.Format(TEXT("%p"), number);
	MessageBox(NULL, s, TEXT("1"), MB_OK);
	return TRUE;
}
BOOL LFile::outputMsg() {
	DWORD err_code = GetLastError();
	LPTSTR err_message = NULL;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, err_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&err_message, 0, NULL);
	if (err_message != NULL) {
		MessageBox(NULL, err_message, TEXT("1"), MB_OK);
		LocalFree(err_message);
		err_message = NULL;
	}
	
	return TRUE;
}
BOOL LFile::setBuffer() {
	DWORD size = GetFileSize(this->h_file, 0);
	this->p_buffer = (DWORD_PTR)MapViewOfFile(this->h_file_mapping, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, size);
	return TRUE;
}