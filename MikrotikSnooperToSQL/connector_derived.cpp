#include "connector_derived.hpp"

ConnectorDerived::~ConnectorDerived() {

	this->closeSocket();

	this->db.removeActiveConnection(this->getAPISettings().getIP());

}