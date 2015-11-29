#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// creates node structure storing first name, last name,
//  residential town, and next node
typedef struct node {
	char fname[15];
	char lname[15];
	char town[50];
  struct node *next;
} Node;


Node *head = NULL;
Node *newNode;

// will compare 2 strings to determine if town2 should be
// placed after town1 in a sorted sequence
int comp(char* town1, char* town2){
		int i = 0;
		for (i = 0; town1[i] != '\0' && town2[i] != '\0'; i++) {
			if (town1[i] != town2[i]) {
				return tolower(town1[i]) < tolower(town2[i]);
			}
		}
		return 1;
}

// function that builds linked list by creating node
// then inserting in the appropriate place
void add(char* firstn, char* lastn, char* city) {
	newNode = malloc(sizeof(Node));
  strcpy(newNode->fname, firstn);
  strcpy(newNode->lname, lastn);
  strcpy(newNode->town, city);
  newNode->next = NULL;
  if (head == NULL) {
    head = newNode; 
  }
  else {
	  Node *current = head;
	  Node *next = current->next;
	  while (1) {
	  		if (comp(newNode->town, head->town)){
	  			newNode->next = head;
	  			head = newNode;
	  			break;
	  		}
	  		if (current->next == NULL) {
	  				current->next = newNode;
				
				break;
			}
	  		if (comp(current->town, newNode->town) && comp(newNode->town, current->next->town)) {
	  			newNode->next = current->next;
	  			current->next = newNode;
	  			break;
	  		}
  	  current = current->next;
		}
  }
}

// function compares the names of 2 nodes to determine whether they are the same
int Node_comp(Node *node, char* name1, char* name2, int len1, int len2) {
	int counter = 0;
	for (counter = 0; counter < len1; counter++) {
		if (tolower(node->fname[counter]) != tolower(name1[counter])) {
			return 0;
		}
	}
	for (counter =0; counter < len2; counter++) {
		if (tolower(node->lname[counter]) != tolower(name2[counter])) {
			return 0;
		}
	}
	return 1;
}

// function removes node based on given name information
// by implementing Node_comp to check
void removerr(char* name, char* lastname, int fnamelen, int lnamelen) {
	if (Node_comp(head, name, lastname, fnamelen, lnamelen)) {
    	head = head->next;
	} 
	else { 
		Node *current = head;
		Node *deleter = head;
		while (current->next != NULL) {

			if (Node_comp(current->next, name, lastname, fnamelen, lnamelen)) {
        free(deleter->next);
				current->next = current->next->next;
				break;
			}
			current = current->next;
			deleter = deleter->next;
		}
	}
}


// function to print list
void print_list() {
	Node *current = head;
	while (current != NULL) {
		printf ("%s %s ", current->fname,current->lname);
    int len = getcity(current->town);
    printf("%.*s\n", len, current->town);
    current = current->next;
	}
}

// function to get city name from address line
int getcity(char* tmi) {
	int d = 0;
  int len = 0;
	for (d = 0; d < 47; d++) {
		if(tmi[d] < 90 && tmi[d+1] <90 && tmi[d+2] <90 && tmi[d+3] < 90) {
      len = d;
      break;
    }
	}
 return len;
}

void addlist(char* filename, char* name, char* sirname, char* city, char* info, int c) {
  FILE *fo;
  fo = fopen(filename, "r");
  if (fo != NULL) {
    while (!feof(fo)) {
      fgets(info, 50, fo);
      c++;
      if (c == 1) {
        strcpy(name, info);
        char *pos;
      if ((pos=strchr(name, '\n')) != NULL){
          *pos = '\0';
        }
      } 
       if (c == 2) {
        strcpy(sirname, info);
        char *pos;
      if ((pos=strchr(sirname, '\n')) != NULL){
          *pos = '\0';
        }

       }
      
       if (c == 4) {
        strcpy(city, info);
        char *pos;
        if ((pos=strchr(city, '\n')) != NULL){
          *pos = '\0';
        }

      } 
      
      if (c == 6) {
        add(name, sirname, city);
        c = 0;
      }

    }
  }
}

// Main function opens file and goes through line by line
// to add information to build a linked list through the
// add function. Main also has the testing component where
// 3 more names are added through another text file called 
// "addtester.txt" and deletes 2 of those names.
int main() {
	char name[15];
	char sirname[30];
	char city[50];
  char info[50];
  int c = 0;
  addlist("input.txt", name, sirname, city, info, c);
  print_list();
  addlist("addtester.txt", name, sirname, city, info, c);
  removerr("Pengfei", "Zheng", strlen("Pengfei"), strlen("Zheng"));
  removerr("Alfredo", "Velasco", strlen("Alfredo"), strlen("Velasco"));
  printf("\n");
  print_list();
  free(head);
  free(newNode);
  return 0;	
}