#include "Entity.h"
#include "Settings.h"
#include <cmath>

#include <iostream>
using namespace std;

Entity::Entity(EntityManager *manager)
{
    mSightRadius = 20;
    mSize = 5;
    mMaxSpeed = 5;
    mMaxForce = 5;
    mCurrentWaypoint = 0;
    mHeading = vec3f(0, 1);
    mPower = 100;
    mIsEaten = false;
    mManager = manager;
    mImage = 0;
    isSmaller = true;
}

Entity::~Entity()
{

}

void Entity::eat(Entity *other)
{
    mSize = min(Settings::maxFishSize, mSize + other->mSize / 10);
    other->mIsEaten = true;
}

bool Entity::isEaten()
{
    return mIsEaten;
}

void Entity::setColor(float r, float g, float b)
{
    mColor.r = r;
    mColor.g = g;
    mColor.b = b;
}

void Entity::setImage(ofImage *image)
{
    mImage = image;
}

void Entity::setPosition(vec3f position)
{
    mPosition = position;
}

void Entity::decreasePower(float amount)
{
    mPower-= amount;
    if (mPower < 0)
        mPower = 0;
}

void Entity::increasePower(float amount)
{
    mPower+= amount;
    if (mPower > 100)
        mPower = 100;
}


void Entity::setSightRadius(float radius)
{
    mSightRadius = radius;
}

void Entity::setSize( float size )
{
    mSize = size;
}

void Entity::setVelocity(vec3f velocity)
{
    velocity.normalize();
    mVelocity = velocity * mMaxSpeed;
}

void Entity::update()
{
    mSteeringForce.set(0, 0, 0);
    mSightRadius = mSize*2 + mPower*2;
    
    if (mSize > 5)
        mSize-= 0.0001*mSize;
    
    mFSM.update();
    
    // update position
    vec3f acceleration = mSteeringForce / (mSize > 0 ? mSize : 1);
    mVelocity += acceleration;
    vec3f targetPosition = mPosition + mVelocity;
    
    float width = ofGetWidth();
    float height = ofGetHeight();
    
    targetPosition.x = ofClamp(targetPosition.x, 0, width);
    targetPosition.y = ofClamp(targetPosition.y, 0, height);
    
    mPosition = targetPosition;
    
    if (!mVelocity.isZero())
    {
        mHeading = mVelocity;
        mHeading.normalize();
    }
}

void Entity::draw()
{
    ofPushMatrix();
        // uncomment the following lines to see the path of the entities
        /*
        glColor3f(0, 0.2, 0.7);
        for(unsigned int i = 0; i < mPath.size(); i++)
        {
            if (i == 0)
                ofLine(mPath[i].x, mPath[i].y, mPath[mPath.size()-1].x, mPath[mPath.size()-1].y);
            else
                ofLine(mPath[i].x, mPath[i].y, mPath[i-1].x, mPath[i-1].y);
                
            if (i == mCurrentWaypoint)
                ofCircle(mPath[i].x, mPath[i].y, 3);
        }
        */
        ofTranslate(mPosition.x, mPosition.y, mPosition.z);

        // entity itself
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

        // uncomment following lines to see the sightradius
        
        if (isSmaller && Settings::showSmallerSightRadius || !isSmaller && Settings::showBiggerSightRadius)
        {
            ofNoFill();
            glColor3f(mColor.r, mColor.g, mColor.b);
            ofCircle(0, 0, mSightRadius);
        }
        
        // uncomment following lines to see the power
        if (isSmaller && Settings::showSmallerEnergy || !isSmaller && Settings::showBiggerEnergy)
        {
            ofNoFill();
            glColor3f(mColor.r, mColor.g, mColor.b);
            ofCircle(0, 0, mPower);
        }
        
        // uncomment following lines to see the velocity
        /*
        ofScale(50, 50);
        // velocity
        glColor3f(0, 1, 0);
        ofLine(0, 0, mVelocity.x, mVelocity.y);
        */
        
        // uncomment following lines to see the steering force
        /*
        glColor3f(0, 0, 1);
        ofLine(0, 0, mSteeringForce.x, mSteeringForce.y);
        */
        if (isSmaller && Settings::showSmallerSize || !isSmaller && Settings::showBiggerSize)
        {
            ofFill();
            glColor3f(0, 0, 0);
            ofRect(10, 0, 40, 10);
            glColor3f(mColor.r, mColor.g, mColor.b);
            ofDrawBitmapString(ofToString(mSize, 2), 10, 10);
        }

    ofPopMatrix();

    glColor3f(1, 1, 1);
}

