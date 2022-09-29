#pragma once
#include "SpriteGameObject.h"

class MoveAtoBObject : public SpriteGameObject
{
protected:
	float speed;
	Vector2i speedRange;
	Vector2i yRange;	

	Vector2f direction;

	Vector2f startPos;
	Vector2f endPos;
public:
	MoveAtoBObject(Texture& tex, Vector2f pos = Vector2f());
	virtual ~MoveAtoBObject();

	virtual void Init() override;
	virtual void Update(float dt) override;

	void Set(Vector2i sRange, Vector2i yRange, Vector2f start, Vector2f end);
};