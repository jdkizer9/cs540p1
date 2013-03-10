//
//  Text.cpp
//  XML Parser
//
//

#include "Text.hpp"
#include <typeinfo>
#include <iostream>
#include <assert.h>


namespace xml {
    
    Text::Text(String &s): text(s){};
    
    Text::~Text() {
        //std::cout << "Destructing Text" <<std::endl;
    }
    
    const String &Text::str() const {
        return text;
    }
    
    bool Text::is_Text(const Node *n) {
        return typeid(*n) == typeid(Text);
    }
    
    const Text *Text::to_Text(const Node *n) {
        //assert(typeid(*n) == typeid(Text));
        return (Text*)n;
    }
    
    void Text::handleVisitor(Visitor *v) const {
        v->visit_text(*this);
    }
}