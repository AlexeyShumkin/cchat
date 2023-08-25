#pragma once
#include<vector>
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
	bool atWork = true;
	bool openDialog_ = false;
	User* current_registered_user_ = nullptr;
	User* current_authorized_user_ = nullptr;
	std::vector<User> userData_;
	std::vector<Message> publicMsgData_;
	std::vector<Message> privateMsgData_;
};