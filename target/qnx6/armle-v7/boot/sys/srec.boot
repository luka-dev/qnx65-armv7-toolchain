[
#
# Boot image attributes for an S-record format image.
#
# The build file MUST specify load address via the [image=] attribute.
#
attr="?-bigendian"
vboot=0xfe000000
+rsvd_vaddr
filter="mkifsf_srec %a %I %i"
pagesizes=4k,64k,1m
+big_pages
]
