#pragma once

#include "ofMain.h"
#include "ofxWebsocket.h"

class ofApp : public ofBaseApp, public ofxWebsocket::Listener
{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void onMessage(ofxWebsocket::Message &msg);
    void onOpen(ofxWebsocket::ConnectionHandle &hdl);
    void onClose(ofxWebsocket::ConnectionHandle &hdl);

    ofxWebsocket::Server _server;
    float _remoteX, _remoteY;
};
