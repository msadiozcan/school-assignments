#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
void rastgele_matris(int satir, int sutun,int sutun2, int matris[satir][sutun],int matris2[sutun][sutun2]);
void matrisi_al(int satir, int sutun, int matris[satir][sutun]);
void naive_method(int satir,int sutun, int sutun2, int matris1[satir][sutun],int matris2[sutun][sutun2],int carpim[satir][sutun2]);
void add(int size, int a[size][size], int b[size][size],int c[size][size]);
void sub(int size,int a[size][size],int b[size][size],int c[size][size]);
void strassen(int n,int a[n][n],int b[n][n],int c[n][n]);
void divide_and_conquer(int n,int a[n][n],int b[n][n],int c[n][n]);

int main(){
	int satir, sutun, sutun2, n, i, j,secim;
	clock_t time1,time2,time3;
	printf("1.matrisin satir ve sutun sayisini sirasiyla giriniz: ");
	scanf("%d",&satir);
	scanf("%d",&sutun);
	printf("\n 2.matrisin sutun sayisini giriniz: ");
	scanf("%d",&sutun2);
	
	int matrix1[satir][sutun], matrix2[sutun][sutun2],carpim_naive[satir][sutun2];
	
	do{
	printf("\n 1-) Matrisi elle girmek istiyorum.\n 2-) Rastgele bir matris olustur.\n");
	scanf("%d",&secim);
	}while(secim!=1 && secim!=2);
	
	switch(secim){
		case 1:
			matrisi_al(satir,sutun,matrix1);
			printf("\n\n");
			matrisi_al(sutun,sutun2,matrix2);
			break;
		case 2:
			rastgele_matris(satir,sutun,sutun2,matrix1,matrix2);
	}
	printf("Standart Matris Carpim Algoritmasi ile Hesaplanan Sonuc:\n");
	
	time1 = clock();														// zaman� �l��yoruz.
	naive_method(satir,sutun,sutun2,matrix1,matrix2,carpim_naive);
	time1 = clock() - time1;												// zaman� �l��yoruz.
	
			for(i=0;i<satir;i++){											//sonu� matrisimizi yazd�r�yoruz.											
				printf("\n");
				for(j=0;j<sutun2;j++){
					printf("%d \t",carpim_naive[i][j]);
				} }
		printf("\n");
	
		n = satir; 													// strassen algoritmas� n 2'nin kuvveti olmak �zere n x n 'lik matrislerde �al��t��� i�in
    	if(sutun>satir){											//    												 matrisler n x n'lik de�ilse n x n'lik hale getirilecek.									
   		 	n=sutun;
				}
		if(sutun2>n){
			n=sutun2;
		}
		n = pow(2, ceil(log(n)/log(2)));	 // n'i 2'nin en yak�n bir �st kuvvetine yuvarlad�k. matrisimiz art�k n x n ve n 2'nin kuvveti oldu�u i�in strassen algoritmas� uygulanabilir hale geldi.
	
		int matris1[n][n], matris2[n][n],carpim[n][n],matris1_2[n][n],matris2_2[n][n],carpim2[n][n];
		for(i=0;i<n;i++){										//strassen i�leminde kullanmak �zere nxn'lik yeni matrisler olu�turduk ve ba�ta ald���m�z matrisleri
			for(j=0;j<n;j++){									// yeni matrise kopyalayaca��z. matrisler nxn'lik de�ilse matrisi kopyalad�ktan sonra geri kalan bo�luklar�
				if(i>satir-1 || j>sutun-1){						// 0 ile dolduraca��z.
				matris1[i][j] = 0;
				matris1_2[i][j] = 0;}							
				else{
				matris1[i][j] = matrix1[i][j];
				matris1_2[i][j] = matrix1[i][j];
				}
			}	
			}
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(i>sutun-1 || j>sutun2-1){
				matris2[i][j] = 0;
				matris2_2[i][j] = 0;
			}
			else{
				matris2[i][j] = matrix2[i][j];
				matris2_2[i][j] = matrix2[i][j];
				}
			}	
			}

		time2 = clock();							//zaman �l��m�n� ba�lat�p fonksiyonu �a��r�yoruz. sonras�nda ge�en zaman� hesapl�yoruz.
		strassen(n,matris1,matris2,carpim);
		time2 = clock() - time2;
		
		time3 = clock();
		divide_and_conquer(n,matris1_2,matris2_2,carpim2);
		time3 = clock() - time3;
		
		printf("\nStrassen Algoritmasi ile Hesaplanan Sonuc:\n");			//sonucu yazd�r�yoruz.
		for(i=0;i<satir;i++){
			printf("\n");
		for(j=0;j<sutun2;j++){
			printf("%d \t",carpim[i][j]);
		} }
		
		printf("\n\nDivide And Conquer Algoritmasi ile Hesaplanan Sonuc:\n");			//sonucu yazd�r�yoruz.
		for(i=0;i<satir;i++){
			printf("\n");
		for(j=0;j<sutun2;j++){
			printf("%d \t",carpim2[i][j]);
		} }
	double oran = ((double)time2)/ ((double)time1);    //y�ld�zl� g�sterimi yapmak i�in zamanlar� birbirine g�re oranl�yoruz.
	double oran2 = ((double)time3) / ((double)time1);  		
	printf ("\n\nProgramin calismasi sirasinda gecen sure: \n\n Standart Algoritma icin:  %.50lf\n Strassen Algoritmasi icin: %.50lf\n Divide And Conquer Algoritmasi icin: %.50lf",((double)time1)/CLOCKS_PER_SEC,((double)time2)/CLOCKS_PER_SEC,((double)time3)/CLOCKS_PER_SEC);
  	
	  if(time1!=0 && time2!=0 && time3!=0){		// program bazen standart algoritma s�resini 0 �l�t��� i�in oran�m�z sonsuz oluyor ve sonsuz y�ld�z at�l�yor. bunu engellemek i�in grafik ko�ullu olarak �izilecek.
	printf("\n\n Standart algoritma suresi: 		**********");
	printf("\n Strassen algoritma suresi: 		" );
  	oran *= 10; oran2*= 10;														// zaman(strassen) / zaman(standart) oran�n� az �nce bulmu�tuk. burada kesirden kurtulmak i�in 10 ile �arp�yoruz.
  	for(i=0;i<=oran;i++){											// daha sonra bu orana g�re fonksiyon s�releri aras�ndaki fark� y�ld�zlarla ifade edece�iz.
  		printf("*");
	  }
	printf("\n Divide and Conquer algoritma suresi:   ");
	for(i=0;i<=oran2;i++){
		printf("*");
	} }
	return 0;
}

void rastgele_matris(int satir, int sutun,int sutun2, int matris[satir][sutun],int matris2[sutun][sutun2]){
	int i,j;																			
	srand(time(0));
	for(i=0;i<satir;i++){
		for(j=0;j<sutun;j++){
			matris[i][j] = rand() % 99 + 1;										//rand fonksiyonunu kullanarak istenen boyutta 2 adet rastgele matris �retmek i�in kullan�lan fonksiyon.
		}
	}
	for(i=0;i<sutun;i++){
		for(j=0;j<sutun2;j++){
			matris2[i][j] = rand() % 99 + 1;
		}
	}
	printf("Olusturulan matris:\n");
	for(i=0;i<satir;i++){
		printf("\n");
		for(j=0;j<sutun;j++){
			printf("%d \t",matris[i][j]);
		}
	}
	printf("\n\nOlusturulan matris:\n");
	for(i=0;i<sutun;i++){
		printf("\n");
		for(j=0;j<sutun2;j++){
			printf("%d \t",matris2[i][j]);
		}
	}
	printf("\n\n");
	return;
}

void matrisi_al(int satir, int sutun, int matris[satir][sutun]){				//kullan�c� matrisi kendi girmek isterse istenen boyutlarda matrisi alan fonksiyon.
	int i,j;
	for(i=0; i<satir; i++){
        for(j=0; j<sutun; j++){
            printf("[%d][%d]) Sayiyi giriniz: ", i+1, j+1);
            scanf("%d", &matris[i][j]);
        }
}
	printf("\nOlusturulan matris:\n");
	for(i=0;i<satir;i++){
		printf("\n");
		for(j=0;j<sutun;j++){
			printf("%d \t",matris[i][j]);
		}
	}
	printf("\n\n");
	
	return;
}

void naive_method(int satir,int sutun, int sutun2, int matris1[satir][sutun],int matris2[sutun][sutun2],int carpim[satir][sutun2]){ // standart matris �arp�m algoritmas�.
	int i,j,k,p;
	float toplam=0;

	for(i=0;i<satir;i++){
		for(j=0;j<sutun2;j++){
			toplam = 0;
			for(k=0;k<sutun;k++){
			toplam += matris1[i][k] * matris2[k][j];
			}
			carpim[i][j] = toplam;
			}
		}
	
return;
}

void add(int size, int a[size][size], int b[size][size],int c[size][size]){				//size x size boyutlar�ndaki iki matrisi toplay�p c matrisine yazan fonksiyon.
    int i,j;   
    for(i=0;i<size;i++){
    	for(j=0;j<size;j++){
            c[i][j] = a[i][j] + b[i][j];
		}
    }
    return;
}

void sub(int size,int a[size][size],int b[size][size],int c[size][size]){				//size x size boyutlar�ndaki a matrisinden b matrisini ��kar�p c matrisine yazan fonksiyon.
    int i,j;
    for(i=0;i<size;i++){
                for(j=0;j<size;j++){
                        c[i][j]= a[i][j] - b[i][j];
                }
        }
        return;
}

void divide_and_conquer(int n,int a[n][n],int b[n][n],int c[n][n]){
	int i,j,m=n/2;														//her a�aman�n ba��nda nxn 'lik matristen n/2 x n/2 boyutlar�nda 4 yeni matris olu�turulur.
	int	c00[m][m],c01[m][m],c10[m][m],c11[m][m];

	if(n==2){													// rek�rsif fonksiyonun base case'i.
		int ae = a[0][0] * b[0][0];			
		int bg = a[0][1] * b[1][0];	
		int af = a[0][0] * b[0][1];					//yap�lmas� gereken 8 �arp�m i�lemini yap�p bunlar� farkl� de�i�kenlere kaydediyoruz.
		int bh = a[0][1] * b[1][1];
		int ce = a[1][0] * b[0][0];
		int dg = a[1][1] * b[1][0];
		int cf = a[1][0] * b[0][1];
		int dh = a[1][1] * b[1][1];
		
		c[0][0]= ae+bg;								//yapt���m�z �arpma i�lemlerinde buldu�umuz de�i�kenleri, algoritmada belirtildi�i gibi toplama ve ��karma
		c[0][1]= af+bh;									//   i�lemlerine tabii tutarak buldu�umuz sonu�lar� sonu� matrisine kaydediyoruz.
		c[1][0]= ce+dg;
		c[1][1]= cf+dh;
	}
	else{																										//fonkiyonun recursive case'i.
		int a00[m][m], a01[m][m], a10[m][m], a11[m][m],	b00[m][m], b01[m][m], b10[m][m], b11[m][m];	//ba�taki matrislerin 4 par�as�n� b�l�p kaydetmek �zere kullan�lacak matrisler.
		int ae1[m][m],bg1[m][m],af1[m][m],bh1[m][m],ce1[m][m],dg1[m][m],cf1[m][m],dh1[m][m],sum1[m][m],sum2[m][m],sub1[m][m],sub2[m][m];
		for(i=0;i<m;i++){
			for(j=0;j<m;j++){								//ba�taki matrisleri 4 par�aya b�l�p yeni olu�turdu�umuz matrislere kaydediyoruz.
				a00[i][j] = a[i][j];						//											
				b00[i][j] = b[i][j];						//											|
				a01[i][j] = a[i][j+m];						//									a00		|		a01
				b01[i][j] = b[i][j+m];						//									b00		|		b01
				a10[i][j] = a[i+m][j];						//						        -----------------------------
				b10[i][j] = b[i+m][j];						//									a10		|		a11
				a11[i][j] = a[i+m][j+m];					//									b10		|		b11
				b11[i][j] = b[i+m][j+m];					//											|
			}
		}
		divide_and_conquer(m,a00,b00,ae1);
		divide_and_conquer(m,a01,b10,bg1);
		divide_and_conquer(m,a00,b01,af1);
		divide_and_conquer(m,a01,b11,bh1);
		divide_and_conquer(m,a10,b00,ce1);
		divide_and_conquer(m,a11,b10,dg1);
		divide_and_conquer(m,a10,b01,cf1);					//base case'de say�larlar yapt���m�z �arp�m i�lemlerini burada matrislerle yap�yoruz.
		divide_and_conquer(m,a11,b11,dh1);

		add(m,ae1,bg1,c00);											
		add(m,af1,bh1,c01);
		add(m,ce1,dg1,c10);
		add(m,cf1,dh1,c11);											
		
		for(i=0;i<m;i++){										//buldu�umuz c00, c01, c10 ve c11 matrislerini sonu� matrisinde birle�tiriyoruz.
			for(j=0;j<m;j++){
				c[i][j] = c00[i][j];
				c[i][j+m] = c01[i][j];
				c[i+m][j] = c10[i][j];
				c[i+m][j+m] = c11[i][j];
			}
		} 
}
	return;
}

void strassen(int n,int a[n][n],int b[n][n],int c[n][n]){
	int i,j,m=n/2;														//her a�aman�n ba��nda nxn 'lik matristen n/2 x n/2 boyutlar�nda 4 yeni matris olu�turulur.
	int	c00[m][m],c01[m][m],c10[m][m],c11[m][m];

	if(n==2){													// rek�rsif fonksiyonun base case'i.
		int P = (a[0][0]+a[1][1]) * (b[0][0]+b[1][1]);			
		int Q = (a[1][0]+a[1][1]) * b[0][0];	
		int R = a[0][0] * (b[0][1]-b[1][1]);					//strassen algoritmas�nda yap�lmas� gereken 7 adet �arp�m i�lemini yap�p bunlar� farkl� de�i�kenlere kaydediyoruz.
		int S = a[1][1] * (b[1][0]-b[0][0]);
		int T = (a[0][0]+a[0][1]) * b[1][1];
		int U = (a[1][0]-a[0][0]) * (b[0][0]+b[0][1]);
		int V = (a[0][1]-a[1][1]) * (b[1][0]+b[1][1]);
		
		c[0][0]= P+S-T+V;								//yapt���m�z �arpma i�lemlerinde buldu�umuz de�i�kenleri, algoritmada belirtildi�i gibi toplama ve ��karma
		c[0][1]= R+T;									//   i�lemlerine tabii tutarak buldu�umuz sonu�lar� sonu� matrisine kaydediyoruz.
		c[1][0]= Q+S;
		c[1][1]= P+R-Q+U;
	}
	else{																										//fonkiyonun recursive case'i.
		int a00[m][m], a01[m][m], a10[m][m], a11[m][m],	b00[m][m], b01[m][m], b10[m][m], b11[m][m];	//ba�taki matrislerin 4 par�as�n� b�l�p kaydetmek �zere kullan�lacak matrisler.
		int p[m][m],q[m][m],r[m][m],s[m][m],t[m][m],u[m][m],v[m][m],sum1[m][m],sum2[m][m],sub1[m][m],sub2[m][m];
		for(i=0;i<m;i++){
			for(j=0;j<m;j++){								//ba�taki matrisleri 4 par�aya b�l�p yeni olu�turdu�umuz matrislere kaydediyoruz.
				a00[i][j] = a[i][j];						//											
				b00[i][j] = b[i][j];						//											|
				a01[i][j] = a[i][j+m];						//									a00		|		a01
				b01[i][j] = b[i][j+m];						//									b00		|		b01
				a10[i][j] = a[i+m][j];						//						        -----------------------------
				b10[i][j] = b[i+m][j];						//									a10		|		a11
				a11[i][j] = a[i+m][j+m];					//									b10		|		b11
				b11[i][j] = b[i+m][j+m];					//											|
			}
		}
		add(m,a00,a11,sum1);									//p = (a00 + a11) * (b00+b11)	BASE CASE'DE SAYILARLA YAPTI�IMIZ ��LEMLER� BURADA MATR�SLERLE YAPIYORUZ.
		add(m,b00,b11,sum2);
		strassen(m,sum1,sum2,p);
		
		add(m,a10,a11,sum1);									//q = (a10+a11) * b00
		strassen(m,sum1,b00,q);
	
		sub(m,b01,b11,sub1);									//r = (b01-b11) * a00
		strassen(m,a00,sub1,r);
		
		sub(m,b10,b00,sub2);									//s = (b10-b00) * a11
		strassen(m,a11,sub2,s);
		
		add(m,a00,a01,sum1);									//t = (a00+a01) * b11
		strassen(m,sum1,b11,t);
		
		sub(m,a10,a00,sub1);									//u = (a10-a00)	* (b00+b01)
		add(m,b00,b01,sum1);
		strassen(m,sub1,sum1,u);
		
		sub(m,a01,a11,sub2);									//v = (a01-a11) * (b10+b11)
		add(m,b10,b11,sum2);
		strassen(m,sub2,sum2,v);
		
		add(m,p,s,c00);											// c00 = p + s - t + v
		add(m,c00,v,c00);
		sub(m,c00,t,c00);
		
		add(m,r,t,c01);											// c01 = r + t
		
		add(m,q,s,c10);											// c10 = q + s
		
		add(m,p,r,c11);											// c11 = p + r + u - q
		add(m,c11,u,c11);
		sub(m,c11,q,c11);
	
		for(i=0;i<m;i++){										//buldu�umuz c00, c01, c10 ve c11 matrislerini sonu� matrisinde birle�tiriyoruz.
			for(j=0;j<m;j++){
				c[i][j] = c00[i][j];
				c[i][j+m] = c01[i][j];
				c[i+m][j] = c10[i][j];
				c[i+m][j+m] = c11[i][j];
			}
		} 
}
	return;
}

