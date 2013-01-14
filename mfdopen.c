/* * Unix routine to do an "fopen" on file descriptor * The mode has to be repeated because you can't query its * status */#include 	<Unix_errno.h>#include	<types.h>#include	"file.h"#include	"mstdio.h"#include 	"macio.h"M_FILE *mfdopen(	long fd,	register char *mode){	register M_FILE 	*iop;	/* Call _findiop(), to get a pointer to an unused M_FILE structure.	 */	iop = _mfindiop();	if (iop != NULL) {		/* Initialize the structure, then return the pointer		 */		iop->_cnt = 0;		iop->_file = fd;		iop->_bufsiz = 0;		iop->_base = iop->_ptr = NULL ;		switch (*mode) {			case 'r':				iop->_flag = _MIOREAD ;				break;			/* Append mode is handled differently in the System			 * V environment.  In that environment files opened			 * with "a" or "a+" are really opened with O_APPEND.			 * This functionality is provided by the "A" and "A+"			 * modes in the ULTRIX environment.			 */			case 'a': #ifndef SYSTEM_FIVE		/* Same as BSD "append modes" */				(void)mlseek(fd, (off_t)0, L_XTND);				iop->_flag = _MIOWRT;				break;			case 'A':#endif				/* Same as System V "append" modes */				(void)mlseek(fd, (off_t)0, L_XTND);				iop->_flag = _MIOWRT|_MIOAPPEND;				break;			case 'w':				iop->_flag = _MIOWRT ;				break ;			default:				/* 004 Invalid arguement, set errno */				errno = EINVAL;				return(NULL) ;		}		mode++;		if (*mode == '+') {			mode++;			iop->_flag &= ~(_MIOREAD|_MIOWRT) ;			iop->_flag |= _MIORW ;		} 		if (*mode != '\000') {			iop->_flag = 0;			/* 004 Invalid, set errno */			errno = EINVAL; 			return(NULL);		}	}	return(iop);}