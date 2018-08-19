#include <windows.h>
#include <wincrypt.h>
#include <errno.h>
#include <stddef.h>
#include <process.h>
#include <sys/types.h>
#include "device_rand.h"

int device_rand(void *buf, size_t len)
{
    HCRYPTPROV provider;

    if (len > 256) {
        return -1;
    }

    if (CryptAcquireContext(&provider, NULL, NULL, PROV_RSA_FULL,
        CRYPT_VERIFYCONTEXT) == 0) {

        return -1;
    }

    if (CryptGenRandom(provider, len, buf) == 0) {
        CryptReleaseContext(provider, 0);

        return -1;
    }

    CryptReleaseContext(provider, 0);

    return 0;
}
