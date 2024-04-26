#include "Parser.h"

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");

    try
    {
        Parser parser("test_data.ini");
        std::cout << std::setprecision(5) << std::fixed << std::endl;
        std::cout << parser.getValue<int>("Section1", "var1") << std::endl << std::endl;
        std::cout << parser.getValue<std::string>("Section1", "var2") << std::endl << std::endl;
        std::cout << parser.getValue<double>("Section2", "var1") << std::endl << std::endl;
        std::cout << parser.getValue<float>("Section2", "var1") << std::endl << std::endl;
    }
    catch (const std::runtime_error& ex)
    {
        std::cout << "Error while reading file. " << ex.what() << std::endl;
    }
    catch (const std::out_of_range& ex)
    {
        std::cout << "The string cannot be converted to an ini number. " << ex.what() << std::endl;
    }
    catch (const std::invalid_argument& ex)
    {
        std::cout << "The string cannot be converted to an ini number. " << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Common Error" << std::endl;
    }
    return 0;
}