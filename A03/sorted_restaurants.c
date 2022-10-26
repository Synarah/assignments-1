#include <stdio.h>
#include <stdlib.h>

struct restaurant{
    int num;
    char name[64];
    int open;
    int close;
    double rate;

};

struct node {
  struct restaurant rest;
  struct node* next;
};

struct node* insert_front(struct restaurant rest, struct node* head) {
  struct node* n = malloc(sizeof(struct node));
  if (n == NULL) {
    printf("ERROR: Out of space!\n");
    exit(1);
  }
  n->rest = rest;
  n->next = head;
  return n;
}

int main() {
  struct node *head = NULL;
  printf("Enter a number of returants: ");
  int n;
  scanf(" %d", &n);
  for(int i = 0; i < n; i++){
    struct restaurant rest;
    rest.num = i;
    printf("Enter a name: ");
    scanf(" %[^\n]%*c", rest.name);
    printf("Open time: ");
    scanf(" %d%*c", &rest.open);
    printf("Close time: ");
    scanf(" %d%*c", &rest.close);
    printf("Stars: ");
    scanf(" %lf%*c", &rest.rate);
    head = insert_front(rest, head);

  }

  void print(struct node* list) {
    for (struct node* n = list; n != NULL; n = n->next) {
      printf(" %d) %s        open: %d:00  close: %d:00  stars: %.1f \n", rest.num, rest.name, rest.open, rest.close, rest.rate);
    }
  }
  return 0;
}