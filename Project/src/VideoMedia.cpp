
#include "VideoMedia.h"

namespace myMedia{
    
    VideoMedia::VideoMedia():Media{}
    {   
        // explanation as to why we have bad behavior from a getline after a cin
        //https://www.geeksforgeeks.org/problem-with-getline-after-cin/
        std::cout<< "Production House:" << std::endl;
        std::getline(std::cin >> std::ws, HouseProduction);
        std::cout<< "Duration:" << std::endl;
        std::cin>> Duration;
    }

    VideoMedia::VideoMedia(const char* filename):Media{filename}{}
    
    VideoMedia::VideoMedia(int id, std::string Title, std::string Author,
                           std::string Date, int Quantity,
                           std::string HouseProduction, int Duration) :

        Media(id, Title, Author,Date,Quantity)
        {
            this->HouseProduction = HouseProduction;
            this->Duration = Duration;
        }

    Media* VideoMedia::clone(){}

    int VideoMedia::getDuration(){
        return Duration;
    }

    std::string VideoMedia::getHouseProduction(){
        return HouseProduction;
    }

    void VideoMedia::setHouseProduction(std::string newHouseProduction){
        HouseProduction = newHouseProduction;
    }

    void VideoMedia::setDuration(int newDuration){
        Duration = newDuration;
    }

    bool VideoMedia::saveToFile(const char* filename, std::string fileFormat){return true;}
    
    bool VideoMedia::searchStr(std::string str){
        // this method looks up for a substring among the attributes of the Media class
        size_t found;
        if(!Media::searchStr(str)){
            found = myUtils::toLowerCase(HouseProduction).find(myUtils::toLowerCase(str));
            if (found != std::string::npos)
                return true;
            found = myUtils::toLowerCase(std::to_string(Duration)).find(myUtils::toLowerCase(str));
            if (found != std::string::npos)
                return true;
            return false;
        }
        else
            return true;

    }

    void VideoMedia::printHeader(bool breakLine){
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }
        Media::printHeader(false);
        std::cout<< std::setw(25) << "HOUSE PRODUCTION"
        << std::setw(10) << "DURATION"
        << separator;
    }

    void VideoMedia::show(bool breakLine){
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }
        Media::show(false);
        std::cout<< std::left
        << std::setw(25) << HouseProduction
        << std::setw(10) << Duration
        << separator;
    }
}
