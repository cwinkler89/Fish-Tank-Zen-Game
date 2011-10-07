#include "StateNormalPlayer.h"

#include <iostream>
using namespace std;

StateNormalPlayer::StateNormalPlayer(Player *player)
{
    mId = eNormalPlayer;
    mParent = player;
}

StateNormalPlayer::~StateNormalPlayer()
{
}

void StateNormalPlayer::initState()
{
    
}

void StateNormalPlayer::enterState()
{
}

void StateNormalPlayer::exitState()
{
}

int StateNormalPlayer::update()
{
    list<int> keyEvents = mParent->getKeyEvents();
    
    int keyUp = mParent->getKeyUp();
    int keyRight = mParent->getKeyRight();
    int keyDown = mParent->getKeyDown();
    int keyLeft = mParent->getKeyLeft();
    
    if (!keyEvents.empty())
    {
        vec3f direction(0, 0);
        if (keyEvents.size() > 1)
            bool breakhere = true;

        list<int>::reverse_iterator it = keyEvents.rbegin();

        for (int i = 0; i < 2; i++)
        {
            if (it == keyEvents.rend())
                break;

            if ((*it) == keyUp)
                direction += vec3f(0, -1);
            if ((*it) == keyRight)
                direction += vec3f(1, 0);
            if ((*it) == keyDown)
                direction += vec3f(0, 1);
            if ((*it) == keyLeft)
                direction += vec3f(-1, 0);

            it++;
        }
       
        
        mParent->addSteeringSeek(mParent->getPosition() + direction);
    }
    else
    {
        vec3f targetPosition =
            mParent->getPosition() + (mParent->getVelocity() * mParent->getMaxSpeed());
        mParent->addSteeringArrive(targetPosition, 2);
    }
    
    mParent->decreasePower(0.1);
    
    if (mParent->getPower() == 0)
        return eSleepPlayer;
    
    return mId;
}

