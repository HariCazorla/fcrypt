#include "iostream"
#include "File.h"
using namespace std;

int main(const int argc, const char** argv)
{
    if (argc != 3)
    {
        cout << "Invalid CLI arguments" << endl;
    }

    File sourceFile(argv[1], "r");
    File destinationFile(argv[2], "w");

    return 0;
}