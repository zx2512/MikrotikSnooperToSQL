#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <vector>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

class UnixSock {
private:

	int sock_fd;

	std::string path;

	int sendSocket(const char *data, const int length, const int flags);

	void closeSocket() const;

public:

	UnixSock(const std::string &path): path(path), sock_fd(-1) { }

	~UnixSock();

	void sendStationInformation(const std::vector<std::string> &information_array);

	int initConnection();

};