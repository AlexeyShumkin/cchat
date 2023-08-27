#pragma once
#include<iostream>
#include<string>

class User
{
public:
	User(const std::string& login, const std::string& password, const std::string& name);
	void setLogin(const std::string& login);
	const std::string& getLogin() const;
	void setPassword(const std::string& password);
	const std::string& getPassword() const;
	void setName(const std::string& name);
	const std::string& getName() const;
	void setConnection(bool connection);
	bool getConnection() const;
private:
	bool connection_ = false;
	std::string login_;
	std::string password_;
	std::string name_;
};
std::ostream& operator << (std::ostream& os, const User& user);
