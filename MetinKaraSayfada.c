#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct Harf{
    struct Harf* onceki;
    char harf;
    struct Harf* sonraki;
};
struct Harf *ilk,*imlec,*son,*gecici,*bas,*tutan,*tutan1,*tutan2;
char girdi,girdid;
int harfsay,kelimesay;
int nereye,bicimliyaz;//nereye:0 kaydet 1 farkli kaydet; bicimliyaz:0 Sayfayaz 1 yaz
FILE *fp;

void ekle();//Bagli listede ekleme
void silme();//Bagli listede silme
void kesme();//kesme islemi
void secenekler();//Secenekleri basar
void denetle();//yapilacak islemi secer
void yonver();//ok tusları
void yaz();//Tumden yazar
void secme();//secer
void girdial();
void yap();
void kopyala();
void kaydet();
void yukle();
void sayfayaz();//sayfa olarak basar


int main(){
    system("color F4");
    system("title Atakan A. Murat D.");
    bicimliyaz=harfsay=0;
    kelimesay=1;
    imlec=son=ilk=NULL;
    bas=malloc(sizeof(struct Harf));
    do{
        girdial();
        //printf("\n%d  %d",girdi,girdid);//Klavyeden girilenin sayisal karsiligini yazar
        denetle();
        if(bicimliyaz==0)
            sayfayaz();
        else
            yaz();

    }while(girdi!=27);

    return 0;
}

void girdial(){
	girdi=_getch();//getche()
  if(girdi==-32||girdi==0)
    girdid=_getch();//getche()
}

void ekle(){
    harfsay++;
	if(ilk!=NULL){//Baðli listede eleman varsa
        gecici=imlec;
        imlec=malloc(sizeof(struct Harf));
        if(gecici->sonraki==NULL){//sondan ekleme
            gecici->sonraki=imlec;
            imlec->onceki=gecici;
            imlec->sonraki=NULL;
            son=imlec;
        }else if(gecici==bas){//Bastan ekleme
            gecici=gecici->sonraki;
            gecici->onceki=imlec;
            imlec->sonraki=gecici;
            imlec->onceki=NULL;
            ilk=imlec;
        }else{//Araya ekleme
            gecici->sonraki->onceki=imlec;
            imlec->sonraki=gecici->sonraki;
            gecici->sonraki=imlec;
            imlec->onceki=gecici;
        }
        imlec->harf=girdi;
    }else{//ilk girdi
        imlec=malloc(sizeof(struct Harf));
        ilk=son=imlec;
        imlec->harf=girdi;
        imlec->onceki=imlec->sonraki=NULL;
    }
    ilk->onceki=bas;
    bas->sonraki=ilk;
    bas->onceki=NULL;
    if(imlec->harf==32||imlec->harf==13||imlec->harf==10)
        if(imlec->onceki->harf!=32&&imlec->onceki->harf!=13&&imlec->onceki->harf!=10&&imlec->onceki!=bas)
            kelimesay++;
}

void silme(){//Del=127  Bs=8

	if(girdi==8&&imlec!=bas){
        gecici=imlec->onceki;
        if(imlec->harf==32||imlec->harf==13||imlec->harf==10)
            if(imlec->onceki->harf!=32&&imlec->onceki->harf!=13&&imlec->onceki->harf!=10&&imlec->onceki!=bas)
                kelimesay--;
		if(imlec==son){//sondan silme
  			gecici->sonraki=NULL;
      	  free(imlec);
  			son=imlec=gecici;
  			if(son==bas)
                ilk=NULL;
 	 }else if(imlec==ilk){//bastan silme
    	  bas->sonraki=imlec->sonraki;
      	imlec->sonraki->onceki=bas;
      	free(imlec);
      	ilk=imlec=gecici;
  	}else{//Aradan silme
     	 gecici->sonraki=imlec->sonraki;
 				imlec->sonraki->onceki=gecici;
      	free(imlec);
      	imlec=gecici;
 	 	}
        harfsay--;
  }else if((girdi==-32&&girdid==83)&&imlec!=son){
   gecici=imlec->sonraki;
   if(imlec==bas){//Bastan silme
        bas->sonraki=gecici->sonraki;
        if(gecici!=son)
        	gecici->sonraki->onceki=bas;
        else
            ilk=NULL;
    	free(gecici);
    }else{
      if(gecici!=son)
     		imlec->sonraki=gecici->sonraki;
      else{
      	imlec->sonraki=NULL;
      	son=imlec;
      }
        if(imlec->harf==32||imlec->harf==13||imlec->harf==10)
            if(imlec->onceki->harf!=32&&imlec->onceki->harf!=13&&imlec->onceki->harf!=10&&imlec->onceki!=bas)
                kelimesay--;
    	free(gecici);
    }
        harfsay--;
  }

}

