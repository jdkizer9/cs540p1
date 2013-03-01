//
//  Input.hpp
//  XML Parser
//
//  Created by James Kizer on 2/19/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#ifndef __XML_Parser__Input__
#define __XML_Parser__Input__

#include "String.hpp"
#include <cstring>

namespace xml {
    class Input : public String {
    public:
        Input(const char *, const size_t);
        char get_char();
        const char peek() const;
        size_t get_pos() const;
        const char * get_abs_pos() const;
        int left() const;
        
        
        Input &operator+=(const size_t);
        Input &operator-=(const size_t);
        
        
        //simulates reading input until char found
        //returns characters in string
        String readUnitl(char);
        String readUnitl(int(*)(int));
        String readUnitl(const String &s);
        
        void PrintNext5Chars();
        
        ~Input();
    
//    inherrited from String
//    protected:
//        const char *get_ptr() const;
//        int get_len() const;
        
    private:
        String readUntilHelper(int);
        size_t pos;
    };
    
}

#endif /* defined(__XML_Parser__Input__) */
