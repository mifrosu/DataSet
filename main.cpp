#include <iostream>
#include "data_set.h"
#include "string_clean.h"

/**
 *
 * ID            Molecule        Solubility    Molecular Weight
 * 1             Paracetamol     4.97          151
 * 2             Caffeine        5.05          194
 * 3             Indomethacin    0.4           358
 * 4             Trimethoprim    3.14          290
 *
 * Write C++ code that can combine two datasets based on an ID (or other)
 * column. You may wish to provide the ability to take set unions, differences
 * and intersections. You may also wish to think about how to combine rows that
 * have the same ID but have different columns.
 */

int main()
{

    std::string test = "Hi\tthere";
    std::vector<std::string> testVector;
    mos::split(test, &testVector);
    std::cout << "Hello, World!" << std::endl;
    std::cout << testVector[0] << " " << testVector[1] << std::endl;
    return 0;
}
