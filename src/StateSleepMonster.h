#pragma once
#include "State.h"
#include "Entity.h"

class StateSleepMonster :
    public State
{
    public:
        StateSleepMonster(Entity *parent);
        ~StateSleepMonster();

        void initState();
        void enterState();
        void exitState();
        int update();			// update game logic, change state if necessary
        int getID() { return mId; };
    private:
        Entity *mParent;
};
