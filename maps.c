#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define INF INT_MAX

queue *initqueue()
{
    // **************** THIS FUNCTION CREATES A QUEUE ************* //
    queue *q;
    q = (queue *)malloc(sizeof(struct queue));
    q->front = (queueNode *)malloc(sizeof(struct queueNode));
    q->rear = (queueNode *)malloc(sizeof(struct queueNode));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

queue *enqueue(queue *q, vertex x)
{
    queueNode *temp = (queueNode *)malloc(sizeof(struct queueNode));

    temp->v = x;
    temp->next = NULL;

    if (q->front == NULL)
    {
        q->front = temp; // ********* THIS FUNCTION ADDS ELEMENT INTO QUEUE FROM BACKSIDE ******* //
        q->rear = temp;
    }

    else
    {
        q->rear->next = temp;
        q->rear = temp;
    }

    return q;
}

int dequeue(queue *q)
{
    int x = q->front->v.vertexId;

    q->front = q->front->next; // ****** THIS FUNCTION REMOVES AN ELEMENT FROM THE FRONT SIDE OF THE QUEUE ****** //

    if (q->front == NULL)
        q->rear = NULL;

    return x;
}

int findInVertexArray(char array[][50], char key[50], int n)
{
    //******** THIS FUNCTION CHECKS IF A PLACE NAME(VERTEX NAME) IS GIVEN BEFORE OR NOT WHILE TAKING THE EDGES AS INPUT*****//
    for (int i = 0; i < n; i++)
    {
        if (strcmp(array[i], key) == 0)
            return 1;
    }
    return 0;
}

//****** THE BELOW FUNCTION CREATES A GRAPH ******//
struct Graph *CreateGraph(int iNumber_of_vertices)
{
    struct Graph *G = (struct Graph *)malloc(sizeof(struct Graph));
    assert(G != NULL);

    G->numVertices = iNumber_of_vertices;

    //AdjacencyList is the array of pointers to listnodes

    G->adjacencyList = (ListNode **)malloc(sizeof(ListNode *) * iNumber_of_vertices);

    //path is the array of pointers to listnodes
    //patharray is used to store the shortest paths of everyvertex by separate-chaining method of hashtables

    G->path = (ListNode **)malloc(sizeof(ListNode *) * iNumber_of_vertices);

    assert(G->adjacencyList != NULL);

    for (int i = 0; i < iNumber_of_vertices; i++)
    {
        G->adjacencyList[i] = NULL;
        G->path[i] = (struct ListNode *)malloc(sizeof(struct ListNode));
        G->path[i]->dest.vertexId = i;
        G->path[i]->next = NULL;
    }

    return G;
}

// the below function adds the streets to the graph //
void AddStreet(struct Graph *G, vertex u, vertex v, struct StreetData SD)
{
    ListNode *temp;
    temp = G->adjacencyList[u.vertexId];
    int found = 0;
    vertex w;

    while (temp != NULL)
    {
        w = temp->dest;

        if (v.vertexId == w.vertexId)
        {
            found = 1;
            break;
        }
        temp = temp->next;
    }
    ///// WE USED THE 'FOUND' CONDITION TO CHECK IF THE EDGE ALREADY EXITS OR NOT. IF NOT THEN ADD TO THE GRAPH ////
    if (!found)
    {
        temp = G->adjacencyList[u.vertexId];
        ListNode *New = (ListNode *)malloc(sizeof(struct ListNode));
        assert(New != NULL);
        New->dest = v;
        New->SD = SD;
        //Add at beginning
        New->next = temp;
        G->adjacencyList[u.vertexId] = New;
    }

    // THE BELOW CODE IS USED TO GIVE THE GRAPH BI-DIRECTIONALITY (WHICH IS STORES EDGES IN BOTH WAYS) //
    ListNode *tempi;
    tempi = G->adjacencyList[v.vertexId];
    int foundi = 0;
    vertex wi;

    while (tempi != NULL)
    {
        wi = tempi->dest;
        if (u.vertexId == wi.vertexId)
        {
            foundi = 1;
            break;
        }
        tempi = tempi->next;
    }

    if (!foundi)
    {
        tempi = G->adjacencyList[v.vertexId];
        ListNode *New = (ListNode *)malloc(sizeof(struct ListNode));
        assert(New != NULL);
        New->dest = u;
        New->SD = SD;
        //Add at beginning
        New->next = tempi;
        G->adjacencyList[v.vertexId] = New;
    }

    return;
}

void getFastestPath(struct Graph *G, vertex src, vertex dest, int flag)
{
    if (src.vertexId == -1 || dest.vertexId == -1)
        return;

    if (flag == 0)
    {
        // find the shortest path if flag is 0
        queue *q = initqueue();
        enqueue(q, src); // ADDING THE ELEMENTS TO THE QUEUE ACCORDING TO THE BFS //

        float cost[G->numVertices];
        float length[G->numVertices];
        float safetyvalue[G->numVertices];
        for (int i = 0; i < G->numVertices; i++)
        {
            cost[i] = INF; // INITIALIZES THE VALUE TO REACH EACH VERTEX TO INFINITY AS IT WAS NOT POSSIBLE TO REACH AT BEGINING //
            length[i] = 0;
            safetyvalue[i] = 0.00f;
        }

        cost[src.vertexId] = 0;

        int visited[G->numVertices];
        for (int i = 0; i < G->numVertices; i++)
        {
            visited[i] = 0;
        }

        visited[src.vertexId] = 1;

        for (int i = 0; i < G->numVertices; i++)
        {
            G->path[i]->dest.vertexId = i;
            G->path[i]->next = NULL;
        }

        while (q->front != NULL)
        {
            // CHECKING ALL ELEMENTS ACCORDING TO THE BFS //
            int x = dequeue(q);
            visited[x] = 1;

            // struct ListNode *crawl = G->adjacencyList[x];
            struct ListNode *temp = G->adjacencyList[x];
            int i = 0;

            while (temp != NULL)
            {
                // CHECKS ALL ITS NEIGHBOURING VERTICES AND FINDS WHICH ONE IS SHORT
                if ((x != temp->dest.vertexId) && (cost[temp->dest.vertexId] >= (cost[x] + temp->SD.weight)))
                {
                    cost[temp->dest.vertexId] = cost[x] + temp->SD.weight;
                    length[temp->dest.vertexId] = length[x] + temp->SD.length;
                    safetyvalue[temp->dest.vertexId] = safetyvalue[x] + (temp->SD.safety_value);
                    G->path[temp->dest.vertexId]->next = G->path[x]; // HERE THE SHORTEST PATH OF EACH VERTEX IS GETTING MODIFIED //
                }
                if (visited[temp->dest.vertexId] == 0)
                {
                    visited[temp->dest.vertexId] = 1;
                    enqueue(q, temp->dest);
                }

                temp = temp->next;
            }
        }

        // the below code reverses the path list to print path in correct order (as the path list will be in reverse order for each vertex) //
        struct ListNode *tempii = G->path[dest.vertexId];
        struct ListNode *tempi = NULL;
        struct ListNode *node;
        while (tempii != NULL)
        {
            node = tempii->next;
            tempii->next = tempi;
            tempi = tempii;
            tempii = node;
        }
        //the above reverses the path list

        printf("\nThe Fastest path (with minimum congestion) between '%s' and '%s' in map is :\n\n", src.vertexName, dest.vertexName);
        printf("\t\t\t");
        while (tempi != NULL)
        {
            // the below code finds the vertexname for the respective vertexid as we used only the vertexids in path list //
            int vr = tempi->dest.vertexId;

            for (int itr = 0; itr < numPlaces; itr++)
            {
                if (itr == vr)
                    printf("%s", placesAndIDs[itr]);
            }

            tempi = tempi->next;
            if (tempi != NULL)
                printf("->");
        }
        printf("\n\nEstimated Distance to cover: %.2fm\n", length[dest.vertexId]);
        printf("Congestion Value: %.2f\n", cost[dest.vertexId]);
        printf("Safety Value: %.2f\n", safetyvalue[dest.vertexId]);
    }

    else
    {
        // finds the safest path if the flag is 1

        queue *q = initqueue();
        enqueue(q, src); // ADDING THE ELEMENTS TO THE QUEUE ACCORDING TO THE BFS //

        float cost[G->numVertices];
        float length[G->numVertices];
        float weights[G->numVertices];
        float safetyvalue[G->numVertices];

        for (int i = 0; i < G->numVertices; i++)
        {
            cost[i] = (float)INF; // INITIALIZES THE VALUE TO REACH EACH VERTEX TO INFINITY AS IT WAS NOT POSSIBLE TO REACH AT BEGINING //
            length[i] = 0;
            weights[i] = 0;
            safetyvalue[i] = 0.00f;
        }

        cost[src.vertexId] = 0;

        int visited[G->numVertices];
        for (int i = 0; i < G->numVertices; i++)
        {
            visited[i] = 0;
        }

        visited[src.vertexId] = 1;

        for (int i = 0; i < G->numVertices; i++)
        {
            G->path[i]->dest.vertexId = i;
            G->path[i]->next = NULL;
        }

        while (q->front != NULL)
        {
            // CHECKING ALL ELEMENTS ACCORDING TO THE BFS //
            int x = dequeue(q);
            visited[x] = 1;

            //struct ListNode *crawl = G->adjacencyList[x];

            struct ListNode *temp = G->adjacencyList[x];
            int i = 0;

            while (temp != NULL)
            {
                // CHECKS ALL ITS NEIGHBOURING VERTICES AND FINDS WHICH ONE IS SHORT
                float weight = 1.00f / (temp->SD.safety_value * 100);
                if ((x != temp->dest.vertexId) && (cost[temp->dest.vertexId] >= (cost[x] + weight)))
                {
                    cost[temp->dest.vertexId] = cost[x] + weight;
                    length[temp->dest.vertexId] = length[x] + temp->SD.length;
                    weights[temp->dest.vertexId] = weights[x] + temp->SD.weight;
                    safetyvalue[temp->dest.vertexId] = safetyvalue[x] + (temp->SD.safety_value);
                    G->path[temp->dest.vertexId]->next = G->path[x]; // HERE THE SHORTEST PATH OF EACH VERTEX IS GETTING MODIFIED //
                }
                if (visited[temp->dest.vertexId] == 0)
                {
                    visited[temp->dest.vertexId] = 1;
                    enqueue(q, temp->dest);
                }

                temp = temp->next;
            }
        }

        // the below code reverses the path list to print path in correct order
        struct ListNode *tempii = G->path[dest.vertexId];
        struct ListNode *tempi = NULL;
        struct ListNode *node;
        while (tempii != NULL)
        {
            node = tempii->next;
            tempii->next = tempi;
            tempi = tempii;
            tempii = node;
        }
        // the above code reverses the path list

        printf("\nThe safest path (with maximum safety value) between '%s' and '%s' in map is :\n\n", src.vertexName, dest.vertexName);
        printf("\t\t\t");
        while (tempi != NULL)
        {
            // the below code finds the vertexname for the respective vertexid as we used only the vertexids in path list //
            int vr = tempi->dest.vertexId;
            for (int itr = 0; itr < numPlaces; itr++)
            {
                if (itr == vr)
                    printf("%s", placesAndIDs[itr]);
            }

            tempi = tempi->next;
            if (tempi != NULL)
                printf("->");
        }
        printf("\n\nEstimated Distance to cover: %.2fm\n", length[dest.vertexId]);
        printf("Congestion Value:%.2f\n", weights[dest.vertexId]);
        printf("Safety Value: %.2f\n", safetyvalue[dest.vertexId]);
    }
    printf("\n");
}

// IN THE MIDDLE OF HIS JOURNEY IF HE FOUNDS TO CHANGE THE DATA OF A STREET DUE TO MARRIAGE PROSSESSIONS, THE BELOW CODE UPDATES THE DATA OF THE ORIGINAL GRAPH //
void UpdateStreet(struct Graph *G, vertex u, vertex v, int cars)
{
    if (u.vertexId == -1 || v.vertexId == -1)
        return;

    ListNode *temp;
    temp = G->adjacencyList[u.vertexId];
    while ((temp != NULL) && temp->dest.vertexId != v.vertexId)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Street does not exist\n");
        return;
    }
    temp->SD.num_cars = cars;
    temp->SD.traffic = 1 / (temp->SD.numLanes * 10 * 0.6) + 1 / temp->SD.speed_limit * 0.4 + temp->SD.num_cars * 1;
    temp->SD.safety_value = 1 / ((temp->SD.num_accidents * 0.8) + (0.2 * temp->SD.speed_limit / 10)); //Safe Routing
    temp->SD.weight = temp->SD.traffic * 0.6 + temp->SD.length * 0.4;                                 // here the weight of edge is calculated

    printf("Done\n");
    return;
}

void DeleteStreet(struct Graph *G, vertex u, vertex v)
{
    //**************** THIS FUNCTION DELETES THE EDGES STORED IN THE MEMORY ********//
    if (u.vertexId == -1 || v.vertexId == -1)
        return;

    ListNode *temp;
    ListNode *prev;
    temp = G->adjacencyList[u.vertexId];

    while ((temp != NULL) && (temp->dest.vertexId != v.vertexId))
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Street does not exist\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    return;
}
