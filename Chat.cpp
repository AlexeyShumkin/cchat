#include"Chat.h"

void Chat::run()
{
	std::cout << "\n Hello! You are welcome to register, or you can enter the chat room if you are already registered.\n";
	showAllUsers();
	do
	{	
		char action = '0';
		std::cout << "\n To register press 1, to authorize press 2, to log out of the account press 3, press q to exit: ";
		std::cin >> action;
		switch (action)
		{
		case '1':
			if (currentUser_ != nullptr)
			{
				std::cout << "\n You are already logged in!\n";
				break;
			}
			registration();
			break;
		case '2':
			if (userData_.size() == 0)
			{
				std::cout << "\n There's no one in the chat room yet, so register first!\n";
				break;
			}
			else
			{
				if (currentUser_ != nullptr)
					std::cout << "\n You are already logged in!\n";
				else
					authorization();
				break;
			}
		case '3':
			if (currentUser_ == nullptr)
			{
				std::cout << "\n You are not authorized yet!\n";
				break;
			}
			else
			{
				std::cout << "\n user " << currentUser_->getLogin() << " left the chat room.\n";
				currentUser_ = nullptr;
				break;
			}
		case 'q':
			currentUser_ = nullptr;
			atWork_ = false;
			break;
		default:
			std::cout << "\n Your command is unclear. Please, select an action from the list:\n";
		}
		
		if (currentUser_)
		{
			showAllUsers();
			showChatMenu();
		}
	} while (atWork_);
	std::cout << "\n Goodbye!\n";
}

void Chat::showChatMenu()
{
	bool menu = true;
	char action = '0';
	do
	{
		std::cout << "\n To write a public message press 1, to go to the dialog press 2, to view chat press 3, press q to exit from chat menu: ";
		std::cin >> action;
		switch (action)
		{
		case '1':
			openDialog_ = false;
			sendMessage();
			break;
		case '2':
			openDialog_ = true;
			sendMessage();
			break;
		case '3':
			showAllMessages();
			break;
		case 'q':
			menu = false;
			break;
		default:
			std::cout << "\n Your command is unclear. Please, select an action from the list.\n";
		}
	} while (menu);
}

void Chat::registration()
{
	std::string login;
	std::string password;
	std::string name;
	std::cout << "\n Enter your login: ";
	std::cin >> login;
	std::cout << "\n Enter your password: ";
	std::cin >> password;
	std::cout << "\n Enter your chat name: ";
	std::cin >> name;
	User newUser(login, password, name);
	if (userData_.size() != 0)
	{
		bool match = false;
		for (const auto& user : userData_)
		{
			if (newUser.getLogin() == user.getLogin())
			{
				match = true;
				break;
			}
		}
		if(match == true)
			std::cout << "\n This login is already taken!\n";
		else
			userData_.push_back(newUser);
	}
	else
		userData_.push_back(newUser);
}

void Chat::authorization()
{
	bool match = false;
	std::string login;
	std::string password;
	do
	{
		std::cout << "\n Enter your login: ";
		std::cin >> login;
		std::cout << "\n Enter your password: ";
		std::cin >> password;
		for (auto& user : userData_)
		{
			if (login != user.getLogin() || password != user.getPassword())
				continue;
			else
			{
				currentUser_ = &user;
				match = true;
			}
		}
		if (!match)
			std::cout << "\n Invalid login or password!\n";
		else
			std::cout << "\n Welcome to the chat room!\n";
	} while (!match);
}

void Chat::sendMessage()
{
	if (openDialog_ == false)
	{
		std::string recipient = "all";
		std::string text;
		std::cout << "\n Message: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, text);
		if (text == "")
			std::cout << "\n You can't send an empty message!\n";
		else
		{
			Message msg(text, currentUser_->getLogin(), recipient);
			pubMsgData_.push_back(msg);
		}
	}
	else
	{
		bool check = false;
		std::string text;
		std::string recipient;
		std::cout << "\n Enter the recipient login: ";
		std::cin >> recipient;
		for (const auto& user : userData_)
		{
			if (recipient != user.getLogin())
				continue;
			else
				check = true;
		}
		if (!check)
			std::cout << "\n User with this login is not in the chat room!\n";
		else
		{
			do
			{
				char query = '0';
				std::cout << "\n to send a message press 1, to view the conversation press 2, to leave the dialog press q: ";
				std::cin >> query;
				if (query == '1')
				{
					std::cout << "\n Message: ";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::getline(std::cin, text);
					if (text == "")
						std::cout << "\n You can't send an empty message!\n";
					else
					{
						Message msg(text, currentUser_->getLogin(), recipient);
						pvtMsgData_.emplace(std::make_pair(currentUser_->getLogin(), recipient), msg);
					}
				}
				else if (query == '2')
					showDialog(recipient);
				else if (query == 'q')
					openDialog_ = false;
				else
					std::cout << "\n Your command is unclear. Please, select an action from the list.\n";
			} while (openDialog_);
		}
	}
}

void Chat::showAllUsers()
{
	if (userData_.size() == 0)
		std::cout << "\n There's no one in the chat room right now.\n";
	else if (userData_.size() == 1)
		std::cout << "\n Now in chat room 1 user:\n\n 1) " << userData_[0] << "\tonline\n";
	else
	{
		int number = 1;
		std::cout << "\n Now in chat room " << userData_.size() << " users:\n";
		for (const auto& user : userData_)
		{
			if (currentUser_ == &user)
			{
				std::cout << "\n " << number << ") " << user << "\tonline\n";
				++number;
			}
			else
			{
				std::cout << "\n " << number << ") " << user << "\toffline\n";
				++number;
			}
		}
	}
}

void Chat::showAllMessages()
{
	if (pubMsgData_.size() == 0)
		std::cout << "\n There are no messages in the chat room yet!\n";
	else
	{
		for (const auto& msg : pubMsgData_)
			std::cout << msg;
	}
}

void Chat::showDialog(const std::string& recipient)
{
	auto dialog = pvtMsgData_.find(std::make_pair(currentUser_->getLogin(), recipient));
	auto reverseDialog = pvtMsgData_.find(std::make_pair(recipient, currentUser_->getLogin()));
	if (dialog != pvtMsgData_.end() && reverseDialog == pvtMsgData_.end())
	{
		for (dialog; dialog != pvtMsgData_.end(); ++dialog)
			std::cout << dialog->second;
	}
	else if (reverseDialog != pvtMsgData_.end() && dialog == pvtMsgData_.end())
	{
		for (reverseDialog; reverseDialog != pvtMsgData_.end(); ++reverseDialog)
			std::cout << reverseDialog->second;
	}
	else if (dialog != pvtMsgData_.end() && reverseDialog != pvtMsgData_.end())
	{
		std::map<std::string, Message> temp;
		for (dialog; dialog != pvtMsgData_.end(); ++dialog)
			temp.emplace(dialog->second.getSendinTime(), dialog->second);
		for (reverseDialog; reverseDialog != pvtMsgData_.end(); ++reverseDialog)
			temp.emplace(reverseDialog->second.getSendinTime(), reverseDialog->second);
		for (const auto& t : temp)
			std::cout << t.second;
	}
	else
		std::cout << "\n There are no messages in this dialog yet!\n";
}