/*                                                           */
/*  HARDCOPY.H  :  Header file for hardcopy.c                */
/*                                                           */
/*                 Programmed By Lee jaekyu                  */
/*                                                           */

#ifndef _HARDCOPY_H
#define _HARDCOPY_H

#define LPT1	0
#define LPT2    1

void wait_hardcopy(int port);
int hardcopy1(int port);
int hardcopy2(int port);
int hardcopy3(int port);

#endif
