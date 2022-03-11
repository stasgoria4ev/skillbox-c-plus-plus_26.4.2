#include <iostream>
#include <string>
#include <vector>

class PhoneNumberAddressBookEntry 
{ 
    std::string phoneNumber;//номер телефона

    bool CorrectInputNumber(std::string& number) { 
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

class Contact {
private:
    PhoneNumberAddressBookEntry numberAddrBook;
    NameAddressBookEntry contactName;
public:
    void setNumberAddrBook(std::string& strNumber) { 
        numberAddrBook.setPhoneNumber(strNumber);
    }
    
    PhoneNumberAddressBookEntry getNumberAddrBook() {
        return numberAddrBook;
    }
    
    void setContactName(std::string& strNumber) { 
        contactName.setName(strNumber);
    }

    NameAddressBookEntry getContactName() {
        return contactName;
    }
};

class Phone
{
private:
    std::vector<Contact> phonebook;//адресная книга
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
            Contact* addressBookContact = new Contact(); 
            do { 
                std::cout << "Enter phone number(10 numbers): +7";
                std::string* strNumber = new std::string;
                std::cin >> *strNumber;
                good = addressBookContact->getNumberAddrBook().getCorrectInputNumber(*strNumber);
                if (good) {
                    addressBookContact->setNumberAddrBook(*strNumber);
                    delete strNumber; strNumber = nullptr;
                } else {
                    std::cout << "Invalid phone number, please try again.\n";
                }
            } while (!good);

            std::cout << "Enter Contact Name: ";
            std::string* strtName = new std::string; 
            std::cin >> *strtName;
            addressBookContact->setContactName(*strtName);
            delete strtName; strtName = nullptr;
            phonebook.push_back(*addressBookContact);//наполнение вектора
            delete addressBookContact; addressBookContact = nullptr;
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
            for (int i = 0; i < phonebook.size(); i++)
                if (phonebook[i].getNumberAddrBook().getPhoneNumber() == choice || phonebook[i].getContactName().getName() == choice) {    
                    std::cout << "CALL " << phonebook[i].getNumberAddrBook().getPhoneNumber() << '\n';
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
            for (int i = 0; i < phonebook.size(); i++)
                if (phonebook[i].getNumberAddrBook().getPhoneNumber() == choice || phonebook[i].getContactName().getName() == choice) {
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