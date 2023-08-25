#include"Message.h"

Message::Message(const std::string& text, User* sender, const std::string& recipient) : text_(text), sender_(sender->getLogin()), recipient_(recipient)
{

}
//Message::Message(const std::string& text, const std::string& sender, const std::string& recipient, const std::string& sendingTime) : text_(text), sender_(sender), recipient_(recipient), sendinTime_(sendingTime) {}
//Message::~Message() { std::cout << this << "Message destructor has called\n"; }


void Message::setText(const std::string& text) { text_ = text; }
const std::string& Message::getText() const { return text_; }
const std::string& Message::getSender() const { return sender_; }
const std::string& Message::getRecipient() const { return recipient_; }
const std::string& Message::getSendinTime() const { return sendinTime_; }

std::ostream& operator << (std::ostream& os, const Message& msg)
{
    return os << "\n from: " << msg.getSender() << "\t" << msg.getText() << "\tposted at: " << msg.getSendinTime() << std::endl;
}