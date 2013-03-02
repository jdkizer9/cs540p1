//
//  Node.hpp
//  XML Parser
//
//  Created by James Kizer on 2/18/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#ifndef __XML_Parser__Node__
#define __XML_Parser__Node__



namespace xml {
    
    class Visitor;
    
    class Node {
    public:
        // Must be present, even if it does nothing.
        
        //This needs to destroy all of its children to prevent memory leaks
        virtual ~Node();
    public:
        virtual void handleVisitor(Visitor *) const = 0;
        // You could add more to the public interface, if you wanted to.
    private:
        // Private things for your implementation.  Probably will not need
        // anything, since this primarily an interface class.
    };
}

#endif /* defined(__XML_Parser__node__) */
