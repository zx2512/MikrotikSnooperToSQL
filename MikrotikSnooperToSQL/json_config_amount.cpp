#include "json_config_amount.hpp"

#include <iostream>

void JSONConfigAmount::parseAndLoad() {

	rapidjson::Document json = getJSONObject();

	this->devices_amount = json["mikrotik_devices"].Size();

}