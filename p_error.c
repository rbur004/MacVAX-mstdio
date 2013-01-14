#include <errors.h>#include "mstdio.h"#include "aprintf.h"void ap_error(	char *s,	OSErr error){	switch(error)	{	case eofErr:		aprintf("%s: Eof error",s);		break;	case tmfoErr:		aprintf("%s: Too many open files",s);		break;	case dskFulErr:		aprintf("%s: Disk full",s);		break;	case wPrErr:	case fLckdErr:	case vLckdErr:	case fBsyErr:	case wrPermErr:		aprintf("%s: Write protected (%d)",s,error);		break;	default:		aprintf("%s: error = %d", s, error);		break;	}}