#include "utils.h"

namespace myUtils{
    std::string toLowerCase(std::string str){
        std::string lowerStr(str.length(), 'X'); // allocating space to string
        std::transform(str.begin(), str.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
}

}