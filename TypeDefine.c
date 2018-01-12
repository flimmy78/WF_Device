#include "TypeDefine.h"

/* Given the high and low-order 32-bit quantities HI and LO, return a u64
   value representing (HI << 32) + LO.  */
u64 u64_Init (unsigned long hi, unsigned long lo)
{
	u64 r;
	r.hi = hi;
	r.lo = lo;
	return r;
}
/* Return a u64 value representing LO.  */
u64 u64_lo (unsigned long lo)
{
	u64 r;
	r.hi = 0;
	r.lo = lo;
	return r;
}
u64 u64_hi (unsigned long hi)
{
	u64 r;
	r.hi = hi;
	r.lo = 0;
	return r;
}
unsigned char u64_lt (u64 x, u64 y)
{
	return x.hi < y.hi || (x.hi == y.hi && x.lo < y.lo);
}
/* Return X & Y.  */
u64 u64_and (u64 x, u64 y)
{
	u64 r;
	r.hi = x.hi & y.hi;
	r.lo = x.lo & y.lo;
	return r;
}
/* Return X | Y.  */
u64 u64_or (u64 x, u64 y)
{
	u64 r;
	r.hi = x.hi | y.hi;
	r.lo = x.lo | y.lo;
	return r;
}
/* Return X ^ Y.  */
u64 u64_xor (u64 x, u64 y)
{
	u64 r;
	r.hi = x.hi ^ y.hi;
	r.lo = x.lo ^ y.lo;
	return r;
}
/* Return X + Y.  */
u64 u64_plus (u64 x, unsigned long hi,unsigned long lo)
{
	u64 r;
	r.lo = x.lo + lo;
	r.hi = x.hi + hi + (r.lo < x.lo);
	return r;
}
/* Return X - Y.  */
u64 u64_decrease (u64 x, unsigned long hi,unsigned long lo)
{
	u64 r;
	if(x.lo<lo)
	{
		x.hi--;
		r.lo=(0xffffffff-lo)+x.lo+1;
	}
	else
		r.lo=x.lo-lo;
	r.hi=x.hi-hi;
	return r;
}
/* Return X << N.  */
u64 u64_shl (u64 x, int n)
{
	u64 r;
	if (n < 32)
	{
		r.hi = (x.hi << n) | (x.lo >> (32 - n));
		r.lo = x.lo << n;
	}
	else
	{
		r.hi = x.lo << (n - 32);
		r.lo = 0;
	}
	return r;
}
/* Return X >> N.  */
u64 u64_shr (u64 x, int n)
{
	u64 r;
	if (n < 32)
	{
		r.hi = x.hi >> n;
		r.lo = (x.hi << (32 - n)) | (x.lo >> n);
	}
	else
	{
		r.hi = 0;
		r.lo = x.hi >> (n - 32);
	}
	return r;
}
u64 u64_lmul(unsigned long multiplier, unsigned long multiplicand)
{
	u64	product,m1;
	product=u64_Init(0,0);
	m1=u64_lo(multiplicand);
	do 
	{		
		if(multiplier & 1)
		{
			product =u64_plus(product,m1.hi,m1.lo);
		}
		m1=u64_shl(m1,1);
		multiplier >>=1;
	} while(multiplier!=0);
	return product;
}
u64 u64_lmuu64(u64 multiplicand, unsigned long multiplier)
{
	u64	product;
	product=u64_Init(0,0);
	do 
	{		
		if(multiplier & 1)
		{
			product =u64_plus(product, multiplicand.hi,multiplicand.lo);
		}
		multiplicand=u64_shl(multiplicand,1);
		multiplier >>=1;//u64_shr(multiplier,1);
	} while(multiplier!= 0 );
	return product;
}
u64 u64_u64muu64(u64 multiplier, unsigned long hi,unsigned long lo)
{
	u64	product,multiplicand;
	product=u64_Init(0,0);
	multiplicand=u64_Init(hi,lo);
	do 
	{		
		if(multiplier.lo & 1)
		{
			product =u64_plus(product, multiplicand.hi,multiplicand.lo);
		}
		multiplicand=u64_shl(multiplicand,1);
		multiplier =u64_shr(multiplier,1);
	} while(multiplier.lo != 0 || multiplier.hi!=0);
	return product;
}







  
