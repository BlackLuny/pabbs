#pragma once

#define  MAP_NAME "lol_v1.0"
#pragma pack(1)

typedef struct _SHARED_MOMORY
{
	DWORD Base_GameStartTime;    //��Ϸ����ʱ��     ƫ��:1    //OD��ַ:0x0056BB6E
	DWORD Base_RoleSelfAddr;    //��һ���ַ     ƫ��:2    //OD��ַ:0x009CB632
	DWORD Base_BufferAddr;    //buff�������ַ     ƫ��:2    //OD��ַ:0x00A0F40A
	DWORD Base_MonsterArrayAddr;    //�����������ַ     ƫ��:2    //OD��ַ:0x005D7552
	DWORD Base_GameWndHwndAddr;    //��Ϸ���ڻ���ַ     ƫ��:2    //OD��ַ:0x00B439F4

	DWORD Base_SkillTravseOffset1;    //���������һ��ƫ��     ƫ��:1    //OD��ַ:0x0099202D
	DWORD Base_SkillTravseOffset2;    //��������ڶ���ƫ��     ƫ��:2    //OD��ַ:0x007D9C40
	DWORD Base_SkillOffset_Object;    //���ܶ���ƫ��     ƫ��:2    //OD��ַ:0x00992044

	DWORD Base_SkillCallEcxAddr;    //����CALL ECX     ƫ��:2    //OD��ַ:0x00E51068
	DWORD Base_SkillCallAddr;    //����CALL     ƫ��:1    //OD��ַ:0x00E5108F
	DWORD Base_SkillCallHookAddr;    //����CALL Hook     ƫ��:1    //OD��ַ:0x00920DBD
	DWORD Base_AttackHeroCallAddr;    //�չ�CALL     ƫ��:1    //OD��ַ:0x009B252E
	DWORD Base_FindWayCallAddr;    //Ѱ·call     ƫ��:1    //OD��ַ:0x0081E1E2

	DWORD Base_MonsterCurrentHpOffset;    //��ǰѪ��ƫ��     ƫ��:4    //OD��ַ:0x007C43B7���Ѹ��£�
	DWORD Base_MonsterCurrentMpOffset;    //��ǰ����ƫ��     ƫ��:5    //OD��ַ:0x00745BAF
	DWORD Base_MonsterBVisableOffset;    //�Ƿ�ɼ�ƫ��     ƫ��:2    //OD��ַ:0x00A5BF03
	DWORD Base_equipmentTravseOffset1;    //װ���������ƫ��1     ƫ��:2    //OD��ַ:0x0061C94B
	DWORD Base_equipmentTravseOffset2;    //װ���������ƫ��2     ƫ��:3    //OD��ַ:0x006A0729

	DWORD Base_SkillOffset_MP;    //��������ƫ��     ƫ��:5    //OD��ַ:0x0077FBDB���Ѹ��£�
	DWORD Base_MousePointAddr;            //���λ�û���ַ���Ѹ��£�
											//����Ĵ�����ʱû��������
	DWORD Base_SkillOffset_Range1;		 //���ܷ�Χƫ�ƣ��Ѹ��£�
	DWORD Base_SkillOffset_Range2;		 //���ܷ�Χƫ�ƣ��Ѹ��£�

	DWORD Base_MonsterOrientationXOffset;  //���X����
	DWORD Base_MonsterBMovingOffset; //����Ƿ��ƶ�
	
	bool bLockQ;
	bool bLockW;
	bool bLockE;
	bool bLockR;
	bool bOpenAA;
}SHARED_MEMORY, *PSHARED_MOMERY;
#pragma pack()