#include "Mediatheque.h"

std::vector<myMedia::Media*> database;
//https://stackoverflow.com/questions/45401822/how-to-convert-filesystem-path-to-string
//https://stackoverflow.com/questions/67273/how-do-you-iterate-through-every-file-directory-recursively-in-standard-c
/* void loadDatabase(std::string path){
    for (auto& dirEntry: std::filesystem::recursive_directory_iterator(path)) {
        if (!dirEntry.is_regular_file()) {
            //std::cout << "Directory: " << dirEntry.path() << std::endl;
            continue;
        }
        std::filesystem::path file = dirEntry.path();
        std::cout << "Filename: " << file.filename() << " extension: " << file.extension() << "relative path "<< file.relative_path() << "root directory: "<< file.root_path() << std::endl;
        std::string currentFileStr = file.relative_path().string();
        const char* currentFile = currentFileStr.c_str();
        if (file.parent_path() == ".\\database\\Books"){
            std::cout<<"Book"<< std::endl;
            database.push_back(new myMedia::Book(currentFile));

        }
        else if(file.parent_path() == ".\\database\\CD"){
            std::cout<<"CD"<< std::endl;
            database.push_back(new myMedia::CD(currentFile));
        }
        else if(file.parent_path() == ".\\database\\DVD"){
            std::cout<<"DVD"<< std::endl;
            database.push_back(new myMedia::DVD(currentFile));
        }
        else if(file.parent_path() == ".\\database\\Magazines"){
            std::cout<<"Magazine"<< std::endl;
            database.push_back(new myMedia::Magazine(currentFile));
        }
        else if(file.parent_path() == ".\\database\\Numeric"){
            std::cout<<"Numeric"<< std::endl;
            database.push_back(new myMedia::Numeric(currentFile));
        }
        else if(file.parent_path() == ".\\database\\VHS"){
            std::cout<<"VHS"<< std::endl;
            database.push_back(new myMedia::VHS(currentFile));
        }
    }
    
    } */