void denetle(){
  if((girdi==8||(girdi==-32&&girdid==83))&&ilk!=NULL){//8 Backspace 127 Del
  	silme();
  }else if(girdi==22||girdi==19){
    yap();
  }else if(girdi>0 && girdi<127||girdi<-32){//ekler
    ekle();
  }else if(girdi==-32&&ilk!=NULL){
  	if(girdid==72|girdid==80||girdid==77||girdid==75)
        yonver();
    else if(girdid==-115||girdid==-111||girdid==116||girdid==115)
    	secme();
  }else if(girdi==0){
    secenekler();
  }
}

void yonver(){
  if(girdid==72){//yukari
    int n=0,m=0,i,durum=0;
    for(gecici=imlec;gecici->harf!=10&&gecici!=bas;gecici=gecici->onceki,n++){
        if(n==120){n=0;durum++;}
    }
    if(durum!=0)
        for(n,gecici;n!=0;n--,gecici=gecici->sonraki){}
    else{
    if(gecici==bas)
        gecici=gecici->sonraki;
    for(gecici=gecici->onceki;gecici->harf!=10&&gecici!=bas;gecici=gecici->onceki,m++){}
    for(n,m,gecici;n!=0&&m!=0;n--,m--,gecici=gecici->sonraki){}
    }imlec=gecici;
  	}else if(girdid==80){//asagi
      int n=0,m=0,k=0;
			for(gecici=imlec;gecici->harf!=10&&gecici!=bas;gecici=gecici->onceki,n++){}
			if(imlec->harf==10&&imlec!=son)
        imlec=imlec->sonraki;
     	for(gecici=imlec;gecici->harf!=10&&gecici!=son;gecici=gecici->sonraki){}
   		 m=n;

  		 for(n=m;n!=0;n--){
       if(gecici==son){
      	  break;
      	 }
        gecici=gecici->sonraki;
         k=k+1;

        if(gecici->harf==10){
        if(k!=1){
         gecici=gecici->onceki;
            break;
        }
        }
        }
    imlec=gecici;
  }else if(girdid==77){//sag
    if(imlec->sonraki!=NULL)
  		imlec=imlec->sonraki;
  }else if(girdid==75){//sol
  	if(imlec->onceki!=NULL)
    	imlec=imlec->onceki;
  }

}
void yaz(){
	system("cls");
	int degdimi=0;
	int yatay=0;
	struct Harf *gecici1;
    printf("Secenekler icin F1'e,kisa komutlari gormek ve yardim icin F2'ye basiniz.\n\n");
	if(ilk!=NULL)
        for(gecici=bas;gecici!=NULL;gecici=gecici->sonraki){
                yatay++;
            if(gecici->harf==13)
                gecici->harf=10;
            if(gecici!=bas)
                printf("%c",gecici->harf);
            if(imlec==gecici){
                printf("|");
                degdimi=1;
            }
            if(tutan==gecici&&degdimi==1)
                printf("<.<");
            else if(tutan==gecici&&degdimi!=1)
                printf(">.>");
        }
        printf("\n\n\t\kelimesay:%d\t\t\t\tharfsay:%d",kelimesay,harfsay);

}
void sayfayaz(){
    system("cls");
    int degdimi=0,k,yatay,l;
    struct Harf *sayfasonu;
    printf("Secenekler icin F1'e,kisa komutlari gormek ve yardim icin F2'ye basiniz.\n\n");
    if(ilk!=NULL){
        for(k=0,gecici=imlec;gecici!=bas&&k<14;k++){
            for(gecici;gecici->harf!=10&&gecici!=bas;gecici=gecici->onceki){}
            if(gecici!=bas)
                gecici=gecici->onceki;
            }
        if(k>=14)for(gecici;gecici->harf!=10&&gecici!=bas;gecici=gecici->onceki){}
        for(sayfasonu=imlec,l=24-k;sayfasonu!=NULL&&l>0;l--){
            for(sayfasonu;sayfasonu->harf!=10&&sayfasonu!=son;sayfasonu=sayfasonu->sonraki){}
            if(sayfasonu!=son)
                sayfasonu=sayfasonu->sonraki;
        }
        for(gecici,k;gecici!=NULL;gecici=gecici->sonraki){
            if(gecici->harf==13)
                gecici->harf=10;
            if(gecici!=bas)
                printf("%c",gecici->harf);
            if(imlec==gecici){
                printf("|");
                degdimi=1;
            }
            if(gecici->harf==10)
                k--;
            if(tutan==gecici&&degdimi==1)
                printf("<.<");
            else if(tutan==gecici&&degdimi!=1)
                printf(">.>");

            if(gecici==sayfasonu)
                break;
        }

        printf("\n\n\t\kelimesay:%d\t\t\t\tharfsay:%d",kelimesay,harfsay);

    }
}

