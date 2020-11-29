/* FILE: mainPhase.c */
/* Author: 13519012 Kahfi Soobhan Zulkifli
           13519116 Jeane Mikha Erwansyah */

#include <stdio.h>
#include <stdlib.h>
#include "./../lib/header/boolean.h"
#include "./../lib/header/str.h"
#include "./../lib/header/prioqueuell.h"
#include "./../lib/header/jam.h"
#include "./../lib/header/wahana.h"
#include "./../lib/header/globals.h"
#include "./../lib/header/map.h"

#ifndef MAINPHASE_H
#define MAINPHASE_H
    /* Memakan waktu */
    /* SERVE {input: type pengunjung, wahana, wahana.antrian} */
void SERVE ();
    /* Memakan waktu */
    /* REPAIR {input: wahana} */
void REPAIR ();
    /* Tidak memakan waktu */
    /* DETAIL {input: wahana} */
void DETAIL ();
    /* Tidak memakan waktu */
    /* OFFICE {input: office} */
void OFFICE ();
    /* Tidak memakan waktu */
    /* PREPARE {kosongkan antrian, --> prep phase} */
void PREPARE ();
#endif
