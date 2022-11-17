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

struct node* insert_middle(struct restaurant rest, struct node* head){
  struct node* temp = head;
  if(temp == NULL){
    return insert_front(rest, head);
  }
  else if(temp->rest.rate < rest.rate){
    return insert_front(rest, head);
  }
  else{
      struct node* n = malloc(sizeof(struct node));
      n->rest = rest;
      n-> next = NULL;
    while(temp->next != NULL){
      if(temp->next->rest.rate < n->rest.rate){
        n->next = temp->next;
        temp->next = n;
        break;
      }
      temp = temp->next;
    }
    if(temp->next == NULL){
      temp->next = n;
      n->next = NULL;
    }
    return head;
  }
  

}

void print(struct node* list) {
    int i = 0;
    for (struct node* n = list; n != NULL; n = n->next) {
      printf(" %d) %s        open: %d:00  close: %d:00  stars: %.1f \n", i, n->rest.name, n->rest.open, n->rest.close, n->rest.rate);
      i++;
    }
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
    head = insert_middle(rest, head);

  }
  print(head);
 
  struct node* curr;
  struct node* td;
  curr = head;
  td = head;
  while(curr != NULL){
    curr = curr->next;
    free(td);
    td = curr; 
  }
 
  return 0;
}