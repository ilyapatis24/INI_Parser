#include "Parser.h"

Parser::Parser(const std::string& filename) : filename_{ filename }
{
    std::ifstream file(filename_);

    if (!file.is_open())
    {
        throw std::runtime_error("File opening error: " + filename_);
    }

    while (std::getline(file, line_))
    {
        if (line_.empty() || line_[0] == ';')
        {
            ++lineNumber_;
            continue;
        }

        if ((line_[0] == '[') && (line_[line_.length() - 1] == ']'))
        {
            ++lineNumber_;
            currentSection_ = line_.substr(1, line_.length() - 2);
        }
        else
        {
            ++lineNumber_;
            std::istringstream iss(line_);

            if (std::getline(iss, key_, '='))
            {   
                if (std::getline(iss, value_))
                {
                    size_t pos = value_.find(';');  

                    if (pos != std::string::npos) 
                    {
                        value_ = value_.substr(0, pos); 
                    }
                    fileData_[currentSection_][key_] = value_;
                }
            }
        }
    }
    file.close();
}

std::string Parser::getStringValue(const std::string currentSection, const std::string key, const int lineNumber)
{
    std::map<std::string, std::map<std::string, std::string>>::iterator it1 = fileData_.find(currentSection);
    if (it1 == fileData_.end())
    {
        printMap(currentSection, key);
        throw std::runtime_error(currentSection + " not found");
    }
    else
    {
        std::map<std::string, std::string>& innerMap = fileData_[currentSection];
        if (!innerMap.count(key))
        {
            printMap(currentSection, key);
            throw std::runtime_error("");
        }
    }
    return fileData_[currentSection][key];
}

void Parser::printMap(const std::string currentSection, const std::string key)
{
    std::cout << "There are no key: " + key + ", in the section " + currentSection << std::endl;
    std::cout << "There are has: " << std::endl;

    const std::map<std::string, std::string>& innerMap = fileData_[currentSection];
    for (auto innerIt = innerMap.begin(); innerIt != innerMap.end(); ++innerIt)
    {
        const std::string& innerKey = innerIt->first;
        std::cout << innerKey << std::endl;
    }
}