#include "Book.h"

namespace myMedia{
    Book::Book():PaperMedia{}
    {
        type = "Book";
        std::cout<< "Book format:" << std::endl;
        std::getline(std::cin >> std::ws, format);
    }

    Book::Book(const char* filename):PaperMedia{filename}
    {
        bool loadSuccess = loadFromFile(filename);
        if (!loadSuccess){
            std::cout<< "Could not load object from file " << filename << std::endl;
        }
    }
    Book::Book(int id, std::string title, std::string author,
                           std::string date, int quantity, 
                           std::string summary, std::string collection,
                           std::string editor, int pagesNumber,
                           std::string format):
        PaperMedia{id, title, author, date, quantity, summary, collection, editor, pagesNumber},
        format{format}
    {
        type = "Book";
    }

    Media* Book::clone(){
        //return this; doesn't create a new object in memory, returns the same addr
        return new Book(this->id, this->title, 
                       this->author, this->date,
                       this->quantity, this->summary,
                       this->collection, this->editor,
                       this->pagesNumber, this->format);
    }


    std::string Book::getFormat(){
        return format;
    }


    void Book::setFormat(std::string newFormat){
        format = newFormat;
    }

    void Book::setAttributes(){
        author = "a";
        format = "comics";
    }

    // for the save and load from file methods we could have implemented a common core in the base classes,
    // however we feel like this is a better way because we'll let each object be fully in charge of 
    // dealing with those operations and we'll have a single open-close file cycle, rathen than 3 
    // (if we called the base classes methods)
    bool Book::saveToFile(const char* filename, std::string fileFormat){
        std::cout<< "Saving book to file " << filename << std::endl;
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
        if(outfile.is_open()){
            outfile<< id << separator;
            outfile<< type << separator;
            outfile<< title << separator;
            outfile<< author << separator;
            outfile<< date << separator;
            outfile<< quantity << separator;
            outfile<< summary << separator;
            outfile<< collection << separator;
            outfile<< editor << separator;
            outfile<< pagesNumber << separator;
            outfile<< format << std::endl;
            outfile.close();
            return true;
        }
        else{
            return false;
        }
    }
    
    /* bool Book::saveToCsv(const char* filename, std::string fileFormat){
        std::cout<< "Saving book to file " << filename << std::endl;
        std::ofstream outfile;
        std::string separator;

        if(fileFormat == "csv"){
            separator = ";";
            outfile.open(filename, std::ios::app);
        }
        else{
            separator = "/n";
            outfile.open(filename);
        }
        
        if(outfile.is_open()){
            outfile<< id << separator;
            outfile<< type << separator;
            outfile<< title << separator;
            outfile<< author << separator;
            outfile<< date << separator;
            outfile<< quantity << separator;
            outfile<< summary << separator;
            outfile<< collection << separator;
            outfile<< editor << separator;
            outfile<< pagesNumber << separator;
            outfile<< format << separator + "\n";
            outfile.close();
            return true;
        }
        else{
            return false;
        }
    } */

    bool Book::loadFromFile(const char* filename){
        std::cout<< "Loading book from file " << filename << std::endl;
        
        std::ifstream infile;
        infile.open(filename);
        std::string auxStr;

        if(!infile.is_open()){
            return false;
        }
        getline(infile, auxStr);
        id = stoi(auxStr);
        getline(infile, type);
        getline(infile, title);
        getline(infile, author);
        getline(infile, date);
        getline(infile, auxStr);
        quantity = stoi(auxStr);
        getline(infile, summary);
        getline(infile, collection);
        getline(infile, editor);
        getline(infile, auxStr);
        pagesNumber = stoi(auxStr);
        //std::cout<< name << std::endl;
        getline(infile, format);

        infile.close();
        return true;
    }

    bool Book::searchStr(std::string str){        // this method looks up for a substring among the attributes of the Media class
        size_t found;
        if(!Media::searchStr(str)){
            found = myUtils::toLowerCase(format).find(myUtils::toLowerCase(str));
            if (found != std::string::npos)
                return true;
            return false;
        }
        else
            return true;

    }

    void Book::printHeader(bool breakLine){
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }
        PaperMedia::printHeader(false);
        std::cout<< std::setw(15) << "FORMAT"
        << separator;
    }

    void Book::show(bool breakLine){
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }
        PaperMedia::show(false);
        std::cout<< std::left
        << std::setw(15) << format
        << separator;
    }

   
}