/* platform/compiler adjustments */
#ifndef PG_PLATFORM_H
#define PG_PLATFORM_H

#if defined(HAVE_SNPRINTF) /* defined in python.h (pyerrors.h) and SDL.h \
                              (SDL_config.h) */
#undef HAVE_SNPRINTF       /* remove GCC redefine warning */
#endif /* HAVE_SNPRINTF */

#ifndef PG_INLINE
#if defined(__clang__)
#define PG_INLINE __inline__ __attribute__((__unused__))
#elif defined(__GNUC__)
#define PG_INLINE __inline__
#elif defined(_MSC_VER)
#define PG_INLINE __inline
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define PG_INLINE inline
#else
#define PG_INLINE
#endif
#endif /* ~PG_INLINE */

/* This is unconditionally defined in Python.h */
#if defined(_POSIX_C_SOURCE)
#undef _POSIX_C_SOURCE
#endif

/* No signal() */
#if defined(__SYMBIAN32__) && defined(HAVE_SIGNAL_H)
#undef HAVE_SIGNAL_H
#endif

#if defined(HAVE_SNPRINTF)
#undef HAVE_SNPRINTF
#endif

/* SDL needs WIN32 */
#if !defined(WIN32) &&                                           \
    (defined(MS_WIN32) || defined(_WIN32) ||                     \
     defined(__WIN32) || defined(__WIN32__) || defined(_WINDOWS))
#define WIN32
#endif

#ifndef PG_TARGET_SSE4_2
#if defined(__clang__) || defined(__GNUC__)
#define PG_FUNCTION_TARGET_SSE4_2 __attribute__((target("sse4.2")))
/* No else; we define the fallback later */
#endif
#endif /* ~PG_TARGET_SSE4_2 */

#ifdef PG_FUNCTION_TARGET_SSE4_2
#if !defined(__SSE4_2__) && !defined(PG_COMPILE_SSE4_2)
#if defined(__x86_64__) || defined(__i386__)
#define PG_COMPILE_SSE4_2 1
#endif
#endif
#endif /* ~PG_TARGET_SSE4_2 */

/* Fallback definition of target attribute */
#ifndef PG_FUNCTION_TARGET_SSE4_2
#define PG_FUNCTION_TARGET_SSE4_2
#endif

#ifndef PG_COMPILE_SSE4_2
#define PG_COMPILE_SSE4_2 0
#endif

#endif /* ~PG_PLATFORM_H */
