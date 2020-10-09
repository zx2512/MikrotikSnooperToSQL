#pragma once

#include <string>

class UnixSockConfig {

private:

	std::string sock_path;

public:

	void setSockPath(const std::string& sock_path) {
		this->sock_path = sock_path;
	}

	const std::string& getSockPath() const {
		return this->sock_path;
	}

};