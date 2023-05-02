#include <stdio.h>
#include <stdint.h>
#ifndef __clang__
#include <stdfix.h>
#endif

typedef union u_ak u_ak;
union u_ak {
  _Accum ak;
  uint8_t ak_x[sizeof(_Accum)];
};

/*
 *  MARK:  show_be()
 */
inline
static
char * show_be(char * str, size_t const sz, uint8_t const akx[]) {
  char * ostr = str;  //  working ptr, preserve str ptr
  for (size_t k_ = 0ul; k_ < sz; ++k_) {
    sprintf(ostr, "%02x ", akx[k_]);
    ostr += 3;  //  bump ptr to next output loc.
  }
  *(--ostr) = '\0';  //  remove trailing space
  
  return str;
}

/*
 *  MARK:  show_le()
 */
inline
static
char * show_le(char * str, size_t const sz, uint8_t const akx[]) {
  char * ostr = str;  //  working ptr, preserve str ptr
  for (ssize_t k_ = sz - 1l; k_ >= 0l; --k_) {
    sprintf(ostr, "%02x ", akx[k_]);
    ostr += 3;  //  bump ptr to next output loc.
  }
  *(--ostr) = '\0';  //  remove trailing space
  return str;
}

/*
 *  MARK:  main()
 */
int main(int argc, char const * argv[]) {
  printf("FixedPoint00\n");

  char str_be[512];
  char str_le[512];

  _Accum a1 = 1.0k;
  _Fract f1 = 0.5r;
  _Accum ar = a1 * f1;
  u_ak uak1 = { .ak = ar, };

  // printf("%k\n", ar);
  printf("%10.3f : %s - %s\n",
         (double) uak1.ak,
         show_be(str_be, sizeof(uak1.ak), uak1.ak_x),
         show_le(str_le, sizeof(uak1.ak), uak1.ak_x));

  uak1.ak = -uak1.ak;
  printf("%10.3f : %s - %s\n",
         (double) uak1.ak,
         show_be(str_be, sizeof(uak1.ak), uak1.ak_x),
         show_le(str_le, sizeof(uak1.ak), uak1.ak_x));

  ar = ar * 10.0k;
  uak1.ak = ar;
  // printf("%k\n", ar);
  printf("%10.3f : %s - %s\n",
         (double) uak1.ak,
         show_be(str_be, sizeof(uak1.ak), uak1.ak_x),
         show_le(str_le, sizeof(uak1.ak), uak1.ak_x));

  uak1.ak = -uak1.ak;
  printf("%10.3f : %s - %s\n",
         (double) uak1.ak,
         show_be(str_be, sizeof(uak1.ak), uak1.ak_x),
         show_le(str_le, sizeof(uak1.ak), uak1.ak_x));

  ar = ar * 10.0k;
  uak1.ak = ar;
  // printf("%k\n", ar);
  printf("%10.3f : %s - %s\n",
         (double) uak1.ak,
         show_be(str_be, sizeof(uak1.ak), uak1.ak_x),
         show_le(str_le, sizeof(uak1.ak), uak1.ak_x));

  uak1.ak = -uak1.ak;
  printf("%10.3f : %s - %s\n",
         (double) uak1.ak,
         show_be(str_be, sizeof(uak1.ak), uak1.ak_x),
         show_le(str_le, sizeof(uak1.ak), uak1.ak_x));

  ar = ar * 2.0k;
  uak1.ak = ar;
  // printf("%k\n", ar);
  printf("%10.3f : %s - %s\n",
         (double) uak1.ak,
         show_be(str_be, sizeof(uak1.ak), uak1.ak_x),
         show_le(str_le, sizeof(uak1.ak), uak1.ak_x));

  uak1.ak = -uak1.ak;
  printf("%10.3f : %s - %s\n",
         (double) uak1.ak,
         show_be(str_be, sizeof(uak1.ak), uak1.ak_x),
         show_le(str_le, sizeof(uak1.ak), uak1.ak_x));

  return 0;
}

//    0    0     0    0     4    0     0    0
// 0000 0000  0000 0000  0010 0000  0000 0000
//    f    f     f    f     c    0     0    0
// 1111 1111  1111 1111  1100 0000  0000 0000

//    0    0     0    2     8    0     0    0
// 0000 0000  0000 0010  1000 0000  0000 0000
//    f    f     f    d     8    0     0    0 
// 1111 1111  1111 1101  1000 0000  0000 0000
