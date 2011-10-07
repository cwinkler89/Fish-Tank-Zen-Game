#pragma once
#include "State.h"
#include "Entity.h"

class StateSleepPlayer :
    public State
{
    public:
        StateSleepPlayer(Entity *parent);
        ~StateSleepPlayer();

        void initState();
        void enterState();
        void exitState();
        // update game logic, change state if necessary
        int update();
        int getID() { return mId; };
    private:
        Entity *mParent;
};
