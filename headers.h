#ifndef _ROUTING_
#define _ROUTING_

typedef struct vertex
{
    char vertexName[50]; //name of the street given by the user
    int vertexId;        //it is a unique value for each vertexname given by the code

} vertex;

int numPlaces, numStreets;

char placesAndIDs[100000][50]; //stores the place names and ids
typedef struct Graph
{
    int numVertices;                 //Number of vertices
    struct ListNode **adjacencyList; //stores the streets in the graph
    struct ListNode **path;          //patharray is used to store the shortest paths of everyvertex by separate-chaining method of hashtables

} Graph;

//***the below structre strores the data of a street***//
struct StreetData
{
    float length;       //length of the street
    float traffic;      //will be calculated based on the constructed formulae
    int numLanes;       //range = 1-4
    int num_cars;       //Average Number of cars on the street per hour ---- range = 10 - 300
    int num_accidents;  //Average Number of accidents per week -------- range = 1 - 10
    int speed_limit;    //Maximum Speed Limit --- range= 10-100 km/h
    float weight;       //Final weightage/congestion index of the street
    float safety_value; //will be calculated based on the constructed formulae
};

typedef struct ListNode
{
    vertex dest;
    struct ListNode *next;
    struct StreetData SD;
} ListNode;

typedef struct queueNode
{
    vertex v;
    struct queueNode *next; // this structure is for queues //
} queueNode;

typedef struct queue
{
    queueNode *front;
    queueNode *rear;
} queue;

typedef struct ListNode *head;

queue *initqueue();                                                      // creates a queue
queue *enqueue(queue *q, vertex x);                                      // adds an element at the end of an queue
int dequeue(queue *q);                                                   // removes the element at the front of queue and returns it
int findInVertexArray(char array[][50], char key[50], int n);            //this function checks if a place name(VERTEX NAME) is given before or not while taking the edges as input
struct Graph *CreateGraph(int n);                                        //n is no of vertices;// creates a graph
void AddStreet(Graph *G, vertex src, vertex dest, struct StreetData SD); //adds streets to the graph
void getFastestPath(struct Graph *G, vertex src, vertex dest, int flag); //find the fastest path between home and exam center //
void UpdateStreet(struct Graph *G, vertex u, vertex v, int cars);        //updates the graph again with the desired street inputs //
void DeleteStreet(struct Graph *G, vertex u, vertex v);                  //deletes the street edges from the memory

#endif
