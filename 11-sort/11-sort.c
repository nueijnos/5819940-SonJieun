#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define SWAP(x,y,t) ((t)=(x), (x) = (y), (y)=(t) )

void generateRandomData(int list[]) { //랜덤 데이터 생성 함수
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++) {
		list[i] = rand() % 1000;
	}
}

void print_list(int list[], int n) { //출력 함수
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}

void doSelectionSort(int list[]) { //선택 정렬 함수
	printf("Selection Sort: \n");
	int i, j, least, temp;
	int n = SIZE;

	for (i = 0; i < n - 1; i++) { //순회하면서 정렬
		least = i;
		for (j = i + 1; j < n; j++)
			if (list[least] > list[j]) least = j;

		SWAP(list[i], list[least], temp); //최솟값과 현재 위치 값을 교환
		if ((i + 1) % 20 == 10) { //10부터 20 간격으로 출력(10, 30, 50, 70, 90)
			printf("Step %d: ", i + 1);
			print_list(list, n);
			printf("\n");
		}
	}
	printf("Step %d: ", i); //99
	print_list(list, n); //마지막 번째 정렬을 출력
}

void doInsertionSort(int list[]) { //삽입 정렬
	int i, j, key, compareCount;
	int n = SIZE;
	int total = 0; //총 비교횟수 저장

	for(int try = 0; try < 20; try++) { //삽입 정렬20회 시도하고
		int randomData[SIZE];
		generateRandomData(randomData);
		compareCount = 0;
		for (i = 1; i < n; i++) { //삽입 정렬 알고리즘
			key = randomData[i];
			for (j = i - 1; j >= 0; j--) {
				compareCount++;
				if (randomData[j] > key) randomData[j + 1] = randomData[j];
				else break;
			}
			randomData[j + 1] = key; //적절한 위치에 키 값 삽입
		}
		total += compareCount;
	}
	int avgCompare = total / 20; //평균 비교횟수 게산
	printf("\n\nInsertion Sort Compare Average: %d\n", avgCompare);
	printf("Insertion Sort Result:\n");
	print_list(list, n); //삽입 정렬 결과 출력
}

void doBubbleSort(int list[]) { //버블 정렬
	int i, j, temp, flag, moveCount;
	int n = SIZE;
	int total = 0; //총 비교횟수 저장

	for(int try = 0; try < 20; try++) { //버블 정렬20회 시도하고
		int randomData[SIZE];
		generateRandomData(randomData);
		moveCount = 0;
		for (i = n - 1; i > 0; i--) { //버블 정렬 알고리즘
			flag = 0;
			for (j = 0; j < i; j++) {
				if (randomData[j] > randomData[j + 1]) {
					SWAP(randomData[j], randomData[j + 1], temp); //값 교환
					flag = 1; 
					moveCount += 3; //각 swap마다 값의 이동을 3회로 간주
				}
			}
			if (flag == 0) break;
		}
		total += moveCount;
	}
	int avgMove = total / 20; //평균 이동횟수 계산
	printf("\n\nBubble Sort Move Average: %d\n", avgMove);
	printf("Bubble Sort Result:\n");
	print_list(list, n); //버블 정렬 결과 출력
}

int main() {
	int randomData[SIZE];
	generateRandomData(randomData);

	doSelectionSort(randomData);
	doInsertionSort(randomData);
	doBubbleSort(randomData);

	return 0;
}

//◈ 0 - 999 사이의 랜덤 데이터 100개로 선택정렬, 삽입정렬, 버블정렬을 수행한다.
//1. 선택 정렬에서 정렬 과정을 10부터 20단위로 출력, 마지막 번째 출력
//2. 삽입 정렬20회 시도하고 평균 비교횟수와 정렬결과 출력
//3. 버블 정렬20회 시도하고 평균 이동횟수(각 swap마다 값의 이동을 3회로 생각)와 정렬결과 출력
//- 20회 반복의 경우, 함수 내부에서 generateRandomNumbers함수를 매회마다 호출해 매번 다른 random값으로 수행한 후 누적한 결과에 대해 출력. (if문 등으로 20회 수행시에는 print안되도록 조정)