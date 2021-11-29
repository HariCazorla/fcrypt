#ifndef __FILE_H__
#define __FILE_H__
#include "stdio.h"
#include "stdlib.h"
#include "Buffer.h"

/**
 * Class to mimic File operations 
 * RAII principle is used to manage cleanup
 */
class File
{
private:
     const char *pFilePath;
     const char *pMode;
     FILE *pFile;

public:
     /**
        * Constructor 
        * @Param filePath - complete file path
        * @Param mode - fopen mode
        */
     File(const char *filePath, const char *mode);

     /**
         * Wrapper function to perform fread
         * @Param size - Indicates the number bytes to be read
         * @Param Buffer - Indicates the buffer
         * @Return int - total number of bytes read 
         */
     int read(int size, Buffer &buffer);

     /**
         * Wrapper function to perform fwrite
         * @Param size - Indicates the number bytes to be read
         * @Param Buffer - Indicates the buffer
         * @Return int - total number of bytes written 
         */
     int write(int size, Buffer &buffer);

     /**
         * Wrapper function to perform fclose
         * @Return void
         */
     void close();

     /**
         * Wrapper function to perform fstat and fetch file size
         * @Return Long - Total size of file in bytes
         */
     long size();

     /**
         * Destructor
         */
     ~File();
};

#endif