Coding style
------------

#include<stdio.h /* not */
#include <stdio.h> /* yes */

//ok 
main() {
    
}

//ok
main() 
{
    
}

// not
main()
    {
        
    }

// not
main(int c,char**argv)

// yes
main(int c, char **argv)

// ok
main(int c, char ** argv)

// ok C++ style
/* ok C style *
/*
 * C style
 */

one;
two;
three;

return 0;

#include "scan.h" // types and constants, macros
no C source code (implementation) in headers

column width
80: classic
90-100 columns: ok
>100: break into multiple lines

Prototypes

// in bar.h
void bar(); // prototype

// in main.c
void foo() {
    bar()    
}

// in bar.c
void bar() {
    
}


main() {
    foo()
}




Clean repos
----------
No build products: *.o executables
.gitignore: add executable
or 
git status
git commit -a -m"comment" /* might commit executable */
