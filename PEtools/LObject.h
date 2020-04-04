#pragma once
class LObject {
public:
	virtual BOOL init() = 0;
	virtual BOOL load() = 0;
	virtual BOOL unload() = 0;
	virtual BOOL outputMsg() = 0;
};