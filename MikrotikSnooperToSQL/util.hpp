#pragma once

#include <string>

#include "db.hpp"

#include "MikrotikPlus/connector.hpp"
#include "MikrotikPlus/exceptions.hpp"
#include "MikrotikPlus/sentence.hpp"

namespace UTIL {

	unsigned long long timeStringToMillis(const std::string &string);

	void connectAndLoginWrapper(MIKROTIKPLUS::Connector &mikrotik, DB &db);

}