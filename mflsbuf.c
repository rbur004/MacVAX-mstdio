#include	"mstdio.h"#include 	"macio.h"long_mflsbuf(	unsigned long c,	register M_FILE	*iop){	register char	*base;	register int	size, n_written;	char		smallbuf;	if (iop->_flag & _MIORW) {		/* If the previous operation was a read and we are		 * in System V append mode, then reset the buffer pointer.		 * Otherwise we might write garbage to the file.		 * This allows the append to work after a read without		 * an intervening fseek().		 */		if ((iop->_flag & _MIOAPPEND) && (iop->_flag & _MIOREAD))			iop->_ptr = iop->_base;		/* Indicate that the last operation was a "write"		 */		iop->_flag |= _MIOWRT;		iop->_flag &= ~(_MIOEOF|_MIOREAD);	}	/* If not in "write" mode then we have an error.	 */	if ((iop->_flag&(_MIOSTRG|_MIOWRT|_MIOREAD)) != _MIOWRT) {		iop->_flag |= _MIOERR ;		return(EOF);	}		/* Find the base of the file buffer.	 */	for (;;) {		base = iop->_base;		if (base != NULL)	/* If we have a buffer, great! */			break;		/* Note that unbuffered files are given a temporary		 * buffer for convience sake.  But this does not		 * change iop->_base which always remain NULL.		 */		if (iop->_flag & _MIONBF) {			base = iop->_ptr = &smallbuf;			break ;		}		/* Attempt to get a buffer.  If no buffer can be allocated,		 * then this routine will change the file to unbuffered.		 */		_mgetstdiobuf(iop);	}	n_written = 0;	if (iop->_flag & (_MIONBF|_MIOLBF|_MIOAPPEND)) {		/* Handle UNBUFFERED and LINE BUFFERED files as well as		 * files opened in System V APPEND mode.  The character is		 * first put into the buffer, then if the buffer is full 		 * (always true for unbuffered files) or if the character is a		 * newline and the file is line buffered, the buffer is		 * written.  The _cnt field is ALWAYS reset to 0 to force		 * the next putc() to call this routine again.  Note that		 * this will also force the next getc() to call _filbuf,		 * which is necessary fo files opened for System V append.		 */		*iop->_ptr++ = c;		size = iop->_ptr - base ;		if ((size >= iop->_bufsiz)		    || ((c == '\n') && (iop->_flag & _MIOLBF))		   ) {			n_written = mwrite(mfileno(iop),base,size);			iop->_ptr = base ;		} else			size = 0;		iop->_cnt = 0 ;	} else {		/* For fully buffered files, write anything in the		 * buffer, then put the character in the empty buffer		 * Note that, unlike unbuffered or line buffered files		 * the character is not put in the buffer until after		 * the buffer has been written.		 */		size = iop->_ptr - base ;		if (size > 0) 			n_written = mwrite(mfileno(iop),base,size);				/* Allow putc() to put this many characters in buffer		 * before calling _mflsbuf();		 */		iop->_cnt = iop->_bufsiz - 1;					 		*base++ = c ;		iop->_ptr = base ;	}	if (size != n_written) {		iop->_flag |= _MIOERR;		return(EOF);	}	return(((int)c)&0xff);}