#include "json_config_router.hpp"

void JSONConfigRouter::parseAndLoad() {

	rapidjson::Document json = getJSONObject();

	this->mikrotik_api_config.setIP(json["mikrotik_devices"][this->getMikrotikAPIConfig().getIndex()]["ip"].GetString());

	this->mikrotik_api_config.setUsername(json["mikrotik_devices"][this->getMikrotikAPIConfig().getIndex()]["username"].GetString());

	this->mikrotik_api_config.setPassword(json["mikrotik_devices"][this->getMikrotikAPIConfig().getIndex()]["password"].GetString());

	this->mikrotik_api_config.setPort(json["mikrotik_devices"][this->getMikrotikAPIConfig().getIndex()]["port"].GetInt());

	this->mikrotik_api_config.setInterface(json["mikrotik_devices"][this->getMikrotikAPIConfig().getIndex()]["interface"].GetString());

	this->mikrotik_api_config.setChannelTimeout(json["mikrotik_devices"][this->getMikrotikAPIConfig().getIndex()]["channel_time"].GetString());

}