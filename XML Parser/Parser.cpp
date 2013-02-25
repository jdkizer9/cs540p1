//
//  Parser.cpp
//  XML Parser
//
//  Created by James Kizer on 2/18/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#include "Parser.hpp"
#include <deque>
#include <iostream>
#include <assert.h>

namespace xml {
    
    
    const String beginCommentTag("<!--");
    const String endCommentTag("-->");
    const String beginEndElementTag("<\\");
    const String xmlnsTag("xmlns:");
    
    
    Parser::Parser() : foundRoot(false), root(nullptr) {
        
    };
    
    //need to be more robust,
    //confirm valid input and element and NSIs
    //&in pointing at first char after '<'
    Element *Parser::processStartTag(Input &in) {
        
        Element *e = new Element;
        String tmpString;
        char pk;
        
        
        //properly formatted Element Start Tags will be in the following format:
        //regexp = <([a-z|A-Z|'_']+:)?[a-z|A-Z|'_']+(\s+(xmlns:[a-z|A-Z|'_']+="string")*\s*>
        
        //Step 1:
        //Read Unil a character is found thats not a valid NSI or Name char
        //This provides either:
        //a)NSI in the case of ':'
        //b)Element name in the case of whitespace or '>'
        //c)invalid input in the case of anything else
        
        tmpString = in.readUnitl(notAlphaNumOrUS);
        std::cout<<"Found tmpString="<<tmpString<<std::endl;
        //pk = in.peek();
        if ( in.peek() == ':') {
            e->nsi = tmpString;
        } else if ( in.peek() == '>' || isspace(in.peek())){
            e->eName = tmpString;
        } else {
            std::cerr << "Invalid input while processing start tag 1"<<std::endl;
            delete e;
            return nullptr;
        }
        
        //if NSI was just found, get element name
        if ( in.peek() == ':') {
            tmpString = in.readUnitl(notAlphaNumOrUS);
            //pk = in.peek();
            if ( in.peek() == '>' || isspace(in.peek())){
                e->eName = tmpString;
            } else {
                std::cerr << "Invalid input while processing start tag 2"<<std::endl;
                delete e;
                return nullptr;
            }
        }
        
        //at this point, we have successfully processed the NSI(optional)
        //and the element name.
        //if pk is whitespace, enter loop that processes
        //namespace bindings
        
        //create a local table for binding resolutions
        //this will make it easy to check for duplicate NSIs in the element
        //std::unordered_map<std::string, String> xmlnsPairs;
        //Should this come off the heap??
        std::unordered_map<const String, String, std::hash<std::string>> xmlnsPairs;
        
        while (isspace(in.peek())) {
            //ignore all whitespace
            in.readUnitl(notspace);
            
            //if '>' found, tag is over, break
            if (in.peek() == '>')
                break;
            
            //all NS bindings must start with 'xmlns:'
            //therefore, 'xmlns:' must be at the current input position
            //otherwise, invalid input
            if (in.find(0, xmlnsTag) != 0) {
                std::cerr << "Invalid input while processing start tag 3"<<std::endl;
                delete e;
                return nullptr;
            }
            
            //advance input position to eat xmlns
            in+=sizeof("xmlns:")-1;
            tmpString = in.readUnitl(notAlphaNumOrUS);
            String nsibind;
            String uribind;
            if ( in.get_char() == '=') {
                nsibind = tmpString;
            } else {
                std::cerr << "Invalid input while processing start tag 4"<<std::endl;
                delete e;
                return nullptr;
            }
            //ensure next char is "'
            if ( in.get_char() != '\"') {
                std::cerr << "Invalid input while processing start tag 5"<<std::endl;
                delete e;
                return nullptr;
            }
            //read URI, stop at "
            //check that the current char is ", then
            //check that the next char in the input stream
            //(need to iterate the pointer) is either '>' or space
            tmpString = in.readUnitl('\"');
            if ( in.get_char() != '\"') {
                std::cerr << "Invalid input while processing start tag 6"<<std::endl;
                delete e;
                return nullptr;
            }
            pk = in.peek();
            if ( in.peek() == '>' || isspace(in.peek())) {
                uribind = tmpString;
            } else {
                std::cerr << "Invalid input while processing start tag 7"<<std::endl;
                delete e;
                return nullptr;
            }
            
            //this binding has already been defined, return an error
            if (!xmlnsPairs[nsibind].isEmpty()) {
                std::cerr << "Invalid input while processing start tag 8"<<std::endl;
                delete e;
                return nullptr;
            }
            
            
            xmlnsPairs[nsibind] = uribind;
        }
        
        e->definedNSIs = new std::deque<String>;
        assert(NSTable != nullptr);
        for ( auto it = xmlnsPairs.begin(); it != xmlnsPairs.end(); ++it ) {
            std::cout<<"Adding Binding to NSTable: NSI=\'"<<it->first<<"\', URI=\'"<<it->second<<"\'\n";
            (*NSTable)[it->first].push(it->second);
            e->definedNSIs->push_front(it->first);
        }

        
        //we should now have processed our entire tag
        pk = in.peek();
        assert(pk == '>');
        
        //we have added all the defined namespace bindings
        //now we finally have enough information to resolve our
        //current element's namespace, if a nsi was provided
        
        if (!e->nsi.isEmpty()) {
            //if the NSI has not been bound to anything,
            //flag an error
            if ((*NSTable)[e->nsi].empty()) {
                std::cerr << "Invalid input while processing start tag 8"<<std::endl;
                delete e;
                return nullptr;
            }
            //Otherwise, resolve the namespace
            e->URI = (*NSTable)[e->nsi].top();
        }
        
        
        //Now that we have successfully created an element,
        //We need to decide where to store it.
        //If we have not found the root element, we must have just processed it
        if (!foundRoot) {
            //do some assertions
            assert(root == nullptr);
            assert(elementStack != nullptr);
            assert(elementStack->empty() == true);
            foundRoot = true;
            root = e;
        } else {
            //Not the root element, the element at the top of the
            //element stack is the parent, add there
            //do some assertions
            assert(root != nullptr);
            assert(elementStack->empty() != true);
            Element *parent = elementStack->top();
            parent->addChild(e);
        }
        //push the new element to the top of the element stack
        elementStack->push(e);
        e->PrintElement();       
        
        return e;
    }
    
