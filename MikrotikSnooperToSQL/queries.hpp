#pragma once

#include <string>

namespace QUERIES {

	const std::string insert_error = "INSERT INTO `errors` (`ip`, `error`) VALUES (INET6_ATON(?), ?);";

	const std::string insert_active_connection = "INSERT INTO `active_connections` (`ip`) VALUES (INET6_ATON(?));";

	const std::string remove_active_connection = "DELETE FROM `active_connections` WHERE `ip` = CAST(INET6_ATON(?) as binary(16))";

	const std::string empty_active_connections = "TRUNCATE `active_connections`;";

}