#pragma once

#include "ofMain.h"
#include "Entity.h"
#include <vector>

class Entity;

class EntityManager
{
    public:
        EntityManager();
        ~EntityManager();
        
        void setPlayer(Entity *player);
        
        void update();
        void draw();
        
        // entities need to read this 2 variables
        vector<Entity*> mEntities;
        Entity *mPlayer;
        
        
    private:
        float mLastSpawnTime;
        
        void spawnNewMonster();
        void spawnPlayer();

        ofImage *mFishRed;
        ofImage *mFishGreen;
        ofImage *mFishBlue;
};