    int Parser::processEndTag(Input &in)
    {
        
        assert(in.peek() == '/');
        //should now be pointing to the first char of the
        //elem name / NSI
        in+=1;
        
        assert(!elementStack->empty());
        //the element on the top of the element stack MUST
        //be the element we are processing, and it must
        //have the same NSI
        Element *e = elementStack->top();
        
        //Step 1:
        //Read Unil a character is found thats not a valid NSI or Name char
        //This provides either:
        //a)NSI in the case of ':'
        //b)Element name in the case of whitespace or '>'
        //c)invalid input in the case of anything else
        
        String tmpString = in.readUnitl(notAlphaNumOrUS);
        std::cout<<"Found tmpString="<<tmpString<<std::endl;
        //pk = in.peek();
        if ( in.peek() == ':') {
            if (e->nsi != tmpString) {
                std::cerr << "End Tag NSI does not match the current element's NSI"<<std::endl;
                return -1;
            }
        } else if ( in.peek() == '>' || isspace(in.peek())){
            if (e->eName != tmpString) {
                std::cerr << "End Tag Name does not match the current element's Name"<<std::endl;
                return -1;
            }
        } else {
            std::cerr << "Invalid input while processing end tag 1"<<std::endl;
            return -1;
        }
        
        //if NSI was just found, get element name
        if ( in.peek() == ':') {
            tmpString = in.readUnitl(notAlphaNumOrUS);
            //pk = in.peek();
            if ( in.peek() == '>' || isspace(in.peek())){
                if (e->eName != tmpString) {
                    std::cerr << "End Tag Name does not match the current element's Name"<<std::endl;
                    return -1;
                }
            } else {
                std::cerr << "Invalid input while processing end tag 2"<<std::endl;
                return -1;
            }
        }
        //based on control flow, the current char should be either
        // '>' or space
        assert(in.peek() == '>' || isspace(in.peek()));
        
        //handle interpunct
        in.readUnitl(notspace);
        
        if (in.peek() == '>') {
            std::cerr << "Invalid input while processing end tag 3"<<std::endl;
            return -1;
        }
        
        //we are now assured that we have valid input.
        //cleanup element
        //1) for each item in definedNSIs, pop the stack for the NSI
        //   in NSTable
        //2) pop the element off the element stack
        
        if (!e->definedNSIs->empty()) {
            for ( auto it = e->definedNSIs->begin(); it != e->definedNSIs->end(); ++it )
            {
                //guarantee that this exists
                assert(!(*NSTable)[*it].empty());
                (*NSTable)[*it].pop();
            }
        }
        assert(e->definedNSIs->empty());
        elementStack->pop();
        
        
        //input stream in a known state
        assert(in.peek() == '>');
        return 0;
    }
    
    
    void Parser::parser_init(){
        
        assert(foundRoot == false);
        assert(elementStack == nullptr);
        assert(NSTable == nullptr);
        
        if (root != nullptr) {
            
            //it is not our responsibilty to delete root
            //the user may still be using this
            //delete root;
            root = nullptr;
        }
        
        elementStack = new std::stack<Element *>;
        NSTable = new std::unordered_map<const String, std::stack<const String>, std::hash<std::string>>;
        
    }
    
    void Parser::parser_cleanup() {
        
        
        foundRoot = false;
        
        if (elementStack != nullptr)
        {
            delete elementStack;
            elementStack = nullptr;
        }
        
        if (NSTable != nullptr)
        {
            delete NSTable;
            NSTable = nullptr;
        }
        
    }
const Element *Parser::parse(const char *doc, size_t sz)
{

    Input in(doc, sz);
    char ch;
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
    
    parser_init();
    
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
                    state = END;
                }
                
            }
                break;

            case LEFT_ANGLE:
            {
                //new element start tag
                if (isAlphaNumOrUS(in.peek())) {
                    
                    Element *newElement = processStartTag(in);
                    if (newElement == nullptr){
                        state = END;
                        break;
                    }
                                        
                    assert(newElement == elementStack->top());
                    assert(in.peek() == '>');
                }
                
                //element end tag
                else if (in.peek() == '/') {
                 
                    int err = processEndTag(in);
                    if (err != 0) {
                        state = END;
                        break;                        
                    }
                    assert(in.peek() == '>');
                }
                
                //comment
            
                
                
                
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
    
    //do parser cleanup
    parser_cleanup();
    
    std::cout<<"\nReturing root element from parser\n";
    if (root == nullptr)
        root = new Element;
    return root;

}
    
}