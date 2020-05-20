#pragma once
#include "ofMain.h"
#include "ofxAsio.h"
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <iostream>

using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

// pull out the type of messages sent by our config
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

namespace ofxWebsocket
{
    class Client
    {
    public:
        typedef websocketpp::client<websocketpp::config::asio_client> client;
        typedef websocketpp::connection_hdl Connection;
        void setup(std::string host, int port)
        {
            try
            {
                // Set logging to be pretty verbose (everything except message payloads)
                _client.set_access_channels(websocketpp::log::alevel::all);
                _client.clear_access_channels(websocketpp::log::alevel::frame_payload);

                // Initialize ASIO
                _client.init_asio();

                // Register our message handler
                // _client.set_socket_init_handler(bind(&type::on_socket_init,this,::_1));
                //m_endpoint.set_tls_init_handler(bind(&type::on_tls_init,this,::_1));
                _client.set_message_handler(bind(&Client::on_message, this, &_client, ::_1, ::_2));
                _client.set_open_handler(bind(&Client::on_open, this, ::_1));
                _client.set_close_handler(bind(&Client::on_close, this, ::_1));
                // _client.set_fail_handler(bind(&type::on_fail,this,::_1));

                websocketpp::lib::error_code ec;
                std::string uri = "ws://";
                uri += host;
                uri += ":";
                uri += ofToString(port);
                client::connection_ptr con = _client.get_connection(uri, ec);
                if (ec)
                {
                    std::cout << "could not create connection because: " << ec.message() << std::endl;
                }

                // Note that connect here only requests a connection. No network messages are
                // exchanged until the event loop starts running in the next line.
                _client.connect(con);

                // Start the ASIO io_service run loop
                // this will cause a single connection to be made to the server. c.run()
                // will exit when this connection is closed.
                // c.run();
                _networkThread = std::thread(&client::run, &_client);
            }
            catch (websocketpp::exception const &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        void send(std::string payload)
        {
            send(_connection, payload);
        }
        void send(Connection con, std::string payload)
        {
            websocketpp::lib::error_code ec;
            _client.send(con, payload, websocketpp::frame::opcode::text, ec);
            if (ec)
            {
                std::cout << "Echo failed because: " << ec.message() << std::endl;
            }
        }
        void addListener(Listener *listener)
        {
            ofAddListener(_messageEvent, listener, &Listener::onMessage);
            ofAddListener(_openEvent, listener, &Listener::onOpen);
            ofAddListener(_closeEvent, listener, &Listener::onClose);
        }
        void on_message(client *c, websocketpp::connection_hdl hdl, message_ptr msg)
        {
            Message message(hdl, msg->get_payload(), msg->get_opcode());
            ofNotifyEvent(_messageEvent, message, this);
        }
        void on_open(websocketpp::connection_hdl hdl)
        {
            _connection = hdl;
            _client.send(hdl, "opened", websocketpp::frame::opcode::text);
            ofNotifyEvent(_openEvent, hdl, this);
        }
        void on_close(websocketpp::connection_hdl hdl)
        {
            ofNotifyEvent(_closeEvent, hdl, this);
        }
        void on_fail(websocketpp::connection_hdl hdl)
        {
            client::connection_ptr con = _client.get_con_from_hdl(hdl);

            std::cout << "Fail handler" << std::endl;
            std::cout << con->get_state() << std::endl;
            std::cout << con->get_local_close_code() << std::endl;
            std::cout << con->get_local_close_reason() << std::endl;
            std::cout << con->get_remote_close_code() << std::endl;
            std::cout << con->get_remote_close_reason() << std::endl;
            std::cout << con->get_ec() << " - " << con->get_ec().message() << std::endl;
        }

        client _client;
        Connection _connection;
        std::thread _networkThread;
        ofEvent<Message> _messageEvent;
        ofEvent<Connection> _openEvent;
        ofEvent<Connection> _closeEvent;
    };
}; // namespace ofxWebsocket
