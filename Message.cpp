#include"Message.h"

Message::Message(const std::string& text, const std::string& sender, const std::string& recipient) : text_(text), sender_(sender), recipient_(recipient), sendinTime_(currentTime()) {}

void Message::setText(const std::string& text) { text_ = text; }

const std::string& Message::getText() const { return text_; }

const std::string& Message::getSender() const { return sender_; }

const std::string& Message::getRecipient() const { return recipient_; }

const std::string& Message::getSendinTime() const { return sendinTime_; }

std::string Message::currentTime() 
{
    time_t t = time(nullptr);
    tm now;
    localtime_s(&now, &t);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%X %d/%m/%Y", &now);
    return buffer;
}

std::ostream& operator << (std::ostream& os, const Message& msg) { return os << "\n From: " << msg.getSender() << "\n to: " << msg.getRecipient() << "\n\n " << msg.getText() << "\n\n " << msg.getSendinTime() << std::endl; }