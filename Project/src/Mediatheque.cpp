#include "Mediatheque.h"

// TODO implement methods already implemented on main.cpp inside the mediatek class
// the class will assume the path of the database as being .\database, we can change
// it via a setter if we want to and we can load the database from a random
// database folder which is not necessarily the database where the context 
// will be loaded to.
namespace myMedia{
    Mediatheque::Mediatheque(std::string dBPath)
    {
        currentdB.dBPath = dBPath;
        loadDatabaseFromCsv(currentdB.dBPath); // loading data from provided path
        //init_Mediatheque(dBPath.c_str());
        resetResearch(); // reseting the research during initialization
    }

    Mediatheque::~Mediatheque(){
        // deleting all allocated vector of pointers
        for (auto & element : currentdB.dbMedia) {
           delete element; 
        }
        for (auto & element : currentdB.researchHelper) {
           delete element; 
        }
        for (auto & element : currentdB.dbUsers) {
           delete element; 
        }
        delete currentUser;
    }


    //--- DATABASE METHODS ---//

    void Mediatheque::loadDatabaseFromCsv(std::string path){
        /* 
        The path argument is the path to the database 
        We iterate over the csv files inside the database folder
        Sources:
            https://en.cppreference.com/w/cpp/filesystem
            https://stackoverflow.com/questions/67273/how-do-you-iterate-through-every-file-directory-recursively-in-standard-c
        */
        
        std::string line, word, auxStr;
        std::vector<std::string> row;
        std::ifstream infile;
        currentdB.dbMedia.clear(); // clear database at new load
        currentdB.dbUsers.clear(); // clear
        // creating the necessary database folder if it doesn't already exist
        if (!std::filesystem::is_directory(path) || !std::filesystem::exists(path)) { // Check if src folder exists
            std::filesystem::create_directory(path); // create database folder
        }
        // recursively looping over database directory
        for (auto& dirEntry: std::filesystem::recursive_directory_iterator(path)) {
            if (!dirEntry.is_regular_file()) {
                //std::cout << "Directory: " << dirEntry.path() << std::endl;
                continue;
                }
            std::filesystem::path file = dirEntry.path();
            //std::cout << "Filename: " << file.filename() << " absolute path" << std::filesystem::absolute(file).string() << " extension: " << file.extension() << "relative path "<< file.relative_path() << "root directory: "<< file.root_path() << std::endl;
            std::string teste = file.root_directory().string();
            std::string currentFileStr = std::filesystem::absolute(file).string();
            //std::string currentFileStr = std::filesystem::absolute(file).string()
            const char* currentFile = currentFileStr.c_str();
            auto filenametest = file.filename();
            infile.open(currentFile);
            if(infile.is_open())
            {   
                // parsing current .csv file
                while(getline(infile, line))
                {   
                    row.clear(); // clearing row vector
                    std::stringstream str(line);
        
                    while(getline(str, word, ';')){
                        // parsing rows from line
                        row.push_back(word);
                        //std::cout<<word << std::endl;
                    }
                    // parsing rows into objects
                    int id = stoi(row[0]); // id and quantity always on the same spot, they are from the Media class
                    int quantity = stoi(row[5]);
                    if(file.filename() == "Book.csv"){
                        int pagesNumber = stoi(row[9]);
                        currentdB.dbMedia.push_back(new myMedia::Book(id, row[2],row[3],row[4], quantity,row[6],row[7],row[8],pagesNumber,row[10]));
                    }

                    else if(file.filename() == "CD.csv"){
                        int duration  = stoi(row[7]);
                        int tracksNumber = stoi(row[8]); 
                        currentdB.dbMedia.push_back(new myMedia::CD(id, row[2], row[3], row[4], quantity, row[6], duration, tracksNumber));
                    }

                    else if(file.filename() == "DVD.csv"){
                        int duration = stoi(row[7]);
                        int chaptersNumber = stoi(row[8]);
                        currentdB.dbMedia.push_back(new myMedia::DVD(id, row[2], row[3], row[4], quantity, row[6], duration, chaptersNumber));
                    }

                    else if(file.filename() == "Magazine.csv"){
                        int pagesNumber = stoi(row[9]);
                        int articlesNumber = stoi(row[10]);
                        currentdB.dbMedia.push_back(new myMedia::Magazine(id, row[2], row[3], row[4], quantity, row[6], row[7], row[8], pagesNumber, articlesNumber));
                    }

                    else if(file.filename() == "Num.csv"){
                        int sizeMb = stoi(row[8]);
                        currentdB.dbMedia.push_back(new myMedia::Numeric(id, row[2], row[3], row[4], quantity, row[6], row[7], sizeMb));
                    }

                    else if(file.filename() == "VHS.csv"){
                        int duration = stoi(row[7]);
                        int colored = stoi(row[8]);
                        currentdB.dbMedia.push_back(new myMedia::VHS(id, row[2], row[3], row[4], quantity, row[6], duration, colored));
                    }

                    else if(file.filename() == "Users.csv"){
                        int authorizationLevel = stoi(row[2]);
                        std::vector<int> borrowedItems = {0};
                        // loading borrowed ids through vector slicing
                        if (row.size() > 4){
                            // if there is a list of borrowed medias
                            for (auto it = row.begin() + 4 ; it != row.end(); ++it){
                                borrowedItems.push_back(stoi(*it));
                            }
                            //currentdB.dbUsers.push_back(new myUsers::User(id, row[1], authorizationLevel, row[3], borrowedItems));
                        }
                        currentdB.dbUsers.push_back(new myUsers::User(id, row[1], authorizationLevel, row[3], borrowedItems));
                    }

                }
                infile.close(); // closing file
            }


        else
            std::cout<<"Could not open the file\n";
        }

        // if after the user file has been parsed, the user vector is empty, 
        // it means that the users database has no user, meaning it's the first time the program is executed
        // we then ask the user to create the first system administrator
        if (currentdB.dbUsers.empty()){
            int id{0};
            srand(time(NULL));
            id = rand()%(myUsers::User::MAX_QUANTITY);
            int authorizationLevel = 3;
            std::string name, password;
            std::cout<< "This is the first execution of this mediatheque, please enter the credentials of the first administrator."<< std::endl;
            std::cout<< "Name" << std::endl;
            std::getline(std::cin >> std::ws, name);
            std::cout<< "Password" << std::endl;
            std::getline(std::cin >> std::ws, password);
            currentdB.dbUsers.push_back(new myUsers::User(id, name, authorizationLevel, password));
            std::cout<< "Your manager id is "<< id << std::endl;
            // after this, in the command line interface, the user will login with the credentials they provided, if he doesn't login, 
            // the default anonymous user will be used, it has only the right to list and search for content but he can't borrow books nor add or delete medias 

        }

    }

