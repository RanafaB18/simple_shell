#ifndef _MAIN_H
#define _MAIN_H
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int runCommand(char *command);
char * dequote(char *line);
char *getInput();
void freeMemory(char **array, int arrayLength);
void allocateMemory(char **array, char *str, char *delim, int length, int addToEnd);
int countWords(char *str, char *delim);
int _strlen(char *str);
char *_getenv(const char *name);
char *getValue(char *env, int indexOfValue);
int isName(char *env, const char *name);
int findIndexOfEqual(char *env);
void slice(const char *str, char *result, size_t start, size_t end);

#endif
