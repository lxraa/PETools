#include "stdafx.h"

#include "LPEFile.h"


LPEFile::LPEFile(CString path) {
	this->path = path;
	this->load(path);
	this->setDosHeader();
	this->setType();
	this->setNtHeader();
	this->setExportDir();
	this->setFirstSectionTable();
	
}

DWORD LPEFile::getPEHeaderOffset() {
	if (this->dos_header == NULL) {
		this->setDosHeader();
	}

	return this->dos_header->e_lfanew;
}


BOOL LPEFile::setDosHeader() {
	if (this->p_buffer == NULL) {
		this->setBuffer();
	}

	
	this->dos_header = (PIMAGE_DOS_HEADER)this->p_buffer;
	return TRUE;
}

BOOL LPEFile::setExportDir() {
	if (this->nt_headers32 == NULL && this->nt_headers64 == NULL) {
		this->setNtHeader();
	}
	if (this->type == 32) {
		this->export_dir = (PIMAGE_EXPORT_DIRECTORY)(this->nt_headers32->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	}
	else {
		this->export_dir = (PIMAGE_EXPORT_DIRECTORY)(this->nt_headers64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	}
	return TRUE;
}
BOOL LPEFile::setNtHeader() {
	if (this->dos_header == NULL) {
		this->setDosHeader();
	}
	if (this->type == 32) {
		this->nt_headers32 = (PIMAGE_NT_HEADERS32)(this->p_buffer + (DWORD_PTR)this->dos_header->e_lfanew);
	}
	else {
		this->nt_headers64 = (PIMAGE_NT_HEADERS64)(this->p_buffer + (DWORD_PTR)this->dos_header->e_lfanew);
	}
	
	return TRUE;
}

BOOL LPEFile::setFirstSectionTable() {
	if (this->nt_headers32 == NULL && this->nt_headers64 == NULL) {
		this->setNtHeader();
	}
	if (this->type == 32) {
		this->first_section_table = (PIMAGE_SECTION_HEADER)((DWORD_PTR)this->nt_headers32 + sizeof(IMAGE_NT_HEADERS32));
	}
	else {
		this->first_section_table = (PIMAGE_SECTION_HEADER)((DWORD_PTR)this->nt_headers64 + sizeof(IMAGE_NT_HEADERS64));
	}

	return TRUE;
}

BOOL LPEFile::setType() {
	if (this->dos_header == NULL) {
		this->setDosHeader();
	}
	PIMAGE_NT_HEADERS nt_header = (PIMAGE_NT_HEADERS)((DWORD_PTR)this->dos_header + this->dos_header->e_lfanew);
	if (nt_header->OptionalHeader.Magic == 0x10B) {
		this->type = 32;
	}
	else if (nt_header->OptionalHeader.Magic == 0x20B) {
		this->type = 64;
	}
	else {
		this->outputMsg(TEXT("unknown pe file type"));
		TerminateProcess(GetCurrentProcess(), 0);
		return FALSE;
	}

	return TRUE;

}