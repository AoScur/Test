#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <list>
#include "MoveAtoBObject.h"
#include "Utils.h"
#include "InputManager.h"
#include "Branch.h"
#include "Player.h"
#include "EffetLog.h"
#include "ResourceMgr.h"

#include <iostream>

using namespace sf;

void UpdateBranches(vector<Branch*>& branches, int& current, vector<Vector2f>& posArr)
{
    current = (current + 1) % branches.size();

    for (int i = 0; i < branches.size(); ++i)
    {
        int index = (current + i) % branches.size();
        branches[index]->SetPosition(posArr[i]);
        if (i == branches.size() - 1)
        {
             branches[index]->SetSide((Sides)Utils::Range(0, 2));
        }
    }
}


int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "timber", Style::Default);

    Vector2u size = window.getSize();

    auto resourceMgr = ResourceMgr::GetInstance();
    Sound timeOutSound;
    timeOutSound.setBuffer(*resourceMgr->GetSound("sound/out_of_time.wav"));
    Sound deathSound;
    deathSound.setBuffer(*resourceMgr->GetSound("sound/death.wav"));
    Sound chopSound;
    chopSound.setBuffer(*resourceMgr->GetSound("sound/chop.wav"));

    Texture texBackground = *resourceMgr->GetTexture("graphics/background.png");
    Texture texBee = *resourceMgr->GetTexture("graphics/bee.png"); 
    Texture texCloud = *resourceMgr->GetTexture("graphics/cloud.png");   
    Texture texTree = *resourceMgr->GetTexture("graphics/tree.png");     
    Texture texPlayer = *resourceMgr->GetTexture("graphics/player.png"); 
    Texture texRIP = *resourceMgr->GetTexture("graphics/rip.png");   
    Texture texAxe = *resourceMgr->GetTexture("graphics/axe.png");     
    Texture texBranch = *resourceMgr->GetTexture("graphics/branch.png");

    Font font = *resourceMgr->GetFont("fonts/KOMIKAP_.ttf");

    bool isPause = true;
    bool isGameOver = false;

    std::list<SpriteGameObject*> gameObjectList;
    gameObjectList.push_back(new SpriteGameObject(texBackground));
    
    std::vector<float> startVector = { 2000, -300 };
    std::vector<float> endVector = { -300, 2000 };
    for (int i = 0; i < 3; ++i)
    {
        auto movingObj = new MoveAtoBObject(texCloud);
        auto index = rand() % 2;

        movingObj->Set({ 200,400 }, { 100, 400 },
            { startVector[index], 0 }, { endVector[index], 0 });
        gameObjectList.push_back(movingObj);
    }


    SpriteGameObject* tree = new SpriteGameObject(texTree, Vector2f(size.x * 0.5f, 900));
    tree->SetOrigin(Origins::BC);
    gameObjectList.push_back(tree);

    Player* player = new Player(texPlayer, texRIP, texAxe, chopSound, deathSound, isPause);
    gameObjectList.push_back(player);
    player->Set(tree->GetPosition());

    vector<Branch*> branches(6);
    for (int i = 0; i < branches.size(); ++i)
    {
        branches[i] = new Branch(texBranch, tree);
        if (branches[i]->GetSide() == player->GetPos())
        {
            branches[i]->SetSide(Sides::None);
        }
        else
        {
            branches[i]->SetSide((Sides)Utils::Range(0, 2));
        }

        gameObjectList.push_back(branches[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        MoveAtoBObject* movingObj = new MoveAtoBObject(texBee);
        movingObj->Set({ 200,400 }, { 500, 1000 }, { 2000, 0 }, { -100, 0 });
        gameObjectList.push_back(movingObj);
    }  
    


    // gameObject를 전부 추가한 후 Init.
    for (auto go : gameObjectList)
    {
        go->Init();
    }

    int currentBranch = -1;
    vector<Vector2f> branchPosArr(branches.size());
    float x = branches[0]->GetPosition().x;
    float y = 800;
    float offset = branches[0]->GetSize().y;
    offset += 100;
    for (int i = 0; i < branches.size(); ++i)
    {
        branchPosArr[i] = Vector2f(x, y);
        y -= offset;
    }
    UpdateBranches(branches, currentBranch, branchPosArr);


    // UI OBJ CREATES
    Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(75);
    messageText.setFillColor(Color::White);
    messageText.setString("Press Enter to start!");
    messageText.setPosition(size.x * 0.5f, size.y * 0.5f);
    Utils::SetOrigin(messageText, Origins::MC);

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(Color::White);
    int score = 0;
    String scoreString = "Score: " + to_string(score);
    scoreText.setString(scoreString);
    scoreText.setPosition(20, 20);
    Utils::SetOrigin(scoreText, Origins::TL);

    Vector2f timerBarSize(400, 80);
    RectangleShape timerBar;
    timerBar.setSize(timerBarSize);
    timerBar.setFillColor(Color::Red);
    timerBar.setPosition(
        size.x * 0.5f - timerBarSize.x * 0.5f,
        size.y - 100);

    float duration = 4.0f;
    float timer = duration;
    timer = duration;

    Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(50);
    timerText.setFillColor(Color::White);
    string timerString = to_string(timer);
    timerString = timerString.substr(0, 4);
    timerText.setString(timerString);
    timerText.setPosition(size.x * 0.5f, size.y - 50);
    Utils::SetOrigin(timerText, Origins::BC);


    Clock clock;
    while (window.isOpen())
    {
        Time dt = clock.restart(); //이전 업데이트 시간과 현재 업데이트 시간 차이 기록

        Event ev;
        InputManager::ClearInput();
        while (window.pollEvent(ev))
        {
            InputManager::UpdateInput(ev);
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))  //static 함수
        {
            window.close();
            continue;
        }

        if (InputManager::GetKeyDown(Keyboard::Return))
        {
            if (isGameOver)
            {
                messageText.setString("Press Enter to start!");
                Utils::SetOrigin(messageText, Origins::MC);
                isGameOver = !isGameOver;
                timer = duration;
                scoreString = "Score: " + to_string(score);
                scoreText.setString(scoreString);

                for (auto go : gameObjectList)
                {
                    go->Init();
                }
                int currentBranch = -1;
                vector<Vector2f> branchPosArr(branches.size());
                float x = branches[0]->GetPosition().x;
                float y = 800;
                float offset = branches[0]->GetSize().y;
                offset += 100;
                for (int i = 0; i < branches.size(); ++i)
                {
                    branchPosArr[i] = Vector2f(x, y);
                    y -= offset;
                }
                UpdateBranches(branches, currentBranch, branchPosArr);
                // 게임 시작할 때 했던 모든 사전작업을 다시 할 수 있게 함
            }
            else
                isPause = !isPause;
        }

       /* if (InputManager::GetKeyDown(Keyboard::Z))
        {
            if (!isPause)
            {
                score++;
                timer += 1.f;
                scoreString = "Score: " + to_string(score);
                scoreText.setString(scoreString);
            }
        }

        if (InputManager::GetKeyDown(Keyboard::X))
        {
            if (score > 0 && !isPause)
            {
                score--;
                scoreString = "Score: " + to_string(score);
                scoreText.setString(scoreString);
            }
        }*/

        //if (InputManager::GetKeyDown(Keyboard::C))
        //{
        //    UpdateBranches(branches, currentBranch, branchPosArr);
        //}

        //if (InputManager::GetKeyDown(Keyboard::D))
        //{
        //    
        //    player->Die();
        //}

        size = window.getSize();
        float deltaTime = isPause ? 0.f : dt.asSeconds();

        // UI update

        timer -= deltaTime;
        if (timer < 0.f)
        {
            if (!isPause)
            {
                timeOutSound.play();
            }
            timer = 0.f;
            messageText.setString("Game Over!!");
            Utils::SetOrigin(messageText, Origins::MC);
            isPause = true;
            isGameOver = true;
            timeOutSound.play();
        }


        float normTime =timer / duration; // 정규화
        float timerSizeX = timerBarSize.x * normTime;
        timerBar.setSize({ timerSizeX, timerBarSize.y });
        timerBar.setPosition
        (size.x * 0.5f - timerSizeX * 0.5f, size.y - 100);

        timerString = to_string(timer);
        timerString = timerString.substr(0, 4);
        timerText.setString(timerString);

        if (!player->isChop)
        {
            if (InputManager::GetKeyDown(Keyboard::Left))
            {
                player->Chop(Sides::Left);
                score += 10;
                timer += 0.1f;
                UpdateBranches(branches, currentBranch, branchPosArr);
            }
            if (InputManager::GetKeyDown(Keyboard::Right))
            {
                player->Chop(Sides::Right);
                score += 10;
                timer += 0.1f;
                UpdateBranches(branches, currentBranch, branchPosArr);
            }
        }
        else
        {
            if (player->GetPos() == Sides::Left && InputManager::GetKeyUp(Keyboard::Left))
            {
                player->isChop = false;
            }
            if (player->GetPos() == Sides::Right && InputManager::GetKeyUp(Keyboard::Right))
            {
                player->isChop = false;
            }
        }
        if (player->GetPos() == branches[currentBranch]->GetSide())
        {
            player->Die();
            isPause = true;
            isGameOver = true;
        }
        // Update
        if (!isPause)
        {
            for (auto go : gameObjectList)
            {
                go->Update(deltaTime);
            }
        }


        // Draw      
        window.clear();
        for (auto go : gameObjectList)
        {
            go->Draw(window);
        }

        if (isPause)
        {
            window.draw(messageText);
        }
        
        scoreString = "Score: " + to_string(score);
        scoreText.setString(scoreString);
        window.draw(scoreText);


        window.draw(timerBar);
        window.draw(timerText);
 
        window.display();
    }     

    for (auto go : gameObjectList)
    {
        go->Release();
        delete go;
    }
    gameObjectList.clear();
    
    return 0;
}