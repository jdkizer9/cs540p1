//
//  Parser.hpp
//  XML Parser
//
//  Created by James Kizer on 2/18/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#ifndef __XML_Parser__Parser__
#define __XML_Parser__Parser__

#include "Element.hpp"
#include "String.hpp"
#include "Input.hpp"
#include <stack>
#include <unordered_map>
#include <cstring> //Is this needed?

namespace xml {
    class Parser {
    public:
        Parser(); // Must be able to create one.
        const Element *parse(const char *doc, size_t sz);
        
    public:
        
    private:
        
        int processStartTag(Input &);
        
        
        //Stack of elements
        //Used to determine which element is in scope
        //when an element start tag is processed, it is added to the stack
        //when its end tag is processed, it is popped from the stack
        //The most recently processed end tag should ALWAYS match the top of the stack
        //Elements are created by their parent element, only the pointer lives here
//        
//        Example Usage::
//        stack<const String *> myStack2;
//        
//        const String s3("MyString3");
//        const String s4("MyString4");
//        
//        myStack2.push((const String *)(&s3));
//        myStack2.push((const String *)(&s4));
//        
//        cout << "Popping out elements...\n";
//        while (!myStack2.empty())
//        {
//            cout << *(myStack2.top()) << endl;
//            myStack2.pop();
//        }
//        cout << endl;
        std::stack<Element *> elementStack;
        bool foundRoot;
        Element *root;
        
        
        //Associative array of String stacks
        //keys=nmspace prefix, values=stack of URIs associated with each nmspace
        //stacks needed to ensure that the correct URI is in scope
        std::unordered_map<std::string, std::stack<const String>> NSTable;
        
        //associative array of xmlns pairs
        //technically, only a list of NSIs is necessary to live in the element
        //the unordered map:
        //std::unordered_map<std::string, String> xmlnsPairs;
        //can live in the context of the START_TAG processing
        //index into array with nsi, if entry found, multiple defs, throw error
        //After all xmlns added, iterate over AA adding pairs
        //to Parser's NSTable and adding nsi to element's NSI list
        //See sample usage of iteration at:
        //http://www.cplusplus.com/reference/unordered_map/unordered_map/begin/
        
        static const String beginCommentTag;
        static const String endCommentTag;
        static const String beginEndElementTag;
        
        
    };
    int isAlphaNumOrUS(int);
}

#endif /* defined(__XML_Parser__Parser__) */
