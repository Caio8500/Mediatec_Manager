#ifndef _CD_H
#define _CD_H

#include <fstream>
#include "Media.h"

namespace myMedia{
        class CD : public Media{

            protected:

            std::string HouseProduction;
            int Duration;
            int TracksNumber;

            public:
            // methods
            CD();
            CD(const char* filename);
            CD(int id, std::string Title, std::string Author,
                       std::string Date, int Quantity,
                       std::string newHouseProduction, int Duration, int TracksNumber);

            // Methods
            bool saveToFile(const char* filename, std::string fileFormat = "csv");
            bool loadFromFile(const char* filename);
            void printHeader(bool breakLine);
            void show(bool breakLine);
            Media *clone();
            bool searchStr(std::string str);

            // Getters
            int getDuration();
            int getTracksNumber();
            std::string getHouseProduction();

            // Setters
            void setDuration(int newDuration);
            void setTracksNumber(int newTracksNumber);
            void setHouseProduction(std::string newHouseProduction);
            void setAttributes();
            };
}

#endif
