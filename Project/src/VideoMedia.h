#ifndef _VIDEO_MEDIA_H
#define _VIDEO_MEDIA_H

#include "Media.h"

namespace myMedia{
        class VideoMedia : public Media{

            protected:
            std::string HouseProduction;
            int Duration;

            public:
            // constructors
            VideoMedia();
            VideoMedia(const char* filename);
            VideoMedia(int id, std::string Title, std::string Author,
                       std::string Date, int Quantity,
                       std::string HouseProduction, int Duration);

            // Methods
            virtual bool saveToFile(const char* filename, std::string fileFormat);   
            virtual bool searchStr(std::string str);
            virtual void printHeader(bool breakLine = true);
            virtual void show(bool breakLine = true);
            virtual Media *clone();

            // Getters
            std::string getHouseProduction();
            int getDuration();

            // Setters
            void setHouseProduction(std::string newHouseProduction);
            void setDuration(int newDuration);
            };
}

#endif
