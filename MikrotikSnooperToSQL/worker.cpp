#include "worker.hpp"

namespace WORKER {

    void start(JSONConfigRouter &json_config_router, JSONConfigDatabase &json_config_database, JSONConfigSock &json_config_sock) {

        DB db(json_config_database.getDatabaseConfig().getIP(), json_config_database.getDatabaseConfig().getUsername(),
              json_config_database.getDatabaseConfig().getPassword(), json_config_database.getDatabaseConfig().getDatabase(),
              json_config_database.getDatabaseConfig().getPort());
         
        db.createConnection();

        UnixSock unix_sock(json_config_sock.getUnixSockConfig().getSockPath());
        unix_sock.initConnection();

        ConnectorDerived mikrotik = ConnectorDerived(json_config_router.getMikrotikAPIConfig().getIP(), json_config_router.getMikrotikAPIConfig().getUsername(),
            json_config_router.getMikrotikAPIConfig().getPassword(), json_config_router.getMikrotikAPIConfig().getPort(), db);

        std::unordered_map<std::string, std::string> sentence_map;

        MIKROTIKPLUS::Sentence sentence_to_write;
        MIKROTIKPLUS::Sentence read_sentence;

        UTIL::connectAndLoginWrapper(mikrotik, db);

        // Set appropriate channel timeout for the snooper
        sentence_to_write.addWord("/interface/wireless/snooper/set");
        sentence_to_write.addWord("=channel-time=" +
            json_config_router.getMikrotikAPIConfig().getChannelTimeout());

        mikrotik.writeSentence(sentence_to_write);

        sentence_to_write.clear();

        // Start snooper
        sentence_to_write.addWord("/interface/wireless/snooper/flat-snoop");
        sentence_to_write.addWord(std::string("=interface=" + json_config_router.getMikrotikAPIConfig().getInterface()));

        mikrotik.writeSentence(sentence_to_write);

        while (true) {

            // We have to ensure the connection doesn't get dropped whilst reading the sentences. If it does, then we will start over.
            while (true) {

                try {

                    read_sentence = mikrotik.readSentence();

                    break;

                } catch (MIKROTIKPLUS::ConnectionTimedOut e) {

                    db.insertError(mikrotik.getAPISettings().getIP(), 3);

                    db.removeActiveConnection(mikrotik.getAPISettings().getIP());

                    UTIL::connectAndLoginWrapper(mikrotik, db);

                    mikrotik.writeSentence(sentence_to_write);

                } catch (MIKROTIKPLUS::NoSocketConnection e) {

                    db.insertError(mikrotik.getAPISettings().getIP(), 1);

                    db.removeActiveConnection(mikrotik.getAPISettings().getIP());

                    UTIL::connectAndLoginWrapper(mikrotik, db);

                    mikrotik.writeSentence(sentence_to_write);

                }

            }

            sentence_map = read_sentence.getMap();

            try {

                if (const auto it = sentence_map.find("type"); it != sentence_map.end() && it->second == "station") {

                    if (sentence_map.find("signal-to-noise") == sentence_map.end()) {
                        sentence_map["signal-to-noise"] = '0';
                    }

                    if (sentence_map.find("address") == sentence_map.end()) {
                        continue;
                    }

                    unix_sock.sendStationInformation(std::vector<std::string> {sentence_map["active"], sentence_map["address"],
                        sentence_map["signal-to-noise"], sentence_map["signal-strength"], mikrotik.getAPISettings().getIP()});

                // Interface doesn't exist
                } else if (const auto it = sentence_map.find("message"); (it != sentence_map.end()) &&
                    ((it->second.find("does not") != std::string::npos))) {

                    db.insertError(mikrotik.getAPISettings().getIP(), 4);

                }

            } catch (...) {}

        }

    }

}