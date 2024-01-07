//
//  State.hpp
//  DFAConverter
//
//  Created by Srushti Desai on 12/31/23.
//

#ifndef State_hpp
#define State_hpp

#include <stdio.h>
#include<map>
#include<set>


class State
{
    
public:
    State(int stateNumber);
    ~State();
    int m_stateNumber;
    std::multimap<char, State> m_transitions;
    std::set<State> m_origin;
};
#endif /* State_hpp */
