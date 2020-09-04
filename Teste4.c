#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

/**Tamanho do alfabeto (# de símbolos)*/

#define ALPHABET_SIZE (26)

/**Converte a chave atual para caractere dentro de um index*/
/**Usar somente 'a' até 'z' em minúsculo*/

#define CHAR_TO_INDEX(c) ((int)c - (int) 'a')

/**Árvore trie*/

struct TrieNode{
/**O tamanho do alfabeto é multiplicado por dois pois armazena de 'A' a 'Z' e de 'a' a 'z'*/
    struct TrieNode *children[ALPHABET_SIZE*2];

    /**a variável isEndOfWord é verdadeira se o nó representa o final de uma palavra*/
    bool isEndOfWord;


};


struct TrieNode *getNode(void){


struct TrieNode *pNode = NULL;

if(pNode){

    int i;

    pNode -> isEndOfWord = false;

    for (i = 0; i < ALPHABET_SIZE; i++)
        pNode -> children[i] = NULL;
}

return pNode;

}


/**Se a chave não existir na árvore, a chave será inserida nela*/
/**Se a chave é um prefixo de um nó da árvore trie, só marque o nó da folha da árvore*/

void insert(struct TrieNode *root, const char *key){

int level;
int length = strlen(key);
int index;

struct TrieNode *pCrawl = root;

for (level = 0; level < length; level ++){
    index = CHAR_TO_INDEX(key[level]);
        if(!pCrawl -> children[index])
            pCrawl -> children[index] = getNode();
        pCrawl = pCrawl -> children[index];
}

/**Marcar o último nó da palavra como uma folha na árvore*/
pCrawl -> isEndOfWord = true;

}

/**Retorna verdadeiro se a chave estiver presente na árvore, se não retorna falso*/

bool search(struct TrieNode *root, const char *key){

int level;
int length = strlen(key);
int index;
struct TrieNode *pCrawl = root;

for (level = 0; level < length; level ++){
    index = CHAR_TO_INDEX(key[level]);
    if(!pCrawl -> children[index])
    return false;

    pCrawl = pCrawl -> children[index];
}

return (pCrawl != NULL && pCrawl -> isEndOfWord);

}


int main(int argc, char *argv[])
{

char palavra[10];

    FILE *fp;
    FILE *fp2;
    char ch;
    int size = 0;
    fp = fopen("data.txt", "r");
    fp2 = fopen("dados_separados.txt", "w");


    if (fp == NULL)
        printf("\nFile unable to open ");
    else
        printf("\nFile opened ");
    fseek(fp, 0, 2);    /** file pointer at the end of file */
    size = ftell(fp);   /** take a position of file pointer un size variable */
    //char *myArray =  (char*)malloc(size * sizeof *myArray);


    char *myArray = (char*)malloc(size);
    char *palavras_separadas = (char*)malloc(size);

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
        struct TrieNode *root = getNode();
        insert(root, myArray);
        insert(root, &myArray[2]);

/*for(int z = 0; z<strlen(index2); z++){
        insert(root, myArray[z]);

}*/
       // insert(root, myArray[index]);
 /*struct TrieNode *root = getNode();
                insert(root, &myArray);*/

        fprintf(fp2, "%s", myArray);

/*for(int z=0; z<contador; z++){
    printf("%s", palavras_separadas[z]);
}*/
        fclose(file);
        fclose(fp2);

        int i;
        for(i = 0;i < sizeof(myArray);i++){
            putchar(myArray[i]);
        }
/*
for(i = 0; i<strlen(myArray); i++){
    printf("%s", myArray[i]);
}
*/



free(myArray);
        //qsort (array, 2, sizeof (const char *), compare);
        //for (int i = 0; i < 2; i++) {
        //    printf ("%d: %s.\n", i, array[i]);
        //}
    }

}

/** Deallocates memory previously allocated for the TrieNode. */
void trieFree(struct TrieNode* root) {

    if(root){

        for(int i = 0; i <=26; i ++)
        {
            trieFree(root->children[i]);
        }
        free(root);

    }

}







/** Returns if there is any word in the trie
    that starts with the given prefix. */
bool startsWith(struct TrieNode* root, char* prefix) {

    struct TrieNode * pCrawl = root;

    int i =0, index=0;
    bool flag = false;
    if(root){
    while(prefix[i] != '\0')
    {
         index = ((int) (prefix[i]) - (int)'a');

     if(pCrawl->children[index] == NULL){
     flag = false;
         return flag;
     }
     else
     flag = true;

     pCrawl = pCrawl->children[index];
     i++;
    }

    }

    return flag;
}
