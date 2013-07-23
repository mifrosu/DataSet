
#include "data_set.h"
#include "string_clean.h"
#include <fstream>
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


template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    // convenience function to display vectors
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
    return os;
}

class myexception: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Syntax error: Too many operation flags were set";
  }
} tooManyOperations;

void verifyConditions(bool& operationFlag,
                      const std::vector<std::string>& inputFileList);

void runner(std::vector<std::string>& inputFileList,
            std::string& outputFile,
            std::string& columnName,
            unsigned int operationType, const char* delimiter=",");


int main(int ac, char* av[])
{
    try {
        enum operationOption { MERGE, DIFFERENCE, INTERSECTION, UNION };

        std::string outputFile;
        std::vector<std::string> inputFileList;
        std::string columnName;
        std::string delimiter=",";
        bool isOperationSet = false;
        unsigned int operationType = -1;

        boost::program_options::options_description
                description("Allowed options");
        description.add_options()
                ("help,h", "Show this message")
                ("input-file,i",
                 boost::program_options::value<std::vector<std::string> >(
                     &inputFileList),
                 "input file(s)")
                ("delimiter,d",
                 boost::program_options::value<std::string>(&delimiter),
                 "delimiter character")
                ("out,o",
                 boost::program_options::value<std::string>(&outputFile),
                 "output file")
                ("merge,M",
                 boost::program_options::value<std::string>(&columnName),
                 "merge input files on column name")
                ("difference,D",
                 boost::program_options::value<std::string>(&columnName),
                 "generate difference set from input files on column name")
                ("intersection,I",
                 boost::program_options::value<std::string>(&columnName),
                 "generate intersection set from input files on column name")
                ("union,U",
                 boost::program_options::value<std::string>(&columnName),
                 "generate union set from input files on column name")
                ;

        boost::program_options::positional_options_description pos_desc;
        pos_desc.add("input-file", -1);

        boost::program_options::variables_map vm;
        boost::program_options::store(
                    boost::program_options::command_line_parser(ac,av).
                    options(description).positional(pos_desc).run(), vm);
        boost::program_options::notify(vm);

        if (vm.count("help")) {
            std::cout << std::endl;
            std::cout << "Usage: options_description [options]\n";
            std::cout << description;
            std::cout << std::endl;
            return 0;
        }

        if (vm.empty()) {
            std::cout << "\nSyntax error\n";
            std::cout << description << std::endl;
            return 1;
        }

        if (inputFileList.empty()) {
            std::cout << "\nSyntax error: One or two input files are required."
                         << std::endl;
            std::cout << description <<std::endl;
        }

        if (inputFileList.size() > 2) {
            std::cout << "Warning: only the first two entered input files, "
                      << inputFileList[0] << " and " << inputFileList[1]
                      << "will be processed." << std::endl;
        }

        if (vm.count("merge")) {
            verifyConditions(isOperationSet, inputFileList);
            operationType = MERGE;
        }
        if (vm.count("difference")) {
            verifyConditions(isOperationSet, inputFileList);
            operationType = DIFFERENCE;
        }
        if (vm.count("intersection")) {
            verifyConditions(isOperationSet, inputFileList);
            operationType = INTERSECTION;
        }
        if (vm.count("union")) {
            verifyConditions(isOperationSet, inputFileList);
            operationType = UNION;
        }

        runner(inputFileList, outputFile, columnName, operationType,
               delimiter.c_str());
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}


void runner(std::vector<std::string> &inputFileList, std::string &outputFile,
            std::string &columnName, unsigned int operationType,
            const char* delimiter)
{
    enum operationOption { MERGE, DIFFERENCE, INTERSECTION, UNION };
    mos::DataSet dataSet1;
    mos::DataSet dataSet2;

    mos::DataSet outputSet;

    dataSet1 = mos::DataSet(inputFileList[0], delimiter);
    if (inputFileList.size() > 1) {
        dataSet2 = mos::DataSet(inputFileList[1], delimiter);
    }



    switch (operationType) {
    case MERGE:
        outputSet = dataSet1.merge(dataSet2, columnName);
        break;
    case DIFFERENCE:
        outputSet = dataSet1.differenceSet(dataSet2,columnName);
        break;
    case INTERSECTION:
        outputSet = dataSet1.intersectionSet(dataSet2, columnName);
        break;
    case UNION:
        outputSet = dataSet1.unionSet(dataSet2, columnName);
        break;
    default:
        break;
    }

    if (!outputFile.empty() && outputSet.getSize() != 0) {
        std::ofstream outFileStream(outputFile.c_str());
        if (!outFileStream) {
            std::cout << "Error creating " << outputFile << std::endl;
        }
        outputSet.displaySet(outFileStream, delimiter);
    }
    else if (outputFile.empty() && outputSet.getSize() != 0) {
        outputSet.displaySet(std::cout, delimiter);
    }
    else {
        if (dataSet1.getSize() != 0) {
            dataSet1.displaySet(std::cout, delimiter);
        }
        if (dataSet2.getSize() != 0) {
            dataSet2.displaySet(std::cout, delimiter);
        }
    }
}

void verifyConditions(bool &operationFlag,
                      const std::vector<std::string> &inputFileList)
{
    if (operationFlag == false &&
            inputFileList.size() >= 2) {
        operationFlag = true;
    }
    else  {
        throw tooManyOperations;
    }
}
