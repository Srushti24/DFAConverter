//
//  NFAConverter.cpp
//  DFAConverter
//
//  Created by Srushti Desai on 1/6/24.
//

#include "NFAConverter.hpp"

NFAConverter::NFAConverter(std::string expression):m_expression(expression), m_stateNumber(0)
{
    
}

NFAConverter::~NFAConverter()
{
    
}

void NFAConverter::convertExpression()
{
    for(int i=0;i <m_expression.size(); i++)
    {
        if(m_expression[i] != '*' && m_expression[i] != '(' && m_expression[i] != ')' && m_expression[i] != '|'  && m_expression[i] != '%')
        {
            push(m_expression[i]);
        }
        else if(operands.empty())
        {
            operands.push(m_expression[i]);
        }
        else if(m_expression[i] == ')')
        {
            if(!operands.empty())
            {
                while(!operands.empty() && operands.top() != '(')
                {
                    char op = operands.top();
                    operands.pop();
                }
            }
        }
        else
        {
            if(!operands.empty())
            {
                
                while(!operands.empty() && priority(m_expression[i]) < priority(operands.top()))
                {
                    
                }
            }
        }
    }
}

void NFAConverter::push(char& input)
{
    State state1(m_stateNumber);
    m_stateNumber++;
    State state2(m_stateNumber);
    state1.m_transitions.insert(std::pair<char, State>(input, state2));
    std::deque<State> stateTable;
    stateTable.push_back(state1);
    stateTable.push_back(state2);
    m_stateStack.push(stateTable);
    m_stateStack.push(stateTable);
}

void NFAConverter::Union()
{
    std::deque<State> s1 = m_stateStack.top();
    m_stateStack.pop();
    std::deque<State> s2 = m_stateStack.top();
    m_stateStack.pop();
    
    State start(m_stateNumber++);
    State end(m_stateNumber++);
    start.m_transitions.insert(std::pair<char, State>('0', s1.front()));
    start.m_transitions.insert(std::pair<char, State>('0', s2.front()));
    s1.back().m_transitions.insert(std::pair<char, State>('0', end));
    s2.back().m_transitions.insert(std::pair<char, State>('0', end));
    s1.push_back(end);
    s1.push_front(start);
    m_stateStack.push(s1);
    
}

void NFAConverter::Compact()
{
    std::deque<State> s1 = m_stateStack.top();
    m_stateStack.pop();
    std::deque<State> s2 = m_stateStack.top();
    m_stateStack.pop();
    s2.back().m_transitions.insert(std::pair<char, State>('0', s1.front()));
    s2.push_back(s1.front());
    s2.push_back(s1.back());
    m_stateStack.push(s2);
    
}

void NFAConverter::Star()
{
    std::deque<State> s1 = m_stateStack.top();
    m_stateStack.pop();
    State start(m_stateNumber++);
    State end(m_stateNumber++);
    start.m_transitions.insert(std::pair<char, State>('0', s1.front()));
    s1.back().m_transitions.insert(std::pair<char, State>('0', end));
    s1.back().m_transitions.insert(std::pair<char, State>('0', s1.front()));
    start.m_transitions.insert(std::pair<char, State>('0', end));
    s1.push_front(start);
    s1.push_back(end);
    m_stateStack.push(s1);
}



int NFAConverter::priority(char& operand)
{
    switch(operand)
    {
        case '*':
            return 1;
        case '%':
            return 2;
        default:
            return 3;
    }
}
