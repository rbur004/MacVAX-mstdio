#ifndef _FILE_H_#define _FILE_H_/* Mode values accessible to open() */# define O_RDONLY	0 		  /* Bits 0 and 1 are used internally */# define O_WRONLY	1 		  /* Values 0..2 are historical */# define O_RDWR		2# define O_APPEND   (1<<3) 	  /* append (writes guaranteed at the end) */# define O_CREAT	(1<<8) 	  /* Open with file create */# define O_TRUNC	(1<<9) 	  /* Open with truncation *//*seek call*/# define L_SET	0# define L_INCR 1# define L_XTND 2typedef int off_t;#endif