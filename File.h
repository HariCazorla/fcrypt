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
     * Wrapper function to perform encryption
     * @Param ctx - void pointer to EVP_CIPHER_CTX
     * @Param size - size of buffer to be encrypted
     * @Param inBuffer - buffer block to be encrypted
     * @Param outBuffer - buffer to store encrypted block
     * @Param isFinal - flag to indicate last block of file
     * @Return int - size of encrypted block 16 bytes aligned
     */
    int encryptBlock(void *ctx, int size, Buffer &inBuffer, Buffer &outBuffer, bool isFinal);

    /**
     * Wrapper function to perform decryption
     * @Param ctx - void pointer to EVP_CIPHER_CTX
     * @Param size - size of buffer to be decrypted
     * @Param inBuffer - buffer block to be decrypted
     * @Param outBuffer - buffer to store decrypted block
     * @Param isFinal - flag to indicate last block of file
     * @Return int - size of decrypted block 16 bytes aligned
     */
    int decryptBlock(void *ctx, int size, Buffer &inBuffer, Buffer &outBuffer, bool isFinal);

    /**
     * Destructor
     */
    ~File();
};

#endif