#include "Client.hpp"

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>
#include <exception>
#include <sstream>
#include <stdexcept>

#include "logging.hpp"

Client::~Client() { close(this->_sockFd); }

Client::Client(const std::string& url) : _url(url), _port(80) {
  size_t pPos = url.find(":");
  if (pPos == std::string::npos) {
    this->_hostName = url.substr(0, url.find("/"));
  } else {
    this->_port = static_cast<u_int16_t>(
        std::atoi(url.substr(pPos + 1, url.find("/")).c_str()));
    this->_hostName = url.substr(0, pPos);
  }
  this->_sockFd = socket(AF_INET, SOCK_STREAM, 0);
  if (this->_sockFd == -1) {
    std::cerr << "fatal: socket() failed" << std::endl;
    return;
  }
  try {
    this->connectToServer();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

void Client::connectToServer() {
  struct addrinfo hints, *result;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  std::stringstream ss;
  ss << this->_port;

  int status =
      getaddrinfo(this->_hostName.c_str(), ss.str().c_str(), &hints, &result);
  if (status != EXIT_SUCCESS) {
    std::stringstream statusString;
    statusString << status;

    throw std::runtime_error("fatal: ft_curl(" + statusString.str() +
                             "): " + std::string(gai_strerror(status)) + ".");
  }
  struct sockaddr_in* addr = (struct sockaddr_in*)result->ai_addr;
  std::cout << "IP addr: " << inet_ntoa(addr->sin_addr) << std::endl;
  this->_srvSocketFd =
      connect(this->_sockFd, result->ai_addr, sizeof(struct sockaddr));
  if (this->_srvSocketFd == -1)
    throw std::runtime_error("fatal: ft_curl: Connection refused.");
}

void Client::print() const {
  LOG("===== CLIENT =====");
  LOG("URL: " << this->_url);
  LOG("Hostname: " << this->_hostName);
  LOG("Port: " << this->_port);
  LOG("Protocol: " << this->_protocol);
  LOG("==================");
}