    int Mediatheque::init_Mediatheque(const char* path) {
        /* ========================= */
        /* === Variables locales === */
        /* ========================= */
        FILE* file;
        std::string Title;
        std::string Author;
        std::string Date;
        std::string Editor;
        std::string Collection;
        std::string Format;
        std::string URL;
        std::string HouseProduction;
        std::string Summary;
        std::string Type;
        std::string TypeDoc;

        int pagesNumber;
        int articlesNumber;
        int tracksNumber;
        int chaptersNumber;
        int quantity;
        int duration;
        int nombreMedias;
        int size;
        int ID;
        int color_track;

        bool color;
       
        currentdB.dbMedia.clear(); // clear database at new load
        
        std::ifstream infile;
        infile.open(path);
        std::string auxStr;

        if (!infile.is_open()) {
            return 0;
        }
        getline(infile, auxStr,'\n');
        Mediatheque::nombre_medias = stoi(auxStr);
        for (int i = 0; i < Mediatheque::nombre_medias; i++) {
            getline(infile, auxStr, '\n');
            ID = stoi(auxStr);
            getline(infile, Type);
            getline(infile, Title);
            getline(infile, Author);
            getline(infile, Date);
            getline(infile, auxStr, '\n');
            quantity = stoi(auxStr);

            if (Type == "Book") {
                getline(infile, Summary);
                getline(infile, Collection);
                getline(infile, Editor);
                getline(infile, auxStr, '\n');
                pagesNumber = stoi(auxStr);
                getline(infile, Format);
                
                currentdB.dbMedia.push_back(new myMedia::Book(ID, Title, Author,
                    Date, quantity,
                    Summary, Collection, Editor, pagesNumber, Format));
            }
            else if (Type == "Magazine") {
                getline(infile, Summary);
                getline(infile, Collection);
                getline(infile, Editor);
                getline(infile, auxStr, '\n');
                pagesNumber = stoi(auxStr);
                getline(infile, auxStr, '\n');
                articlesNumber = stoi(auxStr);
                currentdB.dbMedia.push_back(new myMedia::Magazine(ID, Title, Author,
                    Date, quantity,
                    Summary, Collection, Editor, pagesNumber, articlesNumber));
            }
            else if (Type == "Numeric") {
                getline(infile, TypeDoc);
                getline(infile, URL);
                getline(infile, auxStr, '\n');
                size = stoi(auxStr);
                currentdB.dbMedia.push_back(new myMedia::Numeric(ID, Title, Author,
                    Date, quantity,
                    TypeDoc, URL, size));
            }
            else if (Type == "CD") {
                getline(infile, HouseProduction);
                getline(infile, auxStr, '\n');
                duration = stoi(auxStr);
                getline(infile, auxStr, '\n');
                tracksNumber = stoi(auxStr);
                currentdB.dbMedia.push_back(new myMedia::CD(ID, Title, Author,
                    Date, quantity,
                    HouseProduction, duration, tracksNumber));
            }
            else if (Type == "DVD") {
                getline(infile, HouseProduction);
                getline(infile, auxStr, '\n');
                duration = stoi(auxStr);
                getline(infile, auxStr, '\n');
                chaptersNumber = stoi(auxStr);
                currentdB.dbMedia.push_back(new myMedia::CD(ID, Title, Author,
                    Date, quantity,
                    HouseProduction, duration, chaptersNumber));
            }
            else if (Type == "VHS") {
                getline(infile, HouseProduction);
                getline(infile, auxStr, '\n');
                duration = stoi(auxStr);
                getline(infile, auxStr, '\n');
                color_track = stoi(auxStr);
                if (color_track == 1) {
                    color = true;
                }
                else if (color_track == 0) {
                    color = false;
                }
                currentdB.dbMedia.push_back(new myMedia::CD(ID, Title, Author,
                    Date, quantity,
                    HouseProduction, duration, color));
            }
            }
        infile.close();
        return 1;
    }



