#pragma once

#include <thread>
#include <unordered_map>
#include <array>

#include "MikrotikPlus/exceptions.hpp"
#include "MikrotikPlus/sentence.hpp"

#include "connector_derived.hpp"
#include "db.hpp"
#include "unix_sock.hpp"
#include "util.hpp"
#include "json_config_database.hpp"
#include "json_config_router.hpp"
#include "json_config_sock.hpp"

namespace WORKER {

    void start(JSONConfigRouter& json_config_router, JSONConfigDatabase &json_config_database, JSONConfigSock &json_config_sock);

}