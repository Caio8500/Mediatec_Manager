#include "DVD.h"

namespace myMedia{

    DVD::DVD():VideoMedia{}
    {
        type = "DVD";
        std::cout<< "Number of chapters:" << std::endl;
        std::cin>> ChaptersNumber;
    }

    DVD::DVD(const char* filename):VideoMedia{filename}
    {
        bool loadSuccess = loadFromFile(filename);
        if (!loadSuccess){
            std::cout<< "Could not load object from file " << filename << std::endl;
        }
    }
    
    DVD::DVD(int id, std::string Title, std::string Author,
                           std::string Date, int Quantity,
                           std::string HouseProduction, int Duration, int ChaptersNumber) :

        VideoMedia{id, Title,Author,Date,Quantity,HouseProduction,Duration}
        {
            type = "DVD";
            this->ChaptersNumber = ChaptersNumber;
        }

    Media* DVD::clone(){
        return new DVD(this->id, this->title, 
                       this->author, this->date,
                       this->quantity, this->HouseProduction,
                       this->Duration, this->ChaptersNumber);
    }

    int DVD::getChaptersNumber(){
        return ChaptersNumber;
    }

    void DVD::setChaptersNumber(int newChaptersNumber){
        ChaptersNumber = newChaptersNumber;
    }

    void DVD::setAttributes() {
        ChaptersNumber = 20;
    }

    bool DVD::saveToFile(const char* filename, std::string fileFormat){
        std::cout<< "Saving DVD to file " << filename << std::endl;
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
            outfile<< HouseProduction << separator;
            outfile<< Duration << separator;
            outfile<< ChaptersNumber << std::endl;
            outfile.close();
            return true;
        }
        else{
            return false;
        }
    }

    bool DVD::loadFromFile(const char* filename){
        std::cout<< "Loading DVD from file " << filename << std::endl;
        
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
        getline(infile, HouseProduction);
        getline(infile, auxStr);
        Duration = stoi(auxStr);
        getline(infile, auxStr);
        ChaptersNumber = stoi(auxStr);
        infile.close();
        return true;
    }

    bool DVD::searchStr(std::string str){
        // this method looks up for a substring among the attributes of the DVD class
        size_t found;
        if(!VideoMedia::searchStr(str)){
            found = myUtils::toLowerCase(std::to_string(ChaptersNumber)).find(myUtils::toLowerCase(str));
            if (found != std::string::npos)
                return true;
            return false;
        }
        else
            return true;
    }

    void DVD::printHeader(bool breakLine){
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }
        VideoMedia::printHeader(false);
        std::cout<< std::setw(15) << "CHAPTERS NUMBER"
        << separator;
    }

    void DVD::show(bool breakLine){
        // outputs all particular attributes to the terminal
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }
        VideoMedia::show(false);
        std::cout<< std::left
        << std::setw(15) << ChaptersNumber
        << separator;
    }
}
