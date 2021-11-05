#ifndef __FILE_H__
#define __FILE_H__
#include "stdio.h"
#include "stdlib.h"

class File
{
    private:
        const char* pFilePath;
        const char* pMode;
        FILE *pFile;

    public:
        File(const char* filePath, const char* mode);
        int read(int size);
        int write(int size);
        void close();
        long size();
        ~File();
};

#endif