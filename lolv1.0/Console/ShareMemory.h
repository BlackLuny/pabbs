#pragma once
#include "CShareStruct.h"
class CShareMemory
{
public:
	CShareMemory();
	~CShareMemory();

	//���������ڴ�
	bool CreateSharedMemory();
	//���ٹ����ڴ�
	bool DestorySharedMemory();
	PSHARED_MOMERY GetPointerOfMapView();
private:
	SHARED_MEMORY *m_pSharedMomory;
	HANDLE m_hMapping;
};

