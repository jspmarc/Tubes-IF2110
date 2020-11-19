#ifndef RESOURCES_H
#define RESOURCES_H

/* *** ADT resource *** */
/* ADT untuk resource yang dibutuhkan untuk membangun & mengupgrade
 * wahana serta ADT untuk menyimpan resource yang dimiliki pemain
 */

typedef struct {
    unsigned int uang; /* Uang yang dimiliki atau dibutuhkan */
    unsigned int logam; /* Material logam */
    unsigned int nonlogam; /* Material nonlogam */
    unsigned int metaloid; /* Material metaloid/semi-logam */
} Resource;

#endif
