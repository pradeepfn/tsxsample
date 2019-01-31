#ifndef TM_H
#define TM_H 1

#include "tsx.h"
extern unsigned int ntsx;
extern unsigned int ntm;
extern unsigned int nfallback;


#include <stdio.h>
#include <sched.h>
#include <pthread.h>

#define CORE_FACTOR 4

static inline
void bind_thread(long tid)
{
    int cpuid = (int)((tid) * CORE_FACTOR);
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpuid, &mask);
    if( pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask ) == -1 ) {
        printf("WARNING: Could not bind thread %ld on CPU %d, continuing...\n", tid, cpuid);
    } else {
        printf("Thread %ld bound on CPU %d\n", tid, cpuid);
    }
    fflush(stdout);
}

static inline
void bind_main_thread()
{
    int cpuid = (int)(0 * CORE_FACTOR);
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpuid, &mask);
    if( sched_setaffinity(0, sizeof(mask), &mask ) == -1 ) {
        printf("WARNING: Could not bind main thread on CPU %d, continuing...\n",cpuid);
    } else {
        printf("main thread bound on CPU %d\n", cpuid);
    }
    fflush(stdout);
}




#define MAIN(argc, argv)              int main (int argc, char** argv)

#define MAIN_RETURN(val)              printf("Total transactions : %d \n", ntm); \
									  printf("tsx and fallbackpath counts : %d , %d \n", ntsx, nfallback); \
									  return val

#define GOTO_SIM()                    /* nothing */
#define GOTO_REAL()                   /* nothing */
#define IS_IN_SIM()                   (0)

#define SIM_GET_NUM_CPU(var)          /* nothing */

#define P_MEMORY_STARTUP(numThread)   /* nothing */
#define P_MEMORY_SHUTDOWN()           /* nothing */

#include <assert.h>

#define TM_ARG                        /* nothing */
#define TM_ARG_ALONE                  /* nothing */
#define TM_ARGDECL                    /* nothing */
#define TM_ARGDECL_ALONE              /* nothing */
#define TM_PURE                       /* nothing */
#define TM_SAFE                       /* nothing */

#define TM_STARTUP(numThread)        ntm=0;ntsx=0;nfallback=0; 
#define TM_SHUTDOWN()                 

#define TM_THREAD_ENTER()             ({ \
		                                   long mytid = thread_getId(); \
		                                   bind_thread(mytid); \
		                                })
#define TM_THREAD_EXIT()              /* nothing */

#define SEQ_MALLOC(size)              malloc(size)
#define SEQ_FREE(ptr)                 free(ptr)
#define P_MALLOC(size)                malloc(size)
#define P_FREE(ptr)                   free(ptr)
#define TM_MALLOC(size)               malloc(size)
#define TM_FREE(ptr)                  free(ptr)

#define TM_BEGIN()                    tsxbegin()
#define TM_BEGIN_RO()                 /* nothing */
#define TM_END()                      tsxend()
#define TM_RESTART()                  assert(0)

#define TM_EARLY_RELEASE(var)         /* nothing */

#define TM_SHARED_READ(var)           (var)
#define TM_SHARED_READ_P(var)         (var)
#define TM_SHARED_READ_F(var)         (var)

#define TM_SHARED_WRITE(var, val)     var = val
#define TM_SHARED_WRITE_P(var, val)   var = val
#define TM_SHARED_WRITE_F(var, val)   var = val

#define TM_LOCAL_WRITE(var, val)      var = val
#define TM_LOCAL_WRITE_P(var, val)    var = val
#define TM_LOCAL_WRITE_F(var, val)    var = val

#define TM_IFUNC_DECL                 /* nothing */
#define TM_IFUNC_CALL1(r, f, a1)      r = f(a1)
#define TM_IFUNC_CALL2(r, f, a1, a2)  r = f((a1), (a2))

#endif /* TM_H */

