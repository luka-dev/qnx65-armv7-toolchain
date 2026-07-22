[
#
# Boot image attributes for an ELF format image.
#
# The build file MUST specify load address via the [image=] attribute.
#
attr="?-bigendian"
vboot=0xfe000000
+rsvd_vaddr
len=0x180
filter="mkifsf_elf %a %s %i"
pagesizes=4k,64k,1m
+big_pages
]