void secenekler(){
    char dongu=0;
    system("cls");
    while(girdi!=1&&girdid==59){//F1
   		printf("Secenekler:\t\t\t<.<\n");
      if(girdid==59){//F1 tusu
  	      printf("1-Yaz \n2-Kaydet \n3- Farkli Kaydet \n4-Dosya Ac(Yukle) \n5- Yazim Bicimi \n6- Yapimcilar \n7-Cik \n");
          girdi=getche();
          girdi-=48;
          if(girdi==1){
       		 }else if(girdi==2){//Kaydet
                system("cls");
                kaydet();
             }else if(girdi==3){//Farklý Kaydet
                system("cls");
                nereye=1;
                kaydet();
                nereye=0;
       		 }else if(girdi==4){//Dosya Aç(Yukle)
                system("cls");
                yukle();
       		 }else if(girdi==5){//Yazim Bicimi Degistirme
             system("cls");
             printf("Sayfa olarak basmak(yazmak) icin:1'e\nTumden yazmak icin 2'ye basiniz.\n");
             scanf("%d",&bicimliyaz);
             if(bicimliyaz==1)
                printf("Artik sayfa olarak yazilacak. Islem basarili...\n");
             else if(bicimliyaz==2)
                printf("Tumden yazilacak. Islem basarili...\n");
             else{
                printf("Yanlis giris. Bicim sifirlandi(1).\n");
                bicimliyaz=1;
             }
       		 }else if(girdi==6){//Yapýmcýlar
             system("cls");
       		 printf("Created by Atakan A. Murat M.   <.<\n\n");
       		 }else if(girdi==7){//kapat
             printf("\nProgram Kapatiliyor\n");
             exit(0);
       		 }else{
             system("cls");
           printf("Yanlis girdiniz!\n");
           }


        }
		}
    if(girdi==0&&girdid==60){//F2
        printf("\n\n  Programimiz da secme islemi ctrl(kontrol) ile saglanip, ");
        printf("ctrl-x(kesme islemi), ctrl-c(kopyalama),\n ctrl-v(yapistirma), ");
        printf("ctrl-s (ayni dizinde \"MetinKaraSayfada.txt\" olarak kaydet) ");
        printf("ve F1'e basarak goreceginiz;\n farkli kaydet ve yukle(dosya acmak) ");
        printf("ozelliklerini bulundurur. Sayfa olarak bas(yaz) yada tumden yaz\n ");
        printf("secenekleriylede yazim bicimini degistirebilirsiniz.\n\n\n");
        printf("\t\t\t\t\t\t\t\tCreated by Atakan A. Murat M.   <.<\n\n\n");
        printf("Geri donmek icin herhangi bir tusa basiniz.");
        char tus=_getch();
    }
}

