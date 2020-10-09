#include "json_config_sock.hpp"

void JSONConfigSock::parseAndLoad() {

	rapidjson::Document json = getJSONObject();

	this->unix_sock_config.setSockPath(json["unix_sock"]["path"].GetString());

}