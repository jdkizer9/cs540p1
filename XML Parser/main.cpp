//
//  main.cpp
//  XML Parser
//
//  Created by James Kizer on 2/18/13.
//  Copyright (c) 2013 James Kizer. All rights reserved.
//

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <iostream>
#include "Parser.hpp"
#include "Element.hpp"
#include "Text.hpp"
#include "Visitor.hpp"
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <new>
#include <execinfo.h>
#include <stdio.h>
#include <regex.h>
#include <cxxabi.h>

using namespace xml;
using namespace std;

int main(int argc, const char * argv[])
{

    char infile[32];
    int ec;
    // insert code here...
    printf("Hello, World!\n");
    
    strncpy(infile, "test.xml", sizeof(infile));
    
    int fd = open(infile, O_RDONLY);
    if (fd < 0) {
        cerr << "Open file failed : " << strerror(errno) << endl;
        return 1;
    }
    
    struct stat sb;
    ec = fstat(fd, &sb);
    if ( ec != 0) {
        cerr << "Get file information failed : " << strerror(errno)<<endl;
        return 1;
    }
    
    const char *doc = (const char *) mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(doc == MAP_FAILED) {
        cerr << "mmap document failed : " << strerror(errno) << endl;
        return 1;
    }
    
    Parser parser;
    const Element *r;
    
    r = parser.parse(doc, sb.st_size);
    delete r;
    
    
    
    
    return 0;
}

