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
			if (current_registered_user_ != nullptr)
				std::cout << "\n You are already registered! Authorization required to enter the chat room.\n";
			else
				registration();
			break;
		case '2':
			if (userData_.size() == 0)
			{
				std::cout << "\n There's no one in the chat room yet, so register first!\n";
				break;
			}
			if (current_authorized_user_)
				std::cout << "\n You are already logged in!\n";
			else
				authorization();
			break;
		case '3':
			if (current_registered_user_ == nullptr)
				std::cout << "\n You are not registered yet!\n";
			else
			{
				if(current_authorized_user_ == nullptr)
					std::cout << "\n You are not authorized yet!\n";
				else
				{
					std::cout << "\n user " << current_authorized_user_->getLogin() << " left the chat room.\n";
					current_authorized_user_ = nullptr;
					current_registered_user_ = nullptr;
				}
			}
			break;
		case 'q':
			current_authorized_user_ = nullptr;
			atWork = false;
			break;
		default:
			std::cout << "\n Your command is unclear. Please, select an action from the list.\n";
		}
		
		if (current_authorized_user_)
		{
			showAllUsers();
			showChatMenu();
		}
	} while (atWork);
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
			showAllMessage();
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
	if (userData_.size() != 0)
	{
		bool match = false;
		for (const auto& u : userData_)
		{
			if (user.getLogin() == u.getLogin())
				match = true;
		}
		if(match == true)
			std::cout << "\n This login is already taken!\n";
		else
		{
			userData_.push_back(user);
			current_registered_user_ = &user;
		}
	}
	else
	{
		userData_.push_back(user);
		current_registered_user_ = &user;
	}
}

void Chat::authorization()
{
	if(current_registered_user_ == nullptr)
		std::cout << "\n You are not registered yet!\n";
	else
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
				if (user.signIn(login, password) == nullptr)
					continue;
				else
				{
					current_authorized_user_ = user.signIn(login, password);
					match = true;
				}
			}
			if (!match)
				std::cout << "\n Invalid login or password!" << std::endl;
			else
				std::cout << "\n Welcome to the chat room!" << std::endl;
		} while (!match);
	}
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
		Message msg(text, current_authorized_user_, recipient);
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
					Message msg(text, current_authorized_user_, recipient);
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
	if (userData_.size() == 1)
		std::cout << "\n Now in chat room " << userData_.size() << " user.\n";
	else
		std::cout << "\n Now in chat room " << userData_.size() << " users.\n";
	int number = 1;
	for (const auto& user : userData_)
	{
		if (current_authorized_user_ == &user)
			std::cout << "\n " << number << ") " << user << " <-you\n";
		else
		{
			std::cout << "\n " << number << ") " << user << "\n";
			++number;
		}
	}
}

void Chat::showAllMessage()
{
	if (publicMsgData_.size() == 0)
		std::cout << "\n There are no messages in the chat room yet!\n";
	else
	{
		for (const auto& msg : publicMsgData_)
			std::cout << "\n From: " << msg.getSender() << "\t" << msg;
	}
}

void Chat::showDialog(const std::string& recipient)
{
	if (privateMsgData_.size() == 0)
		std::cout << "\n There are no messages in this dialog yet!\n";
	else
	{
		for (const auto& msg : privateMsgData_)
		{
			if (msg.getRecipient() == recipient)
				std::cout << "\n To: " << msg.getRecipient() << "\t" << msg;
		}
	}
}