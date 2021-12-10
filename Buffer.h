#ifndef __BUFFER_H__
#define __BUFFER_H__

/**
 * Class to maintain buffer of defined size
 * RAII principle is used to manage cleanup
 */
class Buffer
{
private:
    unsigned char *buffer;

public:
    /**
     * Constructor
     * @Param size - total buffer size
     */
    Buffer(int size);

    friend class File;

    /**
     * Destructor
     */
    ~Buffer();
};

#endif