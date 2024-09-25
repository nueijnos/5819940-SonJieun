#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

typedef TreeNode* element;

typedef struct QueueNode {
	element data;
	struct QueueNode* link;
} QueueNode;

typedef struct {
	QueueNode* front, * rear;
} LinkedQueueType;

void init(LinkedQueueType* q) {
	q->front = q->rear = NULL;
}

int is_empty(LinkedQueueType* q) {
	return q->front == NULL;
}

void enqueue(LinkedQueueType* q, element node) {
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->data = node;
	temp->link = NULL;
	if (is_empty(q)) {
		q->front = temp;
		q->rear = temp;
	}
	else { 		
		q->rear->link = temp; 
		q->rear = temp;
	}
}

element dequeue(LinkedQueueType* q) {
	QueueNode* temp = q->front;
	element data;
	if (is_empty(q)) {
		fprintf(stderr, "스택이 비었음\n");
		exit(1);
	}
	else {
		data = temp->data; 
		q->front = q->front->link; 
		if (q->front == NULL) 	
			q->rear = NULL;
		free(temp); 	
		return data;
	}
}

void PlaceNode(TreeNode* node, int direction, int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;

	if (direction == 0) {
		node->left = newNode;
	}
	else if (direction == 1) {
		node->right = newNode;
	}
}

void GenerateLinkTree(TreeNode *root) {
	PlaceNode(root, 0, 2);
	PlaceNode(root, 1, 9);
	PlaceNode(root->left, 0, 3);
	PlaceNode(root->left, 1, 5);
	PlaceNode(root->right, 0, 10);
	PlaceNode(root->right, 1, 13);
	PlaceNode(root->left->left, 0, 4);
	PlaceNode(root->left->left, 1, 6);
	PlaceNode(root->left->right, 0, 7);
	PlaceNode(root->left->right, 1, 8);
	PlaceNode(root->right->left, 0, 11);
	PlaceNode(root->right->left, 1, 12);
	PlaceNode(root->right->right, 0, 14);
	PlaceNode(root->right->right, 1, 15);
}

int GetSumOfNodes(TreeNode* root) { //트리의 모든 노드의 값을 더하기 120
	LinkedQueueType q;
	TreeNode* curr = root;
	int sum = 0;
	init(&q);
	
	while (curr != NULL || !is_empty(&q)) {
		while (curr != NULL) {
			enqueue(&q, curr);
			curr = curr->left;
		}
		curr = dequeue(&q);
		sum += curr->data;
		if (curr != NULL) {
			curr = curr->right;
		}
	}
	return sum;
}

int GetNumberOfNodes(TreeNode* root) { //트리의 전체 노드 갯수 구하기 15
	LinkedQueueType q;
	TreeNode* curr = root; 
	int count = 0;
	init(&q);

	while (curr != NULL || !is_empty(&q)) {
		while (curr != NULL) {
			enqueue(&q, curr);
			curr = curr->left;
		}
		curr = dequeue(&q);
		count++;
		if (curr != NULL) {
			curr = curr->right;
		}
	}
	
	return count;
}

int GetHeightOfTree(TreeNode* root) { //트리의 높이 4
	if (root == NULL) return 0;

	LinkedQueueType q;
	TreeNode* curr = root;
	int height = 0;
	init(&q);

	enqueue(&q, root);

	while (curr != NULL || !is_empty(&q)) {
		int nodeCount = 0;
		QueueNode* temp = q.front;

		while (temp != NULL) { 
			nodeCount++;
			temp = temp->link;
		}

		if (nodeCount == 0) return height; 

		height++; 

		for (int i = 0; i < nodeCount; i++) {
			curr = dequeue(&q);
			if (curr->left != NULL)
				enqueue(&q, curr->left);
			if (curr->right != NULL)
				enqueue(&q, curr->right); 
		}
	}

	return height; 
}

int GetNumberOfLeafNodes(TreeNode* root) { //단말 노드의 수 8
	if (root == NULL) return 0;

	LinkedQueueType q;
	TreeNode* curr = root;
	int leafCount = 0;
	init(&q);

	enqueue(&q, root);

	while (!is_empty(&q)) {
		curr = dequeue(&q);

		if (curr->left == NULL && curr->right == NULL) {
			leafCount++;
		}
		if (curr->left != NULL) {
			enqueue(&q, curr->left);
		}
		if (curr->right != NULL) {
			enqueue(&q, curr->right);
		}
	
	}

	return leafCount;
}

int main() {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1; 
	root->left = NULL;
	root->right = NULL;


	GenerateLinkTree(root);

	printf("Sum of nodes : %d\n", GetSumOfNodes(root)); 
	printf("Number of nodes : %d\n", GetNumberOfNodes(root));
	printf("Height of Tree : %d\n", GetHeightOfTree(root));
	printf("Number of leaf nodes : %d\n ", GetNumberOfLeafNodes(root));

	return 0;
}

//첨부된 pdf파일을 꼼꼼히 읽어보고 구현하세요.

//단, 재귀적 방법이 아닌 반복적 방법을 사용해야 한다
//
//->재귀적 방법으로 구현된 경우 0점

//* *pdf파일의 출력결과 및 제출양식 꼼꼼히 확인하고 제출하세요 * *