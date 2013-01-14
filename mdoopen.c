/* _doopen() * * Common routine to open a file for both fopen() and freopen(). * */#include	"mstdio.h"#include 	"file.h"#include	<types.h>#include 	<errno.h>#include	<String.h>#include 	"macio.h"M_FILE *_mdoopen(	char *file,	short vrefnum,	register char *mode,	register M_FILE *iop){	register unsigned o_flags;	if (iop == NULL) {		/*002 - invalid arguement, set errno */ 		errno = EINVAL;		return(NULL);	}	/* Check the basic mode for the file.	 */	switch(mode[0]) {		case 'r': o_flags = O_RDONLY ;			  iop->_flag = _MIOREAD ;			  break ;		case 'w': o_flags = O_TRUNC|O_CREAT|O_WRONLY ;			  iop->_flag = _MIOWRT ;			  break ;			/* Append mode is handled differently in the System			 * V environment.  In that environment files opened			 * with "a" or "a+" are really opened with O_APPEND.			 * This functionality is provided by the "A" and "A+"			 * modes in the ULTRIX environment.			 */		case 'a':#ifndef SYSTEM_FIVE	  /* Same as BSD "append modes" */			  o_flags = O_CREAT|O_WRONLY ;			  iop->_flag = _MIOWRT ;			  break ;		case 'A':#endif			  /* Same as System V "append" modes */			  o_flags = O_APPEND|O_CREAT|O_WRONLY ;			  iop->_flag = _MIOAPPEND|_MIOWRT ;			  break ;		default:			/*002 Invalid argument, set errno */			errno = EINVAL;   			return(NULL);	}	if (mode[1] == '+') {		/* 		 * In update mode.  Turn off the the readonly/writeonly		 * flags and turn on the read/write flags.		 */		o_flags &= ~(O_RDONLY|O_WRONLY) ;		o_flags |= O_RDWR ;		iop->_flag &= ~(_MIOREAD|_MIOWRT) ;		iop->_flag |= _MIORW ;	} else if (mode[1] != '\000') {		iop->_flag = 0 ;		errno = EINVAL;		/* 002 - set errno */ 		return(NULL);		/* Illegal mode */	}		/* Try to open the file.	 */	if ((iop->_file = _mopen(file,vrefnum,o_flags)) < 0) {		/* 002 - errno will be set to the correct 		 * error message number by open sys call		 */ 		iop->_flag = 0 ;		return(NULL);	}	iop->_cnt = 0;	/* If in append mode seek to the end of the file	 */	if ( mode[0] == 'a'#ifndef SYSTEM_FIVE	     || mode[0] == 'A'#endif	   )		(void)mlseek(mfileno(iop),(off_t)0,L_XTND); 	iop->vrefnum = vrefnum;	strncpy(iop->name, file, 63);  	return(iop);}