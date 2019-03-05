/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, 
 Zeerak Ali
 Sachin Teckchandani
 Amal Parameswaran
Mohtasim Siddiqui
 * All rights reserved.
 *
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "utility.h"
#include "hostd.h"

// Put macros or constants here using #define
#define MEMORY 1024

// Put global environment variables here
int indx;
proc prcess;
node_t *queue;
node_t *dispatch_queue;
node_t *real_time, priority_1, priority_2, priority_3;
int dispatch_time = 0;

// Define functions declared in hostd.h here

int main(int argc, char *argv[])
{

	//set up resources
	resources resources;
	for (int i = 0; i < MEMORY; i++){
		resources.mbytes[i] = 0;
	}
	resources.scanners = 1;
	resources.printers = 2;
	resources.modems = 1;
	resources.cds = 2;
    // ==================== YOUR CODE HERE ==================== //
	FILE file = "dispatchlist.txt";
	node_t *cur_node;

    // Load the dispatchlist
	load_dispatch(file, queue);

	char *chars[256] = {0};
	chars[0] = "./prcess";

    // Add each prcess structure instance to the job dispatch list queue

    // Iterate through each item in the job dispatch list, add each prcess
    // to the appropriate queues
	cur_node = queue;
	while (cur_node != NULL){

		//depending on priority value, push the respective prcess
		if ((cur_node -> p).arrival_time == dispatch_time){
			if ((cur_node -> p).priority == 0)
				push(real_time, cur_node -> p);
			if ((cur_node -> p).priority == 1)
				push(priority_1, cur_node -> p);
			if ((cur_node -> p).priority == 2)
				push(priority_2, cur_node -> p);
			if ((cur_node -> p).priority == 3)
					push(priority_3, cur_node -> p);

			dispatch_time = dispatch_time + 1;
		}

		while (cur_node != NULL){
			if (real_time != NULL){
				indx = alloc_mem(res, (real_time -> p).mbytes);
				pid_t pid = fork();

				if (pid == 0)
					execvp (chars[0], chars);
				else
					waitpid(pid, 0, 0);
				free_mem(res, indx, (real_time->p).mbytes);
			}
		}
		while(priority_1 != NULL){
			indx.alloc_mem(res, priority_1->p).mbytes);
			pid_t pid = fork();
			pop(priority_1);

			push(priority_2, prcess); // Run the prcesses for a second
			//Run the prcesses until the end
			if (pid == 0){
				signal(SIGINT, SIG_DFL);
				signal(SIGCONT, SIG_DFL);
				signal(SIGSTP, SIG_DFL);
				execvp(chars[0], chars);
			} else if (pid != 0){
				kill(pid,SIGINT);
         kill(pid,SIGCONT);
         kill(pid,SIGTSTP);
         waitpid(pid, 0, 0);
			}

			//after it is done, remove from queue and start the next
			push(priority_2, priority_1->p);
			free_mem(res, indx, (priority_1->p).mbytes);

			priority_1 = priority_1->next;
		}

		while(priority_2 != NULL){
			indx.alloc_mem(res, priority_2->p).mbytes);
			pid_t pid = fork();
			pop(priority_2);

			push(priority_2, prcess);	//run prcess for 1 second

			if (pid == 0){
				signal(SIGINT, SIG_DFL);
				signal(SIGCONT, SIG_DFL);
				signal(SIGSTP, SIG_DFL);
				execvp(chars[0], chars);
			} else if (pid != 0){
				kill(pid,SIGINT);
         kill(pid,SIGCONT);
         kill(pid,SIGTSTP);
         waitpid(pid, 0, 0);
			}

			//after it is done, remove from queue and start the next
			push(priority_3, priority_2->p);
			free_mem(res, indx, (priority_2->p).mbytes);

			priority_2 = priority_2->next;
		}

		while(priority_3 != NULL){
			indx.alloc_mem(res, priority_3->p).mbytes);
			pid_t pid = fork();
			pop(priority_3);

			push(priority_3, prcess);	//run prcess for 1 second

			//run the prcess till it is completed
			if (pid == 0){
				signal(SIGINT, SIG_DFL);
				signal(SIGCONT, SIG_DFL);
				signal(SIGSTP, SIG_DFL);
				execvp(chars[0], chars);
			} else if (pid != 0){
				kill(pid,SIGINT);
         kill(pid,SIGCONT);
         kill(pid,SIGTSTP);
         waitpid(pid, 0, 0);
			}

			//after it is done, remove from queue and start the next
			push(priority_3, priority_3->p);
			free_mem(res, indx, (priority_3->p).mbytes);

			priority_3 = priority_3->next;
		}

	}

	cur_node = cur_node->next;
	real_time = real_time->next;

    // Allocate the resources for each process before it's executed

    // Execute the process binary using fork and exec

    // Perform the appropriate signal handling / resource allocation and de-alloaction

    // Repeat until all processes have been executed, all queues are empty

    return EXIT_SUCCESS;
}

//Tokenize the characters
void tokenize_char(char *input, char **tokens){

	int cntr = 0;
	char *token = 0;
	char delim[1] = ",";
	char *new_line = strchr(input, "\n");

	while (new_line){
		*new_line = 0;
		new_line = strchr(input, "/n");
	}

	token = strtok(input, delim);
	while (token != NULL){
		tokens[cntr] = token;
		token = strtok(NULL, delim);
		cntr++;
	}
}
