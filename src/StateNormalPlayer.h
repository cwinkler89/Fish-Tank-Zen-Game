#pragma once
#include "State.h"
#include "Entity.h"
#include "Player.h"

class StateNormalPlayer :
    public State
{
    public:
        StateNormalPlayer(Player *parent);
        ~StateNormalPlayer();

        void initState();
        void enterState();
        void exitState();
        int update();			// update game logic, change state if necessary
        int getID() { return mId; };
    private:
        Player *mParent;
};
