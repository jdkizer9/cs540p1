//
//  Text.hpp
//  XML Parser
//
//

#ifndef __XML_Parser__Text__
#define __XML_Parser__Text__

#include "Node.hpp"
#include "String.hpp"
#include "Visitor.hpp"

namespace xml {
    
    class Visitor;
    class Text : public Node {
    public:
        // Returns the text content as a string.
        const String &str() const;
        // Convenience functions that internally will use RTTI.
        static bool is_Text(const Node *);
        static const Text *to_Text(const Node *);
    public:
        Text(String &);
        // You could add more to the public interface, if you wanted to.
        
        virtual void handleVisitor(Visitor *) const;
        //This must destroy all the child nodes
        //base destructor is virtual
        virtual ~Text();
    private:
        const String text;
        // Private things for your implementation.
    };
}

#endif /* defined(__XML_Parser__Text__) */
