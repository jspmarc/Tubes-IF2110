#include "boolean.h"

#ifndef PARSER_H
#define PARSER_H

/* Contoh file: */
/*
Wahana:
id 0
nama dfasdf
harga 100
kapasitas 10
durasi 7
deskripsi dsajfgasdufgdsafhdsahfhjhjj
ukuranX 1
ukuranY 1
upgrdTree {(nama, deskripsi,[(logam, 100), (nonlogam, 15)], true) {b {d {}, e {}, f {}}}, c {g {}, h {i {}}}}

Material:
logam 100
nonlolgam 50
metaloid 75.

Map:
baris 5
kolom 5
officeX 3
officeY 10.

State:
nama fasjdfhkdasjfdksafjsfadshjf
duit 100
curTime 7200
opTIme 31400
stackAksi [{kode aksi, kode aksi}]
wahana [id, posisi, upgrade tree]
*/

#define ParserMark '.'
#define NewlineMark '\n'
#define ElmtSeparator ','
#define ItemSeparator ' '
#define blank ' '
#define PanjangBaris 100

typedef struct {
    char TabBaris[PanjangBaris];
} Baris;

extern boolean isFileParsed;
extern Baris CBaris;

void StartParser();
void ReadLine();
void StackParser();
void* NTupleParser();
void ArrayParser();
void TreeParser();

#endif
