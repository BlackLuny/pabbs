#pragma once
#include <windows.h>

const DWORD Base_GameStartTime = 0x01A8C570;    //��Ϸ����ʱ��     ƫ��:1    //OD��ַ:0x0056BB6E
const DWORD Base_RoleSelfAddr = 0x01A90F40;    //��һ���ַ     ƫ��:2    //OD��ַ:0x009CB632
const DWORD Base_BufferAddr = 0x01A8BFE4;    //buff�������ַ     ƫ��:2    //OD��ַ:0x00A0F40A
const DWORD Base_MonsterArrayAddr = 0x02AB8FEC;    //�����������ַ     ƫ��:2    //OD��ַ:0x005D7552
const DWORD Base_GameWndHwndAddr = 0x01A8CDFC;    //��Ϸ���ڻ���ַ     ƫ��:2    //OD��ַ:0x00B439F4

const DWORD Base_SkillTravseOffset1 = 0x00002940;    //���������һ��ƫ��     ƫ��:1    //OD��ַ:0x0099202D
const DWORD Base_SkillTravseOffset2 = 0x00000560;    //��������ڶ���ƫ��     ƫ��:2    //OD��ַ:0x007D9C40
const DWORD Base_SkillOffset_Object = 0x000000F4;    //���ܶ���ƫ��     ƫ��:2    //OD��ַ:0x00992044

const DWORD Base_SkillCallEcxAddr = 0x01A90F60;    //����CALL ECX     ƫ��:2    //OD��ַ:0x00E51068
const DWORD Base_SkillCallAddr = 0x00AB8880;    //����CALL     ƫ��:1    //OD��ַ:0x00E5108F
const DWORD Base_SkillCallHookAddr = 0x00920DBD;    //����CALL Hook     ƫ��:1    //OD��ַ:0x00920DBD
const DWORD Base_AttackHeroCallAddr = 0x00BFA700;    //�չ�CALL     ƫ��:1    //OD��ַ:0x009B252E
const DWORD Base_FindWayCallAddr = 0x00BFA700;    //Ѱ·call     ƫ��:1    //OD��ַ:0x0081E1E2

const DWORD Base_MonsterCurrentHpOffset = 0x00000568;    //��ǰѪ��ƫ��     ƫ��:4    //OD��ַ:0x007C43B7���Ѹ��£�
const DWORD Base_MonsterCurrentMpOffset = 0x000001F0;    //��ǰ����ƫ��     ƫ��:5    //OD��ַ:0x00745BAF
const DWORD Base_MonsterBVisableOffset = 0x00003A50;    //�Ƿ�ɼ�ƫ��     ƫ��:2    //OD��ַ:0x00A5BF03
const DWORD Base_equipmentTravseOffset1 = 0x000015D0;    //װ���������ƫ��1     ƫ��:2    //OD��ַ:0x0061C94B
const DWORD Base_equipmentTravseOffset2 = 0x00000288;    //װ���������ƫ��2     ƫ��:3    //OD��ַ:0x006A0729

const DWORD Base_SkillOffset_MP = 0x000005AC;    //��������ƫ��     ƫ��:5    //OD��ַ:0x0077FBDB���Ѹ��£�
const DWORD Base_MousePointAddr = 0x1A90F60;            //���λ�û���ַ���Ѹ��£�
//����Ĵ�����ʱû��������
const DWORD Base_SkillOffset_Range1 = 0x3b0;		 //���ܷ�Χƫ�ƣ��Ѹ��£�
const DWORD Base_SkillOffset_Range2 = 0x3cc;		 //���ܷ�Χƫ�ƣ��Ѹ��£�


