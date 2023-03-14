#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void rotate_right(int array[],int n);
int control(int board[][8],int n,int row);
int update_board(int board[][8],int n, int row,int mode);

int main(){
	setlocale(LC_ALL,"turkish");
	int i,j,n,k,mode_select;
	int board[8][8];
	char colors[8][8][20];
	
	do{
		printf("Tahtan�n boyutunu 3 ile 8 aras�nda giriniz: ");
		scanf("%d",&n);
	}while(n<3 || n>8);
	
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("Tahtan�n [%d][%d]'deki eleman�n� giriniz: ",i,j);
			scanf("%s",colors[i][j]);
		}
	}
	
	do{
		printf("\nNormal mod i�in 0, detay mod i�in 1 tu�una bas�n�z: ");
  		scanf("%d",&mode_select);
	}while(mode_select!=0 && mode_select!=1);
	
	printf("\nGirilen renk matrisi:\n");
	for (i = 0; i < n; i++) {
    	for (j = 0; j < n; j++) {
      		printf("%s\t\t",colors[i][j]);
    	}
    	printf("\n");
	}
	
	for (i = 0; i < n; i++) {				// Girilen renk matrisi bir say� matrisine d�n��t�r�l�p board matrisinde saklan�r. 
    	for (j = 0; j < n; j++) {			// Matriste renklere say� verilirken renk matrisinin ilk s�tununda o rengin indeksine bak�l�r.
      		for (k = 0; k < n; k++) {
        		if (!strcmp(colors[i][j],colors[0][k])) {
          		board[i][j] = k;
        		}
      		}
    	}
  	}
  	
  	printf("\nSay�lara �evrilmi� matris:\n");
	for (i = 0; i < n; i++) { 
    	for (j = 0; j < n; j++) { 
        	printf("%d ", board[i][j]); 
      	}  
      	printf("\n"); 
    }
    
    if(update_board(board,n,0,mode_select)){
    	printf("\nSonu�:\n");
    	for(i=0;i<n;i++){
    		for(j=0;j<n;j++){
    			printf("%s\t\t",colors[0][board[i][j]]);
			}
			printf("\n");
		}
		printf("\nSay�lara �evrilmi� matriste sonu�:\n");
		for(i=0;i<n;i++){
    		for(j=0;j<n;j++){
    			printf("%d ",board[i][j]);
			}
			printf("\n");
		}
	}
	else{
		printf("\nGirilen matris i�in sonu� bulunmamaktad�r.\n");
	}
	
	return 0;
}

void rotate_right(int array[],int n){	// Bir diziyi sa�a kayd�rmak i�in kullan�lan fonksiyon.
	int temp[8];
	int i;
	for(i=0;i<n;i++){					// Dizinin sa�a kayd�r�lm�� halini temp dizisinde kaydeder.
		temp[i] = array[(i-1+n)%n];
	}
	for(i=0;i<n;i++){					// Temp dizisini array dizisine yazar.
		array[i] = temp[i];
	}
}

int control(int board[][8],int n,int row){	// Girilen sat�r de�erinden yukar�ya do�ru bakarak tahtan�n mevcut halinin kurallara uyup uymad���n� kontrol eder.
	int i,j;
	for(i=0;i<row;i++){		
		for(j=0;j<n;j++){
			if(board[i][j] == board[row][j]){			// Daha �stteki bir sat�r�n ayn� s�tununda ayn� de�erle kar��la��l�rsa 0 d�nd�r�r.
				return 0;
			}
		}
	}
	return 1;
}

int update_board(int board[][8],int n, int row,int mode){	// Tahtan�n durumunu girilen sat�r� sa�a kayd�rarak ve kurallara uyup uymad���n� kontrol ederek g�nceller.
	int i,j,k;
	if(row>=n){		// Girilen s�tun say�s� toplam s�tun say�s�ndan b�y�k veya e�itse tahta ba�ar�l� bir �ekilde g�ncellenmi� demektir.
		return 1;
	}
	
	for(i=0;i<n;i++){	// Mevcut sat�r i�in kayd�r�larak olu�turulacak b�t�n olas�l�klar� dener.
		if(mode==1){
			printf("\nG�ncelleniyor:\n");
			for(j=0;j<=row;j++){
				for(k=0;k<n;k++){
					printf("%d ",board[j][k]);
				}
				printf("\n");
			}
			printf("*********************\n");
		}
		if(control(board,n,row)){				// E�er mevcut durum kurallara uyuyorsa bir sonraki s�tun i�in fonksiyon �a�r�l�r.
			if(update_board(board,n,row+1,mode)){	
				return 1;
			}
		}
		rotate_right(board[row],n);	// Mevcut s�tunun de�erleri sa�a d�nd�r�l�r.
	}
	
	return 0;
}
