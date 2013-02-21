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
#include <stack>
#include <unordered_map>
#include <cstring> //Is this needed?

namespace xml {
    class Parser {
    public:
        Parser(); // Must be able to create one.
        const Element *parse(const char *doc, size_t sz);
    private:
        
        //Stack of elements
        std::stack<String> elementStack;
        
        //Associative array of String stacks
        //keys=nmspace prefix, values=stack of URIs associated with each nmspace
        //stacks needed to ensure that the correct URI is in scope
        std::unordered_map<std::string, std::stack<String>> NSTable;
        
    };
}

#endif /* defined(__XML_Parser__Parser__) */
