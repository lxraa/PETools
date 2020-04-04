#pragma once
#include "LFile.h"
class LPEFile : public LFile{
public:
	LPEFile(CString path);
	DWORD getPEHeaderOffset();

	PIMAGE_DOS_HEADER dos_header = NULL;
	PIMAGE_NT_HEADERS32 nt_headers32 = NULL;
	PIMAGE_NT_HEADERS64 nt_headers64 = NULL;
	PIMAGE_SECTION_HEADER first_section_table = NULL;
	PIMAGE_EXPORT_DIRECTORY export_dir = NULL;
	DWORD section_number = 0;
	INT type = 0;
private:
	BOOL setDosHeader();
	BOOL setNtHeader();
	BOOL setFirstSectionTable();
	BOOL setType();
	BOOL setExportDir();
};
