#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct dict{
struct dict *left, *right;
char palavra[10], meaning[20];
}*Root=NULL;

typedef struct dict dictionary;

int check(char[], char[]);
void insert(dictionary *);
void Search();
void view(dictionary *);

int check(char a[], char b[]){
int i, j, c;
for(i=0,j=0; a[i]!='\0' && b[j]!='\0'; i++, j++){
    if(a[i]>b[j]){
        c=1;
        break;
    }
    else if(b[j]>a[i]){
        c=-1;
        break;
    }

    else

    c=0;

}
    if(c==1)
        return 1;
    else if(c==-1)
        return -1;
    else
        return 0;

}

void Search(){
int flag=0;
dictionary *ptr;
char w[10];
ptr=Root;


printf("\nEnter the word...");

scanf("%s", w);
while(ptr!=NULL && flag ==0){
    if(check(w, ptr -> palavra ) > 0){
        ptr =ptr -> right;
    }
    else if(check(w, ptr -> palavra) < 0){
        ptr = ptr -> left;
    }
    else if (check(w,ptr -> palavra) ==0){
        flag=1;
        printf("\nMeaning:" "%s", ptr -> meaning);
    }
}

if(flag==0)
    printf("\nWord not found!");
}

void insert(dictionary *temp){
int flag=0;
dictionary *ptr, *par;
ptr=Root;

if(Root == NULL)
    Root = temp;
else{
    while(ptr!=NULL){
        if(check(temp -> palavra, ptr -> palavra ) > 0){
            par = ptr;
            ptr = ptr -> right;
    }

    else if(check(temp -> palavra, ptr -> palavra) < 0){
        par = ptr;
        ptr = ptr -> left;
    }

    else if (check(temp -> palavra, ptr -> palavra) == 0){
        flag=1;
        printf("\nWord exists!!\n" );
        break;
    }
}
if(flag == 0 && ptr ==NULL){
    if(check(par -> palavra, temp -> palavra) ==1)
        par -> left=temp;
    else if(check(par -> palavra, temp -> palavra)==-1)
        par -> right=temp;
}
}

}

void view(dictionary *ptr){
    if(Root ==NULL)
        printf("\nEmpty Dictionary\n");

        else if(ptr !=NULL){
                view(ptr-> left);
                printf("\nWord: %s\n", ptr -> palavra);
                printf("\nMeaning: %s\n", ptr -> meaning);
                view(ptr -> right);
    }
}




int main(int argc, char *argv[])
{
    int opcao;
    dictionary *temp;
char palavra[10];


    FILE *fp;
    FILE *fp2;
    FILE *fp3;
    char ch;
    int size = 0;
    fp = fopen("data.txt", "r");
    fp2 = fopen("dados_separados.txt", "w");


    if (fp == NULL)
        printf("\nFile unable to open ");
    else
        printf("\nFile opened ");
    fseek(fp, 0, 2);    /* file pointer at the end of file */
    size = ftell(fp);   /* take a position of file pointer un size variable */
    //char *myArray =  (char*)malloc(size * sizeof *myArray);
    char *myArray = (char*)malloc(size);


    static const char filename[] = "data.txt";
    FILE *file = fopen(filename, "r");
    if ( file != NULL ){
        int ch, word = 0, index= 0,index2 = 0;
        while ( (ch = fgetc(file)) != EOF ){
            if ( isspace(ch) || ispunct(ch) ){
                if ( word ){
                    word = 0;
                    myArray[index++] = '\n';
                   //putchar('\n');
                }
            }else{
                word = 1;
                //putchar(ch);
                myArray[index++] = ch;
                index2++;
            }
        }
        printf("%s", myArray);
        fprintf(fp2, "%s", myArray);

        temp=(dictionary *)malloc(sizeof(dictionary));
        temp -> left = NULL;
        temp -> right = NULL;

        //strcpy(myArray, temp ->palavra);

        //printf("\nInsert meaning:");
        //scanf(&myArray[0], temp -> palavra);
        //insert(temp);
        strcpy(&myArray, temp -> meaning);
        scanf("%s", temp -> palavra);
        insert(temp);
        strcpy(&myArray, temp -> meaning);
        insert(temp);


        while (opcao!=4){
    printf("\n1.Search\n2.Insert\n3.View\n4.Quit\nYour choice please...");
    scanf("%d", &opcao);
    switch(opcao){
    case 1: Search(); break;
    case 2:
        temp=(dictionary *)malloc(sizeof(dictionary));
        temp -> left =NULL;
        temp -> right = NULL;
        printf("\nInsert Word:\n");
        scanf("%s", temp -> palavra);
        printf("\nInsert meaning:");
        scanf("%s", temp -> meaning);
        insert(temp);
        break;
    case 3:
        view(Root);
        break;
    case 4: exit(0);
    }
}
        fclose(file);
        fclose(fp2);

        int i;
        for(i = 0;i < sizeof(myArray);i++){
            putchar(myArray[i]);
        }

free(myArray);
        //qsort (array, 2, sizeof (const char *), compare);
        //for (int i = 0; i < 2; i++) {
        //    printf ("%d: %s.\n", i, array[i]);
        //}
    }
}

