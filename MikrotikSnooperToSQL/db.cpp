#include "db.hpp"

DB::DB(const std::string &host, const std::string &user, const std::string &password, const std::string &db, int port) {

	//this->account = mariadb::account::create(host, user, password, db, port);

	this->setAccount(host, user, password, db, port);

	//this->connection = mariadb::connection::create(this->account);

}

DB::~DB() {

	//mysql_close(connection);

}

void DB::setAccount(const std::string &host, const std::string &user, const std::string &password, const std::string &db, int port) {

	this->account = mariadb::account::create(host, user, password, db, port);

}

void DB::createConnection() {

	this->connection = mariadb::connection::create(this->account);

}

void DB::insertError(const std::string &ip, const int error_id) {

	this->statement = this->connection->create_statement(QUERIES::insert_error);

	statement->set_string(0, ip);
	statement->set_unsigned64(1, error_id);
	
	this->executeQuery();

}

void DB::insertActiveConnections(const std::string &ip) {

	this->statement = this->connection->create_statement(QUERIES::insert_active_connection);

	statement->set_string(0, ip);

	this->executeQuery();

}

void DB::removeActiveConnection(const std::string &ip) {

	this->statement = this->connection->create_statement(QUERIES::remove_active_connection);

	statement->set_string(0, ip);

	this->executeQuery();

}

void DB::emptyActiveConnection() {

	this->statement = this->connection->create_statement(QUERIES::empty_active_connections);

	this->executeQuery();

}

void DB::executeQuery() {

	this->statement->execute();

}