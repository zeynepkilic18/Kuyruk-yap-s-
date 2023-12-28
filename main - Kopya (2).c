

#include <stdio.h>
#include <stdlib.h>

typedef struct Musteri {      
    int id;
    struct Musteri *next;
} Musteri;


typedef struct Queue {
    Musteri *front;  // Kuyruðun önü
    Musteri *rear;   // Kuyruðun sonu
} Queue;


Queue *createQueue() {
    Queue *queue=(Queue*)malloc(sizeof(Queue)); //Dinamik bellek tahsisi
    if (!queue) 
	{
        perror("Kuyruk oluþturulurken hata!!!");
        exit(EXIT_FAILURE);
    }
    queue->front=NULL;
	queue->rear=NULL;
    return queue;
}

void enqueue(Queue *queue, int id) {   // Kuyruða müþteri ekleme
    Musteri *yeniMusteri;
	yeniMusteri=(Musteri*)malloc(sizeof(Musteri));
    if (!yeniMusteri) 
	{
        perror("Müþteri eklenirken hata!!!");
        exit(EXIT_FAILURE);
    }
    yeniMusteri->id=id;
    yeniMusteri->next=NULL;

    // Kuyruk boþsa
    if (queue->rear==NULL) 
	{
        queue->front=yeniMusteri;
		queue->rear=yeniMusteri;
    } 
    
	else 
	{
        // ID'ye göre öncelik kontrolü yapýlýr
        if (id==3)
		{
            yeniMusteri->next=queue->front;  // 65 yaþ üstü, kuyruðun baþýna ekle
            queue->front=yeniMusteri;
        }
		 
		else if (id==2)
		{
            yeniMusteri->next=queue->front->next;  // Özel müþteri, kuyruðun en baþýndaki kiþinin iki arkasýna ekle
            queue->front->next=yeniMusteri;
        } 
        
		else
		{
            queue->rear->next=yeniMusteri;  // Diðer durumlar, kuyruðun sonuna ekle
            queue->rear=yeniMusteri;
        }
    }

    printf("ID%d kuyruða eklendi.\n", id);
}

// Kuyruktan müþteri çýkarma
void dequeue(Queue *queue) {
    if (queue->front==NULL) 
	{
        printf("Kuyruk boþ, müþteri çýkarýlamaz.\n");
        return;
    }

    Musteri *temp=queue->front;
    queue->front=queue->front->next;

    // Eðer kuyruk boþsa rear'ý da NULL yap
    if (queue->front==NULL)
	{
        queue->rear=NULL;
    }

    printf("ID%d iþlemden çýkarýldý.\n", temp->id);
    free(temp);
}

// Kuyruðu görüntüleme
void displayQueue(Queue *queue) {
    if (queue->front==NULL) 
	{
        printf("Kuyruk boþ.\n");
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

// Ana menü
void menu(Queue *queue) {
    int secim, id;

    do {
        printf("\n--- Menü ---\n");
        printf("1. Kuyruða müþteri ekle\n");
        printf("2. Kuyruktan müþteri çýkar\n");
        printf("3. Kuyruðu görüntüle\n");
        printf("4. Çýkýþ \n");
        printf("\nLütfen seçiminizi yapýn: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                printf("\nLütfen kiþinin ID'sini girin: ");
                printf("\n -ID=1 normal müþteri \n -ID=2 öncelikli müþteri \n -ID=3 65 yaþ üstü \n");
                scanf("%d", &id);
                if (id<1 || id>3)
				{
                    printf("Geçersiz ID!!! Lütfen 1,2 veya 3 girin.\n");
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
                printf("Programdan çýkýlýyor...\n");
                break;
            default:
                printf("Geçersiz seçim lütfen tekrar deneyin.\n");
        }

    } while (secim!=4);
}

int main() {
    Queue *queue=createQueue();

    menu(queue);

    while (queue->front!=NULL) {  // Kuyruktaki tüm müþterileri temizler
        dequeue(queue);
    }

    free(queue);  // Kuyruk yapýsýný ve programý sonlandýr

    return 0;
}

