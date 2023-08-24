#include"Chat.h"

void Chat::run()
{
	std::cout << " Hello! You are welcome to register, or you can enter the chat room if you are already registered.\n";
	showAllUsers();
	showStartMenu();
	if (userCount_ >= 1 && escFromMenu_ == true)
	{
		showAllUsers();
		showChatMenu();
	}
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
			escFromMenu_ = true;
			menu = false;
			break;
		case 'q':
			std::cout << "\n Goodbye!\n";
			menu = false;
			break;
		default:
			std::cout << "\n I apologize, I didn't understand what you meant.\n";
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
			std::cout << "l\n";
			break;
		case '2':
			sendMessage();
			break;
		case 'q':
			menu = false;
			break;
		default:
			std::cout << "\n I apologize, I didn't understand what you meant.\n";
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
	bool check = false;
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
		std::cout << "\n User with this login is not in the chat room!" << std::endl;
	else
	{
		std::string text;
		std::cout << "\n Message...\n";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, text);
		Message msg(text, currentUser_, recipient);
		msgData_.push_back(msg);
	}
}

void Chat::showAllUsers()
{
	int number = 1;
	std::string pers = "person";
	if (userCount_ > 1)
		std::cout << "\n Now in chat room " << userCount_ << " " + pers + "s" << std::endl;
	else
		std::cout << "\n Now in chat room " << userCount_ << " " + pers << std::endl;

	for (const auto& user : userData_)
	{
		std::cout << "\n " << number << ") " << user;
		++number;
	}
}

void Chat::showAllMessage()
{
	for (const auto& msg : msgData_)
		std::cout << msg;
}