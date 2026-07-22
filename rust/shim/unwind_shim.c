/* QNX 6.5 ARM EHABI: libgcc provides _Unwind_GetIP/_Unwind_GetIPInfo only as
 * inlines in <unwind.h> (built on _Unwind_VRS_Get), so they are not linkable
 * symbols. Rust std references them as extern symbols. Provide real ones. */
typedef unsigned _Uword;
struct _Unwind_Context;
/* _UVRSC_CORE = 0, _UVRSD_UINT32 = 0, ARM PC = core reg 15 */
extern int _Unwind_VRS_Get(struct _Unwind_Context *, int, unsigned, int, void *);

_Uword _Unwind_GetIP(struct _Unwind_Context *ctx) {
    _Uword v = 0;
    _Unwind_VRS_Get(ctx, 0, 15, 0, &v);
    return v & ~(_Uword)1;              /* strip Thumb bit */
}

_Uword _Unwind_GetIPInfo(struct _Unwind_Context *ctx, int *ip_before_insn) {
    if (ip_before_insn) *ip_before_insn = 0;
    return _Unwind_GetIP(ctx);
}
