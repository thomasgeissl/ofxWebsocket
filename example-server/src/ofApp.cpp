#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    _server.addListener(this);
    _server.setup(9002);
}

//--------------------------------------------------------------
void ofApp::update()
{
    _server.update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}

void ofApp::onMessage(ofxWebsocket::Message &msg)
{
    ofLogNotice() << "get message " << msg.getPayload();
    _server.send(msg.getConnection(), msg.getPayload(), msg.getOpCode());
}
