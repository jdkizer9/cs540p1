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
#include <deque>
#include <unordered_map>

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
        void addChild(const Node *);
        
        //This must destroy all the child nodes
        //base destructor is virtual
        //popping all elements off element deque
        virtual ~Element();
               
    private:
        // Private things for your implementation.
        
        //Most of the private variables may need to be updated after construction
        //would be helpful for nsi, eName, URI, definitely children and definedNSIs
        //should only be updated by Parser, make friend and protect setter functions
        
        void set_eName(const String &);
        void set_nsi(const String &);
        void set_URI(const String &);
        
        //optional nsi known as part of START_TAG processing
        String nsi;
        
        //element name known as part of START_TAG processing
        String eName;
        
        //set after NSTable is updated during START_TAG processing
        //this ensures that the propper scope URI is returned
        //(i.e., the nsi could be rebound as part of this element)
        String URI;
        
        //Child Node deque
        //the Nodes should live here
        //they willbe destroyed when removed the deque in the dtor
        //push to the back
        std::deque<const Node *> children;
        
        //Defined NSIs deque
        //populated by the parser during START_TAG processing, guaranteed to
        //be unique as uniqueness is checked by parser before populating
        //necessary so that the parser knows which NSI values to pop off the
        //parser's NSTable when the element comes off the element stack during
        //END_TAG processing
        //This is dynamically created during processStartTag
        //this could technically be destroyed after END_TAG processing
        //std::deque<std::string> *definedNSIs;
        std::deque<String> *definedNSIs;
        
        void PrintElement() const;
        
        friend class Parser;
        
        
    };
}

#endif /* defined(__XML_Parser__Element__) */
