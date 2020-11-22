#include<stdio.h>
#include "../header/parser.h"
#include "../header/mesinkar.h"
#include "../header/str.h"
#include "../header/stacklist.h"
#include "boolean.h"

boolean isFileParsed;
Token CToken;

static FILE *stream;
void StartParser(FILE *f) {
    START(f);
    SkipNewLine();
}

void ReadToken(){
    int i;

    i = 0;
    while(CC != NewlineMark || CC != ParserMark){
        if(i < PanjangToken) CToken.Token[i] = CC;
        ADV();
        i++;
    }
    i = i > PanjangToken ? PanjangToken : i;
    CToken.Token[i] = '\0';
    CToken.length = i;
    SkipBlank();
}

void SkipNewLine(){
    while(CC == NewlineMark) ADV();
    isFileParsed = CC == ParserMark;
}

void SkipBlank(){
    while(CC == blank) ADV();
    isFileParsed = CC == ParserMark;
}

void ReadString(char *str){
    for(int i = 0; i < CToken.length; i++){
        str[i] = CToken.Token[i];
    }
}

int ReadInt(){
    int ret, tmp;

    ret = 0;
    for(int i = 0; i < CToken.length && ret >= 0; i++){
        tmp = CToken.Token[i]-'0';
        if(0 < tmp && tmp < 9) ret = ret * 10 + tmp;
        else ret = -1;
    }
    return ret;
}

UpgradeTree ReadTree(){
    UpgradeTree UTree = Nil, Left = Nil, Right = Nil;
    boolean notFinished;
    int i;
    UpgradeType currentInfo;

    UTree = Nil;

    if(CC == TreeStart){
        notFinished = 1;
        ADV();
        while(notFinished && CC != ParserMark){
            // Buat Pohonnya
            // TODO: gimana cara parse pohon yang baik dan benar?
            if(CC == TreeEnd) notFinished = 0;
            else if(CC == TreeStart){
                if(Left == Nil) Left = ReadTree();
                else Right = ReadTree();
            } else{
                i = 0;
                while(CC != ElmtSeparator){
                    if(i < PanjangToken){
                        CToken.Token[i] = CC;
                        i++;
                    }
                    ADV();
                }
                CToken.length = i;
                currentInfo = ReadUpgrade(); // Baca id
            }
            SkipBlank();
        }
    }
    if(!notFinished) UTree = Tree(currentInfo, Left, Right); // Buat Pohonnya
    return UTree;
}

UpgradeType ReadUpgrade(){
    UpgradeType T;
    boolean notFinished, parsingMaterial;
    int tupleIdx;

    if(CC == TupleStart){
        notFinished = 1;
        ADV();
        while(notFinished && CC != ParserMark){
            if(parsingMaterial){
            }
            if(CC == TupleEnd) notFinished = 0;
            else if(CC == ArrayStart) parsingMaterial = 1;
        }
    }
    return T;
}

Material ReadMaterial(){
    Material M;

    ReadToken();
    ReadString(M.NamaMaterial);
    SkipBlank();
    ReadToken();
    M.harga = ReadInt();
    SkipNewLine();

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

Stack ReadStack() {
    Stack RetS;
    CreateEmptyStack(&RetS);
    void *StackElmt;
    Kata K;
    actBuy aB;
    int i, j;

    if (CC == ArrayStart) {
        ADV();
        while (CC != ArrayEnd) {
            ADV();
            if (CC == TupleStart) {
                ADV(); /* Baca kode */
                switch (CC) {
                    ADV(); /* CC di ElmtSeparator */
                    ADV(); /* CC di start element selanjutnyaa */
                    case BUILD:
                        /* BuildWahana */
                        break;
                    case UPGRD:
                        /* UpgradeWahana */
                        break;
                    case BUY:
                        /* BuyResource */
                        /* Isi Tuple: (BUY, qty_i, nama material) */
                        for (j = 1; j < 3; ++j) {
                            i = 0;
                            while (CC != ElmtSeparator && CC != TupleEnd) {
                                if (i < PanjangToken) {
                                    CToken.Token[i] = CC;
                                    ++i;
                                }
                                ADV();
                            }
                            CToken.length = i;
                            switch (j) {
                                case 1: /* Ngebaca qty_i */
                                    aB.qty_i = ReadInt();
                                    break;
                                case 2: /* Ngisi bagian K dari material */
                                    aB.K.Length = CToken.length;
                                    ReadString(aB.K.TabKata);
                            }
                        }
                        StackElmt = (actBuy*) malloc(sizeof(actBuy));

                        /* Ngepush variabel actBuy ke stack */
                        Push(&RetS, (void*) StackElmt, BUY);
                        break;
                }
            }
        }
    }

    return RetS;
}
