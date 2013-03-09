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
#include <vector>
#include <cstring> //Is this needed?

namespace xml {
    class Parser {
    public:
        Parser(); // Must be able to create one.
        const Element *parse(const char *doc, size_t sz);
        
    public:
        
        ~Parser();
        
    private:
        
        Element *processStartTag(Input &);
        int processEndTag(Input &);
        
        //parser per-run init and cleanup functions
        void parser_init();
        void parser_cleanup();
        
        
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
        
        //the element stack and the NSTable can be created dynamically when
        //beginning the parser, and deleted upon exiting
        std::stack<Element *, std::vector<Element *>> *elementStack;
        bool foundRoot;
        Element *root;
        
        
        //Associative array of String stacks
        //keys=nmspace prefix, values=stack of URIs associated with each nmspace
        //stacks needed to ensure that the correct URI is in scope
        //I believe that this can be improved by switching from std::string
        //to String. However, "class Hash = hash<Key>" needs to be implemented.
        //This still works, just could be more mem efficient.
        //This would also allow use to change xmlnsPairs and definedNSIs
        //also, need to figure out a way to clean this up after running
        //std::unordered_map<const String, std::stack<const String>, const StringHashFunction, const StringEqual> *NSTable;
        
        //Could turn this into a class
        //std::unordered_map<String, std::stack<String, std::vector<String>>, std::hash<std::string>, std::equal_to<std::string> > *NSTable;
        std::unordered_map<String, std::stack<String, std::vector<String>>, std::hash<std::string> > *NSTable;
        
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
        
        std::unordered_map<const String, String, std::hash<std::string>> *xmlnsPairs;
        
        const String beginCommentTag;
        const String endCommentTag;
        const String beginEndElementTag;
        const String xmlnsTag;
        
        
    };
    inline int isAlphaNumOrUS(int c) {
        if(c == '_')
            return !0;
        else
            return isalnum(c);
    }
    
//    inline int notAlphaNumOrUS(int c) {
//        return !isAlphaNumOrUS(c);
//    }
    
    inline int notAlphaNumOrUS(int c) {
        if(c == '_')
            return 0;
        else
            return isalnum(c)==0;
    }
    
    inline int notspace(int c) {
        return !isspace(c);
    }    
    
    inline int isColSpaceOrRA(int c) {
        if(c == ':')
            return !0;
        else if (c == '>')
            return !0;
        else
            return isspace(c);
    }
    
    inline int notColSpaceOrRA(int c) {
        return !isColSpaceOrRA(c);
    }
    
}

#endif /* defined(__XML_Parser__Parser__) */
