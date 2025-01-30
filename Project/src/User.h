#ifndef _USER_H
#define _USER_H


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
namespace myUsers {
    class User {

    private:
        std::string name, password;
        int ID, authorisationLevel;
        bool isLogged = false;
        std::vector<int> borrowedItems; // items borrowed by id
        
    public:
        static const int MAX_QUANTITY = 100000; // max quantity of users, used for id generation
        // constructors
        User();
        User(const char* filename); // create object from file
        User(int ID, std::string name, int authorisationLevel,
            std::string password, std::vector<int> borrowedMedia = {0});

        // methods
        bool saveToFile(const char* filename, std::string fileFormat = "csv");
        bool loadFromFile(const char* filename);
        void printHeader();
        void show();
        void borrowMedia(int id);
        bool returnMedia(int id);
        // Getters 
        int getId();
        std::string getName();
        std::string getPassword();
        int getAuthorisationLevel();
        bool getStatus();
        std::vector<int> getBorrowedItems();

        // Setters
        void login();
        void logout();
        void loadBorrowedItems(std::vector<int> borrowedMedia);
    };
}
#endif