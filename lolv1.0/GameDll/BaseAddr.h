#pragma once
#include <windows.h>

const DWORD Base_GameStartTime = 0x01A6D808;	 //��Ϸ����ʱ��
const DWORD Base_RoleSelfAddr = 0x1A6DA70;		 //��һ���ַ����ұ���
const DWORD Base_BufferAddr = 0x1A7383C;		 //buff�������ַ
const DWORD Base_MonsterArrayAddr = 0x2a991bc;   //�����������ַ

const DWORD Base_SkillTravseOffset1 = 0x2948;    //���������һ��ƫ��
const DWORD Base_SkillTravseOffset2 = 0x560;     //��������ڶ���ƫ��
const DWORD Base_SkillOffset_Object = 0x0f4;     //���ܶ���ƫ��
const DWORD Base_SkillOffset_MP = 0x5a8;		 //��������ƫ��
const DWORD Base_SkillOffset_Range = 0x3b0;		 //���ܷ�Χƫ��
const DWORD Base_equipmentTravseOffset1 = 0x15d8; //װ���������ƫ��1
const DWORD Base_equipmentTravseOffset2 = 0x288;  //װ���������ƫ��2
