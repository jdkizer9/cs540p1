//
//  Visitor.hpp
//  XML Parser
//
//  Created by James Kizer on 2/18/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#ifndef __XML_Parser__Visitor__
#define __XML_Parser__Visitor__

#include "Element.hpp"
#include "Text.hpp"

namespace xml{
    
    class Element;
    
    class Visitor {
    public:
        virtual void start_element_visit(const Element &) = 0;
        virtual void end_element_visit(const Element &) = 0;
        virtual void visit_text(const Text &) = 0;
    };
}

#endif /* defined(__XML_Parser__Visitor__) */
