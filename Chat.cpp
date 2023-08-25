#include"Chat.h"

void Chat::run()
{
	std::cout << " Hello! You are welcome to register, or you can enter the chat room if you are already registered.\n";
	showAllUsers();
	showStartMenu();
	if (userCount_ >= 1 && escFromStartMenu_ == true)
	{
		showAllUsers();
		showChatMenu();
	}
	showAllMessage();
}

void Chat::showStartMenu()
{
	bool menu = true;
	char action = '0';
	do
	{
		std::cout << "\n To register press 1, to enter the chat room press 2, press q to exit: ";
		std::cin >> action;
		switch (action)
		{
		case '1':
			registration();
			break;
		case '2':
			if (userCount_ == 0)
			{
				std::cout << "\n There's no one in the chat room yet, so register first!\n";
				break;
			}
			authorization();
			escFromStartMenu_ = true;
			menu = false;
			break;
		case 'q':
			std::cout << "\n Goodbye!\n";
			menu = false;
			break;
		default:
			std::cout << "\n Your command is unclear. Please, select an action from the list.\n";
		}
	} while (menu);
}

void Chat::showChatMenu()
{
	bool menu = true;
	char action = '0';
	do
	{
		std::cout << "\n To write a public message press 1, to go to the dialog press 2, to return to the start menu press q: ";
		std::cin >> action;
		switch (action)
		{
		case '1':
			sendMessage();
			showAllMessage();
			break;
		case '2':
			openDialog_ = true;
			sendMessage();
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
	User user(login, password, name);
	userData_.push_back(user);
	++userCount_;
}

void Chat::authorization()
{
	bool check = false;
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
			if (user.signIn(login, password) == nullptr)
				continue;
			else
			{
				currentUser_ = user.signIn(login, password);
				check = true;
			}
		}
		if (!check)
			std::cout << "\n Invalid login or password!" << std::endl;
		else
			std::cout << "\n Welcome to the chat room!" << std::endl;
	} while (!check);
}

void Chat::sendMessage()
{
	if (openDialog_ == false)
	{
		std::string recipient = "All";
		std::string text;
		std::cout << "\n Message: ";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, text);
		Message msg(text, currentUser_, recipient);
		publicMsgData_.push_back(msg);
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
			std::cout << "\n User with this login is not in the chat room!\n" << std::endl;
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
					Message msg(text, currentUser_, recipient);
					privateMsgData_.push_back(msg);
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
	int number = 1;
	std::string pers = "user";
	if (userCount_ == 1)
		std::cout << "\n Now in chat room " << userCount_ << " " + pers << std::endl;
	else
		std::cout << "\n Now in chat room " << userCount_ << " " + pers + "s" << std::endl;

	for (const auto& user : userData_)
	{
		std::cout << "\n " << number << ") " << user;
		++number;
	}
}

void Chat::showAllMessage()
{
	for (const auto& msg : publicMsgData_)
		std::cout << msg;
}

void Chat::showDialog(const std::string& recipient)
{
	for (const auto& msg : privateMsgData_)
		if(msg.getRecipient() == recipient)
			std::cout << msg;
}