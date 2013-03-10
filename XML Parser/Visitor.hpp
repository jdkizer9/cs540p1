//
//  Visitor.hpp
//  XML Parser
//
//

#ifndef __XML_Parser__Visitor__
#define __XML_Parser__Visitor__

//#include "Element.hpp"
//#include "Text.hpp"

namespace xml{
    
    class Element;
    class Text;
    
    class Visitor {
    public:
        virtual void start_element_visit(const Element &) = 0;
        virtual void end_element_visit(const Element &) = 0;
        virtual void visit_text(const Text &) = 0;
    };
}

#endif /* defined(__XML_Parser__Visitor__) */
