#ifndef	__unp_h
#define	__unp_h

/*-------------------------------------------------*/
#include	<stdarg.h>		/* ANSI C header file */
#include	<syslog.h>		/* for syslog() */
#include <stdio.h>
#include <errno.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */

#include <unistd.h>

#include <arpa/inet.h>

#include <sys/select.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <sys/time.h>

#include <sys/ioctl.h>

#include <signal.h>

#include <sys/types.h>
#include <sys/wait.h>

/*-------------------------------------------------*/
#define	MAXLINE		4096	/* max text line length */
#define	SA	struct sockaddr
#define	LISTENQ		1024	/* 2nd argument to listen() */


#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
					/* default file access permissions for new files */
#define	DIR_MODE	(FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)
					/* default permissions for new directories */

#define	SERV_PORT		 12345			/* TCP and UDP */

typedef	void	Sigfunc(int);	/* for signal handlers */


/*-------------------------------------------------*/


			/* prototypes for our stdio wrapper functions: see {Sec errors} */
void	 Fclose(FILE *);
FILE	*Fdopen(int, const char *);
char	*Fgets(char *, int, FILE *);
FILE	*Fopen(const char *, const char *);
void	 Fputs(const char *, FILE *);


/*-------------------------------------------------*/




/* prototypes for our own library wrapper functions */
// void	 Connect_timeo(int, const SA *, socklen_t, int);
// int		 Family_to_level(int);
// struct addrinfo *Host_serv(const char *, const char *, int, int);
const char		*Inet_ntop(int, const void *, char *, size_t);
void			 Inet_pton(int, const char *, void *);
// char			*If_indextoname(unsigned int, char *);
// unsigned int		 If_nametoindex(const char *);
// struct if_nameindex	*If_nameindex(void);
// char   **My_addrs(int *);
// ssize_t	 Read_fd(int, void *, size_t, int *);
// int		 Readable_timeo(int, int);
// ssize_t	 Recvfrom_flags(int, void *, size_t, int *, SA *, socklen_t *, struct unp_in_pktinfo *);
// Sigfunc *Signal(int, Sigfunc *);
// Sigfunc *Signal_intr(int, Sigfunc *);
// int		 Sock_bind_wild(int, int);
// char	*Sock_ntop(const SA *, socklen_t);
// char	*Sock_ntop_host(const SA *, socklen_t);
// int		 Sockfd_to_family(int);
// int		 Tcp_connect(const char *, const char *);
// int		 Tcp_listen(const char *, const char *, socklen_t *);
// int		 Udp_client(const char *, const char *, SA **, socklen_t *);
// int		 Udp_connect(const char *, const char *);
// int		 Udp_server(const char *, const char *, socklen_t *);
// ssize_t	 Write_fd(int, void *, size_t, int);
// int		 Writable_timeo(int, int);


/*-------------------------------------------------*/
//wrapunix.c

void	*Calloc(size_t, size_t);
void	 Close(int);
void	 Dup2(int, int);
int		 Fcntl(int, int, int);
void	 Gettimeofday(struct timeval *, void *);
int		 Ioctl(int, int, void *);
pid_t	 Fork(void);
void	*Malloc(size_t);
int	 Mkstemp(char *);
void	*Mmap(void *, size_t, int, int, int, off_t);
int		 Open(const char *, int, mode_t);
void	 Pipe(int *fds);
ssize_t	 Read(int, void *, size_t);
void	 Sigaddset(sigset_t *, int);
void	 Sigdelset(sigset_t *, int);
void	 Sigemptyset(sigset_t *);
void	 Sigfillset(sigset_t *);
int		 Sigismember(const sigset_t *, int);
void	 Sigpending(sigset_t *);
void	 Sigprocmask(int, const sigset_t *, sigset_t *);
char	*Strdup(const char *);
long	 Sysconf(int);
void	 Sysctl(int *, u_int, void *, size_t *, void *, size_t);
void	 Unlink(const char *);
pid_t	 Wait(int *);
pid_t	 Waitpid(pid_t, int *, int);
void	 Write(int, void *, size_t);



/*-------------------------------------------------*/
//wrapsock.c

int		 Accept(int, SA *, socklen_t *);
void	 Bind(int, const SA *, socklen_t);
void	 Connect(int, const SA *, socklen_t);
void	 Getpeername(int, SA *, socklen_t *);
void	 Getsockname(int, SA *, socklen_t *);
void	 Getsockopt(int, int, int, void *, socklen_t *);
#ifdef	HAVE_INET6_RTH_INIT
int		 Inet6_rth_space(int, int);
void	*Inet6_rth_init(void *, socklen_t, int, int);
void	 Inet6_rth_add(void *, const struct in6_addr *);
void	 Inet6_rth_reverse(const void *, void *);
int		 Inet6_rth_segments(const void *);
struct in6_addr *Inet6_rth_getaddr(const void *, int);
#endif
#ifdef	HAVE_KQUEUE
int		 Kqueue(void);
int		 Kevent(int, const struct kevent *, int,
				struct kevent *, int, const struct timespec *);
#endif
void	 Listen(int, int);
#ifdef	HAVE_POLL
int		 Poll(struct pollfd *, unsigned long, int);
#endif
ssize_t	 Readline(int, void *, size_t);
ssize_t	 Readn(int, void *, size_t);
ssize_t	 Recv(int, void *, size_t, int);
ssize_t	 Recvfrom(int, void *, size_t, int, SA *, socklen_t *);
ssize_t	 Recvmsg(int, struct msghdr *, int);
int		 Select(int, fd_set *, fd_set *, fd_set *, struct timeval *);
void	 Send(int, const void *, size_t, int);
void	 Sendto(int, const void *, size_t, int, const SA *, socklen_t);
void	 Sendmsg(int, const struct msghdr *, int);
void	 Setsockopt(int, int, int, const void *, socklen_t);
void	 Shutdown(int, int);
int		 Sockatmark(int);
int		 Socket(int, int, int);
void	 Socketpair(int, int, int, int *);
void	 Writen(int, void *, size_t);



/*-------------------------------------------------*/
//error.c

void	 err_dump(const char *, ...);
void	 err_msg(const char *, ...);
void	 err_quit(const char *, ...);
void	 err_ret(const char *, ...);
void	 err_sys(const char *, ...);




#endif

