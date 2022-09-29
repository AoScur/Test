#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include "Singleton.h"
#include "rapidcsv.h"

using namespace std;
using namespace sf;

//싱글턴
//리소스 전부 로드(파일에 입력)// 릴리즈
//Get(), 

enum class ResourceTypes
{
	Texture,
	Font,
	SoundBuffer,
};

class ResourceMgr : public Singleton<ResourceMgr>
{
private:
	map<string, Texture*> texMap;
	map<string, Font*> fontMap;
	map<string, SoundBuffer*> soundMap;

public:
	ResourceMgr();
	~ResourceMgr();

	static string FilePath;

	void RealeaseAll();

	bool LoadAll();
	bool Load(ResourceTypes type, string id);
	bool LoadTexture(string id);
	bool LoadFont(string id);
	bool LoadSoundBuffer(string id);

	Texture* GetTexture(string id);
	Font* GetFont(string id);
	SoundBuffer* GetSound(string id);

};

