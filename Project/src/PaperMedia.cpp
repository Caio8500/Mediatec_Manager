#include "PaperMedia.h"

namespace myMedia{

    PaperMedia::PaperMedia():Media{}
    {
        std::cout<< "Summary:" << std::endl;
        std::getline(std::cin >> std::ws, summary);
        std::cout<< "Collection:" << std::endl;
        std::getline(std::cin, collection);
        std::cout<< "Editor:" << std::endl;
        std::getline(std::cin, editor);
        std::cout<< "Number of pages:" << std::endl;
        std::cin>> pagesNumber;
    }
    PaperMedia::PaperMedia(const char* filename):Media{filename}{}
    
    PaperMedia::PaperMedia(int id, std::string title, std::string author,
                           std::string date, int quantity, 
                           std::string summary, std::string collection,
                           std::string editor, int pagesNumber):
        Media{id, title, author, date, quantity},
        summary{summary},
        collection{collection},
        editor{editor},
        pagesNumber{pagesNumber}
    {}

    Media* PaperMedia::clone(){}

    std::string PaperMedia::getSummary(){
        return summary;
    }

    std::string PaperMedia::getCollection(){
        return collection;
    }
    
    std::string PaperMedia::getEditor(){
        return editor;
    }

    int PaperMedia::getPagesNumber(){
        return pagesNumber;
    }

    void PaperMedia::setSummary(std::string newSummary){
        summary = newSummary;
    }

    void PaperMedia::setCollection(std::string newCollection){
        collection = newCollection;
    }

    void PaperMedia::setEditor(std::string newEditor){
        editor = newEditor; 
    }

    void PaperMedia::setPagesNumber(int newPagesNumber){
        pagesNumber = newPagesNumber;
    } 

    bool PaperMedia::saveToFile(const char* filename, std::string fileFormat){return true;}

    bool PaperMedia::searchStr(std::string str){
        // this method looks up for a substring among the attributes of the Media class
        size_t found;
        if(!Media::searchStr(str)){
            found = myUtils::toLowerCase(summary).find(myUtils::toLowerCase(str));
            if (found != std::string::npos)
                return true;
            found = myUtils::toLowerCase(collection).find(myUtils::toLowerCase(str));
            if (found != std::string::npos)
                return true;
            found = myUtils::toLowerCase(editor).find(myUtils::toLowerCase(str));
            if (found != std::string::npos)
                return true;
            found = myUtils::toLowerCase(std::to_string(pagesNumber)).find(myUtils::toLowerCase(str));
            if (found != std::string::npos)
                return true;
            return false;
        }
        else
            return true;

    }

    void PaperMedia::printHeader(bool breakLine){
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }
        Media::printHeader(false);
        std::cout<< std::setw(25) << "SUMMARY"
        << std::setw(15) << "COLLECTION"
        << std::setw(15) << "EDITOR"
        << std::setw(15) << "PAGES NUMBER"
        << separator;
    }

    void PaperMedia::show(bool breakLine){
        std::string separator;
        if (breakLine){
            separator = "\n";
        }
        else{
            separator = "";
        }
        Media::show(false);
        std::cout<< std::left
        << std::setw(25) << summary
        << std::setw(15) << collection
        << std::setw(15) << editor
        << std::setw(15) << pagesNumber
        << separator;
    }
}