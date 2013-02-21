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
    public:
        // Copy constructor.
        String(const String &);
        // Conversion to std::string.
        operator std::string() const;
        // Assignment.
        String &operator=(const String &);
        
    public:
        String();
        String(const char *, int);
        
        //compares first len bytes
        int compare(const char *) const;
        int compare(const String &) const;
        
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
}

#endif /* defined(__XML_Parser__String__) */
