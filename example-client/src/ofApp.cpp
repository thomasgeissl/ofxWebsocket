#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    _client.addListener(this);
    _client.setup("127.0.0.1", 9002);
}

//--------------------------------------------------------------
void ofApp::update()
{
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
    ofJson payload;
    payload["type"] = "MOUSEMOVED";
    payload["x"] = (float)(x) / ofGetWidth();
    payload["y"] = (float)(y) / ofGetHeight();
    _client.send(payload.dump());
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
    ofLogNotice() << "got message " << msg.getPayload();
}
void ofApp::onOpen(ofxWebsocket::ConnectionHandle &hdl)
{
    ofLogNotice() << "connection opened";
    _client.send("hello from the ofApp");
}
void ofApp::onClose(ofxWebsocket::ConnectionHandle &hdl)
{
    ofLogNotice() << "connection closed";
}
