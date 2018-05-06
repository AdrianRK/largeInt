/*
 * =====================================================================================
 *
 *       Filename:  log.hpp
 *
 *    Description:  logging helpting function
 *
 *        Version:  1.0
 *        Created:  04/05/2018 00:13:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Adrian Alin RAdu 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef LARGEINT_INC_LOGGING_HELPER_HPP
#define LARGEINT_INC_LOGGING_HELPER_HPP

#include <fstream>
#include <iostream>
std::ofstream lout("output.log");

void _print()
{
        lout << "\n";
}


template <typename T, typename... pack>
void _print ( const T& arg, const pack&... args )
{
        lout << arg;
        _print(args...);
        return ;
}               /* -----  end of template function print  ----- */

#ifdef __DEBUG__D
#define Print(...) _print("[Function: ", __FUNCTION__, "]:[Line:  ", __LINE__, "]: ", __VA_ARGS__)
#else
#define Print(...)
#endif

#endif //LARGEINT_INC_LOGGING_HELPER_HPP
