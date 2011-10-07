#include "StateSleepMonster.h"

#include <iostream>
using namespace std;


StateSleepMonster::StateSleepMonster(Entity *parent)
{
    mId = eSleepMonster;
    mParent = parent;
}

StateSleepMonster::~StateSleepMonster()
{

}

void StateSleepMonster::initState()
{
    
}

void StateSleepMonster::enterState()
{
}

void StateSleepMonster::exitState()
{
}

int StateSleepMonster::update()
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
                return eNormalMonster;
        }
        
        vec3f targetPosition =
            mParent->getPosition() + (mParent->getVelocity() * mParent->getMaxSpeed());
        mParent->addSteeringArrive(targetPosition, 3);
    }
    mParent->increasePower(0.3);
    
    if (mParent->getPower() == 100)
        return eNormalMonster;
    
    return mId;
}

