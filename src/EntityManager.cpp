#include "EntityManager.h"
#include "Monster.h"
#include "Player.h"
#include "Settings.h"

EntityManager::EntityManager()
{
    mPlayer = 0;
    mLastSpawnTime = ofGetElapsedTimef();
    
    mFishRed = new ofImage();
    mFishGreen = new ofImage();
    mFishBlue = new ofImage();
    
    if (!mFishRed->loadImage("fish_bigger.png"))
    {
        ofLog(OF_LOG_ERROR, "failed to load fish_bigger.png");
        delete mFishRed;
        mFishRed = 0;
    }
    if (!mFishGreen->loadImage("fish_smaller.png"))
    {
        ofLog(OF_LOG_ERROR, "failed to load fish_smaller.png");
        delete mFishGreen;
        mFishGreen = 0;
    }
    
    if (!mFishBlue->loadImage("fish_you.png"))
    {
        ofLog(OF_LOG_ERROR, "failed to load fish_you.png");
        delete mFishBlue;
        mFishBlue = 0;
    }
    
}

EntityManager::~EntityManager()
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        delete mEntities[i];
    }   
    mEntities.clear();

    if (mFishRed)
        delete mFishRed;
    if (mFishGreen)
        delete mFishGreen;
    if (mFishBlue)
        delete mFishBlue;
}

void EntityManager::setPlayer(Entity *player)
{
    mPlayer = player;
    mEntities.push_back(mPlayer);
}

void EntityManager::update()
{
    if (mPlayer == 0)
        spawnPlayer();
    
    for (int i = mEntities.size()-1; i >= 0; i--)
    {
        mEntities[i]->update();
        
        if (mEntities[i]->isEaten())
        {
            Entity *toDelete = mEntities[i];
            mEntities.erase(mEntities.begin()+i);
            
            if (toDelete == mPlayer)
                mPlayer = 0;
            
            delete toDelete;
            continue;
        }
        
        if (mPlayer == 0 || mPlayer == mEntities[i])
            continue;
        
        if (mEntities[i]->getSize() < mPlayer->getSize())
        {
            mEntities[i]->setColor(0, 1, 0);
            mEntities[i]->setImage(mFishGreen);
            mEntities[i]->isSmaller = true;
        }
        else
        {
            mEntities[i]->setColor(1, 0, 0);
            mEntities[i]->setImage(mFishRed);
            mEntities[i]->isSmaller = false;
        }
        
    }
    
    float currentTime = ofGetElapsedTimef();
    if (mLastSpawnTime + 1 < currentTime)
    {
        mLastSpawnTime = currentTime;
        spawnNewMonster();
    }
    
}


void EntityManager::draw()
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mPlayer != 0 && mEntities[i] == mPlayer)
            ((Player*)(mEntities[i]))->draw();
        else
            mEntities[i]->draw();
    }
}

void EntityManager::spawnNewMonster()
{
    Monster *newMonster = new Monster(this);
    float minSize = Settings::minFishSize;
    float maxSize = Settings::maxFishSize;
    
    if (mPlayer != 0)
    {
        maxSize = mPlayer->getSize() + 1;
    }
    else
    {
        for (int i = mEntities.size()-1; i >= 0; i--)
        {
            if (mEntities[i]->getSize() > maxSize)
                maxSize = mEntities[i]->getSize();
        }
    }
    
    newMonster->setSize(ofRandom(minSize, maxSize));
    int posX = ofRandom(0, ofGetWidth());
    int posY = ofRandom(0, ofGetHeight());
    newMonster->setPosition(vec3f(posX, posY));
    mEntities.push_back(newMonster);
}


void EntityManager::spawnPlayer()
{
    mPlayer = new Player(this);
    mPlayer->setSize(Settings::startSize);
    
    ((Player*)mPlayer)->setKeyBindings(OF_KEY_UP, OF_KEY_RIGHT, OF_KEY_DOWN, OF_KEY_LEFT);

    int posX = ofRandom(0, ofGetWidth());
    int posY = ofRandom(0, ofGetHeight());
    mPlayer->setPosition(vec3f(posX, posY));
    mPlayer->setColor(0, 0, 1);
    mPlayer->setImage(mFishBlue);
    mEntities.push_back(mPlayer);
}