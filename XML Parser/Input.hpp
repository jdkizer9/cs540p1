//
//  Input.hpp
//  XML Parser
//
//  Created by James Kizer on 2/19/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#ifndef __XML_Parser__Input__
#define __XML_Parser__Input__

#include <cstring>

namespace xml {
    class Input {
    public:
        Input(const char *, const size_t);
        char get_char();
        size_t get_pos();
    private:
        const char *buf;
        const size_t size;
        size_t pos;
    };
}

#endif /* defined(__XML_Parser__Input__) */
