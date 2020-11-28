#include "prepPhase.h"
#include "../lib/header/wahana.h"
#include "../lib/header/stacklist.h"
#include "../lib/header/globals.h"
#include "../lib/header/resources.h"
#include <stdio.h>

void Execute(){
	// Do execute stuff
	// Pop from Stack then pop some more?
	Stack A;
	StackInfoType t;
	PropertiAksi prop;

	// Step 1. reverse the order
	CreateEmptyStack(&A);
	while(!IsStackEmpty(actionStack)){
		Pop(&actionStack, &t, &prop);
		Push(&A, t, prop);
	}

	// Step 2. execute them 1-by-1
	while(!IsStackEmpty(A)){
		Pop(&A, &t, &prop);
		switch(IdAksi(prop)){
			case BUILD:
				// execute build;
				ExecBuild((ATangibleWahana)t);
				break;
			case UPGRD:
				// execute upgrade;
				ExecUpgrade((WahanaUpgradeStack)t);
				break;
			case BUY:
				// execute buy;
				ExecBuy(*(actBuy *)t, &DurasiAksi(prop));
				break;
		}
		// The time is already taken account of, don't need to check
	}
}

void BuildWahana(UpgradeType Wahana, Point Loc) {
	ATangibleWahana w;
	PropertiAksi prop;
	w = (ATangibleWahana) malloc(sizeof(TangibleWahana));
	WahanaPoint(w) = Loc;
	TreeWahana(w) = Wahana;
	UpgradeId(w) = Wahana.id;

	DurasiAksi(prop) = MakeJAM(0, 30, 0); //arbitrary choice
	IdAksi(prop) = BUILD;
	Push(&actionStack, w, prop);
}
void ExecBuild(ATangibleWahana Wahana){
	// Store ATangibleWahana somehow
	// Do not free ATangibleWahana, because we need it.
	ArrayElType el;
	el.id = TreeWahana(Wahana).id;
	el.metadata = Wahana;
	InsArrLast(&BuiltWahana, el);
}

void ToMainPhase(){
	// Go to main phase
	// Pop items from stack, do not execute any
	StackInfoType t;
	PropertiAksi p;
	while(!IsStackEmpty(actionStack)){
		Pop(&actionStack, &t, &p);
	}
}

void Save(){
	// Save state, something something hard to do
}

void Build(){

}

void Upgrade(){
}

void Buy(){

}

void ExecuteBuy(Material M){
}

void Undo() {
    void* t;
    PropertiAksi p;
    t = NULL;
    Pop(&actionStack, t, &p);
}
