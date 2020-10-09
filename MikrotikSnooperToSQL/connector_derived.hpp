// We need to remove the active connection when the destructor is called

#pragma once

#include "db.hpp"

#include "MikrotikPlus/connector.hpp"

class ConnectorDerived : public MIKROTIKPLUS::Connector {
private:

	DB &db;

public:

	ConnectorDerived(const std::string &ip, const std::string &username, 
					 const std::string &password, const int port, DB &db) : 
		MIKROTIKPLUS::Connector(ip, username, password, port), db(db)  { }

	virtual ~ConnectorDerived() override;

};