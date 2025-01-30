#include "Magazine.h"

namespace myMedia{
    
    
    Magazine::Magazine():PaperMedia{}
    {
        type = "Magazine";
        std::cout<< "Number of articles:" << std::endl;
        std::cin >> articlesNumber;
    }

    Magazine::Magazine(const char* filename):PaperMedia{filename}
    {
        bool loadSuccess = loadFromFile(filename);
        if (!loadSuccess){
            std::cout<< "Could not load object from file " << filename << std::endl;
        }
    }
    Magazine::Magazine(int id, std::string title, std::string author,
                           std::string date, int quantity, 
                           std::string summary, std::string collection,
                           std::string editor, int pagesNumber,
                           int articlesNumber):
        PaperMedia{id, title, author, date, quantity, summary, collection, editor, pagesNumber},
        articlesNumber{articlesNumber}
    {
        type = "Magazine";
    }

    Media* Magazine::clone(){
        return new Magazine(this->id, this->title, 
                       this->author, this->date,
                       this->quantity, this->summary,
                       this->collection, this->editor, 
                       this->pagesNumber, this->articlesNumber);
    }

    int Magazine::getArticlesNumber(){
        return articlesNumber;
    }


    void Magazine::setArticlesNumber(int newArticlesNumber){
        articlesNumber = newArticlesNumber;
    }

    void Magazine::setAttributes(){
        author = "a";
        articlesNumber = 3;
    }

    bool Magazine::saveToFile(const char* filename, std::string fileFormat){
        std::cout<< "Saving Magazine to file " << filename << std::endl;
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
            outfile<< id<< separator;
            outfile<< type << separator;
            outfile<< title << separator;
            outfile<< author << separator;
            outfile<< date << separator;
            outfile<< quantity << separator;
            outfile<< summary << separator;
            outfile<< collection << separator;
            outfile<< editor << separator;
            outfile<< pagesNumber << separator;
            outfile<< articlesNumber << std::endl;
            outfile.close();
            return true;
        }
        else{
            return false;
        }
    }

    bool Magazine::loadFromFile(const char* filename){
        std::cout<< "Loading Magazine from file " << filename << std::endl;
        
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
        getline(infile, auxStr);
        articlesNumber = stoi(auxStr);

        infile.close();
        return true;
    }

    bool Magazine::searchStr(std::string str){
        // this method looks up for a substring among the attributes of the DVD class
        size_t found;
        if(!PaperMedia::searchStr(str)){
            found = myUtils::toLowerCase(std::to_string(articlesNumber)).find(myUtils::toLowerCase(str));
            if (found != std::string::npos)
                return true;
            return false;
        }
        else
            return true;
    }

    void Magazine::printHeader(bool breakLine){
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }
        PaperMedia::printHeader(false);
        std::cout<< std::setw(20) << "ARTICLES NUMBER"
        << separator;
    }

    void Magazine::show(bool breakLine){
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }
        PaperMedia::show(false);
        std::cout<< std::left
        << std::setw(15) << articlesNumber
        << separator;
    }

    
}