#pragma once

#ifndef SENECA_FILE_H
#define SENECA_FILE_H

#include "ShoppingRec.h"

//header file for file functions

namespace seneca 
{



    bool openFileForRead();
    bool openFileForOverwrite();
    void closeFile();
    bool freadShoppingRec(ShoppingRec* rec);
    void fwriteShoppingRec(const ShoppingRec* rec);
}

#endif
