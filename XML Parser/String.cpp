//
//  String.cpp
//  XML Parser
//
//  Created by James Kizer on 2/18/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#include "String.hpp"
#include <string>
#include <iostream>

namespace xml {

    // Copy constructor.
    String::String(const String &s) : ptr(s.ptr), len(s.len) {
        //std::cout << "Called the copy ctor" << std::endl;
    }
    
    // Conversion to std::string.
    String::operator std::string() const {
        return std::string(ptr, len);
    }
    
    String::String(const char *p, int l) : ptr(p), len(l) {
        //std::cout << "Called the 2 param ctor" << std::endl;
    }
    
    
    // Assignment.
    String &String::operator=(const String &s) {
        //std::cout << "Called the assignment operator" << std::endl;
        ptr = s.ptr;
        len = s.len;
        return *this;
    }
    
    String::String() : ptr(NULL), len(0) {
        //std::cout << "Called the default ctor" << std::endl;
    }
    
    int String::compare(const char *cStr) const {
        return strncmp(cStr, ptr, len);
    }
    
    int String::compare(const String &s) const {
        if (s.len != len)
            return -1;
        return strncmp(s.ptr, ptr, len);
    }
    
    //This could probably be more efficient. Uses conversion from String to string.
    bool operator==(const std::string &stdStr, const String &myStr){
        return (stdStr.compare(myStr) == 0);
    }
    
    bool operator==(const String &myStr, const std::string &stdStr) {
        return (stdStr == myStr);
    }
    
    bool operator!=(const std::string &stdStr, const String &myStr) {
        return !(stdStr == myStr);
    }
    
    bool operator!=(const String &myStr, const std::string &stdStr) {
        return !(stdStr == myStr);
    }
    
    
    bool operator==(const char *cStr, const String &myStr) {
        return (myStr.compare(cStr) == 0);
    }
    
    bool operator==(const String &myStr, const char *cStr) {
        return (cStr == myStr);
    }
        
    bool operator!=(const char *cStr, const String &myStr) {
        return !(cStr == myStr);
    }
    
    bool operator!=(const String &myStr, const char *cStr) {
        return !(cStr == myStr);
    }
    
    bool operator==(const String &s1, const String &s2) {
        return (s1.compare(s2) == 0);
    }
    
    bool operator!=(const String &s1, const String &s2) {
        return !(s1 == s2);
    }
    
    //This could probably be more efficient. Uses conversion from String to string.
    //However, this gets around forcing this to be a friend function for local access.
    std::ostream &operator<<(std::ostream &out, const String &S) {
        out << std::string(S);
        return out;
    }



}