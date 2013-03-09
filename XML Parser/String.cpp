//
//  String.cpp
//  XML Parser
//
//  Created by James Kizer on 2/18/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#include "String.hpp"
#include <string.h>
#include <iostream>
#include <assert.h>

namespace xml {

    // Copy constructor.
    String::String(const String &s) : ptr(s.ptr), len(s.len) {

    }
    
    // Conversion to std::string.
    String::operator std::string() const {
        return std::string(ptr, (size_t)len);
    }
    
    String::String(const char *p, size_t l) : ptr(p), len(l) {

    }
    
    String::String(const char *p) : ptr(p), len(strlen(p)) {

    }
    
    String::String() : ptr(NULL), len(0) {

    }
    
    // Assignment.
    String &String::operator=(const String &s) {
        ptr = s.ptr;
        len = s.len;
        return *this;
    }
    
    String String::slice(size_t offset, size_t length) const {
        if (length == SIZE_MAX)
            length = len - offset;
        return String(ptr+offset, length);
    }
    
    
    void String::Print(std::ostream &out) const {
        
        out<<std::string(*this);
        //for (int i=0; i<len; i++)
            //out.put(ptr[i]);
        
    }
    
    
    int String::compare(const char *cStr) const {
        return strncmp(cStr, ptr, (size_t)len);
    }
     
    int String::compare(const String &s) const {
        if (s.len != len)
            return -1;
        //return strncmp(s.ptr, ptr, (size_t)len);
        return memcmp(s.ptr, ptr, (size_t)len);
    }
    
    size_t String::find(size_t offset, const char c)  const {
        //boundary checking
        if (offset >= len) {
            assert(false);
            return SIZE_MAX;
        }
        
        //look for c
        for (size_t i=offset; i<len; i++)
            if (ptr[i] == c)
                return i-offset;
        
        //c not found
        return SIZE_MAX;
        
    }
    
    size_t String::find(size_t offset, int(*fp)(int))  const {
        
        //boundary checking
        if (offset >= len) {
            //assert(false);
            return SIZE_MAX;
        }
        
        //look for matching character
        for (size_t i=offset; i<len; i++)
            if (fp(ptr[i]))
                return i-offset;
        
        //c not found
        return SIZE_MAX;
        
    }
    
    size_t String::find(size_t offset, const String &s)  const {
        
        //boundary checking
        if (offset+s.len >= len) {
            //assert(false);
            return SIZE_MAX;
        }
        
        //look for matching String
        for (size_t i=offset; i+s.len<=len; i++)
            if (strncmp(s.ptr, ptr+i, (size_t)s.len) == 0)
                return i-offset;
        
        //c not found
        return SIZE_MAX;
        
    }
    
//    bool String::isEmpty() const {
//        return (len == 0);
//    }
    
    //check for String validity
    bool String::isValid(int (*fp)(int)) const {
        
        if (isEmpty())
            return false;
        for (size_t i=0; i<len; i++) {
            if (!fp(ptr[i]))
                return false;
        }
        return true;
    }
    
//    char String::operator[](size_t i) const {
//        
//        if (i >= (size_t)len) {
//            return '\0';
//        } else {
//            return ptr[i];
//        }
//    }

//    const char *String::get_ptr() const {
//        
//        return ptr;
//    }
//    
//    size_t String::get_len() const {
//        return len;
//    }
    
//    void String::set(const char *p, size_t l) {
//        ptr = p;
//        len = l;
//    }
    
    String::~String() {
//        std::cout << "Destructing String: ";
//        Print(std::cout);
//        std::cout << std::endl;
        //len = 0;
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
    //Could use a public Print member function that returns an ostream
    std::ostream &operator<<(std::ostream &out, const String &S) {
        //out << std::string(S, S.get_len());
        S.Print(out);
        return out;
    }
    
    ::std::size_t StringHashFunction::operator ()(const String &s) const {
        std::hash<std::string> str_hash;
        return str_hash(s);
    }
    
    bool StringEqual::operator ()(const String &a, const String &b) const {
        return a == b;
    }
    



}