#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#define R 1000
#define NAZWABAZY "baza.txt"

int ilezdan(char*);
void wczytajbaze(char**, char*, int);
void powitanie(void);
void porownywacz(char*, char*, int);

int main()
{
    int LZD=ilezdan(NAZWABAZY);
    if(LZD<1)
    {
        printf("Bˆ¥d bazy \n");
        return 0;
    }
    char** t =(char**)malloc(LZD*sizeof(char*));
    int i;
    for (i=0; i<LZD; ++i)
    {
        t[i]=(char*)malloc(R*sizeof(char));
    }
    wczytajbaze(t, NAZWABAZY, LZD);
    printf("Wczytanych zdaä- %d \n\n", --LZD); // -- bo baza jest zrobiona tak, ze ostatni wiersz jest pusty
    powitanie();

    srand(time(NULL));
    int ind, ilewpisal, uzyteindeksy[LZD], ilebylozdan=0;
    float czas;
    char input[R], pomoc, exit;
    clock_t koniec, start;
    for(i=0; i<LZD; ++i)
        uzyteindeksy[i]=0;
    while(1)
    {
        if(ilebylozdan==LZD)
        {
            ilebylozdan=0;
            for(i=0; i<LZD; ++i)
                uzyteindeksy[i]=0;
        }
        ind=rand() % LZD;
        while(uzyteindeksy[ind]!=0)
        {
            ind= (ind+1) % LZD;
        }
        uzyteindeksy[ind]=1;
        ilebylozdan++;
        printf("Przepisz poni¾sze zdanie: \n\n");
        printf("%s", t[ind]);

        ilewpisal=0;
        for(i=0; i<R-1; ++i)
        {
            pomoc=getch();
            if(i==0)
            {
                start=clock();
                koniec=clock();
            }
            if(pomoc=='\r')
            {
                break;
            }
            else if (pomoc==8 && ilewpisal>0)ilewpisal--; // 8 to kod ASCII Backspace'a
            else if (pomoc!=8)
            {
                input[ilewpisal]=pomoc;
                ilewpisal++;
            }
            koniec=clock();
        }
        czas= (float)(koniec-start)/CLOCKS_PER_SEC;
        porownywacz(t[ind], input, ilewpisal);
        printf("Czas wpisywania: %.2f sekund \n\n", czas);

        printf("Naci˜nij 1, aby wylosowa† kolejne zdanie lub 0, aby zakoäczy† \n");
        exit= getch();
        while(exit!='0' && exit!='1')
        {
            exit=getch();
        }
        system("cls");
        if(exit=='0')break;
    }

    for (i=0; i<LZD; ++i)
    {
        free(t[i]);
    }
    free(t);
    printf("Do zobaczenia nast©pnym razem!");
    return 0;
}

int ilezdan(char* nazwapliku)
{
    FILE* p=fopen(nazwapliku,"r");
    if(p)printf("Otwarcie bazy udane (1) \n");
    else {printf("Nie powiodˆo si© otwarcie bazy \n"); return 0;}
    char dummy;
    dummy=fgetc(p);
    if(dummy==EOF)
    {
        printf("Pusta baza \n");
        return 0;
    }
    rewind(p);
    char temp[R];
    int i=0;
    for(;;)
    {
        if(feof(p))break;
        fgets(temp,R,p);
        ++i;
    }
    fclose(p);
    p=NULL;

    return i;

}

void wczytajbaze(char** t, char* nazwapliku, int LZD)
{
    FILE* p=fopen(nazwapliku,"r");
    if(p)printf("Otwarcie bazy udane (2) \n");
    else {printf("Nie powiodˆo si© otwarcie bazy \n"); return ;}

    int i=0;
    for(;i<LZD;)
    {
        if(feof(p))break;
        fgets(t[i],R,p);
        ++i;
    }
    fclose(p);
    p=NULL;

    return;
}

void powitanie(void)
{
    printf("To jest trener pisania na klawiaturze. \n");
    printf("Czas b©dzie mierzony od momentu rozpocz©cia wprowadzania przez Ciebie zdania, zatem nie musisz si© ju¾ w tym momencie stresowa†. \n");
    printf("Po zakoäczeniu wpisywania naci˜nij Enter, aby otrzyma† informacj© zwrotn¥ na temat wpisanego zdania. \n");
    printf("Naci˜nij dowolny klawisz i zatwierd« Enter, by wy˜wietli† losowe zdanie z bazy \n");
    getchar();
    system("cls");
    return;
}

void porownywacz(char* wzor, char* input, int ilewpisal)
{
    printf("Poni¾ej w dw¢ch osobnych linijkach zdanie wzorcowe oraz zdanie wpisane przez Ciebie z zaznaczonymi bˆ©dami: \n");
    int i;
    for (i=0; i<ilewpisal; ++i)
    {
        printf("%c", input[i]);
    }
    printf("\n");
    int dlugwzoru=strlen(wzor)-1;
    int poprawnych=0;
    for(i=0; i<ilewpisal; ++i)
    {
        if(wzor[i]!=input[i])
        {
            printf("[%c]", input[i]);
        }
        else
        {
            printf("%c",input[i]);
            poprawnych++;
        }

    }
    int roznica=dlugwzoru-ilewpisal;
    for(i=0; i<roznica; ++i)
    {
        printf("{ }");
    }
    printf("\n");
    if(roznica>0)ilewpisal+=roznica;
    float procentbledow=(float)(ilewpisal-poprawnych)/ilewpisal;
    procentbledow*=100;
    printf("Bˆ©d¢w: %d \n", ilewpisal-poprawnych);
    printf("Procent bˆ©d¢w w wypisanym zdaniu: %.2f %% \n", procentbledow);

    printf("\n");

    return;
}
