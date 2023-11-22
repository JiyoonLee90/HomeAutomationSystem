#ifndef SMSMANAGER_H
#define	SMSMANAGER_H
#include <memory>
#include <map>
#include <vector>
#include <iostream>

class SMSManager {
	using PHONENUMBER = std::string;
	std::map<std::string, std::vector<PHONENUMBER>> event_addr_map;

public:
	SMSManager();
	
	void send_sms(const std::string& key, const std::string& msg);
};
#endif 

