#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

char str2[MAX];

struct node {
	int data;
	struct node *array[26];
};

struct node* new_node(struct node *h)
{
	int i;
	h = malloc(sizeof (struct node));
	for (i = 0; i < 24; ++i)
		h->array[i] = 0;
	return h;
}

struct node* insert(struct node *h, char *c, int value)
{
	int i;
	if (strlen(c) == 0)
		return h;
	if (h == NULL)
		h = new_node(h);
	struct node *p = h;
	for (i = 0; i < strlen(c); ++i) {
		if (p->array[c[i] - 'a'] == NULL) 
			p->array[c[i] - 'a'] = malloc(sizeof (struct node));
		p = p->array[c[i] - 'a'];
	}
	p->data = value;
	return h;
}

void dfs(struct node *h, char *dat)
{
	int i;
	char k[100] = {0};
	char a[2] = {0};
	if (h == NULL) 
		return;
	if (h->data > 0) 
		printf("Match: %s\n", dat);
	for(i = 0; i < 26; ++i) {
		strcpy(k, dat);
		a[0] = i + 'a';
		a[1] = '\0';
		strcat(k, a);
		dfs(h->array[i], k);
	}
}

void search(struct node *h, char *s, char *dat)
{
	int i;
	char l[100] = {0};
	char a[2];
	strcpy(l, dat);
	if (strlen(s) > 0) {
		a[0] = s[0];
		a[1] = '\0';
		if(h->array[a[0]-'a'] != NULL) {
			strcat(dat, a);
			search(h->array[a[0]-'a'], s+1, dat);
		} else
			printf("No Match");
	} else {
		if (h->data != 0) 
			printf("Match: %s\n",str2);
		for (i = 0; i < 26; ++i) {
			strcpy(l, dat);
			a[0] = i + 'a';
			a[1] = '\0';
			strcat(l, a);
			dfs(h->array[i], l); 
		}
	}
}

struct node* read_keys(struct node *h, char *file)
{
	char s[MAX];
	FILE *a = fopen(file, "r");
	if (a == NULL)
		printf("Error while opening file");
	else 
		while (feof(a) == 0) {
			fscanf(a, "%s", s);
			h = insert(h, s, 1);
		}
	return h;
}

int main()
{
    int choice=0;
    do{
        system("clear");
        printf("\n1. Add words to dictionary");
        printf("\n2. Predict");
        printf("\n3. Exit");
        printf("\nEnter your choice: ");
        scanf("%d",&choice);
        if(choice == 1){
            char str[MAX];
            printf("Enter a word to add to dictionary: ");
            scanf("%s",str);
            FILE *fp = fopen("a.txt","r+");
            if (fp == NULL)
                {
                    printf("Could not open file");
                    return 0;
                }
            fseek(fp,0,SEEK_END);
            fprintf(fp,"\n%s",str);
            fclose(fp);
            printf("%s was successfully added to the dictionary!",str);
            
            
        }else if(choice == 2){
            struct node *h = 0;
            h = read_keys(h, "a.txt");
            char s[MAX];
            printf("Enter a part of word: ");
            scanf("%s", s);
            strcpy(str2,s);
            char dat[100] = "";
            search(h, s, dat);
            while(getchar()!='\n'); // option TWO to clean stdin
            getchar();
        }else{
            printf("Exiting...\n");
        }
    }while(choice!=3);
    return 0;
    
	
}