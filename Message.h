#pragma once
#include<ctime>
#include<memory>
#include"User.h"

class Message
{
public:
    Message(const std::string& text, const std::string& sender, const std::string& recipient);
    void setText(const std::string& text);
    const std::string& getText() const;
    const std::string& getSender() const;
    const std::string& getRecipient() const;
    const std::string& getSendinTime() const;
    std::string currentTime();
private:
    std::string text_;
    std::string sender_;
    std::string recipient_;
    std::string sendinTime_;
};
std::ostream& operator << (std::ostream& os, const Message& msg);