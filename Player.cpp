#include "Player.h"
#include "InputManager.h"


Player::Player(Texture& player, Texture& rip, Texture& _axe, Sound& Chop, Sound& Death,bool& ispause)
	: SpriteGameObject(player),
	texPlayer(player), texRIP(rip), originalPos(2),
	isChop(false), isAlive(true), pos(Sides::Right), isPause(ispause),
	soundChop(Chop),soundDeath(Death)
{
	axe.setTexture(_axe);
	Utils::SetOrigin(axe, Origins::MR);

	Vector2f size = GetSize();
	axePos.x = -size.x * 0.5f + 70;
	axePos.y = -size.y * 0.5f + 30;

	SetOrigin(Origins::BC);
	texLog.loadFromFile("graphics/log.png");
	for (int i = 0; i < 100; ++i)
	{
		auto log = new EffetLog(texLog, 5.f);
		unuseLogs.push_back(log);
	}
}
void Player::Set(Vector2f center)
{
	centerPos = center;
}

void Player::Init()
{
	Vector2f size = GetSize();

	originalPos[(int)Sides::Left].x = centerPos.x - size.x * 2;
	originalPos[(int)Sides::Left].y = centerPos.y;

	originalPos[(int)Sides::Right].x = centerPos.x + size.x * 2;
	originalPos[(int)Sides::Right].y = centerPos.y;
	SetPosition(originalPos[(int)pos]);

	//pos = Sides::Right;

	sprite.setTexture(texPlayer,true);
	Utils::SetOrigin(sprite, Origins::BC);
	SetFlipX(pos == Sides::Left);
	isAlive = true;
	isChop = false;
}


void Player::Release()
{
	for (auto log : unuseLogs)
	{
		delete log;
	}
	unuseLogs.clear();

	for (auto log : useLogs)
	{
		delete log;
	}
	useLogs.clear();
}

void Player::Update(float dt)
{
	SpriteGameObject::Update(dt);

	auto it = useLogs.begin();
	while (it != useLogs.end())
	{
		(*it)->Update(dt);
		if (!(*it)->GetActive())
		{
			unuseLogs.push_back(*it);
			it = useLogs.erase(it);
		}
		else
		{
			++it;
		}
	}
	//if (InputManager::GetKeyDown(Keyboard::Space))
	//{
	//	if (isAlive)
	//	{
	//		Die();
	//	}
	//	else
	//	{
	//		Init();
	//	}
	//	return;
	//}
	//if (!isAlive||!isPause)
	//	return;
	if (!isChop && dt!=0)
	{
		if (InputManager::GetKeyDown(Keyboard::Left))
		{
			Chop(Sides::Left);
		}
		if (InputManager::GetKeyDown(Keyboard::Right))
		{
			Chop(Sides::Right);
		}
	}
	else
	{
		if (Player::GetPos() == Sides::Left && InputManager::GetKeyUp(Keyboard::Left))
		{
			isChop = false;
		}
		if (Player::GetPos() == Sides::Right && InputManager::GetKeyUp(Keyboard::Right))
		{
			isChop = false;
		}
	}
}

void Player::Draw(RenderWindow& window)
{
	SpriteGameObject::Draw(window);
	if (isChop && isAlive)
	{
		window.draw(axe);
	}
	for (auto log : useLogs)
	{
		log->Draw(window);
	}
}


void Player::SetPosition(Vector2f pos)
{
	SpriteGameObject::SetPosition(pos);
	Vector2f axePos2 = axePos;
	if (axe.getScale().x < 0)
	{
		axePos2.x *= -1;
	}
	axe.setPosition(pos + axePos);
}

bool Player::GetAlive() const
{
	return isAlive;
}

Sides Player::GetPos() const
{
	return pos;
}

void Player::Die()
{
	//플레이어 죽음
	//1. 그림 바꾸기
	//2. 도끼 x
	//3. 키 입력 막아야 하고
	isAlive = false;
	isChop = false;
	sprite.setTexture(texRIP,true);
	SetFlipX(false);
	Utils::SetOrigin(sprite, Origins::BC);
	soundDeath.play();
}

void Player::Chop(Sides side)
{	
	pos = side;
	SetFlipX(pos == Sides::Left);
	SetPosition(originalPos[(int)pos]);
	isChop = true;
	soundChop.play();
	ShowLogEffect();
}

void Player::SetFlipX(bool flip)
{
	SpriteGameObject::SetFlipX(flip);

	Vector2f scale = axe.getScale();

	scale.x = flip ? -abs(scale.x) : abs(scale.x);
	axe.setScale(scale);
}

void Player::ShowLogEffect()
{
	if (unuseLogs.empty())
		return;

	auto log = unuseLogs.front();
	unuseLogs.pop_front();
	useLogs.push_back(log);

	Vector2f force;
	force.x = pos == Sides::Left ? 1500 : -1500;
	force.y = -1500;
	float aForce = pos == Sides::Left ? 360*2 : -360*2;

	
	Vector2f pos = centerPos;
	pos.y = axe.getPosition().y;
	log->SetPosition(pos);
	log->SetOrigin(Origins::MC);
	log->Fire(force, aForce);
}
