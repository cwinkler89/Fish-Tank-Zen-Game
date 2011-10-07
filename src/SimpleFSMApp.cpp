#include "SimpleFSMApp.h"
#include "Settings.h"

using namespace std;


//--------------------------------------------------------------
SimpleFSMApp::SimpleFSMApp()
{

}
//--------------------------------------------------------------
void SimpleFSMApp::setup()
{
    mManager = new EntityManager();
    
    if (!background.loadImage("underwater-wide.jpg"))
    {
        ofLog(OF_LOG_ERROR, "failed to load background image\n");
    }

    if (!credits.loadImage("credits.png"))
    {
        ofLog(OF_LOG_ERROR, "failed to load credits image\n");
    }

    if (!help.loadImage("help.png"))
    {
        ofLog(OF_LOG_ERROR, "failed to load help image\n");
    }

    mSoundPlayer.loadSound("super_mario_64_dire_dire_docks.mp3");

    if (!mSoundPlayer.bLoadedOk)
    {
        ofLog(OF_LOG_ERROR, "failed to load sound file\n");
    }

    mLastUpdate = 0;
    /*mPlayer = new Player(mManager);
    mManager->setPlayer(mPlayer);
    mPlayer->setSize(10);
    
    mPlayer->setKeyBindings('w', 'd', 's', 'a');
    mPlayer->setPosition(vec3f(ofGetWidth()/2, ofGetHeight()/2));
    mPlayer->setColor(0, 0, 1);*/
}

//--------------------------------------------------------------
void SimpleFSMApp::update()
{
    ofSetWindowTitle("Fish Tank Zen Game - " + ofToString(ofGetFrameRate(), 0) + " Frames per Second");
    
    
    int currentTime = ofGetElapsedTimeMillis();


    if (currentTime > 5000 && mSoundPlayer.bLoadedOk && !mSoundPlayer.getIsPlaying())
    {
        mSoundPlayer.bLoop = true;
        mSoundPlayer.play();
    }

    int sleepTime = 1000.0f / Settings::maxFrameRate - (currentTime - mLastUpdate);

    if (sleepTime > 0)
        Sleep(sleepTime);

    mLastUpdate += 1000.0f / Settings::maxFrameRate;

    mManager->update();
}


//--------------------------------------------------------------
void SimpleFSMApp::draw()
{
    float timeSinceStartup = ofGetElapsedTimef();

    glColor3f(1, 1, 1);
    background.draw(0, 0, ofGetWidth(), ofGetHeight());


    mManager->draw();

    if (timeSinceStartup < 15 || Settings::showCredits)
        credits.draw(0, 0, ofGetWidth(), ofGetHeight());
    else if (timeSinceStartup > 15 && Settings::showHelpScreen)
        help.draw(0, 0, ofGetWidth(), ofGetHeight());

}

void SimpleFSMApp::exit()
{
    delete mManager;
}

void SimpleFSMApp::keyReleased(int key)
{
    
    switch(key) {
        case OF_KEY_F11: ofToggleFullscreen(); break;
        case OF_KEY_F1: Settings::showHelpScreen = !Settings::showHelpScreen; break;
        case OF_KEY_F2: Settings::showCredits = !Settings::showCredits; break;


        case '1': Settings::showPlayerEnergy = !Settings::showPlayerEnergy; break;
        case '2': Settings::showPlayerSightRadius = !Settings::showPlayerSightRadius; break;
        case '3': Settings::showPlayerSize = !Settings::showPlayerSize; break;

        case '4': Settings::showSmallerEnergy = !Settings::showSmallerEnergy; break;
        case '5': Settings::showSmallerSightRadius = !Settings::showSmallerSightRadius; break;
        case '6': Settings::showSmallerSize = !Settings::showSmallerSize; break;

        case '7': Settings::showBiggerEnergy = !Settings::showBiggerEnergy; break;
        case '8': Settings::showBiggerSightRadius = !Settings::showBiggerSightRadius; break;
        case '9': Settings::showBiggerSize = !Settings::showBiggerSize; break;
        case '0':
            Settings::showPlayerEnergy =
            Settings::showPlayerSightRadius =
            Settings::showPlayerSize =
            Settings::showSmallerEnergy =
            Settings::showSmallerSightRadius =
            Settings::showSmallerSize =
            Settings::showBiggerEnergy =
            Settings::showBiggerSightRadius =
            Settings::showBiggerSize = false;
    }
}
