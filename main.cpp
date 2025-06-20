#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include "ChatClient.h"
using boost::asio::ip::tcp;
using namespace std;

int main() {
    try {
        boost::asio::io_context io_context;
        ChatClient client(io_context);
        client.run();
    }
    catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}