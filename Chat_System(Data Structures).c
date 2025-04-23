#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 100

struct Message {
    char sender[50];
    char content[256];
    float timestamp;
};

struct Queue {
    struct Message messages[MAX_SIZE];
    int front;
    int rear;
};

struct node {
    struct node * left;
    struct Message msg;
    struct node * right;
};

//Initialization of Queue
void initialize_Queue(struct Queue *q){
    q->front=0;
    q->rear=0;
};

// function to enqueu(add message) in the queue
void enqueue(struct Queue *q, struct Message msg){
    if(q->rear==MAX_SIZE){
        printf("Queue is full.\n");
        return;
    }
    else {
        q->messages[q->rear]=msg;
        q->rear++;
    }
}

//function to dequeue an element from queue and return the front message
struct Message dequeue(struct Queue *q){
    if(q->rear==q->front){
        printf("Queue is empty.\n");
        exit (0);
    }
    else {
        return q->messages[q->front];
        q->front++;
    }
}

// inserting messages in the BST
struct node * insert(struct node *root, struct Message msg){
    if(root == NULL){
        struct node * newnode = NULL;
        newnode = (struct node*)malloc(sizeof(struct node));
        newnode->msg = msg;
        newnode->left = NULL;
        newnode->right = NULL;
        return newnode;
    }
    else if(msg.timestamp < root->msg.timestamp){
        root->left = insert(root->left,msg);
    }
    else {
        root->right = insert(root->right,msg);
    }
    return root;
}

// search messages by timestamp
struct Message* searchByTimestamp(struct node * root, float timestamp){
    if(root==NULL){
        return NULL;
    }
    if(timestamp==root->msg.timestamp){
        return &root->msg;
    }
    if(timestamp<root->msg.timestamp){
        return searchByTimestamp(root->left,timestamp);
    }
    else{
        return searchByTimestamp(root->right,timestamp);
    }
}

// function to search by keyword

void searchByKeyword(struct node * root, const char* keyword){
    if(root==NULL){
        return;
    }
    searchByKeyword(root->left,keyword);

    if(strstr(root->msg.content,keyword)!=NULL){
        printf("message found:\n");
        printf("sender: %s\n", root->msg.sender);
        printf("content: %s\n", root->msg.content);
        printf("timestamp: %f\n", root->msg.timestamp);
    }

    searchByKeyword(root->right,keyword);
}

//deleting messages older than given timestamp
// struct node* findMin(struct node* node){
//     while(node&&node->left!=NULL)
//     node= node->left;
//     return node;
// }

// both the findMin function are same 
struct node* findMin(struct node* node) {
    if (node == NULL) {
        return NULL; // Tree is empty, nothing to find
    }

    // Keep going left until there is no more left child
    while (node->left != NULL) {
        node = node->left;
    }

    // Now node is the leftmost (smallest) node
    return node;
}


struct node* deleteOlderThan(struct node* root, float timestamp){
    if(root==NULL) return NULL;

    root->left = deleteOlderThan(root->left, timestamp);
    root->right = deleteOlderThan(root->right, timestamp);

    if(root->msg.timestamp < timestamp){
        struct node * temp;
        if(root->left==NULL){
            temp=root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL){
            temp=root->left;
            free(root);
            return temp;
        }
        else {
            struct node* minRight = findMin(root->right);
            root->msg=minRight->msg;
            root->right=deleteOlderThan(root->right,minRight->msg.timestamp);
        }
    }
    return root;
}

void print(struct node* root){
    if(root==NULL){
        return;
    }
    else{
        
        print(root->left);

        printf("sender: %s\n",root->msg.sender);
        printf("content: %s\n",root->msg.content);
        printf("timestamp: %f\n",root->msg.timestamp);
        printf("\n");

        print(root->right);
    }
}

int main() {
    struct Queue q;
    struct node *root =NULL;

    initialize_Queue(&q);

    printf("* * * Onlline Chat System * * *\n");
    printf("Select numbers from given Menu to perform operation.\n");
    int choice;
    float time;
    float time1;
    char keyword[50];

    struct Message msg;
    do{
        printf("1. Add messages\n2. Search by Timestamp\n3. Search by Keyword\n4. Delete old Messages\n5. Print messages\n6. Exit\nChoice :");
        scanf("%d", &choice);
        switch(choice){
            case 1:
            // printf("Sender :");
            // scanf("%s", msg.sender);
            // printf("Content :");
            // scanf("%s", msg.content);
            printf("Sender: ");
            getchar(); // Clear leftover newline
            fgets(msg.sender, sizeof(msg.sender), stdin);
            msg.sender[strcspn(msg.sender, "\n")] = '\0';

            printf("Content: ");
            fgets(msg.content, sizeof(msg.content), stdin);
            msg.content[strcspn(msg.content, "\n")] = '\0';

            printf("Timestamp (Number):");
            scanf("%f", &msg.timestamp);
            
            printf("* * * * * * * * * \n");

            enqueue(&q, msg);
            root = insert(root, msg);
            break;

            case 2:
            printf("Enter Timestamp :");
            scanf("%f", &time);
            struct Message* result = searchByTimestamp(root,time);
            if(result){
                printf("found : [%s] %s\n", result->sender,result->content);
            }
            else {
                printf("message not found.\n");
            }
            printf("* * * * * * * * * \n");
            break;

            case 3:
            printf("Enter keyword :");
            scanf("%s", keyword);
            printf("message containing '%s' :\n",keyword);
            searchByKeyword(root,keyword);
            printf("* * * * * * * * * \n");
            break;

            case 4:
            printf("Deleting messages older than timestamp :");
            scanf("%f", &time1);
            root = deleteOlderThan(root,time1);
            printf("old messages deleted.\n");
            printf("* * * * * * * * * \n");
            break;

            case 5:
            printf("printing the messages :\n\n");
            print(root);
            break;

            case 6:
            printf("Exiting the program...");
            printf("\nsee u soon.\n");
            break;

            default :
            printf("Invalid Input.\nSelect from menu given.\n");
        }
    } while(choice != 6);
    return 0;
}