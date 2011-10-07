#pragma once
#include "State.h"
#include "Entity.h"

class StateAttack :
    public State
{
    public:
        StateAttack(Entity *parent, Entity *player);
        ~StateAttack();

        void initState();
        void enterState();
        void exitState();
        int update();			// update game logic, change state if necessary
        int getID() { return mId; };
    private:
        Entity *mParent;
        Entity *mPlayer;
};
