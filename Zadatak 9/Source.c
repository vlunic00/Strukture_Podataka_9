#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

struct tree;
typedef struct tree* Node;
typedef struct tree {
	int num;
	Node left;
	Node right;
}_tree;

Node addNew(Node, int);
Node searchFor(Node, int);
Node deleteNode(Node, int);
Node findMinimum(Node);
void printTree(Node);

int main() {
	_tree root;
	root.left = NULL;
	root.right = NULL;
	root.num = 0;
	char c = '\0';
	int i = 0;

	while (1) {
		printf("Sto zelite napraviti: D - dodati novi clan, S - traziti clan stabla, "
			"B - izbrisati clan, I - ispisati stablo:\n");
		scanf(" %c", &c);

		switch (toupper(c)) {
			case 'D':
				printf("Koji broj zelite dodati?\n");
				scanf("%d", &i);
				if (root.num == 0)
					root.num = i;
				else
				addNew(&root, i);
				break;

			case 'S':
				printf("Koji broj zelite pronaci?\n");
				scanf("%d", &i);
				if (searchFor(&root, i))
					printf("Clan %d postoji\n", i);
				else
					printf("Cland %d ne postoji\n", i);
				break;

			case 'B':
				printf("Koji broj zelite izbrisati iz stabla?\n");
				scanf("%d", &i);
				if (deleteNode(&root, i) == NULL)
					printf("Taj clan ne postoji\n");
				else
					printf("Clan uspijesno izbrisan\n");
				break;
				
			case'I':
				printTree(&root);
				break;
		}
	}
		return 0;
}

Node newNode(int n) {
	Node newNode = NULL;
	newNode = (Node)malloc(sizeof(Node));
	
	if (newNode == NULL) {
		printf("Greska pri alokaciji\n");
		return;
	}
	newNode->num = n;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

Node addNew(Node temp, int n) {
	
	if (temp == NULL)
		temp = newNode(n);

	if (n < temp->num)
		temp->left = addNew(temp->left, n);
	else if (n > temp->num)
		temp->right = addNew(temp->right, n);

	return temp;
}

Node searchFor(Node temp, int n) {
	
	if (temp == NULL)
		return NULL;

	if (n < temp->num)
		temp->left = searchFor(temp->left, n);

	else if (n > temp->num)
		temp->right = searchFor(temp->right, n);

	return temp;
}

Node deleteNode(Node current, int n) {
	if (current == NULL)
		return NULL;

	if (n < current->num)
		current->left = deleteNode(current->left, n);

	else if (n > current->num)
		current->right = deleteNode(current->right, n);

	else {
		if (current->left == NULL) {
			Node temp = current->right;
			free(current);
			return temp;
		}

		else if (current->right == NULL) {
			Node temp = current->left;
			free(current);
			return temp;
		}

		Node temp = findMinimum(current->right);
		current->num = temp->num;

		current->right = deleteNode(current->right, temp->num);
	}

	return current;
}

Node findMinimum(Node temp){
		
	if (temp == NULL)
		return NULL;

	if (temp->left == NULL)
		return temp;

	else
		temp->left = findMinimum(temp->left);
}

void printTree(Node temp) {
	
	if (temp == NULL) {
		printf("Stablo je prazno\n");
		return;
	}

	if (temp->left != NULL)
		printTree(temp->left);

	printf("%d ", temp->num);

	if (temp->right != NULL)
		printTree(temp->right);
}