    void Mediatheque::saveDatabase(bool clearDatabase){
        // erasing previous content from the database and if these files didn't previously existed, create them
        std::string dBDestinationPath;
        if (clearDatabase){
            std::ofstream ofs;
            dBDestinationPath = currentdB.dBPath + "\\Book.csv";
            ofs.open(dBDestinationPath.c_str(), std::ofstream::out | std::ofstream::trunc);
            ofs.close();

            dBDestinationPath = currentdB.dBPath + "\\CD.csv";
            ofs.open(dBDestinationPath.c_str(), std::ofstream::out | std::ofstream::trunc);
            ofs.close();

            dBDestinationPath = currentdB.dBPath + "\\DVD.csv";
            ofs.open(dBDestinationPath.c_str(), std::ofstream::out | std::ofstream::trunc);
            ofs.close();

            dBDestinationPath = currentdB.dBPath + "\\Magazine.csv";
            ofs.open(dBDestinationPath.c_str(), std::ofstream::out | std::ofstream::trunc);
            ofs.close();

            dBDestinationPath = currentdB.dBPath + "\\Num.csv";
            ofs.open(dBDestinationPath.c_str(), std::ofstream::out | std::ofstream::trunc);
            ofs.close();

            dBDestinationPath = currentdB.dBPath + "\\VHS.csv";
            ofs.open(dBDestinationPath.c_str(), std::ofstream::out | std::ofstream::trunc);
            ofs.close();

            dBDestinationPath = currentdB.dBPath + "\\Users.csv";
            ofs.open(dBDestinationPath.c_str(), std::ofstream::out | std::ofstream::trunc);
            ofs.close();
        }

        
        // saving all members of the database structure to the database files
        for (auto & element : currentdB.dbMedia) {
            if(element->getType() == "Book"){
                dBDestinationPath = currentdB.dBPath + "\\Book.csv";
            }
            else if(element->getType() == "CD"){
                dBDestinationPath = currentdB.dBPath + "\\CD.csv";
            }
            else if(element->getType() == "DVD"){
                dBDestinationPath = currentdB.dBPath + "\\DVD.csv";
            }
            else if(element->getType() == "Magazine"){
                dBDestinationPath = currentdB.dBPath + "\\Magazine.csv";
            }                         
            else if(element->getType() == "Num"){
                dBDestinationPath = currentdB.dBPath + "\\Num.csv";
            }        
            else if(element->getType() == "VHS"){
                dBDestinationPath = currentdB.dBPath + "\\VHS.csv";
            }
            element->saveToFile(dBDestinationPath.c_str()); 
        }
        
        // saving all users to the database
        dBDestinationPath = currentdB.dBPath + "\\Users.csv";
        for(auto & element : currentdB.dbUsers){
            element->saveToFile(dBDestinationPath.c_str()); 
        }    
    }

