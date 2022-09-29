#pragma once
#include "SpriteGameObject.h"

class EffetLog : public SpriteGameObject
{
protected:
	//�߷�
	//�ӵ�(����)
	//���ӵ�(ȸ��)
	//Ÿ�̸�
	Vector2f velocity;
	float angularvelocity;
	float duration;
	float timer;
	bool active;

public:
	//�ӵ�(����), ���ӵ�(ȸ��)
	static const Vector2f Gravity;
	
	EffetLog(Texture& tex, float duration);
	virtual ~EffetLog();

	void Fire(const Vector2f v, float av);
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	bool GetActive();

	



};

