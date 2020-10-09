#include "unix_sock.hpp"

UnixSock::~UnixSock() {

	this->closeSocket();

}

int UnixSock::initConnection() {

	int length = 0;

	struct sockaddr_un address;

	sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);

	address.sun_family = AF_UNIX;
	std::strcpy(address.sun_path, path.c_str());
	
	length = std::strlen(address.sun_path) + sizeof(address.sun_family);

	int connection_result = connect(sock_fd, (struct sockaddr*) & address, length);

	if (connection_result == -1) {

		//this->closeSocket();

		//this->sock_fd = -1;

		std::cerr << "Can't connect to the unix sock server" << "\n";

		exit(-1);

	}

	return connection_result;

}

void UnixSock::sendStationInformation(const std::vector<std::string> &information_vector) {

	rapidjson::Document json;

	// Specify a json object
	json.SetObject();

	rapidjson::Document::AllocatorType &allocator = json.GetAllocator();

	rapidjson::Value object(rapidjson::kObjectType);

	object.AddMember("active", rapidjson::StringRef(information_vector[0].c_str()), allocator);
	object.AddMember("address", rapidjson::StringRef(information_vector[1].c_str()), allocator);
	object.AddMember("signal-to-noise", rapidjson::StringRef(information_vector[2].c_str()), allocator);
	object.AddMember("signal-strength", rapidjson::StringRef(information_vector[3].c_str()), allocator);
	object.AddMember("source_router_host", rapidjson::StringRef(information_vector[4].c_str()), allocator);

	json.AddMember("station_information", object, allocator);

	rapidjson::StringBuffer buffer;

	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	json.Accept(writer);

	this->sendSocket(buffer.GetString(), buffer.GetSize(), 0);

}

int UnixSock::sendSocket(const char *data, const int length, const int flags) {

	return write(this->sock_fd, data, length);

}

void UnixSock::closeSocket() const {

	close(this->sock_fd);

}