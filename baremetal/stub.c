#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <time.h>
#include <iconv.h>
#include <signal.h>
#include <unistd.h>

// Linker symbols (normally set by linker script)
void *_ebss = 0;
void *__exidx_end = 0;
void *__exidx_start = 0;
void *_sbss = 0;

// System call stubs
int _close(int fd) { return -1; }
void _exit(int status) { while (1); }
int fdatasync(int fd) { return -1; }
int _fstat(int fd, struct stat *st) { return -1; }
pid_t _getpid(void) { return 1; }
int _gettimeofday(struct timeval *tv, void *tz) { return -1; }
int _isatty(int fd) { return 0; }
int _kill(pid_t pid, int sig) { return -1; }
off_t _lseek(int fd, off_t offset, int whence) { return -1; }
int _open(const char *pathname, int flags, ...) { return -1; }
ssize_t _read(int fd, void *buf, size_t count) { return -1; }
caddr_t _sbrk(int incr) { return (caddr_t)-1; }
int _stat(const char *path, struct stat *buf) { return -1; }
long sysconf(int name) { return -1; }
ssize_t _write(int fd, const void *buf, size_t count) { return -1; }

// pthread stubs
int pthread_attr_init(pthread_attr_t *attr) { return 0; }
int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate) { return 0; }
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize) { return 0; }
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine)(void *), void *arg) { return -1; }
int pthread_detach(pthread_t thread) { return 0; }
int pthread_getschedparam(pthread_t thread, int *policy,
                          struct sched_param *param) { return 0; }
int pthread_join(pthread_t thread, void **retval) { return 0; }
int pthread_mutexattr_init(pthread_mutexattr_t *attr) { return 0; }
int pthread_mutex_destroy(pthread_mutex_t *mutex) { return 0; }
int pthread_mutex_init(pthread_mutex_t *mutex,
                       const pthread_mutexattr_t *attr) { return 0; }
int pthread_mutex_lock(pthread_mutex_t *mutex) { return 0; }
int pthread_mutex_trylock(pthread_mutex_t *mutex) { return 0; }
int pthread_mutex_unlock(pthread_mutex_t *mutex) { return 0; }
pthread_t pthread_self(void) { return (pthread_t)1; }
int pthread_setschedparam(pthread_t thread, int policy,
                          const struct sched_param *param) { return 0; }
int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset) { return 0; }

// iconv stubs
size_t iconv(iconv_t cd, char **inbuf, size_t *inbytesleft,
             char **outbuf, size_t *outbytesleft) { return (size_t)-1; }
int iconv_close(iconv_t cd) { return 0; }
iconv_t iconv_open(const char *tocode, const char *fromcode) { return (iconv_t)-1; }

// sched stubs
int sched_get_priority_max(int policy) { return 0; }
int sched_get_priority_min(int policy) { return 0; }

// SDL-related stubs
void *get_sdlapi_entry(const char *name) { return NULL; }
uint32_t SDL_GetCurrentTime_REAL(void) { return 0; }
uint64_t SDL_GetPerformanceCounter_REAL(void) { return 0; }
uint64_t SDL_GetPerformanceFrequency_REAL(void) { return 1; }
void SDL_GetSystemTimeLocalePreferences(void *prefs) {}
void SDL_SYS_DelayNS(uint64_t ns) {}
void SDL_TimeToDateTime_REAL(uint64_t time, void *datetime) {}

// signal stub
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact) { return 0; }

