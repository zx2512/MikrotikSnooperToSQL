#pragma once

#include <string>

#include "json_config_base.hpp"
#include "unix_sock_config.hpp"

class JSONConfigSock : JSONBase {
private:

	UnixSockConfig unix_sock_config;

public:

	JSONConfigSock(const std::string &path) : JSONBase(path) { }

	UnixSockConfig& getUnixSockConfig() {

		return this->unix_sock_config;

	}

	void parseAndLoad();

};