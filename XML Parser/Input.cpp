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
#include <assert.h>

using namespace xml;

Input::Input(const char *s, const size_t l) : String(s, (int)l), pos(0) {
    //std::cout << "Constructing Input" <<std::endl;
}


//upgrades:
//check for NULL character ('\0') and throw exception if one occurs
//that way '\0' can be returned from this function to denote
//that the input has completed
char
Input::get_char() {
    
    char c = this->get_ptr()[pos];

    if (c != '\0')
        pos++;
    
    return c;
}

const char Input::peek() const {
    assert(pos <= get_len());
    return this->get_ptr()[pos];
}

size_t
Input::get_pos() const {
    return pos;
}

const char * Input::get_abs_pos() const {
    return this->get_ptr()+pos;
}

int Input::left() const {
    assert(get_len()>=pos);
    return get_len()-(int)pos;
}

Input &Input::operator+=(const size_t i) {
    pos+=i;
    if (pos > get_len())
        pos = get_len();
    return *this;
}

Input &Input::operator-=(const size_t i) {
    assert(i>pos);
    if (i >= pos)
        pos = 0;
    else
        pos = pos-=i;
    return *this;
}


String Input::readUnitl(char c) {
    int offset = find((int)pos, c);
    //the expected character was not found,
    //set pos = len and return String to end
//    if (offset == -1) {
//        const char *tmpPos = this->get_len()+this->get_ptr();
//        pos = this->get_len();
//        offset = 0;
//        return String(tmpPos, offset);
//    } else {
//        const char *tmpPos = pos+this->get_ptr();
//        pos += offset;
//        return String(tmpPos, offset);
//    }
    
    return readUntilHelper(offset);
}

String Input::readUnitl(int(*fp)(int)) {
    int offset = find((int)pos, fp);
//    const char *tmpPos = pos+this->get_ptr();
//    pos += offset;
//    return String(tmpPos, offset);
    return readUntilHelper(offset);
}

String Input::readUnitl(const String &s) {
    int offset = find((int)pos, s);
    return readUntilHelper(offset);    
}

String Input::readUntilHelper(int offset) {
    //the expected character was not found,
    //set pos = len and return String to end
    if (offset == -1) {
        const char *tmpPos = this->get_len()+this->get_ptr();
        pos = this->get_len();
        offset = 0;
        return String(tmpPos, offset);
    } else {
        const char *tmpPos = pos+this->get_ptr();
        pos += offset;
        return String(tmpPos, offset);
    }
}

void Input::PrintNext5Chars() {
    std::cout << "The next 5 input chars are: \'"<<String(this->get_ptr()+pos, 5)<<"\'"<<std::endl;
}


Input::~Input() {
    
    //std::cout << "Destructing Input" <<std::endl;
}

