//
//  Element.h
//  XML Parser
//
//  Created by James Kizer on 2/18/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#ifndef __XML_Parser__Element__
#define __XML_Parser__Element__

#include "Node.hpp"
#include "String.hpp"
#include "Visitor.hpp"

namespace xml{
    
    class Visitor;
    
    class Element : public Node {
    public:
        // Returns the name of the element.  This is just
        // the part after the colon.  If there is no colon, then
        // it is the whole thing, of course.
        const String &name() const;
        // Returns the full namespace URI (not the prefix) of the element.
        // If the element is not in any namespace, this should simply
        // return an empty String.  Note that 'namespace' is a reserved
        // keyword, so we don't fully spell it out.
        const String &nmspace() const;
        // Returns the number of children nodes.
        size_t n_children() const;
        // Returns the i'th child.
        const Node *child(size_t i) const;
        // Accepts a visitor.
        void accept(Visitor *) const;
        // Convenience functions that internally will use RTTI.
        static bool is_Element(const Node *);
        static const Element *to_Element(const Node *);
    public:
        // You could add more to the public interface, if you wanted to.
    private:
        // Private things for your implementation.
    };
}

#endif /* defined(__XML_Parser__Element__) */
