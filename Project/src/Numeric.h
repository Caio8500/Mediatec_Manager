#ifndef _NUMERIC_H
#define _NUMERIC_H

#include <fstream>
#include "Media.h"

namespace myMedia{
        class Numeric : public Media{

            protected:
            std::string TypeDoc;
            std::string URL;
            int Size;

            public:
            // Constructors
            Numeric();
            Numeric(const char* filename);
            Numeric(int id, std::string Title, std::string Author,
                       std::string Date, int Quantity,
                       std::string TypeDoc, std::string URL, int Size);

            // Methods
            bool saveToFile(const char* filename, std::string fileFormat = "csv");
            bool loadFromFile(const char* filename);
            void printHeader(bool breakLine);
            void show(bool breakLine);
            Media *clone();
            bool searchStr(std::string str);
            
            // Getters
            std::string getTypeDoc();
            std::string getURL();
            int getSize();

            // Setters
            void setTypeDoc(std::string newTypeDoc);
            void setURL(std::string newURL);
            void setSize(int newSize);
            void setAttributes();
            };
}

#endif
