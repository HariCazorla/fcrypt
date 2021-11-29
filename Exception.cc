#include "Exception.h"

Exception::Exception(int errCode)
{
    errorCode = errCode;
}

int Exception::getErrno()
{
    return errorCode;
}

const char *Exception::getMessage()
{
    const char *msg = "";
    switch (errorCode)
    {
    case MALLOC_FAILED:
        msg = "Failed to allocate buffer\n";
        break;

    case FILE_OPEN_FAILED:
        msg = "Failed to open the file\n";
        break;

    case INVALID_FILE:
        msg = "File handle invalid\n";
        break;

    case READ_FAILED:
        msg = "Failed to read file\n";
        break;

    case WRITE_FAILED:
        msg = "Failed to write to file\n";
        break;

    default:
        msg = "Unexpected failure\n";
        break;
    }
    return msg;
}
