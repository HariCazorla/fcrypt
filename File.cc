#include "File.h"
#include "stdio.h"
#include "cerrno"
#include "Exception.h"
#include "iostream"
#include "sys/stat.h"
#include "openssl/conf.h"
#include "openssl/evp.h"
#include "openssl/err.h"

using namespace std;

File::File(const char *path, const char *mode)
{
    cout << "Opening file " << path << endl;
    pFile = fopen(path, mode);
    pFilePath = path;
    pMode = mode;
    if (!pFile)
    {
        throw Exception(FILE_OPEN_FAILED);
    }
}

int File::read(int size, Buffer &buffer)
{
    if (pFile == NULL)
    {
        throw Exception(INVALID_FILE);
    }

    int read = 0;
    read = fread(buffer.buffer, 1, size, pFile);
    // if read bytes is not equal to size, throw exception
    if (read != size)
    {
        if (!feof(pFile))
        {
            throw Exception(READ_FAILED);
        }
    }
    return read;
}

int File::write(int size, Buffer &buffer)
{
    if (pFile == NULL)
    {
        throw Exception(INVALID_FILE);
    }

    int write = fwrite(buffer.buffer, 1, size, pFile);
    // if write bytes is not equal to size, throw exception
    if (write != size)
    {
        throw Exception(WRITE_FAILED);
    }

    return write;
}

void File::close()
{
    if (pFile)
    {
        fclose(pFile);
    }
    return;
}

long File::size()
{
    long fileSize = 0;
    struct stat fileStats;
    int ret = stat(pFilePath, &fileStats);
    {
        throw Exception(FAILED_TO_GET_FILE_INFORMATION);
    }
    fileSize = fileStats.st_size;
    return fileSize;
}

int File::encryptBlock(void *ctx, int size, Buffer &inBuffer, Buffer &outBuffer, bool isFinal)
{
    int len;
    int ciphertextLength;
    if (1 != EVP_EncryptUpdate((EVP_CIPHER_CTX *)ctx, outBuffer.buffer, &len, inBuffer.buffer, size))
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    ciphertextLength = len;
    if (isFinal)
    {
        if (1 != EVP_EncryptFinal_ex((EVP_CIPHER_CTX *)ctx, outBuffer.buffer + len, &len))
        {
            ERR_print_errors_fp(stderr);
            abort();
        }
        ciphertextLength += len;
    }
    cout << "Encrypted " << ciphertextLength << " bytes" << endl;
    BIO_dump_fp(stdout, (const char *)outBuffer.buffer, ciphertextLength);
    cout << endl;
    return ciphertextLength;
}

File::~File()
{
    if (pFile)
    {
        cout << "Closing file " << pFilePath << endl;
        close();
        pFile = NULL;
    }
}