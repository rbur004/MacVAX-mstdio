#include	"mstdio.h"M_FILE *mfopen(	char 	*file,	short   vrefnum,	char	*mode){//	extern	M_FILE *_mdoopen();//	extern	M_FILE *_mfindiop();	M_FILE *fp;	fp = _mfindiop();	if (fp == NULL) 		/* errno is set by _findiop so we wouldn't worry about		 * it here - 002 		 */ 		return (NULL);	return(_mdoopen(file,vrefnum,mode,fp));}