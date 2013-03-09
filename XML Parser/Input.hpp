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
#include <assert.h>

namespace xml {
    class Input : public String {
    public:
        Input(const char *, const size_t);
        char get_char();
        inline const char peek() const {
            assert(pos <= (size_t)get_len());
            return this->get_ptr()[pos];
        };
        inline size_t get_pos() const {return pos;};
        const char * get_abs_pos() const;
        size_t left() const;
        
        
        Input &operator+=(const size_t);
        Input &operator-=(const size_t);
        
        
        //simulates reading input until char found
        //returns characters in string
        void readUnitl(char, String &);
        void readUnitl(int(*)(int), String &);
        void readUnitl(const String &, String &);
        
        void PrintNext5Chars();
        
        ~Input();
    
//    inherrited from String
//    protected:
//        const char *get_ptr() const;
//        int get_len() const;
        
    private:
        void readUntilHelper(size_t, String &);
        size_t pos;
    };
    
}

#endif /* defined(__XML_Parser__Input__) */
