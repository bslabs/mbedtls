/*
 * mbed TLS platform-specific setup/teardown implementation for classic Mac OS
 *
 * Copyright (C) 2018, Brendan Shanks, All Rights Reserved
 */

#ifndef MBEDTLS_MACOS_PLATFORM_H
#define MBEDTLS_MACOS_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * \brief   The platform context structure.
 *
 * \note    This structure may be used to assist platform-specific
 *          setup or teardown operations.
 */
typedef struct {
    char dummy; /**< A placeholder member, as empty structs are not portable. */
}
mbedtls_platform_context;


#ifdef __cplusplus
}
#endif

#endif /* platform_alt.h */