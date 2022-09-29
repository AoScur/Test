#include "Utils.h"

std::random_device Utils::rd;
std::mt19937 Utils::gen(Utils::rd());

void Utils::SetOrigin(Text& obj, Origins origin)
{
	FloatRect bounds = obj.getLocalBounds();
	Vector2f originPos;
	originPos.x = bounds.width * ((int)origin % 3) * 0.5f;
	originPos.y = bounds.height * ((int)origin / 3) * 0.5f;
	obj.setOrigin(originPos);
}

void Utils::SetOrigin(Sprite& obj, Origins origin)
{
	FloatRect bounds = obj.getLocalBounds();
	Vector2f originPos;
	originPos.x = bounds.width * ((int)origin % 3) * 0.5f;
	originPos.y = bounds.height * ((int)origin / 3) * 0.5f;
	obj.setOrigin(originPos);
}

int Utils::Range(int min, int maxExclude)
{
	return (gen() % (maxExclude - min + 1)) + min;
}

float Utils::Range(float min, float maxExclude)
{
	float div = maxExclude - min + 1.0f;
	// 何悼家荐痢 积己
	std::uniform_real_distribution<> dist(min, maxExclude);
	return dist(gen);
}