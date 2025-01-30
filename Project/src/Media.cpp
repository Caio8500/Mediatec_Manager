#include "Media.h"

namespace myMedia{
    Media::Media(int id, std::string title, std::string author, std::string date, int quantity):
        id{id},
        title{title},
        author{author},
        date{date},
        quantity{quantity}
    {}

    Media::Media(const char* filename){} // the base classes constructors to build an object from file are empty, more info on book.cpp
    
    Media::Media()
    {
        // this constructor will be used when the user desires to create a new object in the database
        srand(time(NULL));
        id = rand()%MAX_QUANTITY;
        std::cout<< "Title:" << std::endl;
        std::getline(std::cin >> std::ws, title);
        std::cout<< "Author:" << std::endl;
        std::getline(std::cin, author);
        std::cout<< "Date of publishing:" << std::endl;
        std::getline(std::cin, date);
        std::cout<< "Available items:" << std::endl;
        std::cin>> quantity;
    }

    Media* Media::clone(){}

    bool Media::searchStr(std::string str){
        // this method looks up for a substring among the attributes of the Media class
        size_t found;
        found = myUtils::toLowerCase(std::to_string(id)).find(myUtils::toLowerCase(str));
        if (found != std::string::npos)
            return true;
        found = myUtils::toLowerCase(title).find(myUtils::toLowerCase(str));
        if (found != std::string::npos)
            return true;
        found = myUtils::toLowerCase(author).find(myUtils::toLowerCase(str));
        if (found != std::string::npos)
            return true;
        found = myUtils::toLowerCase(date).find(myUtils::toLowerCase(str));
        if (found != std::string::npos)
            return true;
        found = myUtils::toLowerCase(std::to_string(quantity)).find(myUtils::toLowerCase(str));
        if (found != std::string::npos)
            return true;
        return false;
    }

    void Media::printHeader(bool breakLine){
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }
        std::cout<< std::left<< std::setw(10) << "ID"
        << std::setw(10) << "TYPE"
        << std::setw(25) << "TITLE"
        << std::setw(20) << "AUTHOR"
        << std::setw(15) << "DATE"
        << std::setw(10)  << "ITEMS" << separator;
    }


    void Media::show(bool breakLine){
        // this method shows the media class attributes in an organized way
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }

        std::cout<< std::left
        << std::setw(10) << id 
        << std::setw(10) << type
        << std::setw(25) << title 
        << std::setw(20) << author 
        << std::setw(15) << date 
        << std::setw(10) << quantity << separator;
    }

    std::string Media::getTitle(){
        return title;
    }

    std::string Media::getAuthor(){
        return author;
    }
    
    std::string Media::getDate(){
        return date;
    }

    int Media::getQuantity(){
        return quantity;
    }

    int Media::getId(){
        return id;
    }

    std::string Media::getType(){
        return type;
    }

    void Media::setType(std::string newType){
        type = newType;
    }

    void Media::setTitle(std::string newTitle){
        title = newTitle;
    }

    void Media::setAuthor(std::string newAuthor){
        author = newAuthor;
    }

    void Media::setQuantity(int newQuantity){
        quantity = newQuantity; 
    }

    void Media::setDate(std::string newDate){
        date = newDate;
    }

    void Media::borrowMedia(){
        quantity -= 1;
    }

    bool Media::returnMedia(){
        quantity += 1;
    }

    bool Media::saveToFile(const char* filename, std::string fileFormat){return true;}
    
}