// defining structure that will represent the databse as a whole
/*
struct Database{
    std::vector<myMedia::Book*> databaseBook;
    std::vector<myMedia::CD*> databaseCD;
    std::vector<myMedia::DVD*> databaseDVD;
    std::vector<myMedia::Magazine*> databaseMagazine;
    std::vector<myMedia::Numeric*> databaseNumeric;
    std::vector<myMedia::VHS*> databaseVHS;
};
Database myDatabase;

void loadDatabaseFromCsv(std::string path){
    
    The path argument is the path to the database 
    
    Sources:
        https://en.cppreference.com/w/cpp/filesystem
        https://stackoverflow.com/questions/67273/how-do-you-iterate-through-every-file-directory-recursively-in-standard-c

    std::string line, word, auxStr;
	std::vector<std::string> row;
	std::ifstream infile;
    // creating all necessary database folders if they don't already exist
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
        std::cout << "Filename: " << file.filename() << " extension: " << file.extension() << "relative path "<< file.relative_path() << "root directory: "<< file.root_path() << std::endl;
        std::string currentFileStr = file.relative_path().string();
        const char* currentFile = currentFileStr.c_str();
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
                    myDatabase.databaseBook.push_back(new myMedia::Book(id, row[2],row[3],row[4], quantity,row[6],row[7],row[8],pagesNumber,row[10]));
                }

                else if(file.filename() == "CD.csv"){
                    int duration  = stoi(row[7]);
                    int tracksNumber = stoi(row[8]); 
                    myDatabase.databaseCD.push_back(new myMedia::CD(id, row[2], row[3], row[4], quantity, row[6], duration, tracksNumber));
                }

                else if(file.filename() == "DVD.csv"){
                    int duration = stoi(row[7]);
                    int chaptersNumber = stoi(row[8]);
                    myDatabase.databaseDVD.push_back(new myMedia::DVD(id, row[2], row[3], row[4], quantity, row[6], duration, chaptersNumber));
                }

                else if(file.filename() == "Magazine.csv"){
                    int pagesNumber = stoi(row[9]);
                    int articlesNumber = stoi(row[10]);
                    myDatabase.databaseMagazine.push_back(new myMedia::Magazine(id, row[2], row[3], row[4], quantity, row[6], row[7], row[8], pagesNumber, articlesNumber));
                }

                else if(file.filename() == "Num.csv"){
                    int sizeMb = stoi(row[8]);
                    myDatabase.databaseNumeric.push_back(new myMedia::Numeric(id, row[2], row[3], row[4], quantity, row[6], row[7], sizeMb));
                }

                else if(file.filename() == "VHS.csv"){
                    int duration = stoi(row[7]);
                    int colored = stoi(row[8]);
                    myDatabase.databaseVHS.push_back(new myMedia::VHS(id, row[2], row[3], row[4], quantity, row[6], duration, colored));
                }

            }
            infile.close(); // closing file
        }
        

    else
		std::cout<<"Could not open the file\n";
    }
}

void saveDatabase(struct Database database, bool clearDatabase = true){
    // erasing previous content from the database
    if (clearDatabase){
        std::ofstream ofs;
        ofs.open(".\\database\\Book.csv", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
        ofs.open(".\\database\\CD.csv", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
        ofs.open(".\\database\\DVD.csv", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
        ofs.open(".\\database\\Magazine.csv", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
        ofs.open(".\\database\\Num.csv", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
        ofs.open(".\\database\\VHS.csv", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
    }

    
    // saving all members of the database structure to the database files
    for (auto & element : database.databaseBook) {
        element->saveToFile(".\\database\\Book.csv"); // when inside the mediatheque class, 
                                                      // the .\\database will be a variable called database path
    }
    for (auto & element : database.databaseCD) {
        element->saveToFile(".\\database\\CD.csv");
    }
    for (auto & element : database.databaseDVD) {
        element->saveToFile(".\\database\\DVD.csv");
    }
    for (auto & element : database.databaseMagazine) {
        element->saveToFile(".\\database\\Magazine.csv");
    }
    for (auto & element : database.databaseNumeric) {
        element->saveToFile(".\\database\\Num.csv");
    }
    for (auto & element : database.databaseVHS) {
        element->saveToFile(".\\database\\VHS.csv");
    }
}
*/
int main(){
    
   // myMedia::Media *pureMedia = new myMedia::Media("OSS", "John Doe", "18/06/2001", 3);

   // std::cout<<pureMedia->getAuthor() <<std::endl;

/*    myMedia::PaperMedia *purePaperMedia = new myMedia::PaperMedia("OSS", "John Doe",
                                                                  "18/06/2001", 3, "summary",
                                                                  "collection", "editor", 30); */

   // std::cout<<purePaperMedia->getTitle() <<std::endl;
   // purePaperMedia->setAttributes(); 

/*     myMedia::Book *myBook = new myMedia::Book("OSS", "John Doe",
                                              "18/06/2001", 3,
                                              "summary", "collection", 
                                              "editor", 30, "pocket");
    std::cout<< myBook->getAuthor() << std::endl;
    std::cout<< myBook->getFormat() << std::endl;
    myBook->setAttributes();
    std::cout<< myBook->getAuthor() << std::endl;
    std::cout<< myBook->getFormat() << std::endl; */

/*     myMedia::Magazine *myMagazine = new myMedia::Magazine("OSS", "John Doe",
                                              "18/06/2001", 3,
                                              "summary", "collection", 
                                              "editor", 30, 3);
    std::cout<< myMagazine->getAuthor() << std::endl;
    std::cout<< myMagazine->getArticlesNumber() << std::endl;
    myMagazine->setAttributes();
    std::cout<< myMagazine->getAuthor() << std::endl;
    std::cout<< myMagazine->getArticlesNumber() << std::endl; */
    
/*     myMedia::CD *myCD = new myMedia::CD("OSS", "John Doe", "18/06/2001", 5, "MyHouse", 300, 20); 
    
   
    std::cout<< myCD->getAuthor() << std::endl;
    std::cout<< myCD->getHouseProduction() << std::endl;
    std::cout<< myCD->getTracksNumber() << std::endl;
    myCD->setAttributes();
    std::cout<< myCD->getTracksNumber() << std::endl; */

/*     myMedia::DVD *myDVD = new myMedia::DVD("OSS", "John Doe", "18/06/2001", 5, "MyHouse", 300, 15); 
    
   
    std::cout<< myDVD->getAuthor() << std::endl;
    std::cout<< myDVD->getHouseProduction() << std::endl;
    std::cout<< myDVD->getChaptersNumber() << std::endl;
    myDVD->setAttributes();
    std::cout<< myDVD->getHouseProduction() << std::endl;  */


/*     myMedia::VHS *myVHS = new myMedia::VHS("OSS", "John Doe", "18/06/2001", 5, "MyHouse", 300, true); 
    
   
    std::cout<< myVHS->getAuthor() << std::endl;
    std::cout<< myVHS->getHouseProduction() << std::endl;
    std::cout<< myVHS->getColor() << std::endl;
    myVHS->setAttributes();
    std::cout<< myVHS->getHouseProduction() << std::endl;  */

    // testing building objects from command line
/*     myMedia::DVD *myDVD = new myMedia::DVD();
    std::cout<< myDVD->getTitle() << std::endl;
    std::cout<< myDVD->getAuthor() << std::endl;
    std::cout<< myDVD->getDate() << std::endl;
    std::cout<< myDVD->getQuantity() << std::endl;
    std::cout<< myDVD->getHouseProduction() << std::endl;
    std::cout<< myDVD->getDuration() << std::endl;
    std::cout<< myDVD->getChaptersNumber() << std::endl; */

/*    myMedia::Book *myBook = new myMedia::Book();
    myBook->setType("Book");
     std::cout<< myBook->getId() << std::endl;
    std::cout<< myBook->getType() << std::endl;
    std::cout<< myBook->getTitle() << std::endl;
    std::cout<< myBook->getAuthor() << std::endl;
    std::cout<< myBook->getDate() << std::endl;
    std::cout<< myBook->getQuantity() << std::endl;
    std::cout<< myBook->getCollection() << std::endl;
    std::cout<< myBook->getEditor() << std::endl;
    std::cout<< myBook->getSummary() << std::endl;
    std::cout<< myBook->getPagesNumber() << std::endl;
    std::cout<< myBook->getFormat() << std::endl;  
    //std::string fileNameStr = ".\\database\\Books\\" + myBook->getTitle() + "_" + std::to_string(myBook->getId()) + ".csv";
    std::string fileNameStr = ".\\database\\Books\\" + myBook->getTitle() + ".csv";
    std::cout<< myBook->saveToFile(fileNameStr.c_str()) << std::endl;*/

/*     myMedia::Numeric *myPDF = new myMedia::Numeric();
    std::cout<< myPDF->getTitle() << std::endl;
    std::cout<< myPDF->getAuthor() << std::endl;
    std::cout<< myPDF->getDate() << std::endl;
    std::cout<< myPDF->getQuantity() << std::endl;
    std::cout<< myPDF->getType() << std::endl; 
    std::cout<< myPDF->getURL() << std::endl;
    std::cout<< myPDF->getSize() << std::endl;
    std::cout<< myPDF->saveToFile(".\\database\\test.txt") << std::endl; */

/*     myMedia::Book *myBook = new myMedia::Book(".\\database\\Books\\a_28545.txt");
    std::cout<< myBook->getId() << std::endl;
    std::cout<< myBook->getType() << std::endl;
    std::cout<< myBook->getTitle() << std::endl;
    std::cout<< myBook->getAuthor() << std::endl;
    std::cout<< myBook->getDate() << std::endl;
    std::cout<< myBook->getQuantity() << std::endl;
    std::cout<< myBook->getCollection() << std::endl;
    std::cout<< myBook->getEditor() << std::endl;
    std::cout<< myBook->getSummary() << std::endl;
    std::cout<< myBook->getPagesNumber() << std::endl;
    std::cout<< myBook->getFormat() << std::endl;  */
    //std::string fileNameStr = ".\\database\\" + myBook->getTitle() + ".txt";
    //std::cout<< myBook->saveToFile(fileNameStr.c_str()) << std::endl;

       
/*     myMedia::Magazine *myMag = new myMedia::Magazine(".\\database\\Caras.txt");
    std::cout<< myMag->getTitle() << std::endl;
    std::cout<< myMag->getAuthor() << std::endl;
    std::cout<< myMag->getDate() << std::endl;
    std::cout<< myMag->getQuantity() << std::endl;
    std::cout<< myMag->getCollection() << std::endl;
    std::cout<< myMag->getEditor() << std::endl;
    std::cout<< myMag->getSummary() << std::endl;
    std::cout<< myMag->getPagesNumber() << std::endl;
    std::cout<< myMag->getArticlesNumber() << std::endl;  */
/*     std::string fileNameStr = ".\\database\\" + myMag->getTitle() + ".txt";
    std::cout<< myMag->saveToFile(fileNameStr.c_str()) << std::endl; */

/*     myMedia::VHS *myVHS = new myMedia::VHS(".\\database\\Shrek.txt");
    std::cout<< myVHS->getTitle() << std::endl;
    std::cout<< myVHS->getAuthor() << std::endl;
    std::cout<< myVHS->getDate() << std::endl;
    std::cout<< myVHS->getQuantity() << std::endl;
    std::cout<< myVHS->getDuration() << std::endl;
    std::cout<< myVHS->getColor() << std::endl; */
/*     std::string fileNameStr = ".\\database\\" + myVHS->getTitle() + ".txt";
    std::cout<< myVHS->saveToFile(fileNameStr.c_str()) << std::endl; */


/*     myMedia::DVD *myDVD = new myMedia::DVD(".\\database\\Toy Story.txt");
    std::cout<< myDVD->getTitle() << std::endl;
    std::cout<< myDVD->getAuthor() << std::endl;
    std::cout<< myDVD->getDate() << std::endl;
    std::cout<< myDVD->getQuantity() << std::endl;
    std::cout<< myDVD->getDuration() << std::endl;
    std::cout<< myDVD->getChaptersNumber() << std::endl; */
/*     std::string fileNameStr = ".\\database\\" + myDVD->getTitle() + ".txt";
    std::cout<< myDVD->saveToFile(fileNameStr.c_str()) << std::endl;
  */

/*     myMedia::CD *myDVD = new myMedia::CD(".\\database\\The Wall.txt");
    std::cout<< myDVD->getTitle() << std::endl;
    std::cout<< myDVD->getAuthor() << std::endl;
    std::cout<< myDVD->getDate() << std::endl;
    std::cout<< myDVD->getQuantity() << std::endl;
    std::cout<< myDVD->getQuantity() << std::endl;
    std::cout<< myDVD->getHouseProduction() << std::endl;
    std::cout<< myDVD->getTracksNumber() << std::endl; */
/*     std::string fileNameStr = ".\\database\\" + myDVD->getTitle() + ".txt";
    std::cout<< myDVD->saveToFile(fileNameStr.c_str()) << std::endl; */


/*     myMedia::Numeric *myDVD = new myMedia::Numeric(".\\database\\Datasheet.txt");
    std::cout<< myDVD->getTitle() << std::endl;
    std::cout<< myDVD->getAuthor() << std::endl;
    std::cout<< myDVD->getDate() << std::endl;
    std::cout<< myDVD->getQuantity() << std::endl;
    std::cout<< myDVD->getType() << std::endl;
    std::cout<< myDVD->getURL() << std::endl;
    std::cout<< myDVD->getSize() << std::endl; */
/*     std::string fileNameStr = ".\\database\\" + myDVD->getTitle() + ".txt";
    std::cout<< myDVD->saveToFile(fileNameStr.c_str()) << std::endl; */


/*     myMedia::Media *myBook = new myMedia::Book(".\\database\\SteppenWolf.txt");
    std::cout<< myBook->getTitle() << std::endl;
    std::cout<< myBook->getAuthor() << std::endl;
    std::cout<< myBook->getDate() << std::endl;
    std::cout<< myBook->getQuantity() << std::endl; */
/*     std::cout<< myBook->getCollection() << std::endl;
    std::cout<< myBook->getEditor() << std::endl;
    std::cout<< myBook->getSummary() << std::endl;
    std::cout<< myBook->getPagesNumber() << std::endl;
    std::cout<< myBook->getFormat() << std::endl;  */

    //loadDatabase(".\\database");
    std::string fileNameStr;

/*     myMedia::Book *myBook = new myMedia::Book(); 
    myBook->setType("Book");
    fileNameStr = ".\\database\\Books\\" + myBook->getType() + ".csv";
    std::cout<< myBook->saveToFile(fileNameStr.c_str()) << std::endl; 

    myMedia::Magazine *myMagazine = new myMedia::Magazine();
    myMagazine->setType("Magazine");
    fileNameStr = ".\\database\\Magazines\\" + myMagazine->getType() + ".csv";
    std::cout<< myMagazine->saveToFile(fileNameStr.c_str()) << std::endl; 

    myMedia::VHS *myVHS = new myMedia::VHS();
    myVHS->setType("VHS");
    fileNameStr = ".\\database\\VHS\\" + myVHS->getType() + ".csv";
    std::cout<< myVHS->saveToFile(fileNameStr.c_str()) << std::endl;

    myMedia::DVD *myDVD = new myMedia::DVD();
    myDVD->setType("DVD");
    fileNameStr = ".\\database\\DVD\\" + myDVD->getType() + ".csv";
    myDVD->saveToFile(fileNameStr.c_str());
    */
 
/*     myMedia::CD *myCD = new myMedia::CD();
    myCD->setType("CD");
    fileNameStr = ".\\database\\" + myCD->getType() + ".csv";
    myCD->saveToFile(fileNameStr.c_str()); */
/*     std::string fileNameStr;
    myMedia::Numeric *myNum = new myMedia::Numeric();
    myNum->setType("Num");
    fileNameStr = ".\\database\\" + myNum->getType() + ".csv";
    myNum->saveToFile(fileNameStr.c_str());  */
    //loadDatabase(".\\database");
/*     std::string databasePath;
    std::cout<< "what is the database path" << std::endl; 
    std::cin>> databasePath;
     */
    //loadDatabaseFromCsv(".\\database");
    //saveDatabase(myDatabase, false);

    // testing clone method
/*     myMedia::Media* DVDclone = new myMedia::DVD();
    myMedia::Media* newDVD = DVDclone->clone(); */

    // testing user class creation //
/*     myUsers::User* newUser = new myUsers::User();
    myUsers::User* newUser2 = new myUsers::User(22022, "Caio Molinari", 1, "senha"); */

    // TODO : COMMENT ALL METHODS BY DOCSTRING PATTERN! //

    // Mediatek class tests
   // myMedia::Mediatheque* mediatek = new myMedia::Mediatheque("base_donnees.txt");
   myMedia::Mediatheque* mediatek = new myMedia::Mediatheque();
/*     mediatek->currentdB.test = 5;
    std::cout<< mediatek->currentdB.test << std::endl; */
    //mediatek->loadDatabaseFromCsv();
    //mediatek->addMedia(1);
/*     mediatek->listContent();
    mediatek->listResearchResults();
    mediatek->saveDatabase();
    mediatek->searchMedia("tOlKiEN"); */
    
    int command;
    int QUIT_APP = 0;
    while(!QUIT_APP){
        std::cout << "###################################################"<< std::endl;
        std::cout<< "What would you like to do?" << std::endl;
        std::cout<< "1 to add a new ressource to the mediatheque"<< std::endl;
        std::cout<< "2 to delete a ressource from the mediatheque"<< std::endl;
        std::cout<< "3 to save the modifications to the database"<< std::endl;
        std::cout<< "4 to load a database from path" << std::endl;
        std::cout<< "5 to list all available items"<< std::endl;
        std::cout<< "6 to get detailed information about an item " << std::endl;
        std::cout<< "7 to execute a general research " << std::endl;
        std::cout<< "8 to research by media category" << std::endl;
        std::cout<< "9 to reset the research" << std::endl;
        std::cout<< "10 to login with your id and password"<< std::endl;
        std::cout<< "11 to logout" << std::endl;
        std::cout<< "12 to add a new user" << std::endl;
        std::cout<< "13 to delete an user" << std::endl;
        std::cout<< "14 to list all users" << std::endl;
        std::cout<< "15 to borrow a media" << std::endl;
        std::cout<< "16 to return a media" << std::endl;
        std::cout<< "17 to clear the database" << std::endl;
        std::cout<< "18 to export current database to .txt file" << std::endl;
        std::cout<< "19 to refresh the database" << std::endl;
        std::cout<< "20 to list borrowed items" << std::endl;
        std::cout<< "0 to quit the application" << std::endl;
        std::cout<< "33 for help" << std::endl;
        std::cout << "###################################################"<< std::endl;
        std::cin>> command;
        switch(command){
            case 0:{
                QUIT_APP = 1;
                mediatek->saveDatabase();
                break;
            // we use {} to explicitly tell the compiler that local case variables should be destroyed after the case statement
            // https://stackoverflow.com/questions/5685471/error-jump-to-case-label-in-switch-statement
            }
            case 1:{
                int choice;
                if(mediatek->getCurrentUser()->getStatus() && mediatek->getCurrentUser()->getAuthorisationLevel() > 1){
                    std::cout << "###################################################"<< std::endl;
                    std::cout<< "What kind of Media would you like to add to the Mediatheque?" << std::endl;
                    std::cout<< "1 : Book"<< std::endl;
                    std::cout<< "2 : CD"<< std::endl;
                    std::cout<< "3 : DVD"<< std::endl;
                    std::cout<< "4 : Magazine"<< std::endl;
                    std::cout<< "5 : Num"<< std::endl;
                    std::cout<< "6 : VHS"<< std::endl;
                    std::cout << "###################################################"<< std::endl;
                    std::cin>> choice;
                    mediatek->addMedia(choice);
                }
                else{
                    // if the current user does not have enough authorization or is not logged in
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "This service is exclusive to librarians and system managers, please log in and try again." << std::endl;
                    }

                break;
            }
            case 2:{
                int idToDelete = 0;
                if(mediatek->getCurrentUser()->getStatus() && mediatek->getCurrentUser()->getAuthorisationLevel() > 1){
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "What is the id of the media you would like to delete from the mediathque?" << std::endl;
                    std::cin>> idToDelete;
                    if(mediatek->deleteMedia(idToDelete)){
                        std::cout<< idToDelete << " successfully removed from the Mediatheque " << std::endl;
                    }
                    else{
                        std::cout<< "###################################################"<< std::endl;
                        std::cout<< "The provided id was not found, please try again."<<std::endl;  
                    }
                }
                else{
                    // if the current user does not have enough authorization or is not logged in
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "This service is exclusive to librarians and system managers, please log in and try again." << std::endl;
                    }
                break;
            }
            case 3:{
                if(mediatek->getCurrentUser()->getStatus() && mediatek->getCurrentUser()->getAuthorisationLevel() > 1){
                    std::cout<< "*** Saving modifications to "<< mediatek->getCurrentDatabase().dBPath << "... ***" << std::endl;
                    mediatek->saveDatabase();
                }
                else{
                    // if the current user does not have enough authorization or is not logged in
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "This service is exclusive to librarians and system managers, please log in and try again." << std::endl;
                    }
                break;
            }
            case 4:{
                std::string loadDBPath;
                int choice {0};
                if(mediatek->getCurrentUser()->getStatus() && mediatek->getCurrentUser()->getAuthorisationLevel() > 1){
                    std::cout << "###################################################"<< std::endl;
                    std::cout<< "Would you like to load the database from a .txt file or a .csv folder?" << std::endl;
                    std::cout<< "1 to load from a folder, 0 to load from a .txt file"<< std::endl;
                    std::cin>> choice;
                    std::cout<<"What is the corresponding path?" << std::endl;
                    std::getline(std::cin >> std::ws, loadDBPath);
                    std::cout<< "*** Loading database from "<< loadDBPath << "... ***" << std::endl;
                    if (choice){
                    mediatek->loadDatabaseFromCsv(loadDBPath);
                    }
                    else{
                    mediatek->init_Mediatheque(loadDBPath.c_str());
                    }
                }

                else{
                    // if the current user does not have enough authorization or is not logged in
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "This service is exclusive to librarians and system managers, please log in and try again." << std::endl;
                }

                
                //std::cout<< "*** Loading database from "<< loadDBPath << "... ***" << std::endl;
                //mediatek->loadDatabaseFromCsv(loadDBPath); // TODO: load from txt too according to choice
                break;
            }
            case 5:{
                mediatek->listContent();
                break;
            }
            case 6:{
                int id{0};
                if(mediatek->getCurrentUser()->getStatus() && mediatek->getCurrentUser()->getAuthorisationLevel() > 0){
                    std::cout << "###################################################"<< std::endl;
                    std::cout<< "What is the id of the item you would like to get informations about?" << std::endl;
                    std::cin>> id;
                    if(!mediatek->showInfo(id)){
                        std::cout<< "The provided id was not found, please try again." << std::endl;
                    }
                }
                else{
                        // if the current user does not have enough authorization or is not logged in
                        std::cout<< "###################################################"<< std::endl;
                        std::cout<< "This service is exclusive to subscribers, please log in and try again." << std::endl;
                    }
                break;
            }
            case 7:{
                while(true){
                    std::string searchStr;
                    std::cout<< "Enter the keyword you want to search for (press q to quit or r to reset research): "<< std::endl;
                    std::getline(std::cin >> std::ws, searchStr);
                    if(searchStr == "q"){
                        mediatek->resetResearch();
                        break;
                    }
                    else if(searchStr == "r"){
                        mediatek->resetResearch();
                    }
                    else{
                        mediatek->searchMedia(searchStr);
                    } 
                }
                break;
            }

            case 8:{
                while(true){
                    std::string searchStr;
                    int choice;
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "By which category would you like to search for? "<< std::endl;
                    std::cout<< "1 : Book"<< std::endl;
                    std::cout<< "2 : CD"<< std::endl;
                    std::cout<< "3 : DVD"<< std::endl;
                    std::cout<< "4 : Magazine"<< std::endl;
                    std::cout<< "5 : Num"<< std::endl;
                    std::cout<< "6 : VHS"<< std::endl;
                    std::cout<< "0 : Quit" << std::endl;
                    std::cout<< "###################################################"<< std::endl;
                    std::cin >> choice;
                    if(choice == 0){
                        break;
                    }
                    mediatek->listContentByType(choice);
                    while (true) {
                        std::cout<< "Enter the keyword you want to search for (press q to quit or r to reset research): "<< std::endl;
                        std::getline(std::cin >> std::ws, searchStr);
                        if(searchStr == "q"){
                            mediatek->resetResearch();
                            break;
                        }
                        else if(searchStr == "r"){
                            mediatek->resetResearch();
                        }
                        else{
                            mediatek->searchMediaByType(searchStr, choice);
                        }    
                    }
                }
                break;
            }

            case 9:{
                mediatek->resetResearch();
                std::cout<< "Research reset done!" << std::endl;
                break;
            }

            case 10:{
                int id;
                std::string password;
                std::cout<< "###################################################"<< std::endl;
                if(!mediatek->getCurrentUser()->getStatus()){
                    std::cout<< "Please enter your credentials"<< std::endl;
                    std::cout<< "User Id:"<< std::endl;
                    std::cin>> id;
                    std::cout<< "Password" << std::endl;
                    std::getline(std::cin >> std::ws, password);
                    if(mediatek->login(id, password)){
                        std::cout<< "Hello " << mediatek->getCurrentUser()->getName() << "!" << std::endl;
                    }
                    else{
                        std::cout<< "Id or password incorrect, please try again"<< std::endl;
                    }
                }
                else{
                    std::cout<< "You are already logged in!"<< std::endl;
                }

                break;
            }

            case 11:{
                mediatek->getCurrentUser()->logout();
                std::cout<< "Goodbye " << mediatek->getCurrentUser()->getName() << "!" << std::endl;
                break;
            }

            case 12:{
                if(mediatek->getCurrentUser()->getStatus() && mediatek->getCurrentUser()->getAuthorisationLevel() > 1){
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "Please, enter the information about the new user"<< std::endl;
                    mediatek->addUser();
                }
                else{
                    // if the current user does not have enough privileges or is not logged in
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "This service is exclusive to system managers, please log in and try again." << std::endl;
                }
                break;
            }

            case 13:{
                int idToDelete{0};
                if(mediatek->getCurrentUser()->getStatus() && mediatek->getCurrentUser()->getAuthorisationLevel() > 1){
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "What is the id of the user you would like to delete from the mediathque?" << std::endl;
                    std::cin>> idToDelete;
                    if(mediatek->deleteUser(idToDelete)){
                        std::cout<< "User " << idToDelete << " successfully removed from the Mediatheque " << std::endl;
                    }
                    else{
                        std::cout<< "###################################################"<< std::endl;
                        std::cout<< "The provided id was not found, please try again."<<std::endl;  
                    }
                }
                else{
                    // if the current user does not have enough authorization or is not logged in
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "This service is exclusive to system managers, please log in and try again." << std::endl;
                }
                break;

            }

            case 14:{
                if(mediatek->getCurrentUser()->getStatus() && mediatek->getCurrentUser()->getAuthorisationLevel() > 1){
                    mediatek->listUsers();
                }  
                else{
                    // if the current user does not have enough authorization or is not logged in
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "This service is exclusive to librarians and system managers, please log in and try again." << std::endl;
                }
                break;
            }

            case 15:{
                int idMediaToBorrow{0};
                int idUser{0};
                if(mediatek->getCurrentUser()->getStatus() && mediatek->getCurrentUser()->getAuthorisationLevel() > 1){
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "What is the id of the media you would like to borrow from the mediathque?" << std::endl;
                    std::cin>> idMediaToBorrow;
                    std::cout<< "What is the id of the user borrowing this item?" << std::endl;
                    std::cin>> idUser;
                    if(mediatek->borrowMedia(idMediaToBorrow, idUser)){
                        std::cout<< "Media " << idMediaToBorrow << " lent to user " << idUser << std::endl;
                    }
                    else{
                        std::cout<< "Couldn't borrow media " << idMediaToBorrow << std::endl;
                    }
                }
                else{
                    // if the current user does not have enough authorization or is not logged in
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "This service is exclusive to librarians and system managers, please log in and try again." << std::endl;
                }
                break;
            }

            case 16:{
                int idMediaToReturn{0};
                int idUser{0};
                if(mediatek->getCurrentUser()->getStatus() && mediatek->getCurrentUser()->getAuthorisationLevel() > 1){
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "What is the id of the media you would like to return to the mediathque?" << std::endl;
                    std::cin>> idMediaToReturn;
                    std::cout<< "What is the id of the user returning this item?" << std::endl;
                    std::cin>> idUser;
                    if(mediatek->returnMedia(idMediaToReturn, idUser)){
                        std::cout<< "Media " << idMediaToReturn << " returned from user " << idUser << std::endl;
                    }
                    else{
                        std::cout<< "Couldn't return media" << idMediaToReturn << std::endl;
                    }
                }
                else{
                    // if the current user does not have enough authorization or is not logged in
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "This service is exclusive to librarians and system managers, please log in and try again." << std::endl;
                }
                break;
            }

            case 17:{
                if(mediatek->getCurrentUser()->getStatus() && mediatek->getCurrentUser()->getAuthorisationLevel() == 3){
                    mediatek->clearDatabase();
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "The database was succesfully cleared" << std::endl;
                }
                else{
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "This service is exclusive to system managers, please log in and try again." << std::endl;
                }
                break;
            }

            case 18:{
                std::string pathTxt;
                if(mediatek->getCurrentUser()->getStatus() && mediatek->getCurrentUser()->getAuthorisationLevel() > 1){
                    std::cout<< "Path of the .txt output file" << std::endl;
                    std::getline(std::cin >> std::ws, pathTxt);
                    std::cout<< "*** Exporting database to "<< pathTxt << "... ***" << std::endl;
                    mediatek->saveDatabaseTxt(pathTxt);
                }
                else{
                    // if the current user does not have enough authorization or is not logged in
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "This service is exclusive to librarians and system managers, please log in and try again." << std::endl;
                    }
                break;
            }

            case 19:{
                mediatek->loadDatabaseFromCsv();
                std::cout<< "Database up to date" << std::endl;
                break;
            }

            case 20:{
                int choice{0};
                int userId{0};
                if(mediatek->getCurrentUser()->getStatus() && mediatek->getCurrentUser()->getAuthorisationLevel() > 0){
                    std::cout<< "Would you like to list your own items or another user's? ";
                    std:: cout<< "1 for your own user, 0 for another user" << std::endl;
                    std::cin>> choice;
                    if (choice){
                        mediatek->listUserMedias(mediatek->getCurrentUser()->getId());
                    }
                    else{
                       if(mediatek->getCurrentUser()->getStatus() && mediatek->getCurrentUser()->getAuthorisationLevel() > 2){
                        std::cout<< "What is the user id?" << std::endl;
                        std::cin>> userId;
                        if(!mediatek->listUserMedias(userId)){
                            std::cout<< "Id not found" << std::endl;
                        }
                        
                       } 
                       else{
                        std::cout<< "Only librarians and system managers can list other users borrowed medias"<< std::endl;
                       }
                    }
                }
                else{
                    // if the current user does not have enough authorization or is not logged in
                    std::cout<< "###################################################"<< std::endl;
                    std::cout<< "This service is exclusive to librarians and system managers, please log in and try again." << std::endl;
                    }
                break;
            }

            case 33:{
                std::cout << "This is the help section" << std::endl;
                break;
            }

        }
    }
    std::cout << "End of application" << std::endl;
    // change here for folder or file tests //
    
    //mediatek->saveDatabaseTxt();
    delete mediatek; 
    return 0;

}