void secme(){
  int ilksefer=1;
  do{
 		if(ilksefer==1){
    	tutan=imlec;
    	ilksefer++;
    }
  	if(girdid==-115){
    	girdid=72;

  	}else if(girdid==-111){
  		girdid=80;

  	}else if(girdid==116){
  		girdid=77;

  	}else if(girdid==115){
  		girdid=75;

  	}
    if(girdi==-32)
    	yonver();
    	if(bicimliyaz==0)
            sayfayaz();
        else
            yaz();
		girdial();
	}while(girdid==-115||girdid==-111||girdid==116||girdid==115);

    if(girdi==3){//kopyala
        tutan1=tutan->sonraki;
        tutan2=imlec;
        kopyala();
    }else if(girdi==24){//kesme
        tutan1=tutan;
   	    tutan2=imlec;
   	    if(tutan!=imlec)
            kesme();
    }
    tutan=NULL;

}

void kopyala(){
        for(gecici=bas;gecici!=tutan1;gecici=gecici->sonraki){
            if(tutan2==gecici){
                if(tutan1!=NULL)
                    tutan2=tutan1->onceki;
                else
                    tutan2=tutan1;
                tutan1=gecici->sonraki;
            if(tutan1==tutan2)
                tutan1=tutan2=NULL;
            break;
            }
        }
    int ilksefer=1;
        struct Harf *sontutan;
        for(gecici=tutan1,ilksefer=1;gecici!=NULL;gecici=gecici->sonraki){
            tutan=malloc(sizeof(struct Harf));
            if(ilksefer==1){
                tutan->onceki=tutan->sonraki=NULL;
                tutan->harf=gecici->harf;
                tutan1=sontutan=tutan;
                ilksefer++;
            }else{
                tutan->sonraki=NULL;
                sontutan->sonraki=tutan;
                tutan->harf=gecici->harf;
                tutan->onceki=sontutan;
                sontutan=tutan;
            }
            if(gecici==tutan2)
                break;
        }
        tutan2=sontutan;

}


void kesme(){
	int tutankim=0;
	struct Harf *kesen1,*kesen2;
	struct Harf *say1,*say2;

      for(gecici=bas;gecici!=tutan1;gecici=gecici->sonraki){

              if(tutan2==gecici){
                tutan2=tutan1;
                tutan1=gecici;

            if(tutan1==tutan2)
                tutan1=tutan2=NULL;
            break;
              }
    }

    for(say1=tutan1,say2=tutan2;say1!=say2;say1=say1->sonraki,harfsay--){
        if(say1->harf==32||say1->harf==13||say1->harf==10)
            if(say1->onceki->harf!=32&&say1->onceki->harf!=13&&say1->onceki->harf!=10&&say1->onceki!=bas)
                kelimesay--;
    }

      if((tutan1==bas)&&(tutan2==son)){
          tutan1=tutan1->sonraki;
          bas->sonraki=NULL;
          son=bas;
          ilk=NULL;
        	imlec=bas;
      }else if(tutan1==bas){
      	tutan1=tutan1->sonraki;
      	bas->sonraki=tutan2->sonraki;
      	tutan2->sonraki->onceki=bas;
      	ilk=tutan2->sonraki;
        imlec=bas;
      }else if(tutan2==son){
        tutan1=tutan1->sonraki;
        tutan1->onceki->sonraki=NULL;
        son=tutan1->onceki;
        imlec=son;
      }else{
        tutan1=tutan1->sonraki;
      	tutan1->onceki->sonraki=tutan2->sonraki;
      	tutan2->sonraki->onceki=tutan1->onceki;
        imlec=tutan2->sonraki->onceki;
      }

}

