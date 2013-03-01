//
//  Text.cpp
//  XML Parser
//
//  Created by James Kizer on 2/18/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#include "Text.hpp"
#include <iostream>


namespace xml {
    
    Text::Text(String &s): text(s){};
    
    Text::~Text() {
        std::cout << "Destructing Text" <<std::endl;
    }
}