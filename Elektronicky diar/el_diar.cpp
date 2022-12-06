#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "el_diar.h"
#include <iostream>
#include <stdlib.h>
#include <windows.h>

struct note
{
    char timeAdd[25];
    char noteName[21];
    char note[501];
    char timeEdit[25];
    int saveId = 0;
};

struct note notes[1001];


using namespace std;

void startTxt() {
    FILE*diar;
    diar = fopen("Vase_poznamky.txt", "r");
    char c;
    int k = 0;
    int i = 0;
    int art = 0;
    while ((fscanf(diar, "%c", &c)) != EOF) {
        if (c != '\t' && c != '\n') {
            switch (art){
            case 0:
                notes[i].timeAdd[k] = c;
                break;
            case 1:
                notes[i].noteName[k] = c;
                break;
            case 2:
                notes[i].timeEdit[k] = c;
                break;
            case 3:
                notes[i].note[k] = c;

            }
            
            k++;
        }
        else {
            switch (art) {
            case 0:
                notes[i].timeAdd[k] = '\0';
                k = 0;
                art++;
                break;
            case 1:
                notes[i].noteName[k] = '\0';
                k = 0;
                art++;
                break;
            case 2:
                notes[i].timeEdit[k] = '\0';
                k = 0;
                art++;
                break;
            case 3:
                notes[i].note[k] = '\0';
                notes[i].saveId = 1;
                k = 0;
                art = 0;
                i++;

            }
        }
    }
    fclose(diar);
}


void getNote() {
    FILE* diar;
    diar = fopen("Vase_poznamky.txt", "w");
    for (int i = 0; i <= 1000; i++){
        if(notes[i].saveId == 1){
            fprintf(diar, "%s\t%s\t%s\n%s\n", notes[i].timeAdd, notes[i].noteName, notes[i].timeEdit, notes[i].note);

        }
    }
    fclose(diar);
}


char *getTime() {
    time_t my_time = time(NULL);
    char *needTime = ctime(&my_time);
    needTime[24] = '\0';
    return needTime;
}


void animation() {
    char loading[18] = "ELEKTRONICKY DIAR";
    system("cls");
    for (int i = 0; i < 18; i++) {
        printf("%c", loading[i]);
        Sleep(100);
    }
    system("cls");


}

int startChoice() {
    int operation;
    printf("Dobry den, vita Vas elktronicky diar, prosim zadejte jakou operaci budete chtit provest.\n");
    printf("1. Vytvorit poznamku\n");
    printf("2. Editovat poznamku\n");
    printf("3. Smazat poznamku\n");
    printf("Vase volba: \n");
    scanf("%d", &operation);
    animation();
    return operation;
}

void startDecision(int decision) {
    switch (decision)
    {
    case 1:
        addNote(getTime());
        break;
    case 2:
        editNote(whatEdit(), getTime());
        break;
    case 3:
        removeNote(whatRemove());
        break;
    }
}

void checkPlaces() {
    for (int k = 0; k <= 1000; ++k) {
        if (notes[k].saveId < notes[k + 1].saveId) {
            notes[k] = notes[k+1];
            notes[k+1].saveId = 0;

        }
    }
}

void addNote(char* time) {
    char bufferClean;
    checkPlaces();
    for (int i = 0; ; ++i) {
        if (notes[i].saveId == 0) {
            strcpy(notes[i].timeAdd, time);
            strcpy(notes[i].timeEdit, time);
            printf("VYTVORRENI POZNAMKY\n");
            printf("Zadejte prosim nazev vasi poznamky:\n");
            scanf("%c", &bufferClean); // temp statement to clear buffer
            scanf("%[^\n]", &notes[i].noteName);
            printf("Zadejte vasi poznamku:\n");
            scanf("%c", &bufferClean); // temp statement to clear buffer
            scanf("%[^\n]", &notes[i].note);
            notes[i].saveId = 1;
            break;
        }
    }
    getNote();
    system("cls");
    printf("Vase poznamka byla uspesne vytvorena! Prosim vyckejte, budete presmerovani do menu.");
    Sleep(1500);
    animation();
    startDecision(startChoice());
}

