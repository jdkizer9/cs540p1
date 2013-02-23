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
    class Input {
    public:
        Input(const char *, const size_t);
        char get_char();
        const char peek() const;
        size_t get_pos() const;
        const char * get_abs_pos() const;
        //index operator
        char operator[](size_t) const;
        
        //simulates reading input until char found
        //returns characters in string
        String readUnitl(char);
        
        ~Input();
    private:
        String s;
        size_t pos;
    };
    
}

#endif /* defined(__XML_Parser__Input__) */
