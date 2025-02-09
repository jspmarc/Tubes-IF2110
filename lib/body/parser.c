#include<stdio.h>
#include "../header/parser.h"
#include "../header/mesinkar.h"
#include "../header/str.h"
#include "../header/stacklist.h"
#include "../header/globals.h"
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
	while(CC != CR && CC != LF && CC != ParserMark && CC != TupleStart
			&& CC != TupleEnd && CC != TreeStart && CC != TreeEnd
			&& CC != ArrayStart && CC != ArrayEnd && CC != ElmtSeparator
			&& CC != blank && !EOP){
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
  while(CC != CR && CC != LF && CC != ParserMark && CC != TupleStart
		&& CC != TupleEnd && CC != TreeStart && CC != TreeEnd
		&& CC !=ArrayStart && CC != ArrayEnd && CC != ElmtSeparator && !EOP){
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

	tmp = 0;
	ret = 0;
	for(int i = 0; i < CToken.length && ret >= 0; i++){
		tmp = CToken.Token[i]-'0';
		if(0 <= tmp && tmp <= 9) ret = (ret * 10)+ tmp;
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
  CreateArray(&(Res.materials), MAX_MATERIAL);
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
  while(CC != ArrayEnd) {
	ArrayElType el;
	Material* mater = (Material *) malloc(sizeof(Material));

	if(isFileParsed) break;
	SkipBlank();
	SkipNewLine();
	// Baca id dan jumlah saja
	ReadToken();
	SkipBlank();
	SkipNewLine();
	ReadToken();
	el.id = ReadInt();
	mater->idMaterial = el.id;
	SkipBlank();
	SkipNewLine();
	ReadToken();
	SkipBlank();
	SkipNewLine();
	ReadToken();
	mater->jumlahMaterial = ReadInt();
	Material *pMat = getMaterialByID(BuyableMaterials, el.id);
	if (pMat == NULL) {
		printf("id = %d\n", el.id);
		printf("bruh moment");
		exit(69);
	}
	SalinKataDariKe(pMat->namaMaterial, &(mater->namaMaterial));
	mater->biayaMaterial = pMat->biayaMaterial;
	el.metadata = mater;
	InsArrLast(&(Res.materials), el);
	i++;
	SkipBlank();
	SkipNewLine();
  }
  ADV();
  ReadToken();
  SkipNewLine();
  ReadToken();
  SkipBlank();
  ReadToken();
  Res.uang = ReadInt();
  durJ = DetikToJAM(dur);
  UbahIsiSimpul(T, x, cap, pri, durJ, nam, des, Res);
}

WahanaTree ReadTree(){
	WahanaTree UTree = Nil, Left = Nil, Right = Nil;
	boolean left;
	int i;
	UpgradeType currentInfo;

	/*UTree = Nil;*/

	left = 1; /* left is true */
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
			  if(left){
				left = 0; /* left jadi false */
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

array ReadTreeArray(){
	array TreeArray;
	ArrayElType el;
	WahanaTree Pohon;

	CreateArray(&TreeArray, MAX_WAHANA);
	while (CC != ArrayEnd && !EOP) {
		/* Skip [ di start of file */
		if (CC == ArrayStart) {
			ADV();
			SkipNewLine();
			SkipBlank();
		}
		Pohon = ReadTree();
		while(CC != ElmtSeparator && CC != ArrayEnd){
			ReadUpgrade(&Pohon);
		}

		/* Skip , (pemisah antara tree) */
		if (CC == ElmtSeparator) {
			ADV();
			SkipNewLine();
			SkipBlank();
		}

		/* Masukin pohon ke array */
		el.id = Akar(Pohon).id;
		el.metadata = Pohon;
		el.info = Akar(Pohon).id;
		InsArrLast(&TreeArray, el);
	}

	return TreeArray;
}

Material ReadMaterial(){
	Material M;

	/* ID 1 nama asd biaya 10000, */
	ReadToken(); /* Baca "ID" */
	SkipBlank();
	ReadToken(); /* Baca angka ID */
	M.idMaterial = ReadInt();

	SkipBlank();
	ReadToken(); /* Baca "nama" */
	SkipBlank();
	ReadToken(); /* Baca string nama */
	ReadKata(&M.namaMaterial);

	SkipBlank();
	ReadToken(); /* Baca "biaya" */
	SkipBlank();
	ReadToken(); /* Baca nominal biaya */
	M.biayaMaterial = ReadInt();
	ADV(); /* Baca ',' */
	SkipNewLine();

	M.jumlahMaterial = 0x7fffffff; /* INT_MAX */

	return M;
}

array ReadMaterialArray() {
	array MaterialArray;
	ArrayElType el;
	Material *mater;

	CreateArray(&MaterialArray, MAX_MATERIAL);
	while (CC != ArrayEnd && !EOP) {
		if (CC == ArrayStart) {
			ADV();
			SkipBlank();
			SkipNewLine();
			SkipBlank();
		}

		mater = (Material*) malloc(sizeof(Material));
		if (mater == NULL) {
			printf("bruh moment");
			exit(69);
		}
		*mater = ReadMaterial();

		/* Skip ',' (pemisah antara tree) */
		if (CC == ElmtSeparator) {
			ADV();
			SkipBlank();
			SkipNewLine();
			SkipBlank();
		}

		el.id = mater->idMaterial;
		el.info = mater->biayaMaterial;
		el.metadata = mater;

		InsArrLast(&MaterialArray, el);
	}

	return MaterialArray;
}

Point ReadPoint(){
	// Point is stored as tuple (x,y)
	int p[2], i, j;
	if(CC == TupleStart){
		ADV();
		for(j = 0; j < 2; j++){
			i = 0;
			while(CC != ElmtSeparator && CC != TupleEnd){
				if(i < PanjangToken){
					CToken.Token[i] = CC;
					i++;
				}
				ADV();
			}
			CToken.length = i;
			p[j] = ReadInt();
			ADV();
		}
		SkipBlank();
	}
	return MakePoint(p[0], p[1]);
}

//Stack ReadStack() {
//	  Stack RetS;
//	  CreateEmptyStack(&RetS);
//	  void *StackElmt;
//	  Kata K;
//	  actBuy aB;
//	  int i, j;
//
//	  if (CC == ArrayStart) {
//		  ADV();
//		  while (CC != ArrayEnd) {
//			  ADV();
//			  if (CC == TupleStart) {
//				  ADV(); /* Baca kode */
//				  switch (CC) {
//					  ADV(); /* CC di ElmtSeparator */
//					  ADV(); /* CC di start element selanjutnyaa */
//					  case BUILD:
//						  /* BuildWahana */
//						  break;
//					  case UPGRD:
//						  /* UpgradeWahana */
//						  /* Isi Tuple: () */
//						  break;
//					  case BUY:
//						  /* BuyResource */
//						  /* Isi Tuple: (BUY, qty_i, nama material) */
//						  for (j = 1; j < 3; ++j) {
//							  i = 0;
//							  while (CC != ElmtSeparator && CC != TupleEnd) {
//								  if (i < PanjangToken) {
//									  CToken.Token[i] = CC;
//									  ++i;
//								  }
//								  ADV();
//							  }
//							  CToken.length = i;
//							  switch (j) {
//								  case 1: /* Ngebaca qty_i */
//									  aB.qty_i = ReadInt();
//									  break;
//								  case 2: /* Ngisi bagian K dari material */
//									  aB.K.Length = CToken.length;
//									  ReadKata(aB.K.TabKata);
//							  }
//						  }
//						  StackElmt = (actBuy*) malloc(sizeof(actBuy));
//						  StackElmt = &aB;
//
//						  /* Ngepush variabel actBuy ke stack */
//						  Push(&RetS, StackElmt, BUY);
//						  break;
//				  }
//			  }
//		  }
//	  }
//
//	  return RetS;
//}

MAP ParserMap(int id) {
	MAP map;

	map = WhichMap(id);
	ReadToken();

	ReadToken();
	ID(map) = ReadInt();
	SkipNewLine();

	ReadToken();
	SkipBlank();
	MapSize(map) = ReadPoint();
	SkipNewLine();

	ReadToken();
	SkipBlank();
	Gate1(map) = ReadPoint();
	SkipNewLine();

	ReadToken();
	SkipBlank();
	Gate2(map) = ReadPoint();
	SkipNewLine();

	ReadToken();
	SkipBlank();
	Office(map) = ReadPoint();
	SkipNewLine();

	ReadToken();
	SkipBlank();
	Antrian(map) = ReadPoint();

	return map;
}
