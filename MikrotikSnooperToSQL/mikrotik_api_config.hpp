#pragma once

#include <string>
#include "base_config.hpp"

class MikrotikAPIConfig : public BaseConfig {
private:

	std::string _interface;

	int index;

	std::string channel_timeout;

public:

	MikrotikAPIConfig() : index(-1) { };

	const std::string &getInterface() const {
		return this->_interface;
	}

	const int getIndex() const {
		return this->index;
	}

	const std::string& getChannelTimeout() const {
		return this->channel_timeout;
	}

	void setIndex(int index) {
		this->index = index;
	}

	void setInterface(const std::string &_interface) {
		this->_interface = _interface;
	}

	void setChannelTimeout(const std::string &channel_timeout) {
		this->channel_timeout = channel_timeout;
	}

};