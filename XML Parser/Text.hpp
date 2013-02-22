//
//  Text.hpp
//  XML Parser
//
//  Created by James Kizer on 2/18/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#ifndef __XML_Parser__Text__
#define __XML_Parser__Text__

#include "Node.hpp"
#include "String.hpp"

namespace xml {
    class Text : public Node {
    public:
        // Returns the text content as a string.
        const String &str() const;
        // Convenience functions that internally will use RTTI.
        static bool is_Text(const Node *);
        static const Text *to_Text(const Node *);
    public:
        // You could add more to the public interface, if you wanted to.
        
        //This must destroy all the child nodes
        //base destructor is virtual
        virtual ~Text();
    private:
        // Private things for your implementation.
    };
}

#endif /* defined(__XML_Parser__Text__) */
