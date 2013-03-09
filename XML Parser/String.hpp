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
        String(const char *, size_t);
        String(const char *);
        void Print(std::ostream &) const;

        String slice(size_t, size_t) const;
        
        //compares first len bytes
        int compare(const char *) const;
        int compare(const String &) const;
        
        //find functions
        //return the offset from a given offset in the String
        //overload to accept char, int(*fp)(int), or const char *
        //to accept built-in search functions (e.g., isalpha)
        //return -1 in case of not being able to find it
        //return -2 in case where offset >= len
        size_t find(size_t, char) const;
        size_t find(size_t, int(*)(int)) const;
        size_t find(size_t, const String &) const;
        
        //returns reference to a string from
        //offset to first instance of char
        //String &readUntil(int, char) const;
        
        //provide String validity checks
        inline bool isEmpty() const {return (len == 0); };
        
        //ensures that every char is valid according to input function
        bool isValid(int(*)(int)) const;
        
        size_t hash1() const;
        size_t hash2() const;
        size_t hash3() const;
        
        
        //index operator
        inline char operator[](size_t i) const {
            return at(i);
        }
        
        inline size_t get_len() const {
            return len;
        };
        
        bool lessThan(const String &) const;
        
        
        inline void set(const char *p, size_t l) {
            ptr = p;
            len = l;
        };
        
        ~String();
        
    protected:
        //accessor
        inline const char *get_ptr() const {
            return ptr;
        };
        
        inline char at(size_t i) const {
            
            if (i >= (size_t)len) {
                return '\0';
            } else {
                return ptr[i];
            }
        }
        
    private:
        const char *ptr;
        size_t len;
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
    
bool operator<(const String &, const String &);
    
// Output operator
std::ostream &operator<<(std::ostream &, const String &);
    
    
class StringHashFunction {
public:
    inline std::size_t operator ()(const String &s) const {return s.hash3();};
};
class StringEqual {
public:
    bool operator ()(const String &a, const String &b) const;
};

}




#endif /* defined(__XML_Parser__String__) */
