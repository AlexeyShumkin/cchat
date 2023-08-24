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
	void showStartMenu();
	void showChatMenu();
private:
	bool escFromMenu_ = false;
	std::vector<User> userData_;
	std::vector<Message> msgData_;
	User* currentUser_ = nullptr;
	int userCount_ = 0;
};