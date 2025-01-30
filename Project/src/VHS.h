#ifndef _VHS_H
#define _VHS_H

#include "VideoMedia.h"

namespace myMedia{
        class VHS : public VideoMedia{

            protected:
            bool Color;

            public:
            // methods
            VHS();
            VHS(const char* filename);
            VHS(int id, std::string Title, std::string Author,
                       std::string Date, int Quantity,
                       std::string HouseProduction, int Duration, bool Color);

            // Methods
            bool saveToFile(const char* filename, std::string fileFormat = "csv");
            bool loadFromFile(const char* filename);
            bool searchStr(std::string str);
            
            void printHeader(bool breakLine);
            void show(bool breakLine);
            Media *clone();

            // Getters
            bool getColor();

            // Setters
            void setColor(bool newColor);
            void setAttributes();
            };
}

#endif
