#ifndef SPLIT_STRING_H
#define SPLIT_STRING_H

#include <string>
#include <vector>
#include <functional>

namespace mos_dataset {

void split(const std::string& inString, std::vector<std::string>* store,
           char delimiter='\t')
{
    std::string::size_type i = 0;
    std::string::size_type j = inString.find(delimiter);

    while (j != std::string::npos) {
        store->push_back(inString.substr(i, j-i));
        i = ++j;
        j = inString.find(delimiter, j);

        if (j == std::string::npos) {
            store->push_back(inString.substr(i, inString.length()));
        }
    }
}

}

#endif  // SPLIT_STRING_H
