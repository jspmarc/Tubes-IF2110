#include "prioqueuell.h"
#include "stacklist.h"
#include "point.h"
#include "jam.h"
#include "wahana.h"
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
ukuran (1,1)
upgrdTree {idUpgrade {b {d {}, e {}, f {}}}, c {g {}, h {i {}}}}
upgrade (id, nama, deskripsi, [(material, jumlah)], terpakai).

Material:
logam 100
nonlolgam 50
metaloid 75.

Map:
ukuran (5,5)
office (3,10).

State:
nama fasjdfhkdasjfdksafjsfadshjf
duit 100
curTime 7200
opTIme 31400
stackAksi [(Id list aksi, (tuple aksi))]
wahana [id, posisi, upgrade tree, [(Info, prio)]].
*/

#define ParserMark '.'
#define CR '\r'
#define LF '\n'
#define ElmtSeparator ','
#define ItemSeparator ' '
#define blank ' '
#define PanjangToken 24
#define TupleStart '('
#define TupleEnd ')'
#define TreeStart '{'
#define TreeEnd '}'
#define ArrayStart '['
#define ArrayEnd ']'

typedef struct {
    char Token[PanjangToken];
    int length;
} Token;

extern boolean isFileParsed;
extern Token CToken;

void StartParser();
void SkipNewLine();
void SkipBlank();
void ReadToken();
void ReadLine();
void ReadKata(Kata *str);
int ReadInt();
Material ReadMaterial();
void ReadUpgrade(WahanaTree *T);
WahanaTree ReadTree();
JAM ReadJAM();
Point ReadPoint();
Stack ReadStack();
Queue ReadQueue();

#endif