void yap(){
    int durum;
    struct Harf *say1,*say2;

    for(say1=tutan1,durum=0,say2=tutan2;say1!=say2;say1=say1->sonraki,harfsay++){
        if(say1->onceki==NULL)
            if(say1->harf==32||say1->harf==13||say1->harf==10)
                kelimesay++;
        if(say1->harf==32||say1->harf==13||say1->harf==10)
            if(say1->onceki!=NULL&&say1->onceki->harf!=32&&say1->onceki->harf!=13&&say1->onceki->harf!=10&&say1->onceki!=bas)
                kelimesay++;
    }
    harfsay++;
    if(say1->harf==32||say1->harf==13||say1->harf==10)
        if(say1->onceki->harf!=32&&say1->onceki->harf!=13&&say1->onceki->harf!=10&&say1->onceki!=bas)
            kelimesay++;

    if(tutan1!=NULL&&tutan2!=NULL){
        if(girdi==22){//yapistir
            if(imlec==bas&&imlec->sonraki!=NULL){//bastan
                imlec->sonraki->onceki=tutan2;
                tutan2->sonraki=imlec->sonraki;
           		  tutan1->onceki=bas;
           		  bas->sonraki=ilk=tutan1;
           		  imlec=tutan2;
                kopyala();
            }else if(imlec->sonraki!=NULL){//aradan
                imlec->sonraki->onceki=tutan2;
                tutan2->sonraki=imlec->sonraki;
                imlec->sonraki=tutan1;
                tutan1->onceki=imlec;
                imlec=tutan2;
                kopyala();
            }else{//sondan
                tutan2->sonraki=NULL;
                imlec->sonraki=tutan1;
                tutan1->onceki=imlec;
                son=imlec=tutan2;
                kopyala();
            }
        }
    }

    if(girdi==19){
        kaydet();
    }

}
void kaydet(){
  char dosyaismi[100];
	if(ilk!=NULL&&son!=NULL){
  	if(nereye==0){
   	      fp = fopen("MetinKaraSayfada.txt" , "w+");//w veya w+  dosya oluþturup silip baþtan yazar.
    	    for(gecici=ilk;gecici!=son;gecici=gecici->sonraki){
  				fprintf(fp , "%c" , gecici->harf);
  			}
  			fprintf(fp , "%c" , gecici->harf);
  			fclose(fp);
      	printf("Basariyla kaydedildi\n");
  	}else if(nereye==1){
  		printf("Nereye ve ne adla kaydetmek istersiniz.(Bosluk kullanmayiniz.Uzantisinide yazmalisiniz Orn:.txt .doc vb.)\n");
    	scanf("%s",&dosyaismi);
    	fp = fopen(dosyaismi , "w+");//w veya w+  dosya oluþturup silip baþtan yazar.
      	for(gecici=ilk;gecici!=son;gecici=gecici->sonraki){
      		fprintf(fp , "%c" , gecici->harf);
    	}
    	fprintf(fp , "%c" , gecici->harf);
    	fclose(fp);
    	printf("Basariyla kaydedildi\n");
  	}
	}else{
      printf("Herhangi bir veri girmeden kaydetmeye calistiniz.\nHata!\n");
	}

}

void yukle(){
    char dosyaismi[100];
    if(son!=NULL){
        for(imlec=son,girdi=8;imlec!=bas;){//Bellegibosalt
            silme();
        }
        imlec=bas;
    }

    printf("Hangi Dosyayi acmak istersiniz.(Uzantisinide yazmalisiniz Orn:.txt .doc vb.)\n");
    scanf("%s",&dosyaismi);

    harfsay=0;
  	fp = fopen(dosyaismi , "r+");
		while(fscanf(fp,"%c",&girdi)!=EOF){
  		ekle();
  	}
  	fclose(fp);

	  printf("Okundu!\nYanlis isimli dosya girilmesi durumunda bos dosya gibi algilanip ekran  sifirlanacaktir.\n");
}
