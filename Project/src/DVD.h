#ifndef _DVD_H
#define _DVD_H

#include <fstream>
#include "VideoMedia.h"

namespace myMedia{
        class DVD : public VideoMedia{

            protected:
            int ChaptersNumber;

            public:
            // Constructor
            DVD();
            DVD(const char* filename);
            DVD(int id, std::string Title, std::string Author,
                std::string Date, int Quantity,
                std::string HouseProduction, int Duration, int ChaptersNumber);
                
            // Methods
            bool saveToFile(const char* filename, std::string fileFormat = "csv");
            bool loadFromFile(const char* filename);
            bool searchStr(std::string str);
            void printHeader(bool breakLine = true);
            void show(bool breakLine);
            Media *clone();

            // Getters
            int getChaptersNumber();

            // Setters
            void setChaptersNumber(int newChaptersNumber);
            void setAttributes();
            };
}

#endif
