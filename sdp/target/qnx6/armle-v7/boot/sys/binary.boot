[
#
# Boot image attributes for plain binary image.
#
# Assumes that control is passed to the startup entry point after loading.
#
# The build file MUST specify load address via the [image=] attribute.
#
attr="?-bigendian"
vboot=0xfe000000
+rsvd_vaddr
pagesizes=4k,64k,1m
+big_pages
]
