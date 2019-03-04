#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compare.h"

typedef struct nod{

	char nume[22];
	int priority;
	struct nod *next;
}queue;

/* Functia care initializeaza o coada */
void init(queue **head)
{
	*head = NULL;
}

/* Functie care verifica daca o coada este vida */
int empty(queue* head)
{
	if (head == NULL)
		return 0;
	return 1;
}

//Functie de adaugare a unui proces in coada
void enqueue(queue **head, char nume[22], int priority)
{
	queue *new;
	queue *aux;
	queue *aux2;
	new = (queue*)calloc(1,sizeof(queue));
	aux = *head;
	aux2 = *head;
	int ok = 0;
	new -> priority = priority;
	strcpy(new -> nume, nume);
	if ((*head) == NULL)
	{
		*head = new;
		new -> next = NULL;
	}
	else
	{
      if (new -> priority > aux -> priority) {
         new -> next = *head;
         *head = new;
      } else {
   		while (aux -> next != NULL && aux -> priority > new -> priority) {
				if (ok > 0)
					aux2 = aux2 -> next;
				aux = aux -> next;
				if (ok == 0) ok ++;
			}
			if (aux -> next != NULL) {
         	new -> next = aux2 -> next;
   			aux2 -> next = new;
			} else {
				new -> next = NULL;
				aux -> next = new;
			}
      }
	}
}

//Functie de eliminare a unui proces
void dequeue(queue **head)
{
	queue *aux;
	aux = *head;
	if ((*head) == NULL)
	{
		printf("Coada vida\n");
		return;
	}
	*head = aux -> next;
	free(aux);
}

/* Functia aceasta elibereaza o coada */
void free_queue(queue **head)
{
	while(*head != NULL)
		dequeue(head);
}

int main(int argc, char *argv[])
{
	int plan, cuanta, niv_priority;
	FILE *in;
	FILE *out;
   queue *words;
	char command[7];
   char buf[20000];
	char word[20000];
	char *token;
   int priority, i;
   init(&words);
   if (argc == 1){
      scanf("%s", command);
      while (strcmp(command, "EOF") != 0){
         if (strcmp(command, "insert") == 0) {
            scanf("%s", word);
            scanf("%d", &priority);
            enqueue(&words, word, priority);
         } else if (strcmp(command, "top") == 0){
            if (empty(words) == 1) {
               printf("%s\n", words -> nume);
            } else {printf("\n");}
         } else if (strcmp(command, "pop") == 0){
            if (empty(words) == 1){
               dequeue(&words);
            }
         }
         scanf("%s", command);
      }
   } else {
         out = fopen("output.txt", "w");
         for (i = 1; i < argc; i++){word
            in = fopen(argv[i], "r");
            while (fgets(buf, sizeof(buf), in) != NULL){
					buf[strlen(buf) - 1] = '\0';
			      token = strtok(buf, " ");
               if (strcmp(buf, "insert") == 0) {
						token = strtok(NULL, " ");
			         priority = atoi(strtok(NULL, " "));
                  enqueue(&words, token, priority);
               } else if (strcmp(buf, "top") == 0){
                  if (empty(words) == 1) {
                     fprintf(out, "%s\n", words -> nume);
                  } else {fprintf(out, "\n");}
               } else if (strcmp(buf, "pop") == 0){
                  if (empty(words) == 1){
                     dequeue(&words);
                  }
               }
            }
         	fclose(in);
         }
      	fclose(out);
   }
   free_queue(&words);
	return 0;
}
