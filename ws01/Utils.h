#pragma once
#ifndef SENECA_UTILS_H
#define SENECA_UTILS_H
//#define namespace_name_header_file_name_H
// 
// 
// header file for utility functions


namespace seneca 
{
    void flushkeys();
    bool ValidYesResponse(char ch);
    bool yes();
    void readCstr(char cstr[], int len);
    int readInt(int min, int max);
}

#endif 


