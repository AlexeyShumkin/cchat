#pragma once
#include"User.h"

class Message
{
public:

    Message(const std::string& text, User* sender, const std::string& recipient);
    /* Message(const std::string& text, const std::string& sender, const std::string& recipient, const std::string& sendingTime);*/
    /* ~Message();*/

    void setText(const std::string& text);
    const std::string& getText() const;
    const std::string& getSender() const;
    const std::string& getRecipient() const;
    const std::string& getSendinTime() const;

private:
    std::string text_;
    std::string sender_;
    std::string recipient_;
    std::string sendinTime_;
};

std::ostream& operator << (std::ostream& os, const Message& msg);