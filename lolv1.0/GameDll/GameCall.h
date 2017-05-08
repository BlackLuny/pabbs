#pragma once
#include <mutex>
#include "utils.h"
#include "BaseAddr.h"
#include "person.h"
extern DWORD g_MonsterObj;
class GameCall
{
public:
	~GameCall();
	static GameCall* GetInstance();
	//��ȡ����Ϸʱ��
	float GetClientTickTime()const;
	//��ͨ����call
	bool HeroAttack(DWORD dwNodeBase);
	//���ܹ���
	bool UseSkill(DWORD _index, DWORD monsObj);
	//Hook ����call
	bool HookSkillUse();
	//ֹͣ����
	bool StopAction();
	//Ѱ·
	bool FindWay(EM_POINT_3D pnt);
	//��ȡ���λ��
	EM_POINT_3D GetMousePnt()const;
private:
	static GameCall* m_pInstance;
	static std::mutex m_mutex;
private:
	GameCall();
	GameCall(const GameCall& _call);
	GameCall operator= (const GameCall& _call);
private:
	bool m_bUsedAttack;
	bool m_bUsedSkill;
};


void __stdcall SkillHookStub(DWORD skillObj, PFLOAT xyz, PDWORD monsObj);