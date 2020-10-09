#pragma once

#include <iostream>
#include <string>

#include "json_config_base.hpp"
#include "database_config.hpp"

class JSONConfigDatabase: JSONBase {
private:

	DatabaseConfig database_config;

public:

	JSONConfigDatabase(const std::string &path): JSONBase(path) { }

	DatabaseConfig &getDatabaseConfig() {

		return this->database_config;

	}

	void parseAndLoad();

};