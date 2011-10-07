#include "Player.h"
#include "Settings.h"

#include "StateNormalPlayer.h"
#include "StateSleepPlayer.h"

Player::Player(EntityManager *manager)
:   Entity(manager)
{
    mManager = manager;
    
    mKeyUp = mKeyRight = mKeyDown =  mKeyLeft = 0;
    
    ofAddListener(ofEvents.keyPressed, this, &Player::keyPressed);
    ofAddListener(ofEvents.keyReleased, this, &Player::keyReleased);
    
    mFSM.addState(new StateNormalPlayer(this));
    mFSM.addState(new StateSleepPlayer(this));
    
    mFSM.setInitState(State::eNormalPlayer);
    mMaxSpeed *= 1.2f;
    
}

Player::~Player()
{
    ofRemoveListener(ofEvents.keyPressed, this, &Player::keyPressed);
    ofRemoveListener(ofEvents.keyReleased, this, &Player::keyReleased);
}

void Player::draw()
{
    ofPushMatrix();
        ofTranslate(mPosition.x, mPosition.y, mPosition.z);

        ofPushMatrix();
            float angle = atan2(mHeading.y, mHeading.x) * 180 / 3.1415;
            ofRotate(angle);

            if (mImage != 0)
            {
                mImage->draw(-mSize, -mSize, mSize*2, mSize*2);
            }
            else
            {
                ofFill();
                glColor3f(mColor.r, mColor.g, mColor.b);
                ofTriangle(mSize*2, 0, -mSize, mSize, -mSize, -mSize);
            }
        ofPopMatrix();
        
        // sightradius
        if (Settings::showPlayerSightRadius)
        {
            ofNoFill();
            glColor3f(1, 1, 0);
            ofCircle(0, 0, mSightRadius);
        }
        
        if (Settings::showPlayerEnergy)
        {
            ofNoFill();
            glColor3f(1, 1, 0);
            ofCircle(0, 0, mPower);

        }
        // power
        
        if (Settings::showPlayerSize)
        {
            ofFill();
            glColor3f(0, 0, 0);
            ofRect(10, 0, 40, 10);
            glColor3f(1, 1, 0);
            ofDrawBitmapString(ofToString(mSize, 2), 10, 10);
        }
        
        
    ofPopMatrix();

    glColor3f(1, 1, 1);

}

void Player::setKeyBindings(int keyUp, int keyRight, int keyDown, int keyLeft)
{
    mKeyUp = keyUp;
    mKeyRight = keyRight;
    mKeyDown = keyDown;
    mKeyLeft = keyLeft;
}

void Player::keyPressed( ofKeyEventArgs & args )
{
    int key = args.key;
    
    if (key == mKeyUp || key == mKeyRight || key == mKeyLeft || key == mKeyDown)
    {
        for (list<int>::iterator it=mKeyEvents.begin(); it!=mKeyEvents.end(); it++)
        {
            if ( (*it) == key )
                return;
        }
        mKeyEvents.push_back(key);
    }
}

void Player::keyReleased( ofKeyEventArgs & args )
{
    int key = args.key;
    if (key == mKeyUp || key == mKeyRight || key == mKeyLeft || key == mKeyDown)
        mKeyEvents.remove(key);
}
