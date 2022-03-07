#include <iostream>
#include <string>
#include <map>

class PhoneNumberAddressBookEntry 
{ 
    std::string phoneNumber;//номер телефона

    bool CorrectInputNumber(std::string& number) { //то, что пользователю видеть не нужно?
        bool good = true;
        if (number.length() == 10) {
            for (int i = 0; i < 10 && good; i++) 
                if (number[i] < '0' || number[i] > '9')
                    good = false;
        } else good = false;
        
        return good;
    }
public:
    void setPhoneNumber(std::string& number) { 
        phoneNumber = "+7" + number;
    }

    std::string getPhoneNumber() {
        return phoneNumber;
    }

    void setCorrectInputNumber(std::string& number) { 
        CorrectInputNumber(number);
    }

    bool getCorrectInputNumber(std::string& number) {
        return CorrectInputNumber(number);
    }
};

class NameAddressBookEntry { 
private:
    std::string name;//имя контакта
public:
    void setName(std::string& contactName) { 
        name = contactName;
    }
    
    std::string getName() {
        return name;
    }
};

class Phone
{
private:
    std::map<std::string, std::string> phonebook;//адресная книга
public:
    void CorrectInputCommand(std::string& command) { 
        do {
            std::cout << ":";
            std::cin >> command;
            if (command != "add" && command != "call" && command != "sms" && command != "exit")
                std::cout << "Invalid command, please try again.\n";
        } while (command != "add" && command != "call" && command != "sms" && command != "exit");
    }

    void Add() {
            bool good;
            PhoneNumberAddressBookEntry* numberAddrBook = new PhoneNumberAddressBookEntry();
            do { 
                std::cout << "Enter phone number(10 numbers): +7";
                std::string* strNumber = new std::string;
                std::cin >> *strNumber;
                numberAddrBook->setCorrectInputNumber(*strNumber);
                good = numberAddrBook->getCorrectInputNumber(*strNumber);
                if (good) {
                    numberAddrBook->setPhoneNumber(*strNumber);
                    delete strNumber; strNumber = nullptr;
                } else {
                    std::cout << "Invalid phone number, please try again.\n";
                }
            } while (!good);

            std::cout << "Enter Contact Name: ";
            NameAddressBookEntry* contactName = new NameAddressBookEntry(); 
            std::string* strtName = new std::string; 
            std::cin >> *strtName;
            contactName->setName(*strtName);
            delete strtName; strtName = nullptr;
            phonebook.insert(std::pair<std::string, std::string>(numberAddrBook->getPhoneNumber(), contactName->getName()));
            delete numberAddrBook; numberAddrBook = nullptr;
            delete contactName; contactName = nullptr;
    }

    void Call() {
        if (phonebook.size() == 0) {
            std::cout << "Address book is empty.\n";
            return;
        } else {
            std::cout << "Enter phone number(+7: 10 numbers) or Contact name: ";
            std::string choice;
            std::cin >> choice;
            bool found = false;
            for (std::map<std::string, std::string>::iterator it = phonebook.begin(); it != phonebook.end(); ++it)
                if (it->second == choice || it->first == choice) {
                    std::cout << "CALL " << it->first << '\n';
                    found = true;
                }
            if (!found) std::cout << "No such contact." << '\n';
        }
    }
    
    void Sms() {
        if (phonebook.size() == 0) {
            std::cout << "Address book is empty.\n";
            return;
        } else {
            std::cout << "Enter phone number(+7: 10 numbers) or Contact name: ";
            std::string choice;
            std::cin >> choice;
            bool found = false;
            for (std::map<std::string, std::string>::iterator it = phonebook.begin(); it != phonebook.end(); ++it)
                if (it->second == choice || it->first == choice) {
                    std::cout << "Enter your message\n";
                    std::cout << ":";
                    std::string message;
                    std::cin >> message;
                    found = true;
                }
            if (!found) std::cout << "No such contact." << '\n';
        }
    }
};

int main () { 
    Phone* telephone = new Phone();
    std::string* command = new std::string;
    while (*command != "exit") {
        std::cout << "Choose command(add/call/sms/exit).\n";
        telephone->CorrectInputCommand(*command);
        if (*command == "add") 
            telephone->Add();
        else if (*command == "call")
            telephone->Call();
        else if (*command == "sms") 
            telephone->Sms();
    }
    delete telephone; telephone = nullptr;
    delete command; command = nullptr;    
}