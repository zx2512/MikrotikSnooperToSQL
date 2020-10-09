#pragma once

#include <string>
#include "base_config.hpp"

class DatabaseConfig : public BaseConfig {

private:

	std::string db;

public:

	void setDatabase(const std::string &db) {
		this->db = db;
	}

	const std::string &getDatabase() const {
		return db;
	}

};