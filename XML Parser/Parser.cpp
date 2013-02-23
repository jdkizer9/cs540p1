//
//  Parser.cpp
//  XML Parser
//
//  Created by James Kizer on 2/18/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#include "Parser.hpp"
#include <iostream>
#include <assert.h>

namespace xml {
    
    
    const String beginCommentTag("<!--");
    const String endCommentTag("-->");
    const String beginEndElementTag("<\\");
    
    int isAlphaNumOrUS(int c) {
        if(c == '_')
            return !0;
        else
            return isalnum(c);
    }
    
    
    Parser::Parser() : foundRoot(false), root(nullptr) {
        
    };
    
    //need to be more robust,
    //confirm valid input and element and NSIs
    int Parser::processStartTag(Input &in) {
        
        String eNameString;
        
        int WSOffset = elemString.find(0, isspace);
        int ColOffset = elemString.find(0, ':');
        
        //<e3>
        //simple-case, standalone element
        if ((WSOffset < 0) && (ColOffset < 0)) {
            //all of elemString is the element's name
            e->set_eName(elemString);
            //does not belong to a namespace or bind any new namespaces
            return 0;
        }
        
        //<e3 >
        //Just standalone tag, followed by whitespace
        //all xmlns bindings contain ':'
        if (ColOffset < 0) {
            //strip off whitespace
            e->set_eName(elemString.slice(0, WSOffset));
            //does not belong to a namespace or bind any new namespaces
            return 0;
        }
        
        //<ns2:elem3>
        if (WSOffset < 0) {
            //does not bind any new namespaces, can set nsi and URI now
            String eNSI = elemString.slice(0, ColOffset);
            e->set_nsi(eNSI);
            
            //assert here, something is terribly wrong
            //or could this be invalid input?
            //need to check table for this entry?
            assert(!(NSTable[eNSI].empty()));
            e->set_URI(NSTable[eNSI].top());
            
            std::cout<<eNSI<<" is associated with "<<NSTable[eNSI].top()<<std::endl;
            return 0;
        }
    
        //<ns1:elem2 [...]>
        //if just followed by whitespace, this could be identical
        if (ColOffset < WSOffset) {
            
        }
        
        //<elem2 xmlns:...>
        
        return 0;
    }
    
    
const Element *Parser::parse(const char *doc, size_t sz)
{

    Input in(doc, sz);
    root = new Element();
    char ch;
    int retVal;
    bool readChar = true;
    
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
        if (readChar)
        {
            readChar = false;
            ch = in.get_char();
        }
        if (ch == '\0')
            break;
        
        switch (state)
        {
//            default:
//                std::cout << ch;
//                break;
            case WHITESPACE:
            {
                //if more whitespace, get next char
                if(isspace(ch))
                {
                    //read another char on loop
                    readChar = true;
                    break;
                }
                
                if ( (ch == '<') && !foundRoot ) {
                    state = LEFT_ANGLE;
                }
                //if found a character other than < before root node start tag
                //or a character after root node end tag, return error
                else {
                    if (!foundRoot)
                        std::cerr<<"Invalid input while looking for root element\n";
                    else
                        std::cerr<<"Invalid input at end of stream\n";
                    
                    if (root == nullptr)
                        root = new Element;
                    return root;
                }
                
            }
                break;

            case LEFT_ANGLE:
            {
                if (isAlphaNumOrUS(in[in.get_pos()])) {
                    
                    retVal = processStartTag(in);
                    
                }
                
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
            }
                break;
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
            default:
                assert(false);
        }
        
    }
    
    
    std::cout<<"\nReturing root element from parser\n";
    if (root == nullptr)
        root = new Element;
    return root;

}
    
}