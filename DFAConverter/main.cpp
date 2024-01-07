//
//  main.cpp
//  DFAConverter
//
//  Created by Srushti Desai on 12/28/23.
//

#include <iostream>
#include "NFAConverter.hpp"

bool isInputCharacter(char input)
{
    if(input!= '*' && input!= '(' && input!= ')' && input!= '|'  && input != ' ')
    {
        return true;
    }
    return false;
}

std::string convertToString(std::string& expression)
{
    std::string str;
    for(int i=0;i <expression.size()-1; i++)
    {
        char a = expression[i];
        char b = expression[i+1];
        str += a;
        if(isInputCharacter(a) || a == ')' || a == '*')
        {
            if(b == '(' || isInputCharacter(b))
            {
                str += '%';
            }
        }
    }
    str += expression[expression.size()-1];
    return str;
}

int main(int argc, const char * argv[]) {
    std::string temp ="a(bc)*";
    std::string temp1 ="abc(d|c)";
    std::cout << convertToString(temp) << "\n";
    std::cout << convertToString(temp1);
    
}





