#include "Buffer.h"
#include "stdlib.h"
#include "iostream"
#include "Exception.h"

using namespace std;

Buffer::Buffer(int size)
{
    buffer = (char *)malloc(size);
    if ((buffer == NULL) || (errno > 0))
    {
        cout << "Failed to allocate buffer" << endl;
    }
}

Buffer::~Buffer()
{
    if (buffer)
    {
        free(buffer);
        buffer = NULL;
    }
}