#include "SMSManager.h"

SMSManager::SMSManager() {
	event_addr_map["POWER_ON"].push_back("010-1111-1111");
	event_addr_map["POWER_ON"].push_back("010-2222-2222");
	event_addr_map["POWER_OFF"].push_back("010-3333-3333");
	event_addr_map["POWER_OFF"].push_back("010-4444-4444");
}

/* send msg */
void SMSManager::send_sms(const std::string& key, const std::string& msg) {
	auto it = event_addr_map.find(key);
	if (it != event_addr_map.end()) {
		for (const auto& e : it->second) {
			std::cout << "[To : " << e << "] " << msg << std::endl;
		}
	}
	else std::cerr << "can't find event in event_addr_map" << std::endl;
}