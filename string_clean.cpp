#include "string_clean.h"

namespace mos {

void split(const std::string& inString, std::vector<std::string>* store,
           const char* delimiter)
{
    if (inString.size() == 0) {
        return;
    }

    std::string::size_type i = 0;
    std::string::size_type j = inString.find(delimiter);

    if (j== std::string::npos)  // no delimiter found
    {
        store->push_back(inString);
    }

    while (j != std::string::npos) {
        std::string temp = inString.substr(i, j-i);
        strip(&temp);
        store->push_back(temp);
        i = ++j;
        j = inString.find(delimiter, j);

        if (j == std::string::npos) {
            temp = inString.substr(i, inString.length());
            strip(&temp);
            store->push_back(temp);
        }
    }
}


void stripEnd(std::string* inString)
{
    if (inString->empty()) {
        return;
    }

    std::string::iterator iter = inString->end()-1; // move iter to last char

    while (iter != inString->begin() && isspace(*iter)) {
        --iter;
    }

    if (!isspace(*iter) && iter != inString->end()) {
        ++iter;
    }

    if (isspace(*iter) && iter != inString->end()) {
        inString->erase(iter, inString->end());
    }
}


void stripBegin(std::string* inString)
{
    if (inString->empty()) {
        return;
    }

    std::string::iterator iter = inString->begin();
    while (iter != inString->end() && isspace(*iter)) {
        ++iter;
    }

    if (!isspace(*iter) && iter != inString->begin()) {
        --iter;
    }

    if (isspace(*iter)) {
        inString->erase(inString->begin(), iter+1);
    }
}


void strip(std::string* inString)
{
    if (inString->empty())
        return;

    // trim end
    stripEnd(inString);
    stripBegin(inString);
}

}  // namespace

