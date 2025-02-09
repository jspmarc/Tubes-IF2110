#include "../lib/header/mesinkata.h"
#ifndef COMMANDS_H
#define COMMANDS_H

extern Kata newC, load, exitC, build,
			 upgrade, buy, undo, execute,
			 mainC, serve, repair, detail,
			 office, prepare, Details, Report,
			 Exit, inventory;

void initCommands();

void copyToKata(char *str, Kata *K);
#endif
