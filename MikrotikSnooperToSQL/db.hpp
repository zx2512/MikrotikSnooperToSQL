#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>

#include "mariadb++/connection.hpp"
#include "queries.hpp"

class DB {
private:

	mariadb::connection_ref connection;

	mariadb::statement_ref statement;

	mariadb::account_ref account;

	void executeQuery();

public:

	DB() { };

	DB(const std::string &host, const std::string &user, const std::string &password, const std::string &db, int port);

	~DB();

	void createConnection();

	void setAccount(const std::string &host, const std::string &user, const std::string &password, const std::string &db, int port);

	void insertError(const std::string &ip, const int error_id);

	void insertActiveConnections(const std::string &ip);

	void removeActiveConnection(const std::string &ip);

	void emptyActiveConnection();

};