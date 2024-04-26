#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>

enum class Warnings
{
    pointIsFound = 1, dataTypeFalse = -1
};

class Parser
{
private:
    std::map<std::string, std::map<std::string, std::string>> fileData_;
    std::string filename_;
    std::string currentSection_;
    std::string line_;
    std::string key_;
    std::string value_;
    std::string tmpIniDataString_;
    int tmpIniDataInt_ = 0;
    double tmpIniDataDouble_ = 0.0;
    float tmpIniDataFloat_ = 0.0;
    int lineNumber_ = 0;

    std::string getStringValue(const std::string currentSection, const std::string key, const int lineNumber);
    void printMap(const std::string currentSection, const std::string key);

public:
    Parser(const std::string& filename);

    template <class T>
    T getValue(const std::string currentSection, const std::string key)
    {
        static_assert(sizeof(T) == static_cast<int>(Warnings::dataTypeFalse), "Invalid data type");
    }

    template <>
    std::string getValue(const std::string currentSection, const std::string key)
    {
        return getStringValue(currentSection, key, lineNumber_);
    }

    template <>
    int getValue(const std::string currentSection, const std::string key)
    {
        tmpIniDataString_ = getStringValue(currentSection, key, lineNumber_);

        if (tmpIniDataString_.find(".") == static_cast<size_t>(Warnings::pointIsFound))
        {
            std::cout << "Warning. Type of this value double or float converted to ini !!!" << std::endl;
        }

        try
        {
            tmpIniDataInt_ = std::stoi(tmpIniDataString_);
        }
        catch (const std::out_of_range& ex)
        {
            throw ex;
        }
        catch (const std::invalid_argument& ex)
        {
            throw ex;
        }
        return tmpIniDataInt_;
    }

    template <>
    double getValue(const std::string currentSection, const std::string key)
    {
        try
        {
            tmpIniDataDouble_ = std::stod(getStringValue(currentSection, key, lineNumber_));
        }
        catch (const std::out_of_range& ex)
        {
            throw ex;
        }
        catch (const std::invalid_argument& ex)
        {
            throw ex;
        }
        return tmpIniDataDouble_;
    }

    template <>
    float getValue(const std::string currentSection, const std::string key)
    {
        try
        {
            tmpIniDataFloat_ = std::stof(getStringValue(currentSection, key, lineNumber_));
        }
        catch (const std::out_of_range& ex)
        {
            throw ex;
        }
        catch (const std::invalid_argument& ex)
        {
            throw ex;
        }
        return tmpIniDataFloat_;
    }
};


