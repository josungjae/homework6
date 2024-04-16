#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front, rear; // 큐의 전단(front)과 후단(rear)을 나타내는 변수
} QueueType;

QueueType *createQueue(); // 큐를 생성하는 함수
int freeQueue(QueueType *cQ); // 큐를 해제하는 함수
int isEmpty(QueueType *cQ); // 큐가 비어있는지 확인하는 함수
int isFull(QueueType *cQ); // 큐가 가득 찼는지 확인하는 함수
void enQueue(QueueType *cQ, element item); // 큐에 원소를 추가하는 함수
void deQueue(QueueType *cQ, element *item); // 큐에서 원소를 삭제하는 함수
void printQ(QueueType *cQ); // 큐의 원소를 출력하는 함수
void debugQ(QueueType *cQ); // 디버그 정보를 출력하는 함수
element getElement(); // 사용자로부터 원소를 입력받는 함수

int main(void)
{
	printf("[----- [Jo Sungjae] [2023078001]-----]");
    QueueType *cQ = createQueue(); // 큐 생성
    element data; // 큐에 넣을 데이터 변수
    char command; // 사용자 입력 커맨드 변수

    do {
        printf("\n-----------------------------------------------------\n");
        printf("                     Circular Q                   \n");
        printf("------------------------------------------------------\n");
        printf(" Insert=i    Delete=d    PrintQ=p    Debug=b    Quit=q \n");
        printf("------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); // 사용자로부터 커맨드 입력 받기

        switch(command) {
        case 'i': case 'I':
            data = getElement(); // 데이터 입력 받기
            enQueue(cQ, data); // 큐에 데이터 추가
            break;
        case 'd': case 'D':
            deQueue(cQ, &data); // 큐에서 데이터 삭제
            break;
        case 'p': case 'P':
            printQ(cQ); // 큐 출력
            break;
        case 'b': case 'B':
            debugQ(cQ); // 디버그 정보 출력
            break;
        case 'q': case 'Q':
            freeQueue(cQ); // 큐 해제
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while(command != 'q' && command != 'Q');

    return 0;
}

QueueType *createQueue()
{
    QueueType *cQ;
    cQ = (QueueType *)malloc(sizeof(QueueType)); // 큐 구조체 메모리 할당
    cQ->front = 0; // 전단(front) 초기화
    cQ->rear = 0; // 후단(rear) 초기화
    return cQ; // 생성된 큐 반환
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ); // 큐 메모리 해제
    return 1;
}

element getElement()
{
    element item;
    printf("Input element = ");
    scanf(" %c", &item); // 사용자로부터 원소 입력 받기
    return item;
}

int isEmpty(QueueType *cQ)
{
    return cQ->front == cQ->rear; // 큐가 비어있는지 여부 반환
}

int isFull(QueueType *cQ)
{
    return (cQ->rear + 1) % MAX_QUEUE_SIZE == cQ->front; // 큐가 가득 찼는지 여부 반환
}

void enQueue(QueueType *cQ, element item)
{
    if (isFull(cQ)) { // 큐가 가득 찼는지 확인
        printf("Queue is full.\n");
        return;
    }
    cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; // 후단(rear) 이동
    cQ->queue[cQ->rear] = item; // 후단 위치에 데이터 삽입
}

void deQueue(QueueType *cQ, element *item)
{
    if (isEmpty(cQ)) { // 큐가 비어있는지 확인
        printf("Queue is empty.\n");
        return;
    }
    cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; // 전단(front) 이동
    *item = cQ->queue[cQ->front]; // 전단 위치의 데이터 반환
}

void printQ(QueueType *cQ)
{
    int i, first, last;
    first = (cQ->front + 1) % MAX_QUEUE_SIZE; // 시작 위치 설정
    last = (cQ->rear + 1) % MAX_QUEUE_SIZE; // 마지막 위치 설정

    printf("Circular Queue : [");

    i = first;
    while(i != last) { // 시작부터 끝까지 출력
        printf("%3c", cQ->queue[i]);
        i = (i+1) % MAX_QUEUE_SIZE;
    }
    printf(" ]\n");
}

void debugQ(QueueType *cQ)
{
    printf("\n---DEBUG\n");
    for(int i = 0; i < MAX_QUEUE_SIZE; i++) {
        if(i == cQ->front) {
            printf("  [%d] = front\n", i);
            continue;
        }
        printf("  [%d] = %c\n", i, cQ->queue[i]);
    }
    printf("front = %d    rear = %d\n", cQ->front, cQ->rear);
}
