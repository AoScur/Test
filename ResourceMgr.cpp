#include "ResourceMgr.h"
string ResourceMgr::FilePath("Resources.csv");

ResourceMgr::ResourceMgr()
{
    LoadAll();
}

ResourceMgr::~ResourceMgr()
{
    RealeaseAll();
}

void ResourceMgr::RealeaseAll()
{
    for(auto it : texMap)
    {
        delete it.second;
    }
    for (auto it : fontMap)
    {
        delete it.second;
    }
    for (auto it : soundMap)
    {
        delete it.second;
    }

}

bool ResourceMgr::LoadAll()
{
    RealeaseAll();

    rapidcsv::Document doc(FilePath, rapidcsv::LabelParams(0, -1));

    auto ids = doc.GetColumn<string>(0);
    auto types = doc.GetColumn<int>(1);

    for (int i = 0; i < doc.GetRowCount(); i++)
    {
        if (!Load((ResourceTypes)types[i], ids[i]))
        {
            return false;
        }
    }
    return true;
}

bool ResourceMgr::Load(ResourceTypes type, string id)
{
    switch (type)
    {
    case ResourceTypes::Texture:
        return LoadTexture(id);
    case ResourceTypes::Font:
        return LoadFont(id);
    case ResourceTypes::SoundBuffer:
        return LoadSoundBuffer(id);
    }
    // Erorr ¸Þ¼¼Áö
    return false;
}

bool ResourceMgr::LoadTexture(string id)
{
    if (texMap.find(id) != texMap.end())
    {
        return false;
    }
    auto texture = new Texture();
    if (!texture->loadFromFile(id))
    {
        delete texture;
        return false;
    }
    texMap.insert({ id, texture });
    return true;
}

bool ResourceMgr::LoadFont(string id)
{
    if (fontMap.find(id) != fontMap.end())
    {
        return false;
    }
    auto font = new Font();
    if (!font->loadFromFile(id))
    {
        delete font;
        return false;
    }
    fontMap.insert({ id, font });
    return true;
}

bool ResourceMgr::LoadSoundBuffer(string id)
{
    if (soundMap.find(id) != soundMap.end())
    {
        return false;
    }
    auto sound = new SoundBuffer();
    if (!sound->loadFromFile(id))
    {
        delete sound;
        return false;
    }
    soundMap.insert({ id, sound });
    return true;
}

Texture* ResourceMgr::GetTexture(string id)
{
    auto it = texMap.find(id);
    if (it == texMap.end())
        return nullptr;
    return it->second;
}

Font* ResourceMgr::GetFont(string id)
{
    auto it = fontMap.find(id);
    if (it == fontMap.end())
        return nullptr;
    return it->second;
}

SoundBuffer* ResourceMgr::GetSound(string id)
{
    auto it = soundMap.find(id);
    if (it == soundMap.end())
        return nullptr;
    return it->second;
}
