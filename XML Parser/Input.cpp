//
//  Input.cpp
//  XML Parser
//
//

#include "Input.hpp"
#ifdef DEBUG
#include <stdio.h>
#endif
#include <iostream>
#include <assert.h>


using namespace xml;

Input::Input(const char *s, const size_t l) : String(s, l), pos(0) {
    //std::cout << "Constructing Input" <<std::endl;
}


//upgrades:
//check for NULL character ('\0') and throw exception if one occurs
//that way '\0' can be returned from this function to denote
//that the input has completed
//char
//Input::get_char() {
//    
//    char c = at(pos);
//
//    if (c != '\0')
//        pos++;
//    
//    return c;
//}

//const char Input::peek() const {
//    assert(pos <= (size_t)get_len());
//    return this->get_ptr()[pos];
//}

//size_t
//Input::get_pos() const {
//    return pos;
//}

const char * Input::get_abs_pos() const {
    return this->get_ptr()+pos;
}

size_t Input::left() const {
    //assert(get_len()>=pos);
    return get_len()-pos;
}

Input &Input::operator+=(const size_t i) {
    pos+=i;
    if (pos > (size_t)get_len())
        pos = (size_t)get_len();
    return *this;
}

Input &Input::operator-=(const size_t i) {
    //assert(i>pos);
    if (i >= pos)
        pos = 0;
    else
        pos-=i;
    return *this;
}


void Input::readUnitl(char c, String &r_s) {
    size_t offset = find(pos, c);
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
    
    readUntilHelper(offset, r_s);
}

void Input::readUnitl(int(*fp)(int), String &r_s) {
    size_t offset = find(pos, fp);
//    const char *tmpPos = pos+this->get_ptr();
//    pos += offset;
//    return String(tmpPos, offset);
    readUntilHelper(offset, r_s);
}

void Input::readUnitl(const String &s, String &r_s) {
    size_t offset = find(pos, s);
    readUntilHelper(offset, r_s);
}

void Input::readUntilHelper(size_t offset, String &r_s) {
    //the expected character was not found,
    //set pos = len and return String to end
    if (offset == SIZE_MAX) {
        const char *tmpPos = this->get_len()+this->get_ptr();
        pos = (size_t)this->get_len();
        offset = 0;
        r_s.set(tmpPos, offset);
    } else {
        const char *tmpPos = pos+this->get_ptr();
        pos += (size_t)offset;
        r_s.set(tmpPos, offset);
    }
}

void Input::PrintNext5Chars() {
    std::cout << "The next 5 input chars are: \'"<<String(this->get_ptr()+pos, 5)<<"\'"<<std::endl;
}


Input::~Input() {
    
    //std::cout << "Destructing Input" <<std::endl;
}

