#include "FSM.h"


FSM::FSM(void)
{
	mDefaultState = NULL;
	mCurrentState = NULL;
}


FSM::~FSM(void)
{
	for(list<State *>::iterator i = mStates.begin(); i != mStates.end(); i++){
		if(*i)
			delete (*i);
        // fails if there is only one state in FSM
		//i  = mStates.erase(i);
	}
	// no fail: clear list at end
    mStates.clear();
}

void FSM::setInitState(int stateID)	// set default state
{
	mDefaultState = getStateFromID(stateID);
}

void FSM::addState(State *s)
{
	mStates.push_back(s);
}

void FSM::removeState(int stateID)
{
	State *s = getStateFromID(stateID);
	if(s)		// only remove if stateID exists
	{
		mStates.remove(s);
		delete s;
	}
}

void FSM::update()
{
	// check if there is a valid currentState
	if(!mCurrentState)
		mCurrentState = mDefaultState;
	if(!mCurrentState)
		return;

	// execute actual state and get id back
	int newStateID = mCurrentState->update();

	if(newStateID != mCurrentState->getID())		// should we enter a new state ?
	{
		mCurrentState->exitState();
		mCurrentState = getStateFromID(newStateID);
		mCurrentState->enterState();
	}
}

void FSM::changeState(int stateID)
{
	State *newState = getStateFromID(stateID);
	if(newState)
		mCurrentState = newState;
}

void FSM::reset()
{
	mCurrentState = mDefaultState; 
}

State* FSM::getStateFromID(int stateID)
{
	for(list<State *>::iterator i = mStates.begin(); i != mStates.end(); i++){
		if((*i)->getID() == stateID)
			return *i;
	}
	return NULL;
}