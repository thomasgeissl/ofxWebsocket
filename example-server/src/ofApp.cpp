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
    auto x = 60;
    auto y = 60;
    for (auto i = 0; i < _server.getNumberOfConnectionHandles(); i++)
    {
        ofSetColor(ofColor::pink);
        ofDrawCircle(x, y, 20);
        x += 40;
    }

    if (_server.getNumberOfConnectionHandles() > 0)
    {
        ofSetColor(ofColor::lightYellow);
        ofDrawCircle(_remoteX * ofGetWidth(), _remoteY * ofGetHeight(), 12);
    }
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
    ofLogNotice() << "got message " << msg.getPayload();
    _server.send(msg.getConnectionHandle(), msg.getPayload(), msg.getOpCode());

    auto payload = msg.getPayload();
    if (ofJson::accept(payload))
    {
        auto data = ofJson::parse(payload);
        _remoteX = data["x"];
        _remoteY = data["y"];
    }
}
void ofApp::onOpen(ofxWebsocket::ConnectionHandle &hdl)
{
    ofLogNotice() << "connection opened";
}
void ofApp::onClose(ofxWebsocket::ConnectionHandle &hdl)
{
    ofLogNotice() << "connection closed";
}
