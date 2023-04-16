#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node           //structure declaration for tree               
{
    char data[25];
    struct node *left, *right;
};
typedef struct node *NODE;

//function to insert a node in the tree
NODE insert(NODE root, char gender, char name[])
{
    NODE temp, newnode, temp1;
    char ele;
    temp = root;
    //dynamic memory allocation of the node which is to be inserted
    newnode = (NODE)malloc(sizeof(struct node));
    strcpy(newnode->data, name);
    newnode->left = newnode->right = NULL;
    if (root == NULL)
    {
        root = newnode;
        return root;
    }
    while (temp != NULL)
    {
        temp1 = temp;
        //relationship with the previous node 
        //determines which side node will be attached
        printf("Relation with %s (P for Paternal / M for Maternal) :", temp->data);
        getchar();
        scanf("%c", &ele);
        if (ele == 'p' || ele == 'P')
            temp = temp->left;
        else if (ele == 'm' || ele == 'M')
            temp = temp->right;
    }
    //gender determination
    //another factor to determine the side to be attached
    if (gender == 'm' || gender == 'M')
        temp1->left = newnode;
    else
        temp1->right = newnode;
    return root;
}


struct nodeq      //structure declaration for queue
{
    struct node *item;
    struct nodeq *next;
};
typedef struct nodeq *NODEQ;    


NODEQ insertlast(NODEQ first, NODE ele)     //insrertion at the end function for the queue
{
    NODEQ newnode, temp;
    //dynamic allocation of memory for the new node of queue
    newnode = (NODEQ)malloc(sizeof(struct nodeq));
    newnode->item = ele;
    newnode->next = NULL;
    if (first == NULL)
    {
        first = newnode;
        return first;
    }
    temp = first;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newnode;
    return first;
}

NODEQ deletefirst(NODEQ first)    //function to delete the first element from the queue
{
    NODEQ temp;
    if (first == NULL)
        return first;
    temp = first;
    first = first->next;
    free(temp);
    return first;
}


void levelorder(NODE root)   //level order traversal of the tree using queues
{
    if (root == NULL)
        return;
    NODEQ queue;
    queue = NULL;
    //first the root is inserted into the queue
    queue = insertlast(queue, root);
    //insertion of NULL which acts as a delimiter(it will say that the one level is completed)
    queue = insertlast(queue, NULL);
    while (queue != NULL)
    {
        NODEQ front;
        front = queue;
        if (queue->item != NULL)
        {
            printf("%s ", queue->item->data);
            //pushing of the left children of the popped node
            if (front->item->left != NULL)
                queue = insertlast(queue, front->item->left);
            //pushing of the right children of the popped node
            if (front->item->right != NULL)
                queue = insertlast(queue, front->item->right);
        }
        //pushing the elements left over
        else if (queue->next != NULL)
        {
            queue = insertlast(queue, NULL);
            printf("\n");
        }
        queue = deletefirst(queue);
    }
}


//function to calculate the height of the tree
int height(NODE root)
{
    if (root == NULL)
        return 0;
    //recursive call for the height of the left side of the tree
    int lheight = height(root->left);
    //recursive call for the height of the right side of the tree
    int rheight = height(root->right);
    //determination of the height by
    //comparing the left and right height of the tree
    if (lheight > rheight)
        return lheight + 1;
    else
        return rheight + 1;
}


//function to print the current level of the tree
void printCurrentLevel(NODE root, int level)
{
    if (root == NULL)
    {
        return;
    }
    //prints the elements in the current level
    if (level == 1)
    {
        printf("%s ", root->data);
    }
    //recursive call to print next level left side
    printCurrentLevel(root->left, level - 1);
    //recursive call to print next level right side
    printCurrentLevel(root->right, level - 1);
}


//function which calls the printCurrentLevel
//it gives the proper arguments to print the current level
void LevelOrderRecurtion(NODE root)
{
    int h = height(root);
    for (int i = 1; i <= h; i++)
    {
        printCurrentLevel(root, i);
        printf("\n");
    }
}


//beginning of the main function
int main()
{
    int choice;
    char name[25], gender;
    //initialisation of the root of the tree
    NODE root = NULL;
    while (1)
    {
        printf("\n 1.Insert\n 2.Level Order using queues\n 3.Level order using recursion\n 4.Exit\n Enter your choice :");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:    //element insertion in tree
            printf("Enter the element to be inserted :");
            getchar();
            scanf("%s", name);
            printf("Enter the gender:(M for Male / F for Female) :");
            getchar();
            scanf("%c", &gender);
            root = insert(root, gender, name);
            break;
        case 2:      //level order using queues function call
            levelorder(root);
            printf("\n");
            break;
        case 3:     //level order using recurtion function call
            LevelOrderRecurtion(root);
            printf("\n");
            break;
        case 4:     //terminate the program
            exit(0);
            break;
        default:
            printf("Invalid Input....\n");
            break;
        }
    }
    return 0;
}//end of the main function