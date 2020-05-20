#pragma once
#include "ofxAsio.h"
#include "./message.h"
#include "./listener.h"
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
typedef websocketpp::server<websocketpp::config::asio>::message_ptr message_ptr;

namespace ofxWebsocket
{
    class Server
    {
    public:
        typedef websocketpp::server<websocketpp::config::asio> server;
        typedef websocketpp::connection_hdl ConnectionHandle;
        ~Server()
        {
            stop();
        }
        void setup(int port)
        {
            try
            {
                _server.set_access_channels(websocketpp::log::alevel::all);
                _server.clear_access_channels(websocketpp::log::alevel::frame_payload);
                _server.init_asio();
                // _server.set_socket_init_handler(bind(&type::on_socket_init,this,::_1));
                //_server.set_tls_init_handler(bind(&type::on_tls_init,this,::_1));
                _server.set_message_handler(bind(&Server::on_message, this, &_server, ::_1, ::_2));
                _server.set_open_handler(bind(&Server::on_open, this, ::_1));
                _server.set_close_handler(bind(&Server::on_close, this, ::_1));
                // _server.set_fail_handler(bind(&type::on_fail, this, ::_1));
                _server.listen(port);
                _server.start_accept();

                _networkThread = std::thread(&server::run, &_server);
            }
            catch (websocketpp::exception const &e)
            {
                std::cout << e.what() << std::endl;
            }
            catch (...)
            {
                std::cout << "other exception" << std::endl;
            }
        }
        void update()
        {
        }
        void stop()
        {
            _server.stop();
        }

        void addListener(Listener *listener)
        {
            ofAddListener(_messageEvent, listener, &Listener::onMessage);
            ofAddListener(_openEvent, listener, &Listener::onOpen);
            ofAddListener(_closeEvent, listener, &Listener::onClose);
        }
        void send(websocketpp::connection_hdl connection, std::string payload, websocketpp::frame::opcode::value opCode)
        {
            try
            {
                _server.send(connection, payload, opCode);
            }
            catch (websocketpp::exception const &e)
            {
                ofLogError("ofxWebsocket::Server") << "could not send message.: " << e.what();
            }
        }

        int getNumberOfConnectionHandles()
        {
            return _connectionHandles.size();
        }
        std::vector<ConnectionHandle> getConnectionHandles()
        {
            return _connectionHandles;
        }
        void on_message(server *s, websocketpp::connection_hdl hdl, message_ptr msg)
        {
            Message message(hdl, msg->get_payload(), msg->get_opcode());
            ofNotifyEvent(_messageEvent, message, this);
            return;
        }
        void on_open(websocketpp::connection_hdl hdl)
        {
            _connectionHandles.push_back(hdl);
            ofNotifyEvent(_openEvent, hdl, this);
        }
        void on_close(websocketpp::connection_hdl hdl)
        {
            // auto it = std::find(_connectionHandles.begin(), _connectionHandles.end(), hdl);
            // if (it != _connectionHandles.end())
            // {
            //     _connectionHandles.erase(it);
            // }

            ofNotifyEvent(_closeEvent, hdl, this);
        }

        server _server;
        std::thread _networkThread;
        ofEvent<Message> _messageEvent;
        ofEvent<ConnectionHandle> _openEvent;
        ofEvent<ConnectionHandle> _closeEvent;
        std::vector<websocketpp::connection_hdl> _connectionHandles;
    };

}; // namespace ofxWebsocket