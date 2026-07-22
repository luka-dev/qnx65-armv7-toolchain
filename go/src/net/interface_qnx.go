// Copyright 2026 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// QNX 6.5 network interface enumeration via getifaddrs(3) (libsocket).

package net

import (
	"os"
	"syscall"
	"unsafe"
)

func linkFlags(rawFlags uint32) Flags {
	var f Flags
	if rawFlags&syscall.IFF_UP != 0 {
		f |= FlagUp
	}
	if rawFlags&syscall.IFF_RUNNING != 0 {
		f |= FlagRunning
	}
	if rawFlags&syscall.IFF_BROADCAST != 0 {
		f |= FlagBroadcast
	}
	if rawFlags&syscall.IFF_LOOPBACK != 0 {
		f |= FlagLoopback
	}
	if rawFlags&syscall.IFF_POINTOPOINT != 0 {
		f |= FlagPointToPoint
	}
	if rawFlags&syscall.IFF_MULTICAST != 0 {
		f |= FlagMulticast
	}
	return f
}

func goString(p *byte) string {
	if p == nil {
		return ""
	}
	n := 0
	for {
		c := *(*byte)(unsafe.Add(unsafe.Pointer(p), n))
		if c == 0 {
			break
		}
		n++
	}
	return string(unsafe.Slice(p, n))
}

// interfaceTable returns interfaces. If ifindex is zero, all are returned.
func interfaceTable(ifindex int) ([]Interface, error) {
	head, err := syscall.Getifaddrs()
	if err != nil {
		return nil, os.NewSyscallError("getifaddrs", err)
	}
	defer syscall.Freeifaddrs(head)

	var ifis []Interface
	seen := make(map[int]bool)
	for ifa := head; ifa != nil; ifa = ifa.Next {
		if ifa.Addr == nil || ifa.Addr.Family != syscall.AF_LINK {
			continue
		}
		name := goString(ifa.Name)
		sdl := (*syscall.RawSockaddrDatalink)(unsafe.Pointer(ifa.Addr))
		idx := int(sdl.Index)
		if idx == 0 {
			idx = syscall.IfNametoindex(name)
		}
		if ifindex != 0 && ifindex != idx {
			continue
		}
		// QNX returns more than one AF_LINK entry per interface; keep the first.
		if seen[idx] {
			continue
		}
		seen[idx] = true
		ifi := Interface{
			Index: idx,
			Name:  name,
			Flags: linkFlags(ifa.Flags),
			MTU:   1500,
		}
		// MTU from struct if_data (ifa_data), ifi_mtu is a uint64 at offset 8.
		if ifa.Data != nil {
			mtu := *(*uint64)(unsafe.Add(ifa.Data, 8))
			if mtu > 0 && mtu < 1<<20 {
				ifi.MTU = int(mtu)
			}
		}
		// Hardware address from sockaddr_dl: Data[Nlen : Nlen+Alen].
		if sdl.Alen > 0 && int(sdl.Nlen)+int(sdl.Alen) <= len(sdl.Data) {
			mac := make([]byte, sdl.Alen)
			for i := 0; i < int(sdl.Alen); i++ {
				mac[i] = byte(sdl.Data[int(sdl.Nlen)+i])
			}
			ifi.HardwareAddr = mac
		}
		ifis = append(ifis, ifi)
		if ifindex == idx {
			break
		}
	}
	return ifis, nil
}

// interfaceAddrTable returns addresses. If ifi is nil, all are returned.
func interfaceAddrTable(ifi *Interface) ([]Addr, error) {
	head, err := syscall.Getifaddrs()
	if err != nil {
		return nil, os.NewSyscallError("getifaddrs", err)
	}
	defer syscall.Freeifaddrs(head)

	var addrs []Addr
	for ifa := head; ifa != nil; ifa = ifa.Next {
		if ifa.Addr == nil {
			continue
		}
		if ifi != nil {
			// Match by interface index via the name lookup.
			name := goString(ifa.Name)
			if syscall.IfNametoindex(name) != ifi.Index {
				continue
			}
		}
		var ip IP
		var mask IPMask
		switch ifa.Addr.Family {
		case syscall.AF_INET:
			sa := (*syscall.RawSockaddrInet4)(unsafe.Pointer(ifa.Addr))
			ip = IPv4(sa.Addr[0], sa.Addr[1], sa.Addr[2], sa.Addr[3])
			if ifa.Netmask != nil {
				m := (*syscall.RawSockaddrInet4)(unsafe.Pointer(ifa.Netmask))
				mask = IPv4Mask(m.Addr[0], m.Addr[1], m.Addr[2], m.Addr[3])
			}
		case syscall.AF_INET6:
			sa := (*syscall.RawSockaddrInet6)(unsafe.Pointer(ifa.Addr))
			ip = make(IP, IPv6len)
			copy(ip, sa.Addr[:])
			if ifa.Netmask != nil {
				m := (*syscall.RawSockaddrInet6)(unsafe.Pointer(ifa.Netmask))
				mask = make(IPMask, IPv6len)
				copy(mask, m.Addr[:])
			}
		default:
			continue
		}
		addrs = append(addrs, &IPNet{IP: ip, Mask: mask})
	}
	return addrs, nil
}

func interfaceMulticastAddrTable(ifi *Interface) ([]Addr, error) {
	return nil, nil
}
