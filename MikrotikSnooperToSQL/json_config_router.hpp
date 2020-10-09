#pragma once

#include <string>

#include "json_config_base.hpp"
#include "mikrotik_api_config.hpp"

class JSONConfigRouter: JSONBase {
private:

	MikrotikAPIConfig mikrotik_api_config;

public:

	JSONConfigRouter(const std::string &path, const int index): JSONBase(path) {

		this->mikrotik_api_config.setIndex(index);

	}

	MikrotikAPIConfig &getMikrotikAPIConfig() {

		return this->mikrotik_api_config;

	}

	void parseAndLoad();

};