    void Mediatheque::saveDatabaseTxt(std::string pathTxt){
        std::string filename(pathTxt);
        std::fstream file_out;

        file_out.open(filename, std::ios_base::out);
        file_out << size(currentdB.dbMedia) << std::endl;
        file_out.close();
        for (auto& element : currentdB.dbMedia) {
            element->saveToFile(filename.c_str(), "txt");
        }

        std::cout << "Done saving!" << std::endl;
    }

    myMedia::Mediatheque::Database Mediatheque::getCurrentDatabase(){
        return currentdB;
    }

    void Mediatheque::clearDatabase(){
        // this method clears the database
        currentdB.dbMedia.clear();
    }

    //--- USER CLASS METHODS ---//

    bool Mediatheque::borrowMedia(int mediaId, int userId){
        // this method borrows a media from the Mediatheque
        auto idxMedia = getElementById(mediaId);
        auto idxUser = getUserById(userId);
        // if mediaId exists in media database
        if (idxMedia <= currentdB.dbMedia.end()){
            // if user exists in users database
            if(idxUser <= currentdB.dbUsers.end()){
                auto intIdxMedia = std::distance(currentdB.dbMedia.begin(), idxMedia);
                auto intIdxUser = std::distance(currentdB.dbUsers.begin(), idxUser);
                // if there are resources available
                if(currentdB.dbMedia.at(intIdxMedia)->getQuantity() > 0){
                    currentdB.dbMedia.at(intIdxMedia)->borrowMedia();
                    currentdB.dbUsers.at(intIdxUser)->borrowMedia(mediaId);
                    return true;
                }
            }
        }
        return false;
    }

    bool Mediatheque::returnMedia(int mediaId, int userId){
        // this method returns a media to the database, it increases the available quantity of a certain item and erases the id from the brrowed
        // items list of the provided user 
        auto idxMedia = getElementById(mediaId);
        auto idxUser = getUserById(userId);
        // if mediaId exists in media database
        if (idxMedia <= currentdB.dbMedia.end()){
            // if user exists in users database
            if(idxUser <= currentdB.dbUsers.end()){
                auto intIdxMedia = std::distance(currentdB.dbMedia.begin(), idxMedia);
                auto intIdxUser = std::distance(currentdB.dbUsers.begin(), idxUser);
                // if deleting a media from the specified user and media was successful
                if (currentdB.dbUsers.at(intIdxUser)->returnMedia(mediaId) && currentdB.dbMedia.at(intIdxMedia)->returnMedia()){
                    return true;
                }
            }
        }
        return false;
    }

    void Mediatheque::addUser(){
        currentdB.dbUsers.push_back(new myUsers::User());
    }

    bool Mediatheque::deleteUser(int id){
        // deletes Media according to the id passed as argument
/*         auto idToDelete = currentdB.dbMedia.begin();
        auto idx = currentdB.dbMedia.begin();
        for (auto & element : currentdB.dbMedia) {
            if(element->getId() == id){
                idToDelete = idx;
            }
            idx++;
        }   */
        auto idToDelete = getUserById(id);
        if (idToDelete>currentdB.dbUsers.end()){
            return false;
        }   
        else{
            // deleting Media by id
            if(id != currentUser->getId()){
                currentdB.dbUsers.erase(idToDelete);
            }
            else{
                // a sys manager can't delete itself
                return false;
            }
            
            return true;
        }

    }

    void Mediatheque::listUsers(){
        // this method simply list all content by the commun attributes of the Media base class //
        int idx = 0;
        //printMediaHeader();
        for (auto & element : currentdB.dbUsers) {
            //element->show();
            if(idx == 0){
                    element->printHeader();
            }
            element->show(); // specifically calls the Media class show method
            //std::cout<< std::left << std::setw(10) << "test" << std::endl;
            idx++;
        }
    }

