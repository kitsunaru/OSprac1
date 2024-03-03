
/*********************************************************************
   Program  : miniShell                   Version    : 1.3
 --------------------------------------------------------------------
   skeleton code for linix/unix/minix command line interpreter
 --------------------------------------------------------------------
   File			: minishell.c
   Compiler/System	: gcc/linux

********************************************************************/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define NV 20			/* max number of command tokens */
#define NL 100			/* input buffer size */
char            line[NL];	/* command input buffer */
int isBackground = 0; //define & declare number of background processes
int jobNum = 1;
/* -----------------
scanf(), printf() [stdio.h], signal() [string.h]
----------------- */

/*
	shell prompt
 */

void prompt(void)
{
  //fprintf(stdout, "\n msh> ");
  fflush(stdout);

}


int main(int argk, char *argv[], char *envp[])
/* argk - number of arguments */
/* argv - argument vector from command line */
/* envp - environment pointer */

{
  int             frkRtnVal;	/* value returned by fork sys call */
  //int             wpid;		/* value returned by wait */
  char           *v[NV];	/* array of pointers to command line tokens */ /* intakes command line arguments */
  char           *sep = " \t\n";/* command line token separators    */
  int             i;		/* parse index */

/* v[0] = cd
  v[1]
*/

  /* prompt for and process one command line at a time  */

  while (1) {			/* do Forever */
    prompt();
    fgets(line, NL, stdin);
    fflush(stdin);

    if (feof(stdin)) {		/* non-zero on EOF  */

      //fprintf(stderr, "EOF pid %d feof %d ferror %d\n", getpid(),
	    //  feof(stdin), ferror(stdin));
      exit(0);
    }
    if (line[0] == '#' || line[0] == '\n' || line[0] == '\000')
      continue;			/* to prompt */

    v[0] = strtok(line, sep);
    for (i = 1; i < NV; i++) {
      v[i] = strtok(NULL, sep);
      if (v[i] == NULL)
	      break;
      }
    /* assert i is number of tokens + 1 */


    if (strncmp(v[0], "cd", 2) == 0) { //compares item, exact wording, then number of words
      const char *path = v[1];
      if (chdir(path) == -1) {
        perror("cd error");
        
        /* fork a child process to exec the command in v[0] */
        }
        continue;
      } 
    else if (strncmp(v[i-1], "&", 1) == 0) { //initially wrote 2 within v's arg but that would hardcode it instead of accessing the laast element in the array
      isBackground = 1;
      v[i-1] = NULL;
    }
   
    switch (frkRtnVal = fork()) {
    case -1:			/* fork returns error to parent process */
      {
        perror("error");
	      break;
      }

    case 0:			/* code executed only by child process */
      {
	      if (execvp(v[0], v) == -1) {
        perror("error");
        exit(0);
        }
      }

    default:			/* code executed only by parent process */
      {
	      //int wpid = wait(0); //remove int later
        if (isBackground == 0) {
          wait(0);
	      //printf("%s done \n", v[0]);
	        break;
        } else if (isBackground == 1) {
          printf("[%d] %d\n", jobNum, frkRtnVal);
          jobNum++;
          isBackground = 0; //resets the flag
        }
      }
      
      }				/* switch */
    }				/* while */
  }				/* main */
