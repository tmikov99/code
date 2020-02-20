#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Movie{
    char number[13];
    char name[50];
    char director[50];
    float length;
    int year;
}movie;
typedef struct node{
	struct Movie data;
	struct node *next;
}node;
node* createList();
node* enterNode();
void addMovie(node **head);
void deleteMovie(node **head);
void printMovie(node *head);
void longestMovie(node *head);
void saveChanges(node *head);
int main()
{
    node *head = createList();
    int choice;

    while(choice)
    {
        printf("~~~~~~~~~~~~~~MENU~~~~~~~~~~~~~~\n     Choose option from 1-5\n1-Add new movie to the library\n2-Delete movies of a director\n3-Print all movies by year\n4-Find longest movie\n5-exit\n");
        scanf("%d",&choice);
        fflush(stdin);
        switch(choice)
        {
            case(1):
                addMovie(&head);
                break;
            case(2):
                deleteMovie(&head);
                break;
            case(3):
                printMovie(head);
                break;
            case(4):
                longestMovie(head);
                break;
            case(5):
                choice=0;
                break;
            default:
                printf("Enter valid number!\n");
        }
    }
    saveChanges(head);
    return 0;
}
node* enterNode()
{
    int i;
    node *newNode;
    newNode = (node *)malloc(sizeof(node));
    newNode->next=NULL;
    printf("Enter movie nomenclature number\n");
    do
    {
        gets(newNode->data.number);
        for(i=0;i<12;i++)
        {
            if(strlen(newNode->data.number)>12||newNode->data.number[i]<'0'||newNode->data.number[i]>'9')
            {
                printf("Incorrect length or format\n");
                i=0;
                break;
            }
        }
    }while(i==0);
    printf("Enter movie name\n");
    gets(newNode->data.name);
    printf("Enter movie director\n");
    gets(newNode->data.director);
    printf("Enter movie length\n");
    scanf("%f",&newNode->data.length);
    fflush(stdin);
    printf("Enter movie year\n");
    scanf("%d",&newNode->data.year);
    fflush(stdin);
    return newNode;
}
void addMovie(node **head)
{

    node *temp,*newNode;
    newNode=enterNode();
    if(*head==NULL)
    {
        *head=newNode;
        return;
    }
    temp=*head;
    while(temp->next != NULL)
        temp = temp -> next;
    temp->next=newNode;
	system("pause");
}


void deleteMovie(node **head)
{
    char deleteDirector[50];
    node *current,*temp;
    current = *head;
    printf("Enter director to be deleted\n");
    gets(deleteDirector);
    while(strcmp(deleteDirector,current->data.director)==0)
    {
        if(current->next==NULL)
        {
            *head=NULL;
            return;
        }
        *head = current->next;
        free (current);
        current = *head;
    }
    while(current->next != NULL)
    {
        temp = current -> next;
        if(strcmp(deleteDirector,temp->data.director)==0)
        {
            current->next=temp->next;
            free (temp);
        }
        if(current->next!=NULL)
            current = current -> next;
    }
	system("pause");
}
void printMovie(node *head)
{
    node *temp;
    int maxYear=0,n=0,i=0;
    temp=head;
    while(temp!=NULL)
    {
        if(temp->data.year>maxYear)
            maxYear=temp->data.year;
        n++;
        temp=temp->next;
    }
    while(n>i)
    {
        temp=head;
        while(temp!=NULL)
        {
            if(temp->data.year==maxYear)
            {
                printf("%s\t%s\t%s\t%0.0f minutes\t%d\n",temp->data.number,temp->data.name,temp->data.director,temp->data.length,temp->data.year);
                i++;
            }
            temp=temp->next;
        }
        maxYear--;
    }
    system("pause");
}
void longestMovie(node *head)
{
    node *temp;
    float maxLength=0;
    temp = head;
    while(temp!=NULL)
    {
        if(temp->data.length>maxLength)
            maxLength=temp->data.length;
        temp = temp -> next;
    }
    temp = head;
    while(temp!=NULL)
    {
        if(temp->data.length==maxLength)
            printf("%s\n",temp->data.name);
        temp=temp->next;
    }
    system("pause");
}
node* createList()
{
    int i=0;
    FILE *f;
    movie information;
    struct node *currentNode, *temp;
    node *headNode;
    if((f=fopen("Movies.txt","rb"))==NULL)
    {
        printf("No file in directory\nCreating head of list\n");
        headNode = enterNode();
        return headNode;
    }
    fseek(f, 0, SEEK_END);
    if (ftell(f) == 0)
    {
      printf("No list in file\nCreating head of list\n");
        headNode = enterNode();
        fclose(f);
        return headNode;
    }
    fseek(f, 0, SEEK_SET);
    while(1)
    {
        currentNode = (node *)malloc(sizeof(node));
        if(fread(&information,sizeof(movie),1,f)!=1)
            break;
        currentNode->data=information;

		if(i==0)
            headNode = temp = currentNode;
		else{

			temp->next = currentNode;
			temp = currentNode;
		}
		i=1;
	}
	temp->next = NULL;
	fclose(f);
	return headNode;
}
void saveChanges(node *head)
{
    FILE *f;
    node *temp;
    movie information;
    temp=head;
    f=fopen("Movies.txt","wb");
    while(temp!=NULL)
    {
        information=temp->data;
        fwrite(&information,sizeof(movie),1,f);
        temp=temp->next;
    }
    fclose(f);
}
