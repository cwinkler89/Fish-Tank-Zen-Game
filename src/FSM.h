#pragma once
#include "state.h"
#include <list>
#include <vector>
//#include <algorithm>

using namespace std;

class FSM //:	public State		// inherited from State to enable HFSM (Hierachical FSM)
{
public:
	FSM(void);
	~FSM(void);

	void setInitState(int stateID);	// set default state
	void addState(State *s);
	void removeState(int stateID);
	void update();
	void changeState(int stateID);
	void reset();				// reset machine to inital state
	void cleanup();

private:
	State *getStateFromID(int stateID);
	State *mCurrentState;
	State *mPreviousState;
	State *mDefaultState;

	list<State *> mStates; 
};

