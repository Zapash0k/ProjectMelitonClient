#include <boost/asio.hpp>
#include <iostream>
#include <thread>

using boost::asio::ip::tcp;
using namespace std;
class ChatClient {
public:
    ChatClient(boost::asio::io_context& io_context);
    void run();

private:
    tcp::socket socket_;
    string username_;
};