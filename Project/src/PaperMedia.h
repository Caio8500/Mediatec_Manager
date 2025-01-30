#ifndef _PAPER_MEDIA_H
#define _PAPER_MEDIA_H


#include <iostream>
#include <string>
#include <fstream>
#include "Media.h"

namespace myMedia{
// https://stackoverflow.com/questions/4093407/c-namespaces-and-defining-classes-in-separate-files
        class PaperMedia : public Media{
            
            protected:
            std::string summary, collection, editor;
            int pagesNumber;

            public:
            // constructors
            PaperMedia();
            PaperMedia(const char* filename); // create object from file
            PaperMedia(int id, std::string title, std::string author,
                           std::string date, int quantity, 
                           std::string summary, std::string collection,
                           std::string editor, int pagesNumber);

            // Virtual Methods
            virtual bool saveToFile(const char* filename, std::string fileFormat = "csv");
            virtual bool searchStr(std::string str);
            virtual void printHeader(bool breakLine);
            virtual void show(bool breakLine); 
            virtual Media *clone();
            
            // Getters 
            std::string getSummary();
            std::string getCollection();
            std::string getEditor();
            int getPagesNumber(); 

            // Setters
            void setSummary(std::string newSummary);
            void setCollection(std::string newCollection);
            void setEditor(std::string newEditor);
            void setPagesNumber(int newPagesNumber);
            }; 
}

#endif