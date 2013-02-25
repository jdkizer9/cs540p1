//
//  String.h
//  XML Parser
//
//  Created by James Kizer on 2/18/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#ifndef __XML_Parser__String__
#define __XML_Parser__String__

#include <string>

namespace xml{
    class String {
        //API
    public:
        // Copy constructor.
        String(const String &);
        // Conversion to std::string.
        operator std::string() const;
        // Assignment.
        String &operator=(const String &);
        
        //"Internal" Public Interface
    public:
        String();
        String(const char *, int);
        String(const char *);
        void Print(std::ostream &) const;

        String slice(int, int);
        
        //compares first len bytes
        int compare(const char *) const;
        int compare(const String &) const;
        
        //find functions
        //return the offset from a given offset in the String
        //overload to accept char, int(*fp)(int), or const char *
        //to accept built-in search functions (e.g., isalpha)
        //return -1 in case of not being able to find it
        //return -2 in case where offset >= len
        int find(int, char) const;
        int find(int, int(*)(int)) const;
        int find(int, const String &) const;
        
        //returns reference to a string from
        //offset to first instance of char
        //String &readUntil(int, char) const;
        
        //provide String validity checks
        bool isEmpty() const;
        
        //ensures that every char is valid according to input function
        bool isValid(int(*)(int)) const;
        
        
        //index operator
        char operator[](size_t) const;
        
        
        
        ~String();
        
    protected:
        //accessor
        const char *get_ptr() const;
        int get_len() const;
        
    private:
        const char *ptr;
        int len;
    };
    
    
//}
//using namespace xml;
// Comparison with std::string.
bool operator==(const std::string &, const String &);
bool operator==(const String &, const std::string &);
bool operator!=(const std::string &, const String &);
bool operator!=(const String &, const std::string &);
// Comparison with C string.
// These comparisons only work for the first len bytes
bool operator==(const char *, const String &);
bool operator==(const String &, const char *);
bool operator!=(const char *, const String &);
bool operator!=(const String &, const char *);
    
bool operator==(const String &, const String &);
bool operator!=(const String &, const String &);
    
// Output operator
std::ostream &operator<<(std::ostream &, const String &);
    
    
class StringHashFunction {
public:
    ::std::size_t operator ()(const String &s) const;
};
class StringEqual {
public:
    bool operator ()(const String &a, const String &b) const;
};

}




#endif /* defined(__XML_Parser__String__) */
