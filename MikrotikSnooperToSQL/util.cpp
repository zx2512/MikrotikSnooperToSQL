#include "util.hpp"

namespace UTIL {

	unsigned long long timeStringToMillis(const std::string &string) {

		unsigned long long millis = 0;

		unsigned long num;

		char *stop = nullptr;

		const char *pos = string.data();

		for (const char *end = pos + string.size(); stop != end; ) {

			num = strtol(pos, &stop, 10);

			if (stop == pos) {
				break;
			}

			if (*stop == 'd') {

				millis += (static_cast<unsigned long long>(num) * 86400000);

			} else if (*stop == 'h') {

				millis += (static_cast<unsigned long long>(num) * 3600000);

			} else if (*stop == 's') {

				millis += (static_cast<unsigned long long>(num) * 1000);

			} else if (*stop == 'm') {

				if (stop[1] == 's') {

					millis += num;

				} else {

					millis += (static_cast<unsigned long long>(num) * 60000);

				}

			}

			pos = stop + 1;
		}

		return millis;

	};

	void connectAndLoginWrapper(MIKROTIKPLUS::Connector &mikrotik, DB &db) {

		while (true) {

			try {

				mikrotik.connectAndLogin();

				db.insertActiveConnections(mikrotik.getAPISettings().getIP());

				break;

			} catch (MIKROTIKPLUS::NoSocketConnection e) {

				db.insertError(mikrotik.getAPISettings().getIP(), 1);

			} catch (MIKROTIKPLUS::LoginIncorrect e) {

				db.insertError(mikrotik.getAPISettings().getIP(), 2);

				break;

			}

		}

	}

}