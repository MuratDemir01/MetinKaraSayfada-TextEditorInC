//This project created in C. And used to Linked List for all char.
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

//Harf is our structure. Harf had previous, character and next. We created doubly linked list.
struct Harf{
    struct Harf* onceki;
    char harf;
    struct Harf* sonraki;
};
//ilk is our List's first, imlec is our cursor, son mean last, bas used for head to console
struct Harf *ilk,*imlec,*son,*gecici,*bas,*tutan,*tutan1,*tutan2;
char girdi,girdid,dil;//dil(language):0 English 1 Turkish
int harfsay,kelimesay;
int nereye,bicimliyaz;//nereye:0 save 1 save as; bicimliyaz:0 Sayfayaz(cursor nears) 1 yaz(all of writes)
FILE *fp;

void ekle();//adding to Linked list
void silme();//remove from Linked List
void kesme();//cuting some words
void secenekler();//Options. We will see click to F1
void denetle();//Check(Control) to what to do.
void yonver();//Move(arrow)
void yaz();//write to console
void secme();//select some words
void girdial();//input from keyboard
void yap();//paste
void kopyala();//Copy
void kaydet();//Save
void yukle();//Load
void sayfayaz();//write console to our cursors nears


int main(){
    //for change to console color and set to console title
    system("color F4");
    system("title Atakan A. Murat D.");
    bicimliyaz=harfsay=0;
    kelimesay=1;
    imlec=son=ilk=NULL;
    bas=malloc(sizeof(struct Harf));
    do{
        girdial();
        //printf("\n%d  %d",girdi,girdid);//debug for keyboards input
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
	if(ilk!=NULL){//If linked list not empty
        gecici=imlec;
        imlec=malloc(sizeof(struct Harf));
        if(gecici->sonraki==NULL){//add from last
            gecici->sonraki=imlec;
            imlec->onceki=gecici;
            imlec->sonraki=NULL;
            son=imlec;
        }else if(gecici==bas){//add from first
            gecici=gecici->sonraki;
            gecici->onceki=imlec;
            imlec->sonraki=gecici;
            imlec->onceki=NULL;
            ilk=imlec;
        }else{//add to mid
            gecici->sonraki->onceki=imlec;
            imlec->sonraki=gecici->sonraki;
            gecici->sonraki=imlec;
            imlec->onceki=gecici;
        }
        imlec->harf=girdi;
    }else{//Lisked list empty. Add to first node
        imlec=malloc(sizeof(struct Harf));
        ilk=son=imlec;
        imlec->harf=girdi;
        imlec->onceki=imlec->sonraki=NULL;
    }
    //set to bas(head) to all time before ilk(first)
    ilk->onceki=bas;
    bas->sonraki=ilk;
    bas->onceki=NULL;
    if(imlec->harf==32||imlec->harf==13||imlec->harf==10)
        if(imlec->onceki->harf!=32&&imlec->onceki->harf!=13&&imlec->onceki->harf!=10&&imlec->onceki!=bas)
            kelimesay++;
}

void silme(){//Del=127,Del=-32 83   Bs=8
    //For Backspace
	if(girdi==8&&imlec!=bas){
        gecici=imlec->onceki;
        if(imlec->harf==32||imlec->harf==13||imlec->harf==10)
            if(imlec->onceki->harf!=32&&imlec->onceki->harf!=13&&imlec->onceki->harf!=10&&imlec->onceki!=bas)
                kelimesay--;
		if(imlec==son){//delete from last
  			gecici->sonraki=NULL;
      	  free(imlec);
  			son=imlec=gecici;
  			if(son==bas)
                ilk=NULL;
 	 }else if(imlec==ilk){//remove from first
    	  bas->sonraki=imlec->sonraki;
      	imlec->sonraki->onceki=bas;
      	free(imlec);
      	ilk=imlec=gecici;
  	}else{//del to mid
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
  if((girdi==8||(girdi==-32&&girdid==83))&&ilk!=NULL){//8 Backspace Del=-32 83
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
    //Arrows
  if(girdid==72){//Up
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
  	}else if(girdid==80){//Down
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
  }else if(girdid==77){//Right
    if(imlec->sonraki!=NULL)
  		imlec=imlec->sonraki;
  }else if(girdid==75){//Left
  	if(imlec->onceki!=NULL)
    	imlec=imlec->onceki;
  }

}
void yaz(){
	system("cls");
	int degdimi=0;
	int yatay=0;
	struct Harf *gecici1;
    printf("Secenekler icin (Options)F1'e,kisa komutlari gormek ve yardim icin (Help)F2'ye basiniz.\n\n");
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
        printf("\n\n\tkelimesay(word count):%d\t\t\tharfsay(char count):%d",kelimesay,harfsay);

}
void sayfayaz(){
    system("cls");
    int degdimi=0,k,yatay,l;
    struct Harf *sayfasonu;
    printf("Secenekler icin (Options)F1'e,kisa komutlari gormek ve yardim icin (Help)F2'ye basiniz.\n\n");
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

        printf("\n\n\tkelimesay(word count):%d\t\t\tharfsay(char count):%d",kelimesay,harfsay);

    }
}

void secenekler(){
    char dongu=0;
    system("cls");
    while(girdi!=1&&girdid==59){//F1
   		printf("Secenekler(Options):\t\t\t<.<\nFor change to language (supported languages: Turkish-English): 0 \n");
      if(girdid==59){//F1
          if(dil==0)
            printf("1-Write \n2-Save \n3- Save as \n4-Load \n5- Writing type \n6- Credits \n7-Exit \n");
          else
            printf("1-Yaz \n2-Kaydet \n3- Farkli Kaydet \n4-Dosya Ac(Yukle) \n5- Yazim Bicimi \n6- Yapimcilar \n7-Cik \n");
          girdi=getche();
          girdi-=48;
          if(girdi==1){
       		 }else if(girdi==2){//Save
                system("cls");
                kaydet();
             }else if(girdi==3){//Save as
                system("cls");
                nereye=1;
                kaydet();
                nereye=0;
       		 }else if(girdi==4){//Load
                system("cls");
                yukle();
       		 }else if(girdi==5){//Change to write type
             system("cls");
             if(dil==0)
                printf("Write to cursors near: 0 \n Write to all characters: 1\n");
             else
                printf("Sayfa olarak basmak(yazmak) icin:0'e\nTumden yazmak icin 1'ye basiniz.\n");
             scanf("%d",&bicimliyaz);
             if(bicimliyaz==0)
                printf("Artik sayfa olarak yazilacak. Islem basarili...\nIt will write to cursors nears..\n");
             else if(bicimliyaz==1)
                printf("Tumden yazilacak. Islem basarili...\nIt will write to all characters\n");
             else{
                printf("Yanlis giris. Bicim sifirlandi(0).\nWrong entry! Type reseted(0)\n");
                bicimliyaz=1;
             }
       		 }else if(girdi==6){//Yapımcılar
             system("cls");
       		 printf("Created by Atakan A. Murat M.\t\t<.<\n");
       		 }else if(girdi==7){//kapat
             printf("\nProgram Kapatiliyor\nProgram Closed\n");
             exit(0);
       		 }else if(girdi==0){
                system("cls");
                dil++;
                dil%=2;
                printf("Dil degistirildi. Language have been changed.\n");
       		 }else{
             system("cls");
           printf("Yanlis girdiniz!\nWrong entry!\n");
           }


        }
		}
    if(girdi==0&&girdid==60){//F2
        if(dil==0){
        printf("\n\n  Choosing system work with ctrl. For select to some character, ctrl-arrowKeys, ");
        printf("ctrl-x(cut), ctrl-c(copy),\n ctrl-v(paste), ");
        printf("ctrl-s (save on \"MetinKaraSayfada.txt\") ");
        printf("and click to F1 you will see \n save as and load ");
        printf("that programs features. With write type you can change\n ");
        printf("your writing type\n\n\n");
        printf("\t\t\t\t\t\t\t\tCreated by Atakan A. Murat M.   <.<\n\n\n");
        printf("Press any key to continue...");

        }else{
        printf("\n\n  Programimiz da secme islemi ctrl(kontrol) ile saglanip, ");
        printf("ctrl-x(kesme islemi), ctrl-c(kopyalama),\n ctrl-v(yapistirma), ");
        printf("ctrl-s (ayni dizinde \"MetinKaraSayfada.txt\" olarak kaydet) ");
        printf("ve F1'e basarak goreceginiz;\n farkli kaydet ve yukle(dosya acmak) ");
        printf("ozelliklerini bulundurur. Sayfa olarak bas(yaz) yada tumden yaz\n ");
        printf("secenekleriylede yazim bicimini degistirebilirsiniz.\n\n\n");
        printf("\t\t\t\t\t\t\t\tCreated by Atakan A. Murat M.   <.<\n\n\n");
        printf("Geri donmek icin herhangi bir tusa basiniz.");
        }
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
   	      fp = fopen("MetinKaraSayfada.txt" , "w+");//w veya w+  dosya oluşturup silip baştan yazar.
    	    for(gecici=ilk;gecici!=son;gecici=gecici->sonraki){
  				fprintf(fp , "%c" , gecici->harf);
  			}
  			fprintf(fp , "%c" , gecici->harf);
  			fclose(fp);
      	printf("Basariyla kaydedildi\nSaved\n");
  	}else if(nereye==1){
  	    if(dil==0)
            printf("Waiting for file name (Example: save.txt save.doc etc.)\n");
        else
            printf("Nereye ve ne adla kaydetmek istersiniz.(Bosluk kullanmayiniz.Uzantisinide yazmalisiniz Orn:.txt .doc vb.)\n");
    	scanf("%s",&dosyaismi);
    	fp = fopen(dosyaismi , "w+");//w veya w+  dosya oluşturup silip baştan yazar.
      	for(gecici=ilk;gecici!=son;gecici=gecici->sonraki){
      		fprintf(fp , "%c" , gecici->harf);
    	}
    	fprintf(fp , "%c" , gecici->harf);
    	fclose(fp);
    	printf("Basariyla kaydedildi\nSave successful!\n");
  	}
	}else{
      printf("Herhangi bir veri girmeden kaydetmeye calistiniz.\nHata!\nYou cant save without write!\n");
	}

}

void yukle(){
    char dosyaismi[100];
    if(son!=NULL){
        for(imlec=son,girdi=8;imlec!=bas;){//free to memory
            silme();
        }
        imlec=bas;
    }
    if(dil==0)
        printf("Which file you want to load?(example: load.txt)\n");
    else
        printf("Hangi Dosyayi acmak istersiniz.(Uzantisinide yazmalisiniz Orn:.txt .doc vb.)\n");
    scanf("%s",&dosyaismi);

    harfsay=0;
  	fp = fopen(dosyaismi , "r+");
		while(fscanf(fp,"%c",&girdi)!=EOF){
  		ekle();
  	}
  	fclose(fp);

	  printf("Okundu!\nYanlis isimli dosya girilmesi durumunda bos dosya gibi algilanip ekran  sifirlanacaktir.\n");
	  printf("Read!\n If your entered wrong, system will think like to free file then delete your writes.\n");
}
