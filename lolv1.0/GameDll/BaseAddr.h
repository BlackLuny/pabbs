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


const DWORD Base_SkillOffset_Range1 = 0x3b0;		 //���ܷ�Χƫ��
const DWORD Base_SkillOffset_Range2 = 0x3cc;		 //���ܷ�Χƫ��
const DWORD Base_equipmentTravseOffset1 = 0x15d8; //װ���������ƫ��1
const DWORD Base_equipmentTravseOffset2 = 0x288;  //װ���������ƫ��2
const DWORD Base_MonsterCurrentHpOffset = 0x570;  //��ǰѪ��ƫ��
const DWORD Base_MonsterCurrentMpOffset = 0x1f8;  //��ǰ����ƫ��
const DWORD Base_SkillCallEcxAddr = 0x1E46A3C;     //����CALL ECX
const DWORD Base_SkillCallAddr = 0x009B6DC0;       //����CALL
const DWORD Base_SkillCallHookAddr = 0x0069FA5D;   //����CALL Hook

const DWORD Base_GameWndHwndAddr = 0x1A6E8D0;

