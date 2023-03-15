/**
 * \file ccm.h
 */
#ifndef MBED_CCM_H
#define MBED_CCM_H

#include "sm4.h"

#define CCM_ENCRYPT 1
#define CCM_DECRYPT 0


/**
 * \brief          SM4 context structure
 */

#ifdef __cplusplus
extern "C" {
#endif

void ccm_setkey_enc( sm4_context *ctx, unsigned char key[16] );

int ccm_auth_crypt( sm4_context *ctx, int mode, unsigned int length,
                           const unsigned char *iv, unsigned int iv_len,
                           const unsigned char *add, unsigned int add_len,
                           const unsigned char *input, unsigned char *output,
                           unsigned char *tag, unsigned int tag_len );

#ifdef __cplusplus
}
#endif

#endif /* ccm.h */
