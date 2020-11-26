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
    while(CC != NewlineMark || CC != ParserMark || CC != TupleStart || CC != TupleEnd || CC != TreeStart || CC != TreeEnd || CC != ArrayStart || CC != ArrayEnd){
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

void ReadKata(Kata *K){
    for(int i = 0; i < CToken.length; i++){
        K->TabKata[i] = CToken.Token[i];
    }
    K->Length = CToken.length;
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

void ReadUpgrade(WahanaTree *T){
	int x, cap, pri, dur, cos, i;
	JAM durJ;
	Kata nam, des;
	Resource Res;

	while(!isFileParsed){
		ReadToken();
		ReadToken();
		x = ReadInt();
		ReadToken();
		SkipBlank();
		ReadToken();
		cap = ReadInt();
		ReadToken();
		SkipBlank();
		ReadToken();
		pri = ReadInt();
		ReadToken();
		SkipBlank();
		ReadToken();
		dur = ReadInt();
		ReadToken();
		SkipBlank();
		ReadToken();
		ReadKata(&nam);
		ReadToken();
		SkipBlank();
		ReadToken();
		ReadKata(&des);
		ReadToken();
		SkipBlank();
		ReadToken();
		i = 0;
		while(CC != ArrayEnd && !isFileParsed){
			ADV();
			Res.materials[i] = ReadMaterial();
			SkipBlank();
			i++;
		}
		durJ = DetikToJAM(dur);
		UbahIsiSimpul(T, x, cap, pri, durJ, nam, des, Res);
	}
	SkipNewLine();
}

WahanaTree ReadTree(){
    WahanaTree UTree = Nil, Left = Nil, Right = Nil;
    boolean notFinished;
    int i;
    UpgradeType currentInfo;

    UTree = Nil;

    if(CC == TreeStart){
        notFinished = 1;
        ADV();
        ReadToken();
        i = ReadInt();
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
            }
            SkipBlank();
            currentInfo = BuatSimpulKosong(i);
        }
    }
    if(!notFinished) UTree = Tree(currentInfo, Left, Right); // Buat Pohonnya
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
