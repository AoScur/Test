#pragma once
#include "SpriteGameObject.h"

class EffetLog : public SpriteGameObject
{
protected:
	//중력
	//속도(방향)
	//각속도(회전)
	//타이머
	Vector2f velocity;
	float angularvelocity;
	float duration;
	float timer;
	bool active;

public:
	//속도(방향), 각속도(회전)
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

