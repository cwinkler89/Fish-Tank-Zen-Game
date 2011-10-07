#include "StateNormalMonster.h"


#include <iostream>
using namespace std;

StateNormalMonster::StateNormalMonster(Entity *parent)
{
    mId = eNormalMonster;
    mParent = parent;
}

StateNormalMonster::~StateNormalMonster()
{

}

void StateNormalMonster::initState()
{
    
}

void StateNormalMonster::enterState()
{
}

void StateNormalMonster::exitState()
{
}

int StateNormalMonster::update()
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

        if (distance < mParent->getSightRadius())
        {
            if (mParent->getSize() > entities[i]->getSize())
            {
                mParent->addSteeringPersuit(entities[i]);
                if (distance < mParent->getSize())
                    mParent->eat(entities[i]);
            }
            else
            {
                mParent->addSteeringFlee(entities[i]->getPosition());
                if (distance < entities[i]->getSize())
                    entities[i]->eat(mParent);
            }
        }
    }
    
    mParent->addSteeringFollowPath();
    mParent->decreasePower(0.1);
    
    if (mParent->getPower() == 0)
        return eSleepMonster;
    
    return mId;
}

