#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int ac __attribute__((unused)), char **av, char **env);
void prompt(void);
void handle(int signals);
void _end(char *buffer);
void s_exit(char **cmd);

void child(char **cmd, char *name, char **env, int circles);
int cd(const char *finder);

void execute(char **cmd, char *name, char **env, int circles);
void print_environment(char **env);
char **_getPATH(char **env);
void errormsg(char *name, int circles, char **cmd);

char **tokenize(char *buffer, const char *delim);

int _strcmp(char *str1, char *str2);
unsigned int _strlen(char *str);
char *_strcpy(char *dest, char *src);
int _atoi(char *str);
char *_strcat(char *dest, char *src);

void free_d(char **cmd);
void free_e(char **cmd);

#endif