    bool Mediatheque::listUserMedias(int userId){
        int idx{0};
        auto idxUser = getUserById(userId);
        //auto intIdxUser = std::distance(currentdB.dbUsers.begin(), idxUser);
        if (idxUser<=currentdB.dbUsers.end()){
            int intIdxUser = std::distance(currentdB.dbUsers.begin(), idxUser);
            auto borrowedMedias = currentdB.dbUsers.at(intIdxUser)->getBorrowedItems();
            for (auto& element : borrowedMedias){
                // shwoing info of a given id
                showInfo(element);
            }
            return true;
        }   
        return false;    
    }

    std::vector<myUsers::User*>::iterator Mediatheque::getUserById(int id){
        // returns the index corresponding to a certain database element by its id
        // if the element is not found it will return an index greater than the max index of the vector
        auto idxToDelete = currentdB.dbUsers.end() + 1; // we do this to know weather we found the element or not
        auto idx = currentdB.dbUsers.begin();
        for (auto & element : currentdB.dbUsers) {
            if(element->getId() == id){
                idxToDelete = idx;
            }
            idx++;
        }
        return idxToDelete; 
    }

    bool Mediatheque::login(int id, std::string password){
        // searching if user is present in the database by id
        auto idxUser = std::distance(currentdB.dbUsers.begin(), getUserById(id)); // converting iterator to int
        if (idxUser>std::distance(currentdB.dbUsers.begin(), currentdB.dbUsers.end())){
            return false;
        }   
        else{
            // if id is present, test provided password
            if(password == currentdB.dbUsers.at(idxUser)->getPassword()){
                currentUser = currentdB.dbUsers.at(idxUser); // updates the current user
                currentUser->login();
                return true;
            }
            return false; // if credentials don't match
        }
    }

    void Mediatheque::logout(){
        currentUser->logout();
    }

    myUsers::User* Mediatheque::getCurrentUser(){
        return currentUser;
    }

    //--- MEDIA CLASS METHODS ---//

    void Mediatheque::addMedia(int choice){
        // this method adds a ressource to the current database
        switch(choice){
            case(1):
                currentdB.dbMedia.push_back(new myMedia::Book());
                break;
            case(2):
                currentdB.dbMedia.push_back(new myMedia::CD());
                break;
            case(3):
                currentdB.dbMedia.push_back(new myMedia::DVD());
                break;
            case(4):
                currentdB.dbMedia.push_back(new myMedia::Magazine());
                break;
            case(5):
                currentdB.dbMedia.push_back(new myMedia::Numeric());
                break;
            case(6):
                currentdB.dbMedia.push_back(new myMedia::VHS());
                break;
        }
    }

    bool Mediatheque::deleteMedia(int id){
        // deletes Media according to the id passed as argument
/*         auto idToDelete = currentdB.dbMedia.begin();
        auto idx = currentdB.dbMedia.begin();
        for (auto & element : currentdB.dbMedia) {
            if(element->getId() == id){
                idToDelete = idx;
            }
            idx++;
        }   */
        auto idToDelete = getElementById(id);
        if (idToDelete>currentdB.dbMedia.end()){
            return false;
        }   
        else{
            // deleting Media by id
            currentdB.dbMedia.erase(idToDelete);
            return true;
        }

    }

    std::vector<myMedia::Media*>::iterator Mediatheque::getElementById(int id){
        // returns the index corresponding to a certain database element by its id
        // if the element is not found it will return an index greater than the max index of the vector
        auto idxToDelete = currentdB.dbMedia.end() + 1; // we do this to know weather we found the element or not
        auto idx = currentdB.dbMedia.begin();
        for (auto & element : currentdB.dbMedia) {
            if(element->getId() == id){
                idxToDelete = idx;
                break;
            }
            idx++;
        }
        return idxToDelete;
    }

    bool Mediatheque::isMediaPresent(int id){
        if (getElementById(id) < currentdB.dbMedia.end()){
            return true;
        }
        return false;
    }

    bool Mediatheque::showInfo(int id){
        // shows detailed info about an item by its id, returns false if the item was not found
        auto idxToShow = std::distance(currentdB.dbMedia.begin(), getElementById(id)); // converting iterator to int
        if (idxToShow>std::distance(currentdB.dbMedia.begin(), currentdB.dbMedia.end())){
            return false;
        }   
        else{
            // showing Media by id
            currentdB.dbMedia.at(idxToShow)->printHeader();
            currentdB.dbMedia.at(idxToShow)->show();
            return true;
        }
    }


    void Mediatheque::resetResearch(){
        // this method resets the reserach vector, loading the contents of the current database to the research helper
        clearResearchHelpers();
        for (auto & element : currentdB.dbMedia) {
           currentdB.researchHelper.push_back(element->clone()); // we have to dereference element because it is a pointer, and we really just want to make a copy of the content
                                                             // if we pushed back the pointer, every change done to the reserach helper would impact on the objects of currentdB
                                                             // if the research helpers were to be allocated dinamically as weel, we would build them via a copy constructor
        }
    }

    void Mediatheque::updateResearchResults(std::vector<myMedia::Media*> vect){
        // puts the content of an aux vect inside de research results
        clearResearchHelpers();
        for (auto & element : vect) {
           currentdB.researchHelper.push_back(element->clone()); 
        }
    }

    void Mediatheque::clearResearchHelpers(){
        // erasing elements from research helpers
        currentdB.researchHelper.clear();
    }


    void Mediatheque::listContent(){
        // this method simply list all content by the commun attributes of the Media base class //
        int idx = 0;
        //printMediaHeader();
        for (auto & element : currentdB.dbMedia) {
            //element->show();
            if(idx == 0){
                    element->Media::printHeader();
            }
            element->Media::show(); // specifically calls the Media class show method
            //std::cout<< std::left << std::setw(10) << "test" << std::endl;
            idx++;
        }
    }
    
    void Mediatheque::listContentByType(int choice){
        // this method print the database content according to the given type
        std::string category;
        
        switch(choice){
            case(1):
                category = "Book";
                break;
            case(2):
                category = "CD";
                break;
            case(3):
                category = "DVD";
                break;
            case(4):
                category = "Magazine";
                break;
            case(5):
                category = "Num";
                break;
            case(6):
                category = "VHS";
                break;
        }
        // printing all elements from chosen category
        int idx = 0;
        for(auto & element : currentdB.dbMedia){
            if(element->getType() == category){
                if (idx == 0){
                    element->printHeader();
                }
                element->show();
            idx++;
            } 
        }
    }

    void Mediatheque::listResearchResults(bool isPureMedia){
        // this method simply list all content by the commun attributes of the Media base class //
        
        int idx = 0;
        //printMediaHeader();

        //isPureMedia = (true)?printMediaHeader:
        for(auto & element : currentdB.researchHelper){
            if (isPureMedia){
                if(idx == 0){
                    element->Media::printHeader();
                }
                element->Media::show(); // if category is a pure media, we generally set this for the general research
            }
            else{
                if(idx == 0){
                    element->printHeader();
                }
                element->show();
            }
            idx ++;
            
        }
    }

    void Mediatheque::printMediaHeader(){
        // this method print the header of a media type table
        std::cout<< std::left<< std::setw(10) << "ID"
        << std::setw(30) << "TITLE"
        << std::setw(20) << "AUTHOR"
        << std::setw(15) << "DATE"
        << std::setw(10)  << "ITEMS" << std::endl;
    }


    void Mediatheque::searchMedia(std::string str){
        // matches not exact correspondance in terms of cases
        std::vector<myMedia::Media*>aux;
        for (auto & element : currentdB.researchHelper) {
            if(element->Media::searchStr(str)){
               // std::cout<< "found " << str <<" in " << element->getId() << " - " << element->getTitle() << std::endl; 
                aux.push_back(element->clone());
                //aux.push_back(element); vectors linked by storing the same addr, if in the clone method we return this we return the same addr
            }
/*             else{
                std::cout<< str << " not found in " << element->getId() << " - " << element->getTitle() << std::endl;
            } */
        }
        updateResearchResults(aux);
        listResearchResults();
    }

    void Mediatheque::searchMediaByType(std::string str, int choice){
        // TODO: PRINT ALL ITEMS FROM A CERTAIN TYPE WHEN THIS OPTION IS CHOSEN
        // this method searches a string by the chosen category
        std::string category;
        std::vector<myMedia::Media*>aux;

        switch(choice){
            case(1):
                category = "Book";
                break;
            case(2):
                category = "CD";
                break;
            case(3):
                category = "DVD";
                break;
            case(4):
                category = "Magazine";
                break;
            case(5):
                category = "Num";
                break;
            case(6):
                category = "VHS";
                break;
        }
        // actual search
        for (auto & element : currentdB.researchHelper){
            if(element->getType() == category){
                if (element->searchStr(str)){
                    aux.push_back(element->clone());
                }
            }

        }
        
        updateResearchResults(aux);
        listResearchResults(false);
    }

}