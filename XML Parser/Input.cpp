//
//  Input.cpp
//  XML Parser
//
//  Created by James Kizer on 2/19/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#include "Input.hpp"
#ifdef DEBUG
#include <stdio.h>
#endif
#include <iostream>

using namespace xml;

Input::Input(const char *s, const size_t l) : s(s, (int)l), pos(0) {
    //std::cout << "Constructing Input" <<std::endl;
}


//upgrades:
//check for NULL character ('\0') and throw exception if one occurs
//that way '\0' can be returned from this function to denote
//that the input has completed
char
Input::get_char() {
    
    char c = s[pos];

    if (c != '\0')
        pos++;
    
    return c;
}

size_t
Input::get_pos() {
    return pos;
}

Input::~Input() {
    
    //std::cout << "Destructing Input" <<std::endl;
}
