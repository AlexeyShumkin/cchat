#pragma once
#include<vector>
#include<map>
#include"Message.h"

class Chat
{
public:
	void run();
	void registration();
	void authorization();
	void sendMessage();
	void showAllUsers();
	void showAllMessages();
	void showDialog(const std::string& recipient);
	void showChatMenu();
private:
	bool atWork_ = true;
	bool openDialog_ = false;
	User* currentUser_ = nullptr;
	std::vector<User> userData_;
	std::vector<Message> pubMsgData_;
	std::multimap<std::pair<std::string, std::string>, Message> pvtMsgData_;
};