
#define _CRT_SECURE_NO_DEPRECATE

#include <assert.h>
#include <malloc.h>
#include <process.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef intptr_t ssize_t;

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#undef ERROR
#undef OK

#define WEPOLL_EXPORT static
#include "wepoll/wepoll.c"

static inline int check_fail() {
  fprintf(stderr, "check failed.");
  abort();
}

#define HANDLE_TO_FD(h) ((int) (intptr_t) (h))
#define FD_TO_HANDLE(f) ((HANDLE) (intptr_t) (f))
#define SOCKET_TO_FD(s) ((int) (intptr_t) (s))
#define FD_TO_SOCKET(f) ((SOCKET) (intptr_t) (f))

#define NARROW(to_type, value) ((to_type)(value))

#define epoll_create(x) HANDLE_TO_FD(epoll_create(x))
#define epoll_create1(x) HANDLE_TO_FD(epoll_create(x))
#define epoll_ctl(epfd, x, fd, y) epoll_ctl(FD_TO_HANDLE(epfd), x, FD_TO_SOCKET(fd), y)
#define epoll_wait(epfd, x, y, z) epoll_wait(FD_TO_HANDLE(epfd), x, y, z)

#define close close__
//#define close(f) close__(f)
static inline int close(int fd) { return 0; /* todo */ }

#define poll(x, y, z) (-1) /* referenced but never used/called */

#define signal(x, y) /* Gets called to ignore 'SIGPIPE', is not defined. 
                      * Ignoring signals is unnecessary on Windows. */
#define sigfillset(x)
#define sigemptyset(x)
#define sigaction(x, y, z)
typedef int sigset_t;
typedef struct siginfo siginfo_t;
struct sigaction {
     void     (*sa_handler)(int);
     void     (*sa_sigaction)(int, siginfo_t *, void *);
     sigset_t   sa_mask;
     int        sa_flags;
     void     (*sa_restorer)(void);
 };
                      
                      
                      
typedef HANDLE pthread_t;
typedef struct {} pthread_attr_t;

typedef struct {
  void *(*thread_fn) (void *);
  void* arg;
} pthread_create_info;

static  unsigned int __stdcall pthread_create_trampoline(void* info_ptr) {
  pthread_create_info info = *(pthread_create_info*) info_ptr;
  free(info_ptr);
  info.thread_fn(info.arg);
  return 0;
}

#ifndef return_map_error
#define return_map_error(r) return r;
#define return_set_error(r, err) return r;
#endif

static  int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*thread_fn) (void *), void *arg) {
  pthread_create_info* info = malloc(sizeof *info);
  if (info == NULL) return_set_error(-1, ERROR_NOT_ENOUGH_MEMORY);
  info->thread_fn = thread_fn;
  info->arg = arg;
  uintptr_t r = _beginthreadex(NULL, 0, pthread_create_trampoline, info, 0, NULL);
  if (!r) {
    free(info);
    return -1;
  }
  *thread = (HANDLE)r;
  return 0;
}



static  int pthread_join(pthread_t thread, void **retval) {
  
  /* Returning a value isn't supported. pthread_exit() isn't implemented, so 
   * setting a return value wouldn't be possible. */
  assert(retval == NULL);  
  DWORD r = WaitForSingleObject(thread, INFINITE);
  if (r != WAIT_OBJECT_0) {
    return_map_error(-1);
  }
  return 0;
}


typedef SRWLOCK pthread_mutex_t;
#define PTHREAD_MUTEX_INITIALIZER SRWLOCK_INIT


inline static int pthread_mutex_lock(pthread_mutex_t *mutex) {
  AcquireSRWLockExclusive(mutex);
  return 0;
}
inline static int pthread_mutex_unlock(pthread_mutex_t *mutex) {
  ReleaseSRWLockExclusive(mutex);
  return 0;
}


static  unsigned int sleep(unsigned int seconds) {
  Sleep(seconds * 1000);
  return 0;
}

#define strncasecmp _strnicmp
#define strcasecmp _stricmp

#define F_GETFL 3
#define F_SETFL 4
#define O_NONBLOCK  00004000

#define getsockopt(fd, x, y, optval, z) getsockopt(FD_TO_SOCKET(fd), x, y, (char*) (optval), z);
#define setsockopt(fd, x, y, optval, z) setsockopt(FD_TO_SOCKET(fd), x, y, (const char*) (optval), z);
#define ioctl(fd, x, y) ioctlsocket(FD_TO_SOCKET(fd), x, y)
#define socket(x, y, z) SOCKET_TO_FD(socket(x, y, z))
#define accept(x, y, z) SOCKET_TO_FD(accept(x, y, z))

static ssize_t write(int fd, const void *buf, size_t count) {
  return send(FD_TO_SOCKET(fd), buf, NARROW(int, count), 0);
}

static ssize_t read(int fd, void *buf, size_t count) {
  return recv(FD_TO_SOCKET(fd), buf, NARROW(int, count), 0);
}

static int connect__(int fd, const struct sockaddr *addr, socklen_t addrlen) {
  return connect(FD_TO_SOCKET(fd), addr, addrlen);
}
#define connect connect__


// The only way wrk uses this is for making a socket non-blocking.
// We don't care about the other flags and F_GETFL always returns zero.
static int fcntl(int fd, int cmd, int arg) {
  switch (arg) {
    case F_GETFL:
      return 0;
      
    case F_SETFL: {
      SOCKET sock = FD_TO_SOCKET(fd);
      unsigned long on = !!(arg & O_NONBLOCK);
      int r = ioctlsocket(sock, FIONBIO, &on);
      if (r == SOCKET_ERROR)
        return_map_error(-1);
      return 0;
    }
  }
  return_set_error(-1, ERROR_INVALID_PARAMETER);  
}
  
  
static const uint64_t HNS_PER_SEC = 10000000; /* 1 hns == 100 nanoseconds. */
static const uint64_t HNS_PER_USEC = 10;
static const uint64_t EPOCH_DELTA_IN_HNS = 116444736000000000ull; 

struct timezone;

static  int gettimeofday(struct timeval *tv, struct timezone *tz) {
  uint64_t nt_time;
  /* The time zone isn't retrieved by wrk, so that feature is not implemented. */
  assert(tz == NULL);
  GetSystemTimeAsFileTime((FILETIME*) &nt_time); // Infallible.
  // Translate NT (1601) to Unix epoch (1970). Time is still in 100ns units.
  nt_time -= EPOCH_DELTA_IN_HNS;
  // Convert from 100ns units to a (seconds, microseconds) pair.
  tv->tv_sec = (long) (nt_time / HNS_PER_SEC);
  tv->tv_usec = (long) (nt_time % HNS_PER_SEC / HNS_PER_USEC);
  return 0;
}  
