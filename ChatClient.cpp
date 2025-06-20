#include "ChatClient.h"
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
using boost::asio::ip::tcp;
using namespace std;


ChatClient::ChatClient(boost::asio::io_context& io_context)
    : socket_(io_context) {
    // Connect to server
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("127.0.0.1", "4805");
    boost::asio::connect(socket_, endpoints);

    // Get username prompt
    boost::asio::streambuf buf;
    read_until(socket_, buf, ':');
    cout << &buf;

    // Send username
    getline(cin, username_);
    write(socket_, boost::asio::buffer(username_ + "\n"));

    cout << "Welcome, " << username_ << "! Type messages below:\n";
}

void ChatClient::run() {
    // Start reader thread
    thread([this]() {
        try {
            while (true) {
                boost::asio::streambuf buf;
                read_until(socket_, buf, '\n');
                cout << &buf;
            }
        }
        catch (exception& e) {
            cout << "Connection closed\n";
        }
        }).detach();

    // Main writer loop
    try {
        string msg;
        while (getline(cin, msg)) {
            write(socket_, boost::asio::buffer(msg + "\n"));
        }
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}