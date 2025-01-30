#ifndef _MAGAZINE_H
#define _MAGAZINE_H


#include <iostream>
#include <string>
#include <fstream>
#include "PaperMedia.h"

namespace myMedia{
        class Magazine : public PaperMedia{

            
          private:
          int articlesNumber;

          public:
          // methods
          Magazine();
          Magazine(const char* filename);
          Magazine(int id, std::string title, std::string author,
               std::string date, int quantity, 
               std::string summary, std::string collection,
               std::string editor, int pagesNumber,
               int articlesNumber);
     
          // Methods
          bool saveToFile(const char* filename, std::string fileFormat = "csv");
          bool loadFromFile(const char* filename);
          bool searchStr(std::string str);
          void printHeader(bool breakLine);
          void show(bool breakLine);
          
          Media *clone();
          // Getters 
          int getArticlesNumber();

          // Setters
          void setArticlesNumber(int newArticlesNumber);
          void setAttributes();
          }; 


}

#endif