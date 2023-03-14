#include <stdio.h>
#include <stdlib.h>
#include<time.h>

struct Node{
		int data;
		struct Node *next;
		struct Node *bottom;
	};
	
void EkleSirala(struct Node** node, int number,struct Node** bottomx);
void PrintList(struct Node* node);
void BulveSil(struct Node** node);
void Build(struct Node** node,struct Node** yeni);
int Search(struct Node** node,int key,int level);

int main(){
	srand(time(0));	
	int number,i,k,key;
	int selection,sayi;
	printf("NOTE: You need to either enter the numbers of the list or randomly generate the list first. Then you need to press 5 to build all levels of list.\n\n");
	printf("How many upper levels do you want your list to have?: ");
	scanf("%d",&k);
	struct Node **ar = calloc(k+1,(sizeof(struct Node)));
	struct Node *head = NULL;
	struct Node *null = NULL;
	
	while(1){
		printf("\n\n1- Add Node\t2- Randomly Generate Nodes\t3- Delete Node\t4- Print List\n5- Build\t6- Print List With All Levels\t7- Search\t8- Exit\n");
		scanf("%d",&selection);
		switch(selection){
			case 1:
				printf("\nNumber you want to add:  ");
				scanf("%d",&number);
				EkleSirala(&head,number,&null);
				ar[0]=head;
				PrintList(ar[0]);
				printf("\n");
				break;
			case 2:
				printf("How many numbers do you want your list to have?: ");
				scanf("%d",&sayi);
				for(i=0;i<sayi;i++){
					number = rand()%100;
					EkleSirala(&head,number,&null);
					ar[0]=head;
					}
					for(i=0;i<k;i++){
					Build(&ar[i],&ar[i+1]);
					}	
					break;
			case 3:
				BulveSil(&ar[0]);
				for(i=0;i<k;i++){
					Build(&ar[i],&ar[i+1]);
				}
				printf("\n");
				for(i=k;i>=0;i--){
				PrintList(ar[i]);
				printf("\n");}
				break;
			case 4:
				printf("\n");
				PrintList(head);
				printf("\n");
				break;
			case 5:
				for(i=0;i<k;i++){
				Build(&ar[i],&ar[i+1]);
				}
				for(i=k;i>=0;i--){
				PrintList(ar[i]);
				printf("\n");}
				break;
			case 6:
				printf("\n");
				for(i=k;i>=0;i--){
				PrintList(ar[i]);
				printf("\n");}
				break;
			case 7:
				printf("\nWhich number do you want to search?: ");
				scanf("%d",&key);
				printf("\n");
				Search(&ar[k],key,k);
				break;		
			case 8:
				return 0;
		}
	}
	return 0;
}

void EkleSirala(struct Node** node, int number,struct Node** bottomx){
	struct Node *new = (struct Node*)malloc(sizeof(struct Node));
	struct Node *ileri = *node;
	struct Node *tmp;
	new->data = number;
	new->next = NULL;
	new->bottom = *bottomx;
	if(*node == NULL)                                  //Daha �nce d���me veri eklenmediyse ilk eklenen veri head de�eri olarak atan�r.
    {
        new->next = NULL;
       (*node) = new;
       return;
	}
	if((new->data)<((*node)->data)){                   //Eklenen veri t�m de�erlerden k���kse en ba�taki node yerine ge�er.
		new->next = *node;
		(*node) = new;
		return;
	}
	while((ileri->data)<(new->data) && (ileri->next) != NULL){					//Eklenen veri d���mler aras�nda artan s�rayla uygun yere yerle�tirilir.
		tmp = ileri;
		ileri = ileri->next;
	}
	if(ileri->next == NULL && (ileri->data)<(new->data)){
		ileri->next = new;
		new->next = NULL;
	}
	else{
		tmp->next = new;
		new->next = ileri;
		}

 return;
}

void PrintList(struct Node* node){
	while(node != NULL){
		printf("%d  ",node->data);
		node = node->next;
	}
	return;
}

