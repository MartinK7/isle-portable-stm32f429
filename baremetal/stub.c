#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <time.h>
#include <iconv.h>
#include <signal.h>
#include <unistd.h>

extern ssize_t _write(int fd, const void *buf, size_t count);
#define STUB_ENTRY \
	do { \
		const char *prefix = "[STUB] "; \
		const char *suffix = "() is not implemented!\r\n"; \
		_write(1, prefix, strlen(prefix)); \
		_write(1, __func__, strlen(__func__)); \
		_write(1, suffix, strlen(suffix)); \
	} while(0);

// Linker symbols (normally set by linker script)
void *__exidx_end = 0;
void *__exidx_start = 0;

// System call stubs
void _exit(int status) { STUB_ENTRY while (1); }
int fdatasync(int fd) { STUB_ENTRY return -1; }
int _fstat(int fd, struct stat *st) { STUB_ENTRY return -1; }
pid_t _getpid(void) { STUB_ENTRY return 1; }
int _gettimeofday(struct timeval *tv, void *tz) { STUB_ENTRY return -1; }
int _isatty(int fd) { STUB_ENTRY return 0; }
int _kill(pid_t pid, int sig) { STUB_ENTRY return -1; }
int _stat(const char *path, struct stat *buf) { STUB_ENTRY return -1; }
long sysconf(int name) { STUB_ENTRY return -1; }

// pthread stubs
int pthread_attr_init(pthread_attr_t *attr) { STUB_ENTRY return 0; }
int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate) { STUB_ENTRY return 0; }
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize) { STUB_ENTRY return 0; }
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg) { STUB_ENTRY return -1; }
int pthread_detach(pthread_t thread) { STUB_ENTRY return 0; }
int pthread_getschedparam(pthread_t thread, int *policy,
                          struct sched_param *param) { STUB_ENTRY return 0; }
int pthread_join(pthread_t thread, void **retval) { STUB_ENTRY return 0; }
int pthread_mutexattr_init(pthread_mutexattr_t *attr) { STUB_ENTRY return 0; }
int pthread_mutex_destroy(pthread_mutex_t *mutex) { STUB_ENTRY return 0; }
int pthread_mutex_init(pthread_mutex_t *mutex,
                       const pthread_mutexattr_t *attr) { STUB_ENTRY return 0; }
int pthread_mutex_lock(pthread_mutex_t *mutex) { STUB_ENTRY return 0; }
int pthread_mutex_trylock(pthread_mutex_t *mutex) { STUB_ENTRY return 0; }
int pthread_mutex_unlock(pthread_mutex_t *mutex) { STUB_ENTRY return 0; }
pthread_t pthread_self(void) { STUB_ENTRY return (pthread_t)1; }
int pthread_setschedparam(pthread_t thread, int policy,
                          const struct sched_param *param) { STUB_ENTRY return 0; }
int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset) { STUB_ENTRY return 0; }

// iconv stubs
size_t iconv(iconv_t cd, char **inbuf, size_t *inbytesleft,
             char **outbuf, size_t *outbytesleft) { STUB_ENTRY return (size_t)-1; }
int iconv_close(iconv_t cd) { STUB_ENTRY return 0; }
iconv_t iconv_open(const char *tocode, const char *fromcode) { STUB_ENTRY return (iconv_t)-1; }

// sched stubs
int sched_get_priority_max(int policy) { STUB_ENTRY return 0; }
int sched_get_priority_min(int policy) { STUB_ENTRY return 0; }

// SDL-related stubs
void *get_sdlapi_entry(const char *name) { STUB_ENTRY return NULL; }
uint32_t SDL_GetCurrentTime_REAL(void) { STUB_ENTRY return 0; }
uint64_t SDL_GetPerformanceCounter_REAL(void) { STUB_ENTRY return 0; }
uint64_t SDL_GetPerformanceFrequency_REAL(void) { STUB_ENTRY return 1; }
void SDL_GetSystemTimeLocalePreferences(void *prefs) { STUB_ENTRY }
void SDL_SYS_DelayNS(uint64_t ns) { STUB_ENTRY }
void SDL_TimeToDateTime_REAL(uint64_t time, void *datetime) { STUB_ENTRY }

// signal stub
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact) { STUB_ENTRY return 0; }

