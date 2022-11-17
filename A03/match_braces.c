int main() {

  struct node{
    int l; 
    int col;
    struct node* next;
  }

  void push(struct node** n, int l, int col){
    struct node* nn;
    nn = malloc(sizeof(struct node));
    if(!nn){
      printf("Error");
      exit(1);
    }
  }
  return 0;
}
