#include "StateSleepPlayer.h"

#include <iostream>
using namespace std;


StateSleepPlayer::StateSleepPlayer(Entity *parent)
{
    mId = eSleepPlayer;
    mParent = parent;
}

StateSleepPlayer::~StateSleepPlayer()
{

}

void StateSleepPlayer::initState()
{
    
}

void StateSleepPlayer::enterState()
{
}

void StateSleepPlayer::exitState()
{
}

int StateSleepPlayer::update()
{
    if (mParent->isEaten())
        return mId;
        
    vector<Entity*> entities = mParent->mManager->mEntities;

    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i] == mParent)
            continue;

        vec3f direction = (entities[i]->getPosition() - mParent->getPosition());
        float distance = direction.getLength();
        
        if (entities[i]->getSize() > mParent->getSize() || mParent->getPower() == 100)
        {
            if (distance < mParent->getSightRadius())
                return eNormalPlayer;
        }
        
        vec3f targetPosition =
            mParent->getPosition() + (mParent->getVelocity() * mParent->getMaxSpeed());
        mParent->addSteeringArrive(targetPosition, 3);
    }
    
    mParent->increasePower(0.5);
    
    if (mParent->getPower() == 100)
        return eNormalPlayer;
    
    return mId;
}

