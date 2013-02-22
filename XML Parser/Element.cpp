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
    
}