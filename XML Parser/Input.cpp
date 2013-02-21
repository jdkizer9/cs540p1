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

using namespace xml;

Input::Input(const char *s, const size_t l) : buf(s), size(l), pos(0) {}


//upgrades:
//check for NULL character ('\0') and throw exception if one occurs
//that way '\0' can be returned from this function to denote
//that the input has completed
char
Input::get_char() {
    if (pos == size) {
        return '\0';
    } else {
#ifdef DEBUG
        printf("%c",buf[pos]);
#endif
        return buf[pos++];
    }
}

size_t
Input::get_pos() {
    return pos;
}
