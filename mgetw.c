#include "mstdio.h"longmgetw(	register M_FILE *iop){	register i;	register char *p;	int w;	p = (char *)&w;	for (i=sizeof(int); --i>=0;)		*p++ = mgetc(iop);	if (mfeof(iop))		return(EOF);	return(w);}