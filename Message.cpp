#include"Message.h"

Message::Message(const std::string& text, User* sender, const std::string& recipient) : text_(text), sender_(sender->getLogin()), recipient_(recipient)
{

}

void Message::setText(const std::string& text) { text_ = text; }
const std::string& Message::getText() const { return text_; }
const std::string& Message::getSender() const { return sender_; }
const std::string& Message::getRecipient() const { return recipient_; }
const std::string& Message::getSendinTime() const { return sendinTime_; }

std::ostream& operator << (std::ostream& os, const Message& msg)
{
    return os << "\n from: " << msg.getSender() << "\t\t" << msg.getText() << "\tposted at: " << msg.getSendinTime() << std::endl;
}