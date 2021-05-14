#include <stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node *previousPtr; //onceki ve sonraki dugum adreslerini tanimla
	struct node *nextPtr;
};

//ilk ve son olarak iki dugum adresi tanimla
struct node *ilkDugum;
struct node *sonDugum;

//belirtilen kadar dugum iceren cift baglantili liste olustur
void ciftBaglantiliListeOlustur(int dugumSayisi);

void deleteIlkDugum();
void deleteSonDugum();
void deleteBelirtilenDugum(int dugumYeri);
void ciftBaglantiliListeyiGoruntule();

int main(){

	int dugumSayisi;
	
	int dugumYeri;
	
	ilkDugum=NULL;
	sonDugum=NULL;
	
	printf("Dugum sayisini giriniz : ");
	scanf("%d",&dugumSayisi);
	
	ciftBaglantiliListeOlustur(dugumSayisi);
	
	printf("\n Listeye girilen veriler : \n");
	ciftBaglantiliListeyiGoruntule();
	
	printf("Silmek istediginiz dugum konumunu giriniz (1 ile %d arasi)  : ",dugumSayisi);
	scanf("%d",&dugumYeri);
	
	//dugum konumunu kontorl et gecersiz ise hata ver
	if(dugumYeri<1 || dugumYeri>dugumSayisi){
		printf("Gecersiz konum ! \n");
		
	}
	else{
		deleteBelirtilenDugum(dugumYeri);
		printf("Yeni liste : \n");
		ciftBaglantiliListeyiGoruntule();
	}
	
	
	
	
	return 0;

}

void ciftBaglantiliListeOlustur(int dugumSayisi){
	int nodeCtr;
	int nodeData; 
	struct node *newNode;
	
	//belirtilen dugum sayisi pozitif ve sýfýrdan farkliysa
	if(dugumSayisi>=1){
		//cift baglantili listenin ilk dugumu icin bellek ayirma
		ilkDugum=(struct node *)malloc(sizeof(struct node));
		
		//ilk dugum icin bellek ayýrma basarili olursa, 
		//cift baglantili liste olusturma islemine devam et		
		if(ilkDugum !=NULL){
			printf("Dugum giris verileri 1 : ");
			scanf("%d", &nodeData);
			
			ilkDugum->data=nodeData;
			ilkDugum->previousPtr=NULL;
			ilkDugum->nextPtr=NULL;
			
			sonDugum=ilkDugum;
			
			//olusturulan cift baglantili liste icin dugum sayisina kadar dongu yapin
			for(nodeCtr =2;nodeCtr<=dugumSayisi;nodeCtr++){
				newNode = (struct node *)malloc(sizeof(struct node));
				
				if(newNode!=NULL){
					printf("Dugum giris verileri %d : ",nodeCtr);
					scanf("%d", &nodeData);
					
					//yeni dugum olusturmaya basla
					newNode->data=nodeData;
					newNode->previousPtr=NULL;
					newNode->nextPtr=NULL;
					
					//yeni olusan dugumu listedeki dugumlere baglama
					newNode->previousPtr=sonDugum;
					sonDugum->nextPtr=newNode;
					
					sonDugum=newNode;
					
				}
				else{
					printf("Bellek ayrýlamaz !");
					break;
				}
			}
		}
		else{
			printf("Bellek ayrýlamaz !");
		}
	}
}


void deleteBelirtilenDugum(int dugumYeri){
	struct node *currentNode;
	int nodeCtr;
	
	currentNode=ilkDugum;
	
	//belirtilen konumdaki dugum bulunana kadar dongu yap
	for(nodeCtr=1;nodeCtr<dugumYeri&&currentNode !=NULL; nodeCtr++){
		currentNode=currentNode->nextPtr;
	}
	
	if(dugumYeri==1){
		deleteIlkDugum();
	}
	else if(currentNode==sonDugum){
		deleteSonDugum();
	}
	else if(currentNode!=NULL){
		
		//silinecek dugumun baglantisini kaldirin
		currentNode->previousPtr->nextPtr=currentNode->nextPtr;
		currentNode->nextPtr->previousPtr=currentNode->previousPtr;
		
		//gecerli dugum icin bos bellek ayir
		free(currentNode);
		
	}
	else{
		printf("Gecersiz pozisyon !\n");
	}
}


void deleteIlkDugum()
{
	struct node * nodeToDelete;
	if(ilkDugum==NULL){
		printf("Listede veri yok ! Silinemez.");
	}
	else{
		//silinecek dugumu ayarla
		nodeToDelete=ilkDugum;
		
		//gecerli ilk dugumun baglantisini kaldir
		ilkDugum = ilkDugum->nextPtr;
		ilkDugum->previousPtr=NULL;
		
		//silinecek dugum icin bos bellek ayir
		free(nodeToDelete);
	}
}

void deleteSonDugum(){
	struct node *nodeToDelete;
	
	if(sonDugum==NULL){
		printf("Listede veri yok ! Silinemez.\n");
		
	}else{
		
		//silinecek dugumu ayarla
		nodeToDelete = sonDugum;
		
		//baglantiyi kaldir
		sonDugum=sonDugum->previousPtr;
		sonDugum->nextPtr=NULL;
		
		//bos bellek ayir
		free(nodeToDelete);
		
	}
}

void ciftBaglantiliListeyiGoruntule(){
	struct node *currentNode;
	int nodeCtr =1;
	
	if(ilkDugum ==NULL){
		printf("Listede henüz veri yok ! ");
		
	}else{
		
		//gecerli dugumu baslat
		currentNode = ilkDugum;
		
		while(currentNode!=NULL){
			printf("Dugum %d : %d \n",nodeCtr,currentNode->data);
			nodeCtr++;
			
			//bir sonraki dugume gec
			currentNode=currentNode->nextPtr;
		}
	}

}
