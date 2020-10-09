#pragma once

#include <string>

class BaseConfig {

private:

	std::string ip;
	std::string username;
	std::string password;
	int port;

public:

	BaseConfig() : port(0) { };

	void setIP(const std::string &ip) {
		this->ip = ip;
	}

	void setUsername(const std::string &username) {
		this->username = username;
	}

	void setPassword(const std::string &password) {
		this->password = password;
	}

	void setPort(const int port) {
		this->port = port;
	}

	const std::string &getIP() const {
		return this->ip;
	}

	const std::string &getUsername() const {
		return this->username;
	}

	const std::string &getPassword() const {
		return this->password;
	}

	const int getPort() const {
		return this->port;
	}

};