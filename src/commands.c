#include "commands.h"
#include "../lib/header/mesinkata.h"
Kata newC, load, exitC, build,
			 upgrade, buy, undo, execute,
			 mainC, serve, repair, detail,
			 office, prepare, Details, Report,
			 Exit, inventory;


void initCommands(){
	newC.Length = 3;
	copyToKata("new", &newC);
	copyToKata("load", &load);
	copyToKata("exit", &exitC);
	copyToKata("build", &build);
	copyToKata("upgrade", &upgrade);
	copyToKata("buy", &buy);
	copyToKata("undo", &undo);
	copyToKata("execute", &execute);
	copyToKata("main", &mainC);
	copyToKata("serve", &serve);
	copyToKata("repair", &repair);
	copyToKata("detail", &detail);
	copyToKata("office", &office);
	copyToKata("prepare", &prepare);
	copyToKata("Details", &Details);
	copyToKata("Report", &Report);
	copyToKata("Exit", &Exit);
	copyToKata("inventory", &inventory);
}

void copyToKata(char *str, Kata *K){
	int i = 0;
	while(*str != '\0'){
		K->TabKata[i] = *str;
		str++;
		i++;
	}
	K->Length = i;
}
