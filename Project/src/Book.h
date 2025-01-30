#ifndef _BOOK_H
#define _BOOK_H


#include <iostream>
#include <string>
#include <fstream>
#include "PaperMedia.h"

namespace myMedia{
        class Book : public PaperMedia{          

          protected:
          std::string format;

          public:
          // Constructors
          Book(); // create object from command line
          Book(const char* filename); // create object from file
          Book(int id, std::string title, std::string author, // standard object creation
               std::string date, int quantity, 
               std::string summary, std::string collection,
               std::string editor, int pagesNumber,
               std::string format);

          // Methods
          bool saveToFile(const char* filename, std::string fileFormat = "csv");
          //bool saveToCsv(const char* filename, std::string fileFormat = "csv");
          //bool saveToCSV(const char* filename);
          bool loadFromFile(const char* filename);
          bool searchStr(std::string str); 
          void printHeader(bool breakLine = true);
          void show(bool breakLine = true);
          Media *clone();

          // Getters 
          std::string getFormat();

          // Setters
          void setFormat(std::string newFormat);
          void setAttributes();
          }; 


}

#endif