bool Entity::addSteeringSeek(vec3f targetPosition)
{
    vec3f direction = (targetPosition - mPosition);
    direction.normalize();
    
    vec3f desiredVelocity = direction * mMaxSpeed;
    vec3f steeringForce = desiredVelocity - mVelocity;
    
    return accumulateForce(steeringForce);
}

bool Entity::addSteeringFollowPath()
{
    if (mCurrentWaypoint < mPath.size())
    {
        float distance = (mPath[mCurrentWaypoint]-mPosition).getLength();
        if ( distance < mSightRadius )
        {
            mCurrentWaypoint = (mCurrentWaypoint+1)%mPath.size();
        }
        
        return addSteeringSeek(mPath[mCurrentWaypoint]);
    }
    else
    {
        return addSteeringArrive(mPosition, 3); // 3 = fast
    }
}

bool Entity::addSteeringFlee(vec3f targetPosition)
{
    vec3f direction = (mPosition - targetPosition);
    direction.normalize();
    
    vec3f desiredVelocity = direction * mMaxSpeed;
    vec3f steeringForce = desiredVelocity - mVelocity;
    
    return accumulateForce(steeringForce);
}

bool Entity::addSteeringPersuit(Entity *evader)
{
    vec3f toEvader = evader->getPosition() - mPosition;
    vec3f steeringForce;
    
    float relativeHeading = mHeading.dot(evader->getHeading());
    if (toEvader.dot(mHeading) > 0 && relativeHeading < -0.95)
        return addSteeringSeek(evader->getPosition());
    
    float evaderSpeed = evader->getVelocity().getLength();
    float lookAheadTime = toEvader.getLength() / mMaxSpeed + evaderSpeed;
    
    return addSteeringSeek(evader->getPosition() + evader->getVelocity() * evaderSpeed); 
}

bool Entity::addSteeringArrive( vec3f targetPosition, unsigned int deceleration )
{
    // only allow values from 1 to 3
    // 1 == slow, 2 == medium, 3 == fast
    if (deceleration < 1)
        deceleration = 1;
    else if(deceleration > 3)
        deceleration = 3;
        
    vec3f toTarget = targetPosition - mPosition;
    float distance = toTarget.getLength();
    
    if (distance > 0)
    {
        // tweeker needs to be a bit higher than maxSpeed
        float decelerationTweeker = mMaxSpeed*1.1;
        float speed = distance / ((float)deceleration * decelerationTweeker);
        speed = min(speed, mMaxSpeed);
        vec3f desiredVelocity = toTarget * speed / distance;
        vec3f steeringForce =  desiredVelocity - mVelocity;
        return accumulateForce(steeringForce);
    }
    
    return accumulateForce(vec3f(0,0));
}


bool Entity::accumulateForce(vec3f steeringToAdd)
{
    float forceUsed = mSteeringForce.getLength();
    float forceRemaining = mMaxForce - forceUsed;
    
    if (forceRemaining <= 0)
        return false;
        
    float forceToAdd = steeringToAdd.getLength();
    
    if (forceToAdd < forceRemaining)
    {
        mSteeringForce += steeringToAdd;
    }
    else
    {
        steeringToAdd.normalize();
        mSteeringForce += steeringToAdd * forceRemaining;
    }
    
    return true;
}