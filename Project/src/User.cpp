#include "User.h"

namespace myUsers {

    User::User(){
        // this constructor will be used when the user desires to create a new object in the database
        srand(time(NULL));
        ID = rand()%MAX_QUANTITY;
        std::cout<< "Name:" << std::endl;
        std::getline(std::cin >> std::ws, name);
/*         std::cout<< "Surname:" << std::endl;
        std::getline(std::cin >> std::ws, surname); */
        std::cout<< "Password:" << std::endl;
        std::getline(std::cin >> std::ws, password);
        std::cout<< "Authorisation Level:" << std::endl;
        std::cin>> authorisationLevel;
        if (authorisationLevel < 1){
            authorisationLevel = 1; // 0 is only for the default anonymous user
        }
    }


    User::User(const char* filename){
        bool loadSuccess = loadFromFile(filename);
        if (!loadSuccess) {
            std::cout << "Could not load object from file " << filename << std::endl;
        }
    }

    User::User(int ID, std::string name, int authorisationLevel, std::string password, std::vector<int> borrowedMedia):
    // constructor used to retrieve data from the database
    ID{ID}, name{name}, authorisationLevel{authorisationLevel}, password{password}
    {
        borrowedItems = std::vector<int>(borrowedMedia.begin() + 1, borrowedMedia.end());
    }

    int User::getId() {
        return ID;
    }

    int User::getAuthorisationLevel() {
        return authorisationLevel;
    }

    std::string User::getName() {
        return name;
    }

    std::string User::getPassword() {
        return password;
    }

    bool User::getStatus(){
        return isLogged;
    }

    std::vector<int> User::getBorrowedItems(){
        return borrowedItems;
    }

    void User::login(){
        isLogged = true;
    }

    void User::logout(){
        isLogged = false;
    }

    void User::loadBorrowedItems(std::vector<int> borrowedMedia){
        borrowedItems = std::vector<int>(borrowedMedia.begin() + 1, borrowedMedia.end()); // copying content  
    }

    void User::borrowMedia(int id){
        borrowedItems.push_back(id);
    }

    bool User::returnMedia(int id){
        auto idxIdToReturn = borrowedItems.end() + 1; // starts at -1 so that if the element is not found we can identify it by checking that idxIdToReturn == -1
        auto idxAux = borrowedItems.begin();
        // looping through the specified user borrowed items vector
        for (auto & element : borrowedItems){
            // if media was found in the borrowed items vector
            if(element == id){
                // retrieve the corresponding index
                idxIdToReturn = idxAux;
            }
            idxAux++;
        }
        // if id was found
        if (idxIdToReturn > borrowedItems.end()){
            return false;
        }   
        else{
            borrowedItems.erase(idxIdToReturn);
        }
        return true;
    }

    void User::printHeader(){
        std::cout<< std::left
        << std::setw(10) << "ID"
        << std::setw(25) << "NAME"
        << std::setw(10) << "AUTH LVL."
        << std::endl;
    }

    void User::show(){
        std::cout<< std::left
        << std::setw(10) << ID 
        << std::setw(25) << name
        << std::setw(10) << authorisationLevel 
        << std::endl;
    }

    bool User::saveToFile(const char* filename, std::string fileFormat) {
        std::cout << "Saving User to file " << filename << std::endl;
        std::ofstream outfile;
        std::string separator;

        if(fileFormat == "csv"){
            separator = ";";
            outfile.open(filename, std::ios::app);
        }
        else{
            separator = "\n";
            outfile.open(filename, std::ios::app);
        }

        if (outfile.is_open()) {
            outfile << ID << separator;
            outfile << name << separator;
            outfile << authorisationLevel << separator;
            if(borrowedItems.empty()){ 
                outfile << password << std::endl;
            }
            else{
                outfile << password << separator;
                for(auto & element : borrowedItems){
                    // saving borrowed items
                    if (element == borrowedItems.back()){
                        separator = "\n";
                    }
                    outfile<< element << separator;
                }
            }

            outfile.close();
            return true;
        }
        else {
            return false;
        }
    }

    bool User::loadFromFile(const char* filename) {
        std::cout << "Loading User ressource from file " << filename << std::endl;

        std::ifstream infile;
        infile.open(filename);
        std::string auxStr;

        if (!infile.is_open()) {
            return false;
        }
        getline(infile, auxStr);
        ID = stoi(auxStr);
        getline(infile, name);
        getline(infile, auxStr);
        authorisationLevel = stoi(auxStr);
        getline(infile, password);
        infile.close();
        return true;
    }
}