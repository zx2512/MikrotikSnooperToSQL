#include "json_config_database.hpp"

void JSONConfigDatabase::parseAndLoad() {

	rapidjson::Document json = getJSONObject();

	this->database_config.setIP(json["mysql_database"]["login_information"]["host"].GetString());

	this->database_config.setDatabase(json["mysql_database"]["login_information"]["db"].GetString());

	this->database_config.setUsername(json["mysql_database"]["login_information"]["username"].GetString());

	this->database_config.setPassword(json["mysql_database"]["login_information"]["password"].GetString());

	this->database_config.setPort(json["mysql_database"]["login_information"]["port"].GetInt());

}