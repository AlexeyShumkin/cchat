#include"User.h"

User::User(const std::string& login, const std::string& password, const std::string& name) :login_(login), password_(password), name_(name) {}
void User::setLogin(const std::string& login) { login_ = login; }
const std::string& User::getLogin() const { return login_; }
void User::setPassword(const std::string& password) { password_ = password; }
const std::string& User::getPassword() const { return password_; }
void User::setName(const std::string& name) { name_ = name; }
const std::string& User::getName() const { return name_; }
bool User::getConnection() const { return connection_; }

User* User::signIn(const std::string& login, const std::string& password)
{
    if (login != login_ || password != password_)
        return nullptr;
    else
    {
        connection_ = true;
        return this;
    }
}

std::ostream& operator << (std::ostream& os, const User& user)
{
    return os << "login: " << user.getLogin() << "\tname: " << user.getName() << std::endl;
}