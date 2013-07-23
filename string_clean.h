#ifndef STRING_CLEAN_H
#define STRING_CLEAN_H

#include <string>
#include <vector>
#include <sstream>


namespace mos {


void split(const std::string& inString, std::vector<std::string>* store,
           const char* delimiter=",");

/// in-place strip terminal whitespace
void strip(std::string* inString);
void stripEnd(std::string* inString);
void stripBegin(std::string* inString);

template <typename T>
std::string convertToString(T inValue)
{
    std::stringstream ss;
    ss << inValue;
    return ss.str();

}

//                std::stringstream inValue;
//                inValue << (*iter)[k-1];
//                unsigned int typeId;
//                inValue >> typeId;


} //namespace

#endif      // "STRING_CLEAN_H"
