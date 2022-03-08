 //===================================================================================================//
/**
 *  WRITER: TechnicaluserX
 *  
 *  DESCRIPTION: Handles errors with various program termination methods.
 *  
 *  LICENSE: This library is not currently under any license and it is free to modify/distribute. 
 * 
 */
 //===================================================================================================//


#ifndef _TECHLIB_PANIC_HPP
#define _TECHLIB_PANIC_HPP

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <iostream>



#ifdef TECHLIB_PANIC_CHARSET_UTF
    
    #ifndef TECHLIB_PANIC_DISABLE_ERRORS
        #define TECHLIB_PANIC(str)              { fwprintf(stderr, L"PANIC: %s\n",str);}
        #define TECHLIB_PANIC_EXIT(str,code)    { fwprintf(stderr, L"PANIC: %s\n",str);         fwprintf(stderr, L"%s\n",strerror(errno)); exit(code);}
        #define TECHLIB_PANIC_RETURN(str,code)  { fwprintf(stderr, L"PANIC_RETURN: %s\n",str);  fwprintf(stderr, L"%s\n",strerror(errno)); return(code);}
        #define TECHLIB_PANIC_THROW(str,code)   { fwprintf(stderr, L"PANIC_THROW: %s\n",str);   fwprintf(stderr, L"Error code from throw: %d\n",code); throw(code);}
    #else
        #define TECHLIB_PANIC(str)              {}
        #define TECHLIB_PANIC_EXIT(str,code)    { exit(code); }
        #define TECHLIB_PANIC_RETURN(str,code)  { return(code); }
        #define TECHLIB_PANIC_THROW(num)        { throw(code); }
    #endif


#else

    #ifndef TECHLIB_PANIC_DISABLE_ERRORS
        #define TECHLIB_PANIC(str)              { fprintf(stderr, "PANIC: %s\n",str);}
        #define TECHLIB_PANIC_EXIT(str,code)    { fprintf(stderr, "PANIC_EXIT: %s\n",str);      fprintf(stderr, "%s\n",strerror(errno)); exit(code); }
        #define TECHLIB_PANIC_RETURN(str,code)  { fprintf(stderr, "PANIC_RETURN: %s\n",str);    fprintf(stderr, "%s\n",strerror(errno)); return(code); }
        #define TECHLIB_PANIC_THROW(str,code)   { fprintf(stderr, "PANIC_THROW: %s\n",str);     fprintf(stderr, "Error code from throw: %d\n",code); throw(code); }
    #else
        #define TECHLIB_PANIC(str)              {}
        #define TECHLIB_PANIC_EXIT(str,code)    { exit(code); }
        #define TECHLIB_PANIC_RETURN(str,code)  { return(code); }
        #define TECHLIB_PANIC_THROW(code)       { throw(code); }
    #endif



#endif


#endif
