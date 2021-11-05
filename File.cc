#include "File.h"
#include "stdio.h"
#include "cerrno"
#include "Exception.h"
#include "iostream"

using namespace std;

File::File(const char* path, const char* mode)
{
    cout << "Opening file " << path << endl;
    pFile = fopen(path, mode);
    pFilePath = path;
    pMode = mode;
    if (!pFile)
        cout << "Failed to open file" << endl;
}

int File::read(int size)
{
    return 0;
}

int File::write(int size)
{
    return 0;
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
        cout << "Closing file "<< pFilePath << endl;
        close();
        pFile = NULL;
    }
}