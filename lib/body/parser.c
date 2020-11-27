#include<stdio.h>
#include "../header/parser.h"
#include "../header/mesinkar.h"
#include "../header/str.h"
#include "../header/stacklist.h"
#include "boolean.h"

boolean isFileParsed;
Token CToken;

void StartParser(FILE *f) {
    START(f);
    SkipNewLine();
}

void ReadToken(){
    int i;

    i = 0;
    while(CC != CR && CC != LF && CC != ParserMark && CC != TupleStart && CC != TupleEnd && CC != TreeStart && CC != TreeEnd && CC != ArrayStart && CC != ArrayEnd && CC != ElmtSeparator && CC != blank && !EOP){
        if(i < PanjangToken) CToken.Token[i] = CC;
        ADV();
        i++;
    }
    i = i > PanjangToken ? PanjangToken : i;
    CToken.Token[i] = '\0';
    CToken.length = i;
    SkipBlank();
    isFileParsed = EOP;
}

void ReadLine(){
  int i;
  
  i = 0;
  while(CC != CR && CC != LF && CC != ParserMark && CC != TupleStart && CC != TupleEnd && CC != TreeStart && CC != TreeEnd && CC !=ArrayStart && CC != ArrayEnd && CC != ElmtSeparator && !EOP){
    if(i < PanjangToken) CToken.Token[i] = CC;
    ADV();
    i++;
  }
  i = i > PanjangToken ? PanjangToken : i;
  CToken.Token[i] = '\0';
  CToken.length = i;
}

void SkipNewLine(){
    while((CC == CR || CC == LF) && CC != ParserMark) ADV();
    isFileParsed = EOP;
}

void SkipBlank(){
    while(CC == blank) ADV();
    isFileParsed = EOP;
}

void ReadKata(Kata *K){
    int i;
    for(i = 0; i < CToken.length; i++){
        K->TabKata[i] = CToken.Token[i];
    }
    K->TabKata[i] = '\0';
    K->Length = CToken.length;
}

int ReadInt(){
    int ret, tmp;

    ret = 0;
    for(int i = 0; i < CToken.length && ret >= 0; i++){
        tmp = CToken.Token[i]-'0';
        if(0 <= tmp && tmp < 9) ret = ret * 10 + tmp;
        else ret = -1;
    }
    return ret;
}

void ReadUpgrade(WahanaTree *T){
  int x, cap, pri, dur, i;
  JAM durJ;
  Kata nam, des;
  SkipBlank();
  SkipNewLine();
  Resource Res;
  ReadToken();
  SkipBlank();
  ReadToken();
  x = ReadInt();
  SkipNewLine();
  ReadToken();
  SkipBlank();
  ReadToken();
  cap = ReadInt();
  SkipNewLine();
  ReadToken();
  SkipBlank();
  ReadToken();
  pri = ReadInt();
  SkipNewLine();
  ReadToken();
  SkipBlank();
  ReadToken();
  dur = ReadInt();
  SkipNewLine();
  ReadToken();
  SkipBlank();
  ReadLine();
  ReadKata(&nam);
  SkipNewLine();
  ReadToken();
  SkipBlank();
  ReadLine();
  ReadKata(&des);
  SkipNewLine();
  i = 0;
  ADV();
  while(CC != ArrayEnd){
    if(isFileParsed) break;
    SkipBlank();
    SkipNewLine();
    // Baca id dan jumlah saja
    ReadToken();
    SkipBlank();
    SkipNewLine();
    ReadToken();
    Res.materials[i].idMaterial = ReadInt();
    SkipBlank();
    SkipNewLine();
    ReadToken();
    SkipBlank();
    SkipNewLine();
    ReadToken();
    Res.materials[i].jumlahMaterial = ReadInt();
    i++;
    SkipBlank();
    SkipNewLine();
  }
  ADV();
  durJ = DetikToJAM(dur);
  UbahIsiSimpul(T, x, cap, pri, durJ, nam, des, Res);
}

WahanaTree ReadTree(){
    WahanaTree UTree = Nil, Left = Nil, Right = Nil;
    boolean left;
    int i;
    UpgradeType currentInfo;

    UTree = Nil;

    left = 0;
    if(CC == TreeStart){
        SkipBlank();
        ADV();
        ReadToken();
        if(CToken.length > 0) i = ReadInt();
        else i = -1;
        if(i >= 0) currentInfo = BuatSimpulKosong(i);
        while(CC != TreeEnd && CC != ParserMark){
            // Buat Pohonnya
            // TODO: gimana cara parse pohon yang baik dan benar?
            if(CC == TreeStart){
              if(!left){
                left = 1;
                Left = ReadTree();
              } 
              else Right = ReadTree();
            }
            SkipBlank();
            ADV();
        }
    }
    if(i >= 0) UTree = Tree(currentInfo, Left, Right); // Buat Pohonnya
    ADV();
    SkipNewLine();
    return UTree;
}

Material ReadMaterial(){
    Material M;

    ReadToken();
    M.idMaterial = ReadInt();
    SkipBlank();
    ReadToken();
    ReadKata(&M.namaMaterial);
    SkipBlank();
    ReadToken();
    M.biayaMaterial = ReadInt();
    SkipNewLine();

    M.jumlahMaterial = 0x7fffffff; /* INT_MAX */

    return M;
}

Point ReadPoint(){
    // Point is stored as tuple (x,y)
    int p[2], i, j;
    if(CC == TupleStart){
        ADV();
        for(j = 0; j < 2; j++){
            i = 0;
            while(CC != ElmtSeparator || CC != TupleEnd){
                if(i < PanjangToken){
                    CToken.Token[i] = CC;
                    i++;
                }
                ADV();
            }
            CToken.length = i;
            p[j] = ReadInt();
        }
        SkipBlank();
    }
    return MakePoint(p[0], p[1]);
}

//Stack ReadStack() {
//    Stack RetS;
//    CreateEmptyStack(&RetS);
//    void *StackElmt;
//    Kata K;
//    actBuy aB;
//    int i, j;
//
//    if (CC == ArrayStart) {
//        ADV();
//        while (CC != ArrayEnd) {
//            ADV();
//            if (CC == TupleStart) {
//                ADV(); /* Baca kode */
//                switch (CC) {
//                    ADV(); /* CC di ElmtSeparator */
//                    ADV(); /* CC di start element selanjutnyaa */
//                    case BUILD:
//                        /* BuildWahana */
//                        break;
//                    case UPGRD:
//                        /* UpgradeWahana */
//                        /* Isi Tuple: () */
//                        break;
//                    case BUY:
//                        /* BuyResource */
//                        /* Isi Tuple: (BUY, qty_i, nama material) */
//                        for (j = 1; j < 3; ++j) {
//                            i = 0;
//                            while (CC != ElmtSeparator && CC != TupleEnd) {
//                                if (i < PanjangToken) {
//                                    CToken.Token[i] = CC;
//                                    ++i;
//                                }
//                                ADV();
//                            }
//                            CToken.length = i;
//                            switch (j) {
//                                case 1: /* Ngebaca qty_i */
//                                    aB.qty_i = ReadInt();
//                                    break;
//                                case 2: /* Ngisi bagian K dari material */
//                                    aB.K.Length = CToken.length;
//                                    ReadKata(aB.K.TabKata);
//                            }
//                        }
//                        StackElmt = (actBuy*) malloc(sizeof(actBuy));
//                        StackElmt = &aB;
//
//                        /* Ngepush variabel actBuy ke stack */
//                        Push(&RetS, StackElmt, BUY);
//                        break;
//                }
//            }
//        }
//    }
//
//    return RetS;
//}
