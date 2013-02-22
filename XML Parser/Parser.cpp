//
//  Parser.cpp
//  XML Parser
//
//  Created by James Kizer on 2/18/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#include "Parser.hpp"
#include "Input.hpp"
#include <iostream>
#include <assert.h>

namespace xml {
    
Parser::Parser(){
        
};
    
    
const Element *Parser::parse(const char *doc, size_t sz)
{

    Input in(doc, sz);
    Element *e = new Element;
    
    enum {
        WHITESPACE = 1,
        LEFT_ANGLE,
        START_TAG,
        END_TAG,
        CONTENT,
        COMMENT,
        END
    } state = WHITESPACE;
    
    while (state != END)
    {        
        char ch = in.get_char();
        
        if (ch == '\0')
            break;
        
        switch (state)
        {
            default:
                //std::cout << ch;
                break;
//            case WHITESPACE:
//            {
//                if (ch == '<') {
//                    printf("Found Left Angle\n");
//                    state = LEFT_ANGLE;
//                } else if (!isspace(ch)) {
//                    assert(false);
//                }
//            }
//                break;
//                
//            case LEFT_ANGLE:
//            {
//                if (ch=='!') {
//                    printf("Found Comment\n");
//                    state = COMMENT;
//                } else if ((ch=='_') || (isalnum(ch))) {
//                    printf("Found START_TAG\n");
//                    state = START_TAG;
//                } else if (ch == '/') {
//                    printf("Found END_TAG\n");
//                    state = END_TAG;
//                }
//            }
//                break;
//                
//            case START_TAG:
//            {
//                if (ch=='>') {
//                    printf("End of START_TAG. Beginning Content.");
//                }
//                
//            }
//                break;
//                
//            case END_TAG:
//            {
//                
//            }
//                break;
//                
//            case CONTENT:
//            {
//                
//            }
//                break;
//                
//            case COMMENT:
//            {
//                
//            }
//                break;
//                
//            default:
//                assert(false);
        }
        
    }
    
    
    std::cout<<"\nReturing root element from parser\n";
    return e;

}
    
}