#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <sys/types.h>

#include <string>

class Client {
 public:
  Client(const std::string&);
  ~Client();

  void print() const;

 private:
  Client();

  void connectToServer();

  const std::string& _url;
  std::string _protocol;
  std::string _hostName;
  u_int16_t _port;

  int _sockFd;
  int _srvSocketFd;
};

#endif  // __CLIENT_HPP__
