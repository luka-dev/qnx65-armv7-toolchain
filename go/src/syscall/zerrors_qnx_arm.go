// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// QNX 6.5 / ARM errno and constant values (from the 6.5 sysroot headers).

package syscall

// Errno values (errno.h).
const (
	EPERM           = Errno(1)
	ENOENT          = Errno(2)
	ESRCH           = Errno(3)
	EINTR           = Errno(4)
	EIO             = Errno(5)
	ENXIO           = Errno(6)
	E2BIG           = Errno(7)
	ENOEXEC         = Errno(8)
	EBADF           = Errno(9)
	ECHILD          = Errno(10)
	EAGAIN          = Errno(11)
	ENOMEM          = Errno(12)
	EACCES          = Errno(13)
	EFAULT          = Errno(14)
	ENOTBLK         = Errno(15)
	EBUSY           = Errno(16)
	EEXIST          = Errno(17)
	EXDEV           = Errno(18)
	ENODEV          = Errno(19)
	ENOTDIR         = Errno(20)
	EISDIR          = Errno(21)
	EINVAL          = Errno(22)
	ENFILE          = Errno(23)
	EMFILE          = Errno(24)
	ENOTTY          = Errno(25)
	ETXTBSY         = Errno(26)
	EFBIG           = Errno(27)
	ENOSPC          = Errno(28)
	ESPIPE          = Errno(29)
	EROFS           = Errno(30)
	EMLINK          = Errno(31)
	EPIPE           = Errno(32)
	EDOM            = Errno(33)
	ERANGE          = Errno(34)
	EDEADLK         = Errno(45)
	ENOLCK          = Errno(46)
	ECANCELED       = Errno(47)
	ENOTSUP         = Errno(48)
	EILSEQ          = Errno(88)
	ENOSYS          = Errno(89)
	ELOOP           = Errno(90)
	ENOTEMPTY       = Errno(93)
	EOPNOTSUPP      = Errno(103)
	EOVERFLOW       = Errno(79)
	ENAMETOOLONG    = Errno(78)
	ETIME           = Errno(62)
	EWOULDBLOCK     = EAGAIN
	EINPROGRESS     = Errno(236)
	EALREADY        = Errno(237)
	ENOTSOCK        = Errno(238)
	EDESTADDRREQ    = Errno(239)
	EMSGSIZE        = Errno(240)
	EPROTOTYPE      = Errno(241)
	ENOPROTOOPT     = Errno(242)
	EPROTONOSUPPORT = Errno(243)
	EAFNOSUPPORT    = Errno(247)
	EADDRINUSE      = Errno(248)
	EADDRNOTAVAIL   = Errno(249)
	ENETDOWN        = Errno(250)
	ENETUNREACH     = Errno(251)
	ECONNABORTED    = Errno(253)
	ECONNRESET      = Errno(254)
	ENOBUFS         = Errno(255)
	EISCONN         = Errno(256)
	ENOTCONN        = Errno(257)
	ESHUTDOWN       = Errno(258)
	ETIMEDOUT       = Errno(260)
	ECONNREFUSED    = Errno(261)
	EHOSTDOWN       = Errno(264)
	EHOSTUNREACH    = Errno(265)
)

// Signal numbers (QNX order — see runtime/defs_qnx_arm.go).
const (
	SIGHUP   = Signal(1)
	SIGINT   = Signal(2)
	SIGQUIT  = Signal(3)
	SIGILL   = Signal(4)
	SIGTRAP  = Signal(5)
	SIGABRT  = Signal(6)
	SIGFPE   = Signal(8)
	SIGKILL  = Signal(9)
	SIGBUS   = Signal(10)
	SIGSEGV  = Signal(11)
	SIGSYS   = Signal(12)
	SIGPIPE  = Signal(13)
	SIGALRM  = Signal(14)
	SIGTERM  = Signal(15)
	SIGURG   = Signal(21)
	SIGSTOP  = Signal(23)
	SIGTSTP  = Signal(24)
	SIGCONT  = Signal(25)
	SIGCHLD  = Signal(18)
	SIGTTIN  = Signal(26)
	SIGTTOU  = Signal(27)
	SIGIO    = Signal(22)
	SIGWINCH = Signal(20)
	SIGUSR1  = Signal(16)
	SIGUSR2  = Signal(17)
)

// open/fcntl flags (fcntl.h, octal in the header).
const (
	O_RDONLY    = 0x0
	O_WRONLY    = 0x1
	O_RDWR      = 0x2
	O_APPEND    = 0x8
	O_SYNC      = 0x20
	O_NONBLOCK  = 0x80
	O_CREAT     = 0x100
	O_TRUNC     = 0x200
	O_EXCL      = 0x400
	O_NOCTTY    = 0x800
	O_CLOEXEC   = 0x2000
	O_NDELAY    = O_NONBLOCK
	O_DSYNC     = 0x10
	O_LARGEFILE = 0x8000
	// QNX 6.5 has neither O_DIRECTORY nor O_NOFOLLOW; 0 makes them no-ops.
	// ponytail: os.Root symlink protection is weakened without O_NOFOLLOW.
	O_DIRECTORY = 0x0
	O_NOFOLLOW  = 0x0

	// File type / mode bits (sys/stat.h).
	S_IFMT   = 0xF000
	S_IFIFO  = 0x1000
	S_IFCHR  = 0x2000
	S_IFDIR  = 0x4000
	S_IFBLK  = 0x6000
	S_IFREG  = 0x8000
	S_IFLNK  = 0xA000
	S_IFSOCK = 0xC000
	S_ISUID  = 0x800
	S_ISGID  = 0x400
	S_ISVTX  = 0x200
	S_IRUSR  = 0x100
	S_IWUSR  = 0x80
	S_IXUSR  = 0x40
	S_IRWXU  = 0x1C0
	S_IRGRP  = 0x20
	S_IWGRP  = 0x10
	S_IXGRP  = 0x8
	S_IROTH  = 0x4
	S_IWOTH  = 0x2
	S_IXOTH  = 0x1

	F_DUPFD = 0
	// QNX 6.5 has no F_DUPFD_CLOEXEC; 0 disables the fast path in
	// internal/poll.DupCloseOnExec, which falls back to F_DUPFD + FD_CLOEXEC.
	F_DUPFD_CLOEXEC = 0
	F_GETFD         = 1
	F_SETFD         = 2
	F_GETFL         = 3
	F_SETFL         = 4
	F_GETLK         = 14
	F_SETLK         = 6
	F_SETLKW        = 7

	FD_CLOEXEC = 0x1
)

// Socket constants (socket.h / netinet/in.h).
const (
	AF_UNSPEC = 0
	AF_INET   = 2
	AF_INET6  = 24
	AF_LOCAL  = 1
	AF_UNIX   = AF_LOCAL

	SOCK_STREAM    = 1
	SOCK_DGRAM     = 2
	SOCK_RAW       = 3
	SOCK_SEQPACKET = 5
	SOCK_RDM       = 4

	SOL_SOCKET   = 0xffff
	SO_REUSEADDR = 0x0004
	SO_REUSEPORT = 0x0200
	SO_KEEPALIVE = 0x0008
	SO_BROADCAST = 0x0020
	SO_LINGER    = 0x0080
	SO_ERROR     = 0x1007
	SO_TYPE      = 0x1008
	SO_RCVBUF    = 0x1002
	SO_SNDBUF    = 0x1001
	SO_RCVTIMEO  = 0x1006
	SO_SNDTIMEO  = 0x1005

	IPPROTO_IP   = 0
	IPPROTO_ICMP = 1
	IPPROTO_TCP  = 6
	IPPROTO_UDP  = 17
	IPPROTO_IPV6 = 41

	// TCP options (QNX 6.5 has only TCP_KEEPALIVE, no idle/intvl/cnt split).
	TCP_NODELAY   = 0x01
	TCP_MAXSEG    = 0x02
	TCP_KEEPALIVE = 0x04

	// IPv4 options (netinet/in.h).
	IP_TOS             = 3
	IP_TTL             = 4
	IP_MULTICAST_IF    = 9
	IP_MULTICAST_TTL   = 10
	IP_MULTICAST_LOOP  = 11
	IP_ADD_MEMBERSHIP  = 12
	IP_DROP_MEMBERSHIP = 13

	// IPv6 options (netinet6/in6.h).
	IPV6_UNICAST_HOPS   = 4
	IPV6_MULTICAST_IF   = 9
	IPV6_MULTICAST_HOPS = 10
	IPV6_MULTICAST_LOOP = 11
	IPV6_JOIN_GROUP     = 12
	IPV6_LEAVE_GROUP    = 13
	IPV6_V6ONLY         = 27
	IPV6_TCLASS         = 61

	SHUT_RD   = 0
	SHUT_WR   = 1
	SHUT_RDWR = 2

	SCM_RIGHTS = 0x1

	MSG_OOB       = 0x0001
	MSG_PEEK      = 0x0002
	MSG_DONTROUTE = 0x0004
)

// rlimit
const (
	SOMAXCONN     = 0x80
	RLIMIT_NOFILE = 5
	RLIM_INFINITY = 1<<63 - 1
)

// exec syscall number placeholder (unused on the libc-call model).
const SYS_EXECVE = 0

// errors maps errno -> message for Errno.Error(). Minimal set.
var errors = [...]string{
	1:   "operation not permitted",
	2:   "no such file or directory",
	4:   "interrupted system call",
	9:   "bad file descriptor",
	11:  "resource temporarily unavailable",
	12:  "not enough space",
	13:  "permission denied",
	14:  "bad address",
	17:  "file exists",
	22:  "invalid argument",
	24:  "too many open files",
	32:  "broken pipe",
	89:  "function not implemented",
	260: "connection timed out",
}

// signals maps signal number -> name for Signal.String().
var signals = [...]string{
	1:  "hangup",
	2:  "interrupt",
	9:  "killed",
	11: "segmentation fault",
	13: "broken pipe",
	15: "terminated",
	21: "urgent I/O condition",
}
