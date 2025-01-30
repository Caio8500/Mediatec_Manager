#include "Numeric.h"

namespace myMedia{

    Numeric::Numeric():Media{}
    {
        type = "Num";
        std::cout<< "TypeDoc:" << std::endl;
        std::getline(std::cin >> std::ws, TypeDoc);
        std::cout<< "URL:" << std::endl;
        std::getline(std::cin, URL);        
        std::cout<< "Size (in Mb):" << std::endl;
        std::cin>> Size;
    }
    
    Numeric::Numeric(const char* filename):Media{filename}
    {
        bool loadSuccess = loadFromFile(filename);
        if (!loadSuccess){
            std::cout<< "Could not load object from file " << filename << std::endl;
        }
    }

    Numeric::Numeric(int id, std::string Title, std::string Author,
                           std::string Date, int Quantity,
                           std::string TypeDoc, std::string URL, int Size):
        Media(id, Title, Author, Date, Quantity)
        {
            type = "Num";
            this->TypeDoc = TypeDoc;
            this->Size = Size;
            this->URL = URL;
        }

    Media* Numeric::clone(){
        return new Numeric(this->id, this->title, 
                       this->author, this->date,
                       this->quantity, this->TypeDoc,
                       this->URL, this->Size);
    }

    std::string Numeric::getTypeDoc(){
        return TypeDoc;
    }

    int Numeric::getSize(){
        return Size;
    }

    std::string Numeric::getURL(){
        return URL;
    }

    void Numeric::setTypeDoc(std::string newTypeDoc){
        TypeDoc = newTypeDoc;
    }

    void Numeric::setURL(std::string newURL){
        URL = newURL;
    }

    void Numeric::setSize(int newSize){
        Size = newSize;
    }

    void Numeric::setAttributes() {
        std::cout<< "setAttr" << std::endl;
    }

    bool Numeric::saveToFile(const char* filename, std::string fileFormat){
        std::cout<< "Saving Numeric to file " << filename << std::endl;
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
            outfile<< TypeDoc << separator;
            outfile<< URL << separator;
            outfile<< Size << std::endl;
            outfile.close();
            return true;
        }
        else{
            return false;
        }
    }

    bool Numeric::loadFromFile(const char* filename){
        std::cout<< "Loading Numeric ressource from file " << filename << std::endl;
        
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
        getline(infile, TypeDoc);
        getline(infile, URL);
        getline(infile, auxStr);
        Size = stoi(auxStr);
        infile.close();
        return true;
    }

    bool Numeric::searchStr(std::string str){        // this method looks up for a substring among the attributes of the Media class
        size_t found;
        if(!Media::searchStr(str)){
            found = myUtils::toLowerCase(TypeDoc).find(myUtils::toLowerCase(str));
            if (found != std::string::npos)
                return true;
            found = myUtils::toLowerCase(std::to_string(Size)).find(myUtils::toLowerCase(str));
            if (found != std::string::npos)
                return true;
            found = myUtils::toLowerCase(URL).find(myUtils::toLowerCase(str));
            if (found != std::string::npos)
                return true;
            return false;
        }
        else
            return true;

    }

    void Numeric::printHeader(bool breakLine){
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }
        Media::printHeader(false);
        std::cout<< std::setw(15) << "DOC TYPE"
        << std::setw(10) << "SIZE (Mb)"
        << std::setw(20) << "URL"
        << separator;
    }
    void Numeric::show(bool breakLine){
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }
        Media::show(false);
        std::cout<< std::left
        << std::setw(15) << TypeDoc
        << std::setw(10) << Size
        << std::setw(20) << URL
        << separator;
    }
}
