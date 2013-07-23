
#include "data_set.h"
#include "string_clean.h"
#include <iostream>
#include <algorithm>
#include <boost/program_options.hpp>

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

using namespace boost;

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
    return os;
}

int main(int ac, char* av[])
{
    try {
        std::string outputFile;
        boost::program_options::options_description
                description("Allowed options");
        description.add_options()
                ("help,h", "Show this message")
                ("out,o",
                 boost::program_options::value<std::string>(&outputFile),
                 "output file")
                ("input-file,i",
                 boost::program_options::value<std::vector<std::string> >(),
                 "input file(s)")
                ;

        boost::program_options::positional_options_description pos_desc;
        pos_desc.add("input-file", -1);

        boost::program_options::variables_map vm;
        boost::program_options::store(
                    boost::program_options::command_line_parser(ac,av).
                    options(description).positional(pos_desc).run(), vm);
        boost::program_options::notify(vm);

        if (vm.count("help")) {
            std::cout << "Usage: options_description [options]\n";
            std::cout << description;
            return 0;
        }

        if (vm.count("input-file")) {
            std::cout << "input files are: "
                      << vm["input-file"].as<std::vector<std::string> >()
                      << "\n";
        }

        if (vm.count("out")) {
            std::cout << "the output file is: "
                      << outputFile << "\n";
        }
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << "\n";
        return 1;
    }
    return 0;
}
