#include<stdio.h>
#include<stdlib.h>

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize;
int * list;
int length;
void shrink();
int clear_flag=0;


void initializeList()
{
    listMaxSize = LIST_INIT_SIZE;
    list = (int*)malloc(sizeof(int)*listMaxSize) ;
    length = 0 ;
}

int searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item ) return i;
    }
    return NULL_VALUE;
}


int insertItem(int newitem)
{
    if(clear_flag)
    {
        initializeList();
        clear_flag=0;
    }
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
    return SUCCESS_VALUE ;
}


int deleteItemAt(int position) //version 2, do not preserve order of items
{
    if ( position >= length ) return NULL_VALUE;
    list[position] = list[length-1] ;
    length-- ;
    shrink();
    return SUCCESS_VALUE ;
}



int deleteItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return NULL_VALUE;
    deleteItemAt(position) ;
    shrink();
    return SUCCESS_VALUE ;
}

void printList()
{
    if(clear_flag)
    {
        printf("List is not initialized\n");
        return;
    }
    /*
    else if(length==0)
    {
        printf("List is empty\n");
        return;
    }*/
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

int getLength()
{
    return length;
}

int insertItemAt(int pos,int item)
{
    if(clear_flag)
    {
        initializeList();
        clear_flag=0;
    }
    int *temp;
    if(pos<0||pos>length)return NULL_VALUE;

    if(length==listMaxSize)
    {
        //int *temp;
        listMaxSize=2*listMaxSize;
        temp=(int *)malloc(listMaxSize*sizeof(int));
        for(int i=0; i<length; i++)temp[i]=list[i];
        free(list);
        list=temp;
    }
    if(pos==length)
    {
        list[length]=item;
        length++;
        return SUCCESS_VALUE;
    }/*
    else{
        for(int i=length;i>pos;i--)list[i]=list[i-1];
        list[pos]=item;
        length++;
        return SUCCESS_VALUE;
    }*/
    int temp2=list[pos];
    list[pos]=item;
    list[length]=temp2;
    length++;
    return SUCCESS_VALUE;
}

void shrink()
{
    if(length*2<=listMaxSize&&listMaxSize>=2)
    {
        listMaxSize=listMaxSize/2;
        int *temp;
        temp=(int *)malloc(listMaxSize*sizeof(int));
        for(int i=0; i<length; i++)temp[i]=list[i];
        free(list);
        list=temp;
    }
}
/*
void deleteLast()
{
if(length>0){
    deleteItemAt(length-1);
}
}
*/
int deleteLast()
{
    if(length>0){
    int m=list[length-1];
    deleteItemAt(length-1);
    return m;
    }
    return NULL_VALUE;
}

void clear()
{
    if(!clear_flag)
    {
        free(list);
        length=0;
        clear_flag=1;
    }
}
void deleteAll()
{
    length=0;
    if(listMaxSize>2){
        free(list);
        initializeList();
    }
}

int getItem(int pos)
{
    return list[pos];
}

int getPos(int item)
{
    return searchItem(item);
}




//First portion for Task 1-6

int main()
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item at. 3. Delete item.\n");
        printf("4. Insert new item in a specific position. 5. Print. 6. exit.\n");
        printf("7. Search Item.  8. Delete Last item  9. Get length  10. Clear list  11. Delete All\n");


        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==4)
        {
            printf("Enter position and Item:: ");
            int item,pos;
            scanf("%d %d",&pos,&item);
            insertItemAt(pos,item);
        }
        else if(ch==5)
        {
            printList();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==7){
            int k;
            scanf("%d",&k);
            int l=searchItem(k);
            if(l==NULL_VALUE){
                printf("%d is absent in list\n",k);
            }
            else{
                printf("%d Item is got in [%d] position\n",k,l);
            }
        }
        else if(ch==8)
        {
            deleteLast();
        }
        else if(ch==9)
        {
            printf("Length =%d\n",getLength());
        }
        else if(ch==10)
        {
            clear();
        }
        else if(ch==11)
        {
            deleteAll();
        }

    }

}


//Postfix Evaluation Task 7

/*
int main()
{
    char str[20];
    int m,i=0;
    printf("Give a valid postfix Expression: \n");
    scanf("%s",str);
    while(str[i]){
            if((str[i]-'0')>=0&&(str[i]-'0')<10){
                insertItem(str[i]-'0');
            }else{
                int q=deleteLast();
                int p=deleteLast();
                switch(str[i]){
                case '+':
                    m=p+q;
                    break;
                case '*':
                    m=p*q;;
                    break;
                case '/':
                    m=p/q;
                    break;
                case '-':
                    m=p-q;
                    break;
                }
                insertItem(m);
            }
        i++;
    }
    printf("%d",getItem(length-1));
    return 0;
}
*/

/*
int main()
{
    char str[20];
    int m,i=0;
    printf("Give a valid postfix expression: \n");
    scanf("%s",str);
    initializeList();
    while(str[i])
    {
        if((str[i]-'0')>=0&&(str[i]-'0'<10))insertItem(str[i]-'0');
        else{
            switch(str[i]){
                case '+':
                    m=getItem(length-1)+getItem(length-2);
                    break;
                case '*':
                    m=getItem(length-1)*getItem(length-2);
                    break;
                case '/':
                    m=getItem(length-2)/getItem(length-1);
                    break;
                case '-':
                    m=getItem(length-2)-getItem(length-1);
                    break;
            }
            deleteLast();
            deleteLast();

                insertItem(m);
        }
        i++;
    }
    if(length==2){
        printf("Result is ::%d%d",getItem(length-2),getItem(length-1));
        return 0;
    }
    printf("Result is :::%d",getItem(length-1));
    return 0;
}
*/
