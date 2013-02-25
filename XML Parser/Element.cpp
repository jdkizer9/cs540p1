//
//  Element.cpp
//  XML Parser
//
//  Created by James Kizer on 2/18/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#include "Element.hpp"
#include <iostream>

namespace xml {
    
    Element::~Element() {
        std::cout << "Destructing Element" <<std::endl;
        //needs to destroy all children by removing them from
        //the deque and deleting them
        //Elements are dynamically allocated in processStartTag
        
        //needs to destroy all definedNSIs by removing them from
        //the deque, then delete the deque
        
        
    }
    
    void Element::addChild(const Node *node) {
        children.push_back(node);
    }
    
    const String &Element::name() const {
        return eName;
    }
    
    const String &Element::nmspace() const {
        return URI;
    }
    
    void Element::set_eName(const String &s) {
        eName = s;
    }
    
    void Element::set_nsi(const String &s) {
        nsi = s;
    }
    
    void Element::set_URI(const String &s) {
        URI = s;
    }
    
    void Element::PrintElement() const {
        std::cout << "Element Name: " <<eName<<std::endl;
        std::cout << "NSI: " <<eName<<std::endl;
        std::cout << "URI: " <<eName<<std::endl;
        std::cout << "Its NSI bindings are as follows:"<<std::endl;
        for (std::deque<String>::iterator it = definedNSIs->begin(); it!=definedNSIs->end(); ++it)
            std::cout << *it <<std::endl;
    }
    
}