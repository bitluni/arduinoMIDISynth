//LITTLE ENDIAN ONLY
//gcc still isn't intelligent enoug to discard unsuded bytes after casts and multiplications. 
//what a bummer wasting majority of the cpu cycles

typedef unsigned char  uf0p8;

typedef char           f8p0;
typedef unsigned char  uf8p0;

typedef short          f16p0;
typedef unsigned short uf16p0;

typedef unsigned short uf0p16;

typedef long           f32p0;
typedef unsigned long  uf32p0;

typedef long           f8p24;
typedef long           f16p16;
typedef long           f24p8;

typedef unsigned long  uf8p24;
typedef unsigned long  uf16p16;
typedef unsigned long  uf24p8;

typedef unsigned long  f8p8;
typedef unsigned long  uf8p8;

#define f8p24_1     0x1000000
#define f16p16_1    0x10000
#define uf8p24_1    0x1000000
#define uf16p16_1   0x10000
#define f8p8_1      0x100
#define uf8p8_1     0x100

inline f8p0 cast_f8p24_f8p0(f8p24 a)
{
  return ((f8p0*)&a)[3];
}

inline uf8p0 cast_uf8p24_uf8p0(uf8p24 a)
{
  return ((uf8p0*)&a)[3];
}
  
inline f8p0 cast_uf8p0_f8p0(uf8p0 a)
{
  return (f8p0)a;
}

inline uf8p0 cast_f8p0_uf8p0(f8p0 a)
{
  return (uf8p0)a;
}

inline f8p8 cast_f8p24_f8p8(f24p8 a)
{
  f8p8 c;
  ((char*)&c)[0] = ((char*)&a)[2];
  ((char*)&c)[1] = ((char*)&a)[3];
  return c;
}

inline uf8p8 cast_uf8p24_uf8p8(uf24p8 a)
{
  uf8p8 c;
  ((char*)&c)[0] = ((char*)&a)[2];
  ((char*)&c)[1] = ((char*)&a)[3];
  return c;
}

inline f8p8 cast_f16p16_f8p8(f16p16 a)
{
  f8p8 c;
  ((char*)&c)[0] = ((char*)&a)[1];
  ((char*)&c)[1] = ((char*)&a)[2];
  return c;
}

inline f8p0 cast_f24p8_f8p0(f8p24 a)
{
  return ((f8p0*)&a)[3];
}

inline f8p0 cast_f16p16_f8p0(f16p16 a)
{
  return ((f8p0*)&a)[2];
}

inline f8p8 mul_f8p8_uf0p8_f8p8(f8p8 a, uf0p8 b)
{
  f16p16 c = a * b;
  return cast_f16p16_f8p8(c);
}

inline f8p0 mul_f8p8_uf0p8_f8p0(f8p8 a, uf0p8 b)
{
  f16p16 c = a * b;
  return cast_f16p16_f8p0(c);
}

inline f8p0 mul_f8p8_uf0p16_f8p0(f8p8 a, uf0p16 b)
{
  f8p24 c = a * b;
  return cast_f8p24_f8p0(c);
}

inline uf0p8 cast_uf8p24_uf0p8(uf8p24 a)
{
  return ((uf0p8*)&a)[2];
}

inline uf0p16 cast_f8p24_uf0p16(f8p24 a)
{
  uf0p16 c;
  ((char*)&c)[0] = ((char*)&a)[1];
  ((char*)&c)[1] = ((char*)&a)[2];
  return c;
}

inline uf0p16 cast_uf8p24_uf0p16(uf8p24 a)
{  
  uf0p16 c;
  ((char*)&c)[0] = ((char*)&a)[1];
  ((char*)&c)[1] = ((char*)&a)[2];
  return c;
}

inline f8p0 cast_f8p8_f8p0(f8p8 a)
{
  return ((f8p0*)&a)[1];
}

inline uf0p8 cast_uf0p16_uf0p8(f8p8 a)
{
  return ((uf0p8*)&a)[1];
}

inline f8p0 mul_f8p0_uf0p8_f8p0(f8p0 a, uf0p8 b)
{
  f8p8 c = a * b;
  return cast_f8p8_f8p0(c);
}

inline uf0p8 cast_uf0p16_uf0p8(uf0p16 a)
{
  return ((uf0p8*)&a)[1];
}

inline uf0p16 mul_uf0p16_uf0p8_uf0p16(uf0p16 a, uf0p8 b)
{
  uf0p16 c1 = ((uf8p0*)&a)[0] * b;
  uf0p16 c2 = ((uf8p0*)&a)[1] * b + ((uf8p0*)&c1)[1];
  return c2;
}

inline f8p0 mul_uf0p8_uf0p8_uf0p8(uf0p8 a, uf0p8 b)
{
  uf0p16 c = a * b;
  return cast_uf0p16_uf0p8(c);
}