void BulveSil(struct Node** node){
	int k;
	struct Node *ileri = *node;
	struct Node *tmp;
	printf("\nWhich data do you want to delete?: ");
	scanf(" %d",&k);
	while(k!=(ileri->data) && (ileri->next) != NULL){
		tmp = ileri;
		ileri = ileri->next;
	}
	if(ileri->next==NULL && k!=(ileri->data)){
	printf("Searched data could not be found in the list.\n");
	PrintList(*node);
	printf("\n\n");
	return;
	}
	if(k==(ileri->data)){
		tmp->next = ileri->next;
		if(ileri == *node){
		*node = (*node)->next;
		}
	}
	return;
}

void Build(struct Node** node,struct Node** yeni){	// node k�sm�na ar[i] (i. levelin ilk eleman�) girecek, yap�lan i�lemler sonucu 
	srand(time(NULL));								// ar[i+1] (i+1'inci levelin ilk eleman�) yeni olarak giren de�i�kene atanacak. 
    int i;
	struct Node *top1 = (struct Node*)malloc(sizeof(struct Node));
	struct Node *tmp = *node;
	top1->data = (*node)->data;			//top1 de�i�keni bir �st seviyenin ilk eleman� olacak. data's� node->data'ya e�it olacak.
	top1->bottom = *node;				//bottom de�eri ise alt seviyedeki ilk elemana i�aret edecek.
	top1->next = NULL;
	while(tmp->next != NULL){			//�st seviyedeki ilk elemandan sonra gelecek elemanlar random olarak belirlenecek.
		int random = rand()%(2);
		if(random==1){
		EkleSirala(&top1,tmp->data,&tmp);
		}
		tmp = tmp->next;
	}
	*yeni = top1;
	return;
}

int Search(struct Node** node,int key,int level){
	int count=0,seviye = level;
	struct Node *ileri = *node;
	struct Node *tmp = *node;
	if(key<(ileri->data)){							//Aranan say� liste ba��ndaki say�dan k���kse listede yoktur.
		printf("\nSearched data could ne be found.");
		return 0;
	}
	else{
	while((ileri->data)!=key){					//Aranan say� ileri->data'ya e�it olmad��� s�rece arama yap�lacakt�r.
		if((ileri->data)<key){					
			if((ileri->next)==NULL){
			tmp = ileri;						//Aranan say� ileri->data'dan k���kse liste sonuna gelene kadar ilerlenecek. Liste sonuna gelindi�inde
			ileri = ileri->bottom;			//ilerinin alt�nda bir seviye varsa oraya ge�ilecek.
			seviye--;
			}
			else{
			tmp = ileri;
			ileri = ileri->next;
			}
	    }
	    else{								//Kar��m�za ��kan say� aranan say�dan b�y�kse ileri, tmp'nin alt�ndaki say�ya ge�ecek.
	    	ileri = tmp->bottom;
	    	seviye--;
	    }
		if((ileri->next)==NULL && (ileri->bottom)==NULL && key!=(ileri->data)){		//Son gelinen say�n�n alt�nda ve sa��nda yeni bir de�er yoksa t�m liste taranm�� ve say�
		printf("\nSearched data could not be found.");								// bulunamam�� oldu�u i�in fonksiyondan s�f�r d�nd�r�lecek.
		return 0;
		}
		if(key<(ileri->data)&&key!=(tmp->data)&&tmp->bottom==NULL){		//Aranan say� ileri'den k���k ve tmp'e e�it de�ilse, tmp->bottom'a d�n�lemiyorsa (en alt seviyedeysek)
		printf("\nSearched data could not be found.");					//fonksiyon s�f�r d�nd�recek.
		return 0;
		}
		printf("\tIteration #%d#: Data found: %d\t\n",count+1,ileri->data);
		count++;
	}
	if(count==0 && key==(ileri->data)){
	printf("\nSearched data is the first data of the list.");
	}
	printf("\nSearched data found at %d iterations and level %d",count,seviye);}
	return 1;
}
