#include"User.h"

User::User(const std::string& login, const std::string& password, const std::string& name) :login_(login), password_(password), name_(name) {}

const std::string& User::getLogin() const { return login_; }

void User::setPassword(const std::string& password) { password_ = password; }

const std::string& User::getPassword() const { return password_; }

void User::setName(const std::string& name) { name_ = name; }

const std::string& User::getName() const { return name_; }

std::ostream& operator << (std::ostream& os, const User& user) { return os << "login: " << user.getLogin() << "\tname: " << user.getName(); }