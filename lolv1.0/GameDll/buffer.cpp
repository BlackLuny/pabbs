#include "stdafx.h"
#include "buffer.h"



buffer::buffer(DWORD dwNodeBase):base(dwNodeBase)
{

}

buffer::~buffer()
{
}

char* buffer::GetName() const
{
	__try
	{
		return (char*)(utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x10));
	}
	__except (1) {
		utils::GetInstance()->log("ERROR: buffer::GetName() �����쳣��\n");
		return nullptr;
	}
}

DWORD buffer::GetBufferCount() const
{
	__try {
		return utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x2c);
	}
	__except (1) {
		return 0;
	}
}
