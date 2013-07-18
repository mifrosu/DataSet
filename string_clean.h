#ifndef STRING_CLEAN_H
#define STRING_CLEAN_H

#include <string>
#include <vector>


namespace mos {


void split(const std::string& inString, std::vector<std::string>* store,
           const char* delimiter="\t");

/// in-place strip terminal whitespace
void strip(std::string* inString);
void stripEnd(std::string* inString);
void stripBegin(std::string* inString);

} //namespace

#endif      // "STRING_CLEAN_H"
