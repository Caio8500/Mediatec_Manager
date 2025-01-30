#include "CD.h"

namespace myMedia{

    CD::CD():Media{}
    {
        type = "CD";
        std::cout<< "Production House: " << std::endl;
        std::getline(std::cin >> std::ws, HouseProduction);
        std::cout<< "Duration: " << std::endl;
        std::cin>> Duration;        
        std::cout<< "Number of Tracks: " << std::endl;
        std::cin>> TracksNumber;
    }

    CD::CD(const char* filename):Media{filename}
    {
        bool loadSuccess = loadFromFile(filename);
        if (!loadSuccess){
            std::cout<< "Could not load object from file " << filename << std::endl;
        }
    }

    CD::CD(int id, std::string Title, std::string Author,
           std::string Date, int Quantity,
           std::string HouseProduction, int Duration, int TracksNumber) :

        Media(id, Title, Author,Date,Quantity)
        {
            type = "CD";
            this->HouseProduction = HouseProduction;
            this->Duration = Duration;
            this->TracksNumber = TracksNumber;
        }

    Media* CD::clone(){
        return new CD(this->id, this->title, 
                    this->author, this->date,
                    this->quantity, this->HouseProduction,
                    this->Duration, this->TracksNumber);
    }
    int CD::getDuration(){
        return Duration;
    }

    std::string CD::getHouseProduction(){
        return HouseProduction;
    }

    int CD::getTracksNumber(){
        return TracksNumber;
    }

    void CD::setHouseProduction(std::string newHouseProduction){
        HouseProduction = newHouseProduction;
    }

    void CD::setDuration(int newDuration){
        Duration = newDuration;
    }

    void CD::setTracksNumber(int newTracksNumber){
        TracksNumber = newTracksNumber;
    }

    void CD::setAttributes() {
        TracksNumber = 12;
    }

    bool CD::saveToFile(const char* filename, std::string fileFormat){
        std::cout<< "Saving CD to file " << filename << std::endl;
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
            outfile<< HouseProduction << separator;
            outfile<< Duration << separator;
            outfile<< TracksNumber << std::endl;
            outfile.close();
            return true;
        }
        else{
            return false;
        }
    }

    bool CD::loadFromFile(const char* filename){
        std::cout<< "Loading CD from file " << filename << std::endl;
        
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
        TracksNumber = stoi(auxStr);
        infile.close();
        return true;
    }

    bool CD::searchStr(std::string str){        // this method looks up for a substring among the attributes of the Media class
        size_t found;
        if(!Media::searchStr(str)){
            found = myUtils::toLowerCase(HouseProduction).find(myUtils::toLowerCase(str));
            if (found != std::string::npos)
                return true;
            found = myUtils::toLowerCase(std::to_string(Duration)).find(myUtils::toLowerCase(str));
            if (found != std::string::npos)
                return true;
            found = myUtils::toLowerCase(std::to_string(TracksNumber)).find(myUtils::toLowerCase(str));
            if (found != std::string::npos)
                return true;
            return false;
        }
        else
            return true;

    }

    void CD::printHeader(bool breakLine){
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }
        Media::printHeader(false);
        std::cout<< std::setw(30) << "HOUSE PRODUCTION"
        << std::setw(10) << "DURATION"
        << std::setw(20) << "TRACKS NUMBER"
        << separator;
    }
    void CD::show(bool breakLine){
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }
        Media::show(false);
        std::cout<< std::left
        << std::setw(30) << HouseProduction
        << std::setw(10) << Duration
        << std::setw(20) << TracksNumber
        << separator;
    }

}
