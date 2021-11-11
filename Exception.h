#ifndef __EXECPTION_H__
#define __EXECPTION_H__

enum
{
    FAILED_TO_OPEN_FILE = 1,
    FAILED_TO_ALLOCATE_BUFFER = 2
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
