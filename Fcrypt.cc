#include "iostream"
#include "File.h"
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include "Exception.h"
#define BUFFER_SIZE 128
using namespace std;

int main(const int argc, const char **argv)
{
    string inFileName = "";
    string outFileName = "";
    string ckey = "01234567890123456789012345678901";
    string ivec = "0123456789012345";
    string mode = "e";
    if (argc != 6)
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
    else
    {
        inFileName = argv[1];
        outFileName = argv[2];
        ckey = argv[3];
        ivec = argv[4];
        mode = argv[5];
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
    int s = 0, read = 0;
    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new()))
    {
        ERR_print_errors_fp(stderr);
        abort();
    }

    int cipherBlockSize = EVP_CIPHER_block_size(EVP_aes_256_cbc());
    try
    {
        /* code */
        if (strcmp(mode.c_str(), "e") == 0)
        {
            cout << "Starting Encryption..." << endl;

            if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char *)ckey.c_str(), (const unsigned char *)ivec.c_str()))
            {
                throw Exception(OPENSSL_INIT_ERROR);
            }
            while (true)
            {
                Buffer inBuffer(BUFFER_SIZE);
                Buffer outBuffer(BUFFER_SIZE + cipherBlockSize);
                read = sourceFile.read(BUFFER_SIZE, inBuffer);
                if (read == BUFFER_SIZE)
                {
                    cout << "Reading..." << endl;
                    s = sourceFile.encryptBlock((void *)ctx, BUFFER_SIZE, inBuffer, outBuffer, false);
                    destinationFile.write(s, outBuffer);
                }
                else
                {
                    cout << "Reading last block..." << endl;
                    s = sourceFile.encryptBlock((void *)ctx, read, inBuffer, outBuffer, true);
                    destinationFile.write(s, outBuffer);
                    break;
                }
            }
        }

        if (strcmp(mode.c_str(), "d") == 0)
        {
            cout << "Starting Decryption..." << endl;
            if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char *)ckey.c_str(), (const unsigned char *)ivec.c_str()))
            {
                throw Exception(OPENSSL_INIT_ERROR);
            }

            while (true)
            {
                Buffer inBuffer(BUFFER_SIZE);
                Buffer outBuffer(BUFFER_SIZE + cipherBlockSize);
                read = sourceFile.read(BUFFER_SIZE, inBuffer);
                if (read == BUFFER_SIZE)
                {
                    cout << "Reading..." << endl;
                    s = sourceFile.decryptBlock((void *)ctx, BUFFER_SIZE, inBuffer, outBuffer, false);
                    destinationFile.write(s, outBuffer);
                }
                else
                {
                    cout << "Reading last block..." << endl;
                    s = sourceFile.decryptBlock((void *)ctx, read, inBuffer, outBuffer, true);
                    destinationFile.write(s, outBuffer);
                    break;
                }
            }
        }
    }
    catch (Exception &e)
    {
        cout << e.getMessage();
    }

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);
    return 0;
}