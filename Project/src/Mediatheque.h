#ifndef _MEDIATHEQUE_H
#define _MEDIATHEQUE_H

#include <vector>
#include <filesystem>
#include <sstream>
#include <iomanip>
#include "Book.h"
#include "Magazine.h"
#include "CD.h"
#include "DVD.h"
#include "VHS.h"
#include "Numeric.h"
#include "User.h"

namespace myMedia{
    class Mediatheque{
        private:
            int nombre_medias;
            myUsers::User* currentUser = new myUsers::User(00000, "Anonymous", 0, ""); // default user, used if no login attempt is made
            // defining struct that represents the database
            // for now the struct will be public, later on we'll see if it should go private
            struct Database {
                int test;
                std::string dBPath; // path to the database
                std::vector<myMedia::Media*>dbMedia; // represents the current database in RAM
                std::vector<myMedia::Media*>researchHelper; // used for manipulating the current database during research procedures
                std::vector<myUsers::User*>dbUsers;
            };
            Database currentdB;
        public:

            inline static const std::string DEFAULT_DB_PATH {".\\database"}; // https://stackoverflow.com/questions/1563897/static-constant-string-class-member

            //--- Constructors ---// 
            Mediatheque(std::string dBPath = DEFAULT_DB_PATH); // if no path is provided, the database will be saved in the cwd in a folder called database
            
            //--- Destructor ---//
            ~Mediatheque();

            //--- Methods ---//

            // Database Methods //
            void loadDatabaseFromCsv(std::string path = DEFAULT_DB_PATH);
            int init_Mediatheque(const char* path);
            void saveDatabase(bool clearDatabase = true);
            void saveDatabaseTxt(std::string pathTxt = "base_donnees.txt");
            void clearDatabase();

            // Media methods //
            void addMedia(int choice);
            bool deleteMedia(int id);
            void resetResearch();
            void listContent();
            void searchMedia(std::string str);
            void searchMediaByType(std::string str, int choice);
            void listContentByType(int choice);
            bool showInfo(int id);
            bool isMediaPresent(int id);

            // User methods //
            void addUser();
            bool deleteUser(int id);
            void listUsers();
            bool listUserMedias(int userId);
            bool borrowMedia(int mediaId, int userId);
            bool returnMedia(int mediaId, int userId);
            myUsers::User* getCurrentUser();
            Database getCurrentDatabase();
            bool login(int id, std::string password);
            void logout();

        private:
            // Media methods //
            void clearResearchHelpers();
            void printMediaHeader();
            void listResearchResults(bool isPureMedia = true);
            void updateResearchResults(std::vector<myMedia::Media*> vect);
            std::vector<myMedia::Media*>::iterator getElementById(int id); // returns index iterator of a certain element by its id 
            // User methods //
            std::vector<myUsers::User*>::iterator getUserById(int id);
    };
}

#endif