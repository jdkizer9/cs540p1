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
}