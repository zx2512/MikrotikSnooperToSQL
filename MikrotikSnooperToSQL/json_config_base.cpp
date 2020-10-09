#include "json_config_base.hpp"

const rapidjson::Document JSONBase::getJSONObject() {

	this->config_file.open(this->path);

	rapidjson::IStreamWrapper stream_wrapper(this->config_file);
	rapidjson::Document json;
	rapidjson::ParseResult parse_result = json.ParseStream(stream_wrapper);

	if (!parse_result) {
		
		std::cerr << "The configuration file is incorrect: " << 
			rapidjson::GetParseErrorFunc(parse_result.Code()) << "\n";

		exit(-1);

	}

	this->config_file.close();

	return json;

}