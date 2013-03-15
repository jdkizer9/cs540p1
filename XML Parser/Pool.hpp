//
//  Pool.hpp
//  XML Parser
//
//  Concepts based on Prof. Kenneth Chiu's Allocator template
//  
//

#ifndef __XML_Parser__Pool__
#define __XML_Parser__Pool__

#include <string>

namespace xml {
    
    struct Object {
        Object *next;
    };
    
    struct Block {
        Block *next;
        Object first;
    };
    
    class Pool {
    public:
        //if initObjects is nonzero, rounded up to the nearest block
        Pool(size_t s, size_t initObjects=0);
        ~Pool();
        void *allocate();
        void deallocate(void *);
        inline bool checkSize(size_t s) const {return (s == typeSize);};
        
    private:
        void allocateBlocks(size_t);
        Object *headObject;
        Block *headBlock;
        size_t count;
        size_t typeSize;
        size_t objectsPerBlock;
    };
}


#endif /* defined(__XML_Parser__Pool__) */
