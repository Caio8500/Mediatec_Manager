#include "VHS.h"

namespace myMedia{

    // https://stackoverflow.com/questions/20173877/base-class-dont-have-default-constructor-when-derived-class-constructor-initial
    VHS::VHS():VideoMedia{}
    {
        type = "VHS";
        std::cout<< "Colored:" << std::endl;
        std::cin>> Color;
    }

    VHS::VHS(const char* filename):VideoMedia{filename}
    {
        bool loadSuccess = loadFromFile(filename);
        if (!loadSuccess){
            std::cout<< "Could not load object from file " << filename << std::endl;
        }
    }

    VHS::VHS(int id, std::string Title, std::string Author,
             std::string Date, int Quantity,
             std::string HouseProduction, int Duration, bool Color) :
             VideoMedia(id, Title, Author,Date,Quantity,HouseProduction,Duration)
        {
            type = "VHS";
            this->Color = Color;
        }

    Media* VHS::clone(){
        return new VHS(this->id, this->title, 
                       this->author, this->date,
                       this->quantity, this->HouseProduction,
                       this->Duration, this->Color);
    }

    bool VHS::getColor(){
        return Color;
    }

    void VHS::setColor(bool newColor){
        Color = newColor;
    }

    void VHS::setAttributes() {
        std::cout<< "setAttr" << std::endl;
    }

    bool VHS::saveToFile(const char* filename, std::string fileFormat){
        std::cout<< "Saving VHS to file " << filename << std::endl;
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
            outfile<< Color << std::endl;
            outfile.close();
            return true;
        }
        else{
            return false;
        }
    }

    bool VHS::loadFromFile(const char* filename){
        std::cout<< "Loading VHS from file " << filename << std::endl;
        
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
        Color = stoi(auxStr);
        infile.close();
        return true;
    }

    bool VHS::searchStr(std::string str){
        // this method looks up for a substring among the attributes of the DVD class
        size_t found;
        if(!VideoMedia::searchStr(str)){
            found = myUtils::toLowerCase(std::to_string(Color)).find(myUtils::toLowerCase(str));
            if (found != std::string::npos)
                return true;
            return false;
        }
        else
            return true;
    }

    void VHS::printHeader(bool breakLine){
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }
        VideoMedia::printHeader(false);
        std::cout<< std::setw(10) << "Color"
        << separator;
    }

    void VHS::show(bool breakLine){
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
        << std::setw(10) << Color
        << separator;
    }
}
