#include "iostream"
#include "File.h"
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>

using namespace std;

int main(const int argc, const char **argv)
{
    string inFileName = "";
    string outFileName = "";
    string ckey = "01234567890123456789012345678901";
    string ivec = "0123456789012345";
    string mode = "e";
    if (argc != 5)
    {
        cout << "Interactive mode..." << endl;
        cout << "Enter source file name..." << endl;
        cin >> inFileName;
        cout << "Enter destination file name..." << endl;
        cin >> outFileName;
        cout << "Enter a secret key consisting of 32 charecters..." << endl;
        cin >> ckey;
        cout << "Enter a secret initial vector consisting of 16 charecters..." << endl;
        cin >> ivec;
        cout << "Choose e for encryption / d for decryption..." << endl;
        cin >> mode;
    }
    if (inFileName.length() == 0 || outFileName.length() == 0)
    {
        cout << "Enter valid file names..." << endl;
        return 1;
    }
    if (ckey.length() != 32)
    {
        cout << "secret key is not consisting of 32 charecters, using defaults..." << endl;
        ckey = "01234567890123456789012345678901";
    }
    if (ivec.length() != 16)
    {
        cout << "secret initial vector is not consisting of 16 charecters, using defaults..." << endl;
        ivec = "0123456789012345";
    }

    File sourceFile(inFileName.c_str(), "r");
    File destinationFile(outFileName.c_str(), "w");
    EVP_CIPHER_CTX *ctx;
    int s = 0;
    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new()))
    {
        ERR_print_errors_fp(stderr);
        abort();
    }

    if (strcmp(mode.c_str(), "e") == 0)
    {
        cout << "Starting Encryption..." << endl;
        return 0;
    }

    if (strcmp(mode.c_str(), "d") == 0)
    {
        cout << "Starting Decryption..." << endl;
        return 0;
    }
}