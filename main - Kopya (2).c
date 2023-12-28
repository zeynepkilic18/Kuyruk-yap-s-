

#include <stdio.h>
#include <stdlib.h>

typedef struct Musteri {      
    int id;
    struct Musteri *next;
} Musteri;


typedef struct Queue {
    Musteri *front;  // Kuyru�un �n�
    Musteri *rear;   // Kuyru�un sonu
} Queue;


Queue *createQueue() {
    Queue *queue=(Queue*)malloc(sizeof(Queue)); //Dinamik bellek tahsisi
    if (!queue) 
	{
        perror("Kuyruk olu�turulurken hata!!!");
        exit(EXIT_FAILURE);
    }
    queue->front=NULL;
	queue->rear=NULL;
    return queue;
}

void enqueue(Queue *queue, int id) {   // Kuyru�a m��teri ekleme
    Musteri *yeniMusteri;
	yeniMusteri=(Musteri*)malloc(sizeof(Musteri));
    if (!yeniMusteri) 
	{
        perror("M��teri eklenirken hata!!!");
        exit(EXIT_FAILURE);
    }
    yeniMusteri->id=id;
    yeniMusteri->next=NULL;

    // Kuyruk bo�sa
    if (queue->rear==NULL) 
	{
        queue->front=yeniMusteri;
		queue->rear=yeniMusteri;
    } 
    
	else 
	{
        // ID'ye g�re �ncelik kontrol� yap�l�r
        if (id==3)
		{
            yeniMusteri->next=queue->front;  // 65 ya� �st�, kuyru�un ba��na ekle
            queue->front=yeniMusteri;
        }
		 
		else if (id==2)
		{
            yeniMusteri->next=queue->front->next;  // �zel m��teri, kuyru�un en ba��ndaki ki�inin iki arkas�na ekle
            queue->front->next=yeniMusteri;
        } 
        
		else
		{
            queue->rear->next=yeniMusteri;  // Di�er durumlar, kuyru�un sonuna ekle
            queue->rear=yeniMusteri;
        }
    }

    printf("ID%d kuyru�a eklendi.\n", id);
}

// Kuyruktan m��teri ��karma
void dequeue(Queue *queue) {
    if (queue->front==NULL) 
	{
        printf("Kuyruk bo�, m��teri ��kar�lamaz.\n");
        return;
    }

    Musteri *temp=queue->front;
    queue->front=queue->front->next;

    // E�er kuyruk bo�sa rear'� da NULL yap
    if (queue->front==NULL)
	{
        queue->rear=NULL;
    }

    printf("ID%d i�lemden ��kar�ld�.\n", temp->id);
    free(temp);
}

// Kuyru�u g�r�nt�leme
void displayQueue(Queue *queue) {
    if (queue->front==NULL) 
	{
        printf("Kuyruk bo�.\n");
        return;
    }

    Musteri *current=queue->front;
    printf("Kuyruk: ");
    while (current != NULL)
	{
        printf("ID%d ", current->id);
        current=current->next;
    }
    printf("\n");
}

// Ana men�
void menu(Queue *queue) {
    int secim, id;

    do {
        printf("\n--- Men� ---\n");
        printf("1. Kuyru�a m��teri ekle\n");
        printf("2. Kuyruktan m��teri ��kar\n");
        printf("3. Kuyru�u g�r�nt�le\n");
        printf("4. ��k�� \n");
        printf("\nL�tfen se�iminizi yap�n: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                printf("\nL�tfen ki�inin ID'sini girin: ");
                printf("\n -ID=1 normal m��teri \n -ID=2 �ncelikli m��teri \n -ID=3 65 ya� �st� \n");
                scanf("%d", &id);
                if (id<1 || id>3)
				{
                    printf("Ge�ersiz ID!!! L�tfen 1,2 veya 3 girin.\n");
                } 
				else
				{
                    enqueue(queue, id);
                }
                break;
            case 2:
                dequeue(queue);
                break;
            case 3:
                displayQueue(queue);
                break;
            case 4:
                printf("Programdan ��k�l�yor...\n");
                break;
            default:
                printf("Ge�ersiz se�im l�tfen tekrar deneyin.\n");
        }

    } while (secim!=4);
}

int main() {
    Queue *queue=createQueue();

    menu(queue);

    while (queue->front!=NULL) {  // Kuyruktaki t�m m��terileri temizler
        dequeue(queue);
    }

    free(queue);  // Kuyruk yap�s�n� ve program� sonland�r

    return 0;
}

