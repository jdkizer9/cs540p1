//
//  Pool.h
//  XML Parser
//
//  Created by James Kizer on 3/9/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#ifndef __XML_Parser__Pool__
#define __XML_Parser__Pool__

#include <string>

namespace xml {
    
    struct Object {
        Object *next;
    };
    
    class Pool {
    public:
        Pool(size_t);
        ~Pool();
        void *allocate();
        void deallocate(void *);
        inline bool checkSize(size_t s) const {return (s == typeSize);};
        
    private:
        Object *head;
        size_t count;
        size_t typeSize;
        
    };
}


#endif /* defined(__XML_Parser__Pool__) */
