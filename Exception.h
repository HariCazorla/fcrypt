#ifndef __EXECPTION_H__
#define __EXECPTION_H__

enum
{
    FILE_OPEN_FAILED = 1,
    MALLOC_FAILED = 2,
    INVALID_FILE = 3,
    READ_FAILED = 4,
    WRITE_FAILED = 5,
    FAILED_TO_GET_FILE_INFORMATION = 6
};

/**
 * Exception class
 */
class Exception
{
private:
    int errorCode;

public:
    /**
    * Constructor 
    * @Param int - error code
    */
    Exception(int errorCode);

    /**
    * Function to return appropriate error message based on error code
    * @Return char* - error message 
    */
    const char *getMessage();

    /**
    * Function to return appropriate error code
    * @Return int - error message 
    */
    int getErrno();
};

#endif
