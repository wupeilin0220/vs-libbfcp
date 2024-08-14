#ifndef _BFCP_THREADS_
#define _BFCP_THREADS_

#if defined(WIN32) || defined(_WIN64) 
#include <windows.h>
#include <process.h>
typedef CRITICAL_SECTION bfcp_mutex_t;
typedef HANDLE bfcp_thread_t;
#define sleep(x) Sleep(1000 * (x))
#define pthread_mutex_init(mutex, attr) InitializeCriticalSection(mutex)
#define pthread_mutex_lock(mutex) EnterCriticalSection(mutex)
#define pthread_mutex_unlock(mutex) LeaveCriticalSection(mutex)
#define pthread_create(thread, attr, start_routine, arg) \
    *thread = (HANDLE)_beginthreadex(NULL, 0, start_routine, arg, 0, NULL)
#define pthread_mutex_destroy(mutex) DeleteCriticalSection(mutex)
#define pthread_detach(thread) CloseHandle(thread)
#define pthread_cancel(thread) TerminateThread(thread, 0)
#define pthread_exit(arg) _endthreadex(0)
#define close closesocket
#else
#include <pthread.h>
typedef pthread_mutex_t bfcp_mutex_t;
typedef pthread_t bfcp_thread_t;
#endif

#define bfcp_mutex_init(a,b) pthread_mutex_init(a,b)
#define bfcp_mutex_destroy(a) pthread_mutex_destroy(a)
#define bfcp_mutex_lock(a)				\
		pthread_mutex_lock(a);
#define bfcp_mutex_unlock(a)				\
		pthread_mutex_unlock(a);

#endif
