#ifndef _MEDIA_H
#define _MEDIA_H


#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include "utils.h"

namespace myMedia{

        class Media{
            
            protected:
                std::string type, title, author, date;
                int quantity, id;
                static const int MAX_QUANTITY = 100000;

            public:
                // Constructors
                Media(); // create object from command line
                Media(const char* filename); // create object from existing file
                Media(int id, std::string title, std::string author, std::string date, int quantity); // standard object creation

                // Virtual Methods
                virtual bool saveToFile(const char* filename, std::string fileFormat = "csv");
                virtual bool searchStr(std::string str);
                // visualization methods
                virtual void printHeader(bool breakLine = true);
                virtual void show(bool breakLine = true);
                virtual Media *clone();

                // Getters 
                std::string getType();
                std::string getTitle();
                std::string getAuthor();
                std::string getDate();
                int getQuantity(); // whether the book is available or not
                int getId();

                // Setters
                void setTitle(std::string newTitle);
                void setAuthor(std::string newAuthor);
                void setDate(std::string newDate);
                void setQuantity(int newQuantity);
                void borrowMedia();
                bool returnMedia();
                void setType(std::string newType);
            }; 


}

#endif