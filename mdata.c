#include "mstdio.h"/* Pointers to dynamically allocated array of pointers to M_FILE structures */M_FILE	**_miob_start = (M_FILE **)0;M_FILE	**_miob_end;#define active(iop) ((iop)->_flag & (_MIOREAD|_MIOWRT|_MIORW))void_mfwalk(	register long (*function)()){	if (_miob_start != NULL) 	{		/* Step through all the M_FILE structures.		 */		register M_FILE **iov;		for (iov = _miob_start; iov < _miob_end; iov++)			if (*iov != NULL && active(*iov))				(*function)(*iov);	}}void_mcleanup(void){	_mfwalk(mfclose);}