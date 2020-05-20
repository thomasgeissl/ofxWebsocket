#pragma once
#include "ofxAsio.h"
#include "./message.h"

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <iostream>

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
typedef websocketpp::server<websocketpp::config::asio>::message_ptr message_ptr;

namespace ofxWebsocket
{
    class Listener
    {
    public:
        typedef websocketpp::connection_hdl Connection;
        virtual void onMessage(Message &msg)
        {
        }
        virtual void onOpen(Connection &con)
        {
        }
        virtual void onClose(Connection &con)
        {
        }
    };
}; // namespace ofxWebsocket