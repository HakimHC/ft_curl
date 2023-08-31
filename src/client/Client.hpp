#ifndef __CLIENT_HPP__
# define __CLIENT_HPP__

# include <string>
#include <sys/types.h>

class Client {
	public:
		Client(const std::string&);
		~Client();

		void print() const;
	private:
		Client();

		const std::string& 	_url;
		std::string 		_protocol;
		std::string 		_hostName;
		u_int16_t		_port;

		int 			_sockFd;

};

#endif // __CLIENT_HPP__
