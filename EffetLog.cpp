#include "EffetLog.h"

const Vector2f EffetLog::Gravity = Vector2f(0.f,1000.f);

EffetLog::EffetLog(Texture& tex, float duration)
	:SpriteGameObject(tex), duration(duration)
{
	SetOrigin(Origins::MC);
}

EffetLog::~EffetLog()
{
}

void EffetLog::Fire(const Vector2f v, float av)
{
	active = true;
	timer = 0.f;
	velocity = v;
	angularvelocity = av;

}

void EffetLog::Init()
{
	SpriteGameObject::Init();

	SetOrigin(Origins::MC);
}

void EffetLog::Release()
{
	SpriteGameObject::Release();
}

void EffetLog::Update(float dt)
{
	SpriteGameObject::Update(dt);
	timer += dt;
	if (timer > duration)
	{
		active = false;
	}

	float angle = sprite.getRotation();
	angle += angularvelocity * dt;
	sprite.setRotation(angle);

	velocity += Gravity * dt;
	Vector2f delta = velocity * dt;
	Translate(delta);
}

void EffetLog::Draw(RenderWindow& window)
{
	SpriteGameObject::Draw(window);
}

bool EffetLog::GetActive()
{
	return active;
}
