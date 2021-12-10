#include "Buffer.h"
#include "stdlib.h"
#include "iostream"
#include "Exception.h"

using namespace std;

Buffer::Buffer(int size)
{
    buffer = (unsigned char *)malloc(size);
    if ((buffer == NULL) || (errno > 0))
    {
        throw Exception(MALLOC_FAILED);
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