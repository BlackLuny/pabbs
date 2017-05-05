#pragma once
#include <mutex>
#include "utils.h"
#include "BaseAddr.h"


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
private:
	static GameCall* m_pInstance;
	static std::mutex m_mutex;
private:
	GameCall();
	GameCall(const GameCall& _call);
	GameCall operator= (const GameCall& _call);
};


void __stdcall SkillHookStub(DWORD skillObj, PFLOAT xyz, PDWORD monsObj);