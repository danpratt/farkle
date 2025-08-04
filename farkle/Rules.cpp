#include "Rules.h" 
#include <iostream>  
#include <fstream>  

void Rules::displayRulesFile() const  
{  
    std::ifstream file(rulesFilePath);  
    if (file.is_open())  
    {  
        std::string line;  
        while (std::getline(file, line))  
        {  
            std::cout << line << std::endl;  
        }  
        file.close();  
    }  
    else  
    {  
        std::cerr << "Unable to open rules file: " << rulesFilePath << std::endl;  
    }  
}
