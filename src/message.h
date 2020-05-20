#pragma once
#include "ofxAsio.h"
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <iostream>

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
typedef websocketpp::server<websocketpp::config::asio>::message_ptr message_ptr;

namespace ofxWebsocket
{
    class Message
    {
    public:
        Message(websocketpp::connection_hdl hdl, std::string payload, websocketpp::frame::opcode::value opCode) : _connectionHandle(hdl), _payload(payload), _opCode(opCode)
        {
        }
        websocketpp::connection_hdl getConnectionHandle()
        {
            return _connectionHandle;
        }

        std::string getPayload()
        {
            return _payload;
        }

        websocketpp::frame::opcode::value getOpCode()
        {
            return _opCode;
        }
        websocketpp::connection_hdl _connectionHandle;
        std::string _payload;
        websocketpp::frame::opcode::value _opCode;
    };
}; // namespace ofxWebsocket