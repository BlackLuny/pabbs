#pragma once
#include <windows.h>

const DWORD Base_GameStartTime = 0x01A6D808;    //��Ϸ����ʱ��     ƫ��:1    //OD��ַ:0x0060610E
const DWORD Base_RoleSelfAddr = 0x01A6DA70;    //��һ���ַ     ƫ��:2    //OD��ַ:0x0055AF00
const DWORD Base_BufferAddr = 0x01A7383C;    //buff�������ַ     ƫ��:2    //OD��ַ:0x00565F9A
const DWORD Base_MonsterArrayAddr = 0x02A991BC;    //�����������ַ     ƫ��:2    //OD��ַ:0x006FA547
const DWORD Base_SkillTravseOffset1 = 0x00002948;    //���������һ��ƫ��     ƫ��:1    //OD��ַ:0x006C246D
const DWORD Base_SkillTravseOffset2 = 0x00000560;    //��������ڶ���ƫ��     ƫ��:2    //OD��ַ:0x0059EC70
const DWORD Base_SkillOffset_Object = 0x000000F4;    //���ܶ���ƫ��     ƫ��:2    //OD��ַ:0x006C2484
const DWORD Base_SkillOffset_MP = 0x000005A8;    //��������ƫ��     ƫ��:5    //OD��ַ:0x0077FBDB
const DWORD Base_SkillCallEcxAddr = 0x01E46A3C;    //����CALL ECX     ƫ��:2    //OD��ַ:0x00DD9028
const DWORD Base_SkillCallAddr = 0x009B6DC0;    //����CALL     ƫ��:1    //OD��ַ:0x00DD904F
const DWORD Base_SkillCallHookAddr = 0x0069FA5D;    //����CALL Hook     ƫ��:1    //OD��ַ:0x0069FA5D
const DWORD Base_GameWndHwndAddr = 0x01A6E8D0;    //��Ϸ���ڻ���ַ     ƫ��:2    //OD��ַ:0x0055DC54
const DWORD Base_MonsterCurrentHpOffset = 0x00000570;    //��ǰѪ��ƫ��     ƫ��:4    //OD��ַ:0x007C43B7
const DWORD Base_MonsterCurrentMpOffset = 0x000001F8;    //��ǰ����ƫ��     ƫ��:5    //OD��ַ:0x008967DF
const DWORD Base_equipmentTravseOffset2 = 0x00000288;    //װ���������ƫ��2     ƫ��:3    //OD��ַ:0x00B8C079
const DWORD Base_equipmentTravseOffset1 = 0x000015D8;    //װ���������ƫ��1     ƫ��:2    //OD��ַ:0x00B3CCDB
const DWORD Base_MonsterBVisableOffset = 0x0000394C;    //�Ƿ�ɼ�ƫ��     ƫ��:2    //OD��ַ:0x00A9CB43
const DWORD Base_MousePointAddr = 0x1E46A3C;            //���λ�û���ַ
const DWORD Base_FindWayCallAddr = 0x00827650; //Ѱ·call
const DWORD Base_AttackHeroCallAddr = 0x00827650; //�չ�CALL
//����Ĵ�����ʱû��������
const DWORD Base_SkillOffset_Range1 = 0x3b0;		 //���ܷ�Χƫ��
const DWORD Base_SkillOffset_Range2 = 0x3cc;		 //���ܷ�Χƫ��


