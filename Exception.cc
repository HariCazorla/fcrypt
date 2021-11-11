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
    case FAILED_TO_ALLOCATE_BUFFER:
        msg = "Failed to allocate\n";
        break;

    case FAILED_TO_OPEN_FILE:
        msg = "Failed to open the file\n";
        break;

    default:
        msg = "Unexpected failure\n";
        break;
    }
    return msg;
}
