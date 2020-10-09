#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/filereadstream.h"

class JSONBase {
private:

	std::string path;

	std::ifstream config_file;
	 
public:

	JSONBase(const std::string &path): path(path) { }

	// Opens the file, parses it, closes and returns the json object
	const rapidjson::Document getJSONObject();

	virtual void parseAndLoad() = 0;

};