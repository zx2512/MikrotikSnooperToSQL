#pragma once

#include <string>

#include "json_config_base.hpp"

class JSONConfigAmount: public JSONBase {
private:

	int devices_amount;

public:

	JSONConfigAmount(const std::string &path): JSONBase(path), devices_amount(-1) { }

	int getDevicesAmount() const {

		return this->devices_amount;

	}

	void parseAndLoad();

};