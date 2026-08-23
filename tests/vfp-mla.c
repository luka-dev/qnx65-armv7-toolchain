#include <stdio.h>
/* Each expression lives in its own noinline function so the product is used
   exactly once - that is what lets GCC fuse it into a VFP multiply-accumulate.
   Inline them, or reuse a*b twice, and GCC emits plain vmul+vsub instead and
   the test proves nothing. */
__attribute__((noinline)) static float f_mls (float a, float b, float c){ return c - a*b; }
__attribute__((noinline)) static float f_nmls(float a, float b, float c){ return a*b - c; }
__attribute__((noinline)) static float f_nmla(float a, float b, float c){ return -(c + a*b); }
volatile float A = 3.0f, B = 4.0f, C = 100.0f;
int main(void){
    float a=A, b=B, c=C;
    printf("c-a*b    = %.1f (expect 88.0)\n",    f_mls (a,b,c));
    printf("a*b-c    = %.1f (expect -88.0)\n",   f_nmls(a,b,c));
    printf("-(c+a*b) = %.1f (expect -112.0)\n",  f_nmla(a,b,c));
    return 0;
}
