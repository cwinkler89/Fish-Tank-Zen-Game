#pragma once
#include "State.h"
#include "Entity.h"

class StateNormalMonster :
    public State
{
    public:
        StateNormalMonster(Entity *parent);
        ~StateNormalMonster();

        void initState();
        void enterState();
        void exitState();
        int update();			// update game logic, change state if necessary
        int getID() { return mId; };
    private:
        Entity *mParent;
};
