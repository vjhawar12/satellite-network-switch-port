// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

/**
 * \file
 * \brief OS custom header file
 * \details This file is a skeleton to be replaced by for customer specific OS.
 */

#include <string.h> /* For memset and friend (not in stdlib) */
#include <stdlib.h> /* For malloc and friends */
#include <stdio.h>  /* For sprintf and friends */
#include <stdint.h>
#include <stddef.h>

#define uint  unsigned int  /**< Define API uint type - unsigned 16 bits */
#define ulong unsigned long /**< Define API ulong - unsigned 32 bits */

/** \brief C99 Integer types */
typedef signed char i8;  /**<  8-bit signed */
typedef int16_t     i16; /**< 16-bit signed */
typedef int32_t     i32; /**< 32-bit signed */
typedef int64_t     i64; /**< 64-bit signed */

typedef uint8_t  u8;  /**<  8-bit unsigned */
typedef uint16_t u16; /**< 16-bit unsigned */
typedef uint32_t u32; /**< 32-bit unsigned */
typedef uint64_t u64; /**< 64-bit unsigned */

typedef u8 BOOL; /**< Boolean implemented as 8-bit unsigned */
typedef BOOL bool;

void delay_ms(const uint16_t ms);
void delay_us(const uint16_t us);
u32 get_global_ms();
void* mesa_malloc(size_t bytes);
void mesa_free(void *ptr);

// Define how to do a 1 millisecond sleep
#define VTSS_MSLEEP(msec) delay_ms(msec)
#define VTSS_USLEEP(usec) delay_us(usec)
#define VTSS_NSLEEP(nsec) VTSS_USLEEP(nsec / 1000)


// Define Timer function
typedef struct {
    BOOL enabled;
    u32 timeout;
} vtss_mtimer_t;
/**< Timer */


#define VTSS_MTIMER_START(pTimer, msec)                  \
    do {                                                 \
        (pTimer)->timeout = get_global_ms() + (msec);   \
        (pTimer)->enabled = TRUE;                        \
    } while (0)

#define VTSS_MTIMER_TIMEOUT(pTimer)                      \
    ((pTimer)->enabled &&                                \
     ((i32)(get_global_ms() - (pTimer)->timeout) >= 0))

#define VTSS_MTIMER_CANCEL(pTimer)                       \
    do {                                                 \
        (pTimer)->enabled = FALSE;                       \
    } while (0)

#define VTSS_DIV64(dividend, divisor) (dividend / divisor) /**< support for 64 bit division */
#define VTSS_MOD64(dividend, divisor) (dividend % divisor) /**< support for 64 bit division */
#define VTSS_LABS(arg)                (labs(arg)) /**< long to abs */
#define VTSS_LLABS(arg)               (llabs(arg)) /**< long long to abs */

/**
 * Count trailing zeros of a 32-bit unsigned.
 * Requirements/examples:
 *   VTSS_OS_CTZ(0x00000001) =  0
 *   VTSS_OS_CTZ(0x80000000) = 31
 *   VTSS_OS_CTZ(0x00000000) >= 32 (if result is taken as unsigned; Most
 * implementations return -1, and (u32)(-1) >= 32).
 *
 * __builtin_ctz() is included in GCC 3.2.2 and later according to
 * http://en.wikipedia.org/wiki/Find_first_set.
 */
#define VTSS_OS_CTZ(val32) __builtin_ctzl(val32)

/**
 * Count trailing zeros of a 64-bit unsigned.
 * Requirements/examples:
 *   VTSS_OS_CTZ64(0x00000000_00000001) =  0
 *   VTSS_OS_CTZ64(0x00000000_80000000) = 31
 *   VTSS_OS_CTZ64(0x00000001_00000000) = 32
 *   VTSS_OS_CTZ64(0x80000000_00000000) = 63
 *   VTSS_OS_CTZ64(0x00000000_00000000) >= 64 (if result is taken as unsigned;
 * Most implementations return -1, and (u32)(-1) >= 64).
 */
#define VTSS_OS_CTZ64(val64) __builtin_ctzll(val64)

/**
 * Request OS to allocate size bytes of memory.
 *
 * The first argument is the number of bytes that must
 * be allocated. Type is size_t.
 *
 * The second argument is a mask of flags that the
 * implementation must obey. Type is vtss_mem_flags_t.
 *
 * The returned pointer should be at least 8-byte aligned,
 * to make it suitable for a struct.
 */

#define VTSS_OS_MALLOC(size, flags) mesa_malloc(size)

/**
 * Request OS to free memory previously allocated with
 * VTSS_OS_MALLOC().
 *
 * The first argument is the pointer previously
 * obtained with a call to VTSS_OS_MALLOC(). Type is
 * void *.
 *
 * The second argument is a mask of flags identical to
 * those passed to VTSS_OS_MALLOC() when the memory
 * was requested.
 */
#define VTSS_OS_FREE(ptr, flags) mesa_free(ptr)

/**
 * Convert a CPU address into a DMA address.
 *
 * The first argument is a CPU address that was obtain with
 * VTSS_OS_MALLOC() using the VTSS_MEM_FLAGS_DMA flag.
 *
 * The returned value is a DMA address that can be passed
 * to DMA capable hardware.
 */
#define VTSS_OS_CPU_TO_DMA_ADDR(addr) do {} while (0)

/**
 * Wrap of call to rand() defined in stdlib.h
 */
#define VTSS_OS_RAND() rand()

#define VTSS_MEMSET(s, c, n) (void)memset(s, c, n)
#define VTSS_MEMCMP(s, c, n) memcmp(s, c, n)
#define VTSS_MEMCPY(s, c, n) (void)memcpy(s, c, n)

#define VTSS_STRLEN(s)      strlen(s)
#define VTSS_STRCPY(sd, ss) strcpy(sd, ss)

#define VTSS_TOUPPER(arg) (toupper(arg))
#define VTSS_TOLOWER(arg) (tolower(arg))

#define VTSS_PROF_ENTER(id, sub) do {} while (0)
#define VTSS_PROF_EXIT(id, sub) do {} while (0)
