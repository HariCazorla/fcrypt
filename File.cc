#include "File.h"
#include "stdio.h"
#include "cerrno"
#include "Exception.h"
#include "iostream"

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
    return 0;
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