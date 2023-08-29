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
	void showAllMessage();
	void showDialog(const std::string& recipient);
	void showChatMenu();
private:
	bool atWork_ = true;
	bool openDialog_ = false;
	User* currentUser_ = nullptr;
	std::vector<User> userData_;
	std::vector<Message> publicMsgData_;
	std::vector<Message> privateMsgData_;
	std::vector<std::pair<std::string, std::string>*> dialogData_;
	std::multimap<std::pair<std::string, std::string>*, Message> pmd_;

};