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
	void showStartMenu();
	void showChatMenu();
private:
	int userCount_ = 0;
	bool escFromStartMenu_ = false;
	bool openDialog_ = false;
	User* currentUser_ = nullptr;
	std::vector<User> userData_;
	std::vector<Message> publicMsgData_;
	std::vector<Message> privateMsgData_;
};