int whatEdit() {
    checkPlaces();
    printf("PREHLED ULOZENYCH POZNAMEK\n");
    printf("Poznamky jsou vapsane ve tvaru: Poradi poznamky/Nazev poznamky/Cas posledni zmeny a nasledne dole samtonta poznamka\n\n");
    int what;
    for (int i = 0; i <= 1000; i++)
    {
        if (notes[i].saveId == 1)
        {
            int place = i + 1;
            printf("%d.           %s          %s\n", place, notes[i].noteName, notes[i].timeEdit);

            printf("%s\n\n\n", notes[i].note);
        }
    }
    printf("Kterou poznamkou chcete editovat:\n");
    scanf("%d", &what);
    animation();
    return what;

}



void editNote(int what, char* editTime) {
    char bufferClean;
    int whatEdit;
    printf("Prejete si editovat\n");
    printf("1. Nazev poznamky\n");
    printf("2. Vasi poznamku\n");
    printf("3. Nazev i poznamku dohromady\n");
    printf("Jakou akci budete chtit provest?(V pripade editace je automaticky editovany poznatek smazan):");
    scanf("%d", &whatEdit);
    animation();
    int i = what-1;
    

    switch (whatEdit)
    {
    case 1:
        printf("Zadejte novy nazev poznamky:\n");
        scanf("%c", &bufferClean); // temp statement to clear buffer
        scanf("%[^\n]", &notes[i].noteName);
        strcpy(notes[i].timeEdit, getTime());
        getNote();
        system("cls");
        printf("Vase poznamka byla uspesne upravena! Prosim vyckejte, budete presmerovani do menu.");
        Sleep(1500);
        animation();
        break;
    case 2:
        printf("Zadejte novou poznamku:\n");
        scanf("%c", &bufferClean); // temp statement to clear buffer
        scanf("%[^\n]", &notes[i].note);
        strcpy(notes[i].timeEdit, getTime());
        getNote();
        system("cls");
        printf("Vase poznamka byla uspesne upravena! Prosim vyckejte, budete presmerovani do menu.");
        Sleep(1500);
        animation();
        break;
    case 3:
        printf("Zadejte novy nazev poznamky:\n");
        scanf("%c", &bufferClean); // temp statement to clear buffer
        scanf("%[^\n]", &notes[i].noteName);
        printf("Zadejte novou poznamku:\n");
        scanf("%c", &bufferClean); // temp statement to clear buffer
        scanf("%[^\n]", &notes[i].note);
        strcpy(notes[i].timeEdit, getTime());
        getNote();
        system("cls");
        printf("Vase poznamka byla uspesne upravena! Prosim vyckejte, budete presmerovani do menu.");
        Sleep(1500);
        animation();
        break;
    }
    startDecision(startChoice());
}

int whatRemove() {
    checkPlaces();
    printf("PREHLED ULOZENYCH POZNAMEK\n");
    printf("Poznamky jsou vapsane ve tvaru: Poradi poznamky/Nazev poznamky/Cas posledni zmeny a dale pod bude samotna poznamka\n\n");
    int what;
    for (int i = 0; i <= 1000; i++)
    {
        if (notes[i].saveId == 1)
        {
            int place = i + 1;
            printf("%d.           %s          %s\n", place, notes[i].noteName, notes[i].timeEdit);

            printf("%s\n\n\n", notes[i].note);
        }
    }
    printf("Kterou poznamkou chcete smazat?\n");
    scanf("%d", &what);
    animation();
    return what;

}

void removeNote(int what) {
    checkPlaces();
    int i = what-1;
    notes[i].saveId = 0;
    checkPlaces();
    getNote();
    system("cls");
    printf("Vase poznamka byla uspesne smazana! Prosim vyckejte, budete presmerovani do menu.");
    Sleep(1500);
    animation();
    startDecision(startChoice());

}



