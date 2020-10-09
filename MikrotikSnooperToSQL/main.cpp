#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <fstream>

#include "mariadb++/exceptions.hpp"

#include "json_config_amount.hpp"
#include "json_config_database.hpp"
#include "json_config_router.hpp"
#include "json_config_sock.hpp"
#include "worker.hpp"

namespace {

	DB db_global;

	//std::atomic<bool> got_signal = false;

}


#if defined _WIN32

#include <filesystem>

BOOL closeEvent(DWORD event) {

	db_global.emptyActiveConnection();

	//got_signal = true;

	return true;

}

#elif defined __unix__ || defined __APPLE__

#include <experimental/filesystem>

#include <csignal>

void signal_handler(int signal) {

	if ((signal == SIGTERM) || (signal == SIGABRT)) {

		db_global.emptyActiveConnection();

	}

}

#endif

int main(int argc, char* argv[]) {

	std::string path;

	if (argc == 2) {

		path = argv[1];

	} else if (argc == 1) {

		path = "./mikrotik.json";

	} else {

		std::cerr << "Incorrect arguments passed to the program" << "\n";
		std::cerr << "Correct usage: [program_name] [path_to_json_config]" << "\n";

	}

#if defined _WIN32

	if (!std::filesystem::exists(path)) {

#elif defined __unix__ || defined __APPLE__

	if (!std::experimental::filesystem::exists(path)) {

#endif

		std::cerr << "The path to the file is incorrect." << "\n";

		if (argc == 1) {
			std::cerr << "Correct usage: [program_name] [path_to_json_config]" << "\n";
		}

		exit(-1);

	}

	std::vector<std::thread> vector_thread;

	try {

		JSONConfigAmount json_config_amount(path);
		json_config_amount.parseAndLoad();

		JSONConfigDatabase json_config_database(path);
		json_config_database.parseAndLoad();

		JSONConfigSock json_config_sock(path);
		json_config_sock.parseAndLoad();

		db_global.setAccount(json_config_database.getDatabaseConfig().getIP(), json_config_database.getDatabaseConfig().getUsername(),
			json_config_database.getDatabaseConfig().getPassword(), json_config_database.getDatabaseConfig().getDatabase(),
			json_config_database.getDatabaseConfig().getPort());

		db_global.createConnection();

#if defined _WIN32

		SetConsoleCtrlHandler((PHANDLER_ROUTINE)(closeEvent), TRUE);

#elif defined __unix__ || defined __APPLE__

		std::signal(SIGINT, signal_handler);

#endif

		// Due to improper shutdowns and such, this table might be filled with IPs that aren't really connected to by this program
		db_global.emptyActiveConnection();

		for (int i = 0; i < json_config_amount.getDevicesAmount(); ++i) {

			vector_thread.push_back(std::thread([&json_config_database, &json_config_sock, &path, i] {

				JSONConfigRouter json_config_router(path, i);
				json_config_router.parseAndLoad();

				WORKER::start(json_config_router, json_config_database, json_config_sock);

			}));

		}

		for (std::thread& thread : vector_thread) {

			if (thread.joinable()) {

				thread.join();

			}

		}

	} catch (mariadb::exception::connection e) {

		std::cerr << "Cannot connect to the database; the information is wrong or the server is unavailable" << "\n";

		exit(-1);

	}

	/*while (got_signal == false) {}

	db_global.emptyActiveConnection(); */

}