#pragma once
#include "LObject.h"
class LFile : public LObject{
public:
	BOOL init();
	BOOL load();
	BOOL load(CString path);
	BOOL unload();
	
	BOOL setBuffer();
	BOOL outputMsg();
	BOOL outputMsg(LPCTSTR m);
	BOOL outputMsg(CString m);
	BOOL outputMsg(DWORD number);
	CString path;
public:
	HANDLE h_file = NULL;
	HANDLE h_file_mapping = NULL;
	DWORD_PTR p_buffer = NULL;
	
};