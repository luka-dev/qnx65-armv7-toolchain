// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// QNX 6.5 / ARM (32-bit) type layouts (from the 6.5 sysroot headers).

package syscall

const (
	sizeofPtr      = 0x4
	sizeofShort    = 0x2
	sizeofInt      = 0x4
	sizeofLong     = 0x4
	sizeofLongLong = 0x8
)

type (
	_C_short     int16
	_C_int       int32
	_C_long      int32
	_C_long_long int64
)

type Timespec struct {
	Sec  int32
	Nsec int32
}

type Timeval struct {
	Sec  int32
	Usec int32
}

// struct stat (QNX 6.5, 32-bit, little-endian: ino/size/blocks are lo+hi pairs).
type Stat_t struct {
	Ino       uint64 // st_ino + st_ino_hi
	Size      int64  // st_size + st_size_hi
	Dev       int32
	Rdev      int32
	Uid       uint32
	Gid       uint32
	Mtim      int32
	Atim      int32
	Ctim      int32
	Mode      uint32
	Nlink     int32
	Blocksize int32
	Nblocks   int32
	Blksize   int32
	Blocks    int64 // st_blocks + hi
}

// struct dirent (QNX 6.5, 32-bit). d_name is a flexible array; use a fixed cap.
type Dirent struct {
	Ino     uint64 // d_ino + d_ino_hi
	Offset  int64  // d_offset + d_offset_hi
	Reclen  uint16
	Namelen uint16
	Name    [256]int8
}

type Rlimit struct {
	Cur uint64
	Max uint64
}

type _Socklen uint32

// BSD-style sockaddrs (QNX has sa_len as the first byte).
type RawSockaddr struct {
	Len    uint8
	Family uint8
	Data   [14]int8
}

type RawSockaddrInet4 struct {
	Len    uint8
	Family uint8
	Port   uint16
	Addr   [4]byte /* in_addr */
	Zero   [8]int8
}

type RawSockaddrInet6 struct {
	Len      uint8
	Family   uint8
	Port     uint16
	Flowinfo uint32
	Addr     [16]byte /* in6_addr */
	Scope_id uint32
}

type RawSockaddrUnix struct {
	Len    uint8
	Family uint8
	Path   [104]int8
}

type RawSockaddrAny struct {
	Addr RawSockaddr
	Pad  [96]int8
}

type Linger struct {
	Onoff  int32
	Linger int32
}

type Iovec struct {
	Base *byte
	Len  uint32
}

type Cmsghdr struct {
	Len   uint32
	Level int32
	Type  int32
}

type Msghdr struct {
	Name       *byte
	Namelen    uint32
	Iov        *Iovec
	Iovlen     uint32
	Control    *byte
	Controllen uint32
	Flags      int32
}

type IPMreq struct {
	Multiaddr [4]byte /* in_addr */
	Interface [4]byte /* in_addr */
}

type IPv6Mreq struct {
	Multiaddr [16]byte /* in6_addr */
	Interface uint32
}

type ICMPv6Filter struct {
	Filt [8]uint32
}

const (
	SizeofSockaddrInet4 = 0x10
	SizeofSockaddrInet6 = 0x1c
	SizeofSockaddrAny   = 0x6c
	SizeofSockaddrUnix  = 0x6a
	SizeofLinger        = 0x8
	SizeofIPMreq        = 0x8
	SizeofIPv6Mreq      = 0x14
	SizeofMsghdr        = 0x1c
	SizeofCmsghdr       = 0xc
	SizeofICMPv6Filter  = 0x20
)
