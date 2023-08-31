#include <unistd.h>

#include "Client.hpp"
#include "logging.hpp"

Client::~Client() {
	close(this->_sockFd);
}

Client::Client(const std::string& url)
	: _url(url), _port(80) {
	
}

void Client::print() const {
	LOG("===== CLIENT =====");
	LOG("URL: " << this->_url);
	LOG("Hostname: " << this->_hostName);
	LOG("Port: " << this->_port);
	LOG("Protocol: " << this->_protocol);
	LOG("==================");
}
