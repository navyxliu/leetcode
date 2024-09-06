#include <stdio.h>

//Serialize and Deserialize an N-ary Tree
#define N 4
#define MARKER ')'

struct Node {
  int val; 
  Node * kids[N];
  Node(int val);
};

Node::Node(int value) : val(value) {
  for (int i=0; i<N; ++i) 
kids[i] = NULL;
}

Node * newNode(int value) {
  Node * t = new Node(value);
  return t; 
}

Node *createDummyTree()
{
    Node *root = newNode('A');
    root->kids[0] = newNode('B');
    root->kids[1] = newNode('C');
    root->kids[2] = newNode('D');
    root->kids[0]->kids[0] = newNode('E');
    root->kids[0]->kids[1] = newNode('F');
    root->kids[2]->kids[0] = newNode('G');
    root->kids[2]->kids[1] = newNode('H');
    root->kids[2]->kids[2] = newNode('I');
    root->kids[2]->kids[3] = newNode('J');
    root->kids[0]->kids[1]->kids[0] = newNode('K');
    return root;
}
void traverse(Node * root) {
  if (root) {
    printf("%c", (char)root->val);
    for (int i=0; i<N; ++i) 
      traverse(root->kids[i]);
  }
}

void serialize(Node * t, FILE * fp) {
  if (!t) return ;
  fprintf(fp, "%c", (char)t->val);
  for (int i=0; i<N; ++i) 
    serialize(t->kids[i], fp);
  fprintf(fp, "%c", MARKER);
}

int  deserialize(Node *& root, FILE * fp) {
  int val; 
  int i = 0;
  if (!fscanf(fp, "%c", &val) || val == MARKER)
    return 1; 
  
  root  = newNode(val);
  for (int i=0; i<N; ++i) {
    if (deserialize(root->kids[i], fp))
      break;
  }

  return 0;  
}

// Driver program to test above functions
int main()
{
    // Let us create an N-ary tree shown in above diagram
    Node *root = createDummyTree();
 
    // Let us open a file and serialize the tree into the file
    FILE *fp = fopen("tree.txt", "w");
    if (fp == NULL)
    {
        puts("Could not open file");
        return 0;
    }
    serialize(root, fp);
    fclose(fp);
 
    // Let us deserialize the storeed tree into root1
    Node *root1 = NULL;
    fp = fopen("tree.txt", "r");
    deserialize(root1, fp);
 
    printf("Constructed N-Ary Tree from file is \n");
    traverse(root1);
 
    return 0;
}


