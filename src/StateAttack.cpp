#include "StateAttack.h"

#include <iostream>
using namespace std;


StateAttack::StateAttack(Entity *parent, Entity *player)
{
    mId = eAttack;
    mParent = parent;
    mPlayer = player;
}

StateAttack::~StateAttack()
{

}

void StateAttack::initState()
{
    
}

void StateAttack::enterState()
{

}

void StateAttack::exitState()
{

}

int StateAttack::update()
{
    vec3f direction = (mPlayer->getPosition() - mParent->getPosition());
    float distance = direction.getLength();
    
    if (distance > mParent->getSightRadius())
        return eNormalMonster;
    
    //mParent->addSteeringArrive(mPlayer->getPosition(), 1);
    mParent->addSteeringPersuit(mPlayer);
    
    
    return mId;
}

