#pragma once
#include "base.h"
/*
���buff
*/

class buffer :
	public base
{
public:
	buffer(DWORD dwNodeBase);
	~buffer();

	virtual char* GetName()const;
	//��ȡbuff����
	DWORD GetBufferCount()const;
};

