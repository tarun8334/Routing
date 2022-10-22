#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int getVertexID(vertex v)
{
    for (int i = 0; i < numPlaces; i++)
    {
        if (strcmp(placesAndIDs[i], v.vertexName) == 0)
            return i;
    }

    printf("**No such place exists in the city map**\n");
    return -1;
}

int main(void)
{
    printf("Enter the number of places(nodes) and number of streets(edges) in the city map\n");
    scanf("%d %d", &numPlaces, &numStreets);

    struct Graph *City = CreateGraph(numPlaces);

    int vertexCount = 0;

    printf("Enter the data for each street\n");

    for (int i = 0; i < numStreets; i++)
    {
        vertex src, dest;
        struct StreetData SD; // asking user about the details of each street

        scanf("%s %s %f %d %d %d %d", src.vertexName, dest.vertexName, &SD.length, &SD.numLanes, &SD.num_cars, &SD.num_accidents, &SD.speed_limit);

        // the following code gives unique vertexid for each unique vertexname entered

        //Giving vertexId to srcVertex

        if (findInVertexArray(placesAndIDs, src.vertexName, vertexCount) == 0)
        {
            strcpy(placesAndIDs[vertexCount], src.vertexName);
            src.vertexId = vertexCount;
            vertexCount++;
        }

        else
        {
            for (int i = 0; i < numPlaces; i++)
            {
                if (strcmp(placesAndIDs[i], src.vertexName) == 0)
                    src.vertexId = i;
            }
        }

        //Giving vertexId to destVertex

        if (findInVertexArray(placesAndIDs, dest.vertexName, vertexCount) == 0)
        {
            strcpy(placesAndIDs[vertexCount], dest.vertexName);
            dest.vertexId = vertexCount;
            vertexCount++;
        }

        else
        {
            for (int i = 0; i < numPlaces; i++)
            {
                if (strcmp(placesAndIDs[i], dest.vertexName) == 0)
                    dest.vertexId = i;
            }
        }

        // calculation of traffic, safety_value and weight(Conegestion) of each street
        SD.traffic = 1.00f / (SD.numLanes * 10 * 0.6) + 1.00f / SD.speed_limit * 0.4 + SD.num_cars * 1;
        SD.safety_value = 1.00f / ((SD.num_accidents * 0.8) + (0.2 * SD.speed_limit / 10)); //Safe Routing
        SD.weight = SD.traffic * 0.6 + SD.length * 0.4;                                     //Congestion

        AddStreet(City, src, dest, SD);
    }

    //-------------------------------------------------City graph is made------------------------------------------------//

    int choice;

    do
    {

        printf("\n1.FIND THE SAFEST PATH\n2.FIND THE FASTEST PATH\n3.DELETE STREET IN THE CITY MAP\n");
        printf("4.CHANGE THE STREET DATA FOR ANY STREET\n5.EXIT\n\nEnter you choice(1/2/3/4/5)\n");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            printf("Enter source and destination\n");
            ListNode *temp;
            vertex finalSource, finalDestination;
            scanf("%s %s", finalSource.vertexName, finalDestination.vertexName);

            finalSource.vertexId = getVertexID(finalSource);
            finalDestination.vertexId = getVertexID(finalDestination);

            getFastestPath(City, finalSource, finalDestination, 1);

            break;
        }
        case 2:

        {
            printf("Enter source and destination\n");
            ListNode *temp;
            vertex finalSource, finalDestination;
            scanf("%s %s", finalSource.vertexName, finalDestination.vertexName);

            finalSource.vertexId = getVertexID(finalSource);
            finalDestination.vertexId = getVertexID(finalDestination);

            getFastestPath(City, finalSource, finalDestination, 0);
            break;
        }

        case 3:
        {
            vertex dSource, dDestination;
            printf("Enter the source and destination of the street to be deleted\n");
            scanf("%s %s", dSource.vertexName, dDestination.vertexName);
            dSource.vertexId = getVertexID(dSource);
            dDestination.vertexId = getVertexID(dDestination);
            DeleteStreet(City, dSource, dDestination);
            break;
        }
        case 4:

            printf("Enter number of streets for which you want to change data for :-\n");
            int changeStreetsNum = 0;

            scanf("%d", &changeStreetsNum);

            printf("Enter the changed streets' data (source destination (average_number_of_cars_on_the_street_per_hour))\n");

            for (int i = 0; i < changeStreetsNum; i++)
            {
                vertex srcChange, destChange;
                int carsNum;
                scanf("%s %s %d", srcChange.vertexName, destChange.vertexName, &carsNum);
                srcChange.vertexId = getVertexID(srcChange);
                destChange.vertexId = getVertexID(destChange);
                UpdateStreet(City, srcChange, destChange, carsNum);
            }

            //printf("Done\n");
            break;

        case 5:
            exit(0);

        default:
            printf("INVALID CHOICE, ENTER AGAIN");
        }

    } while (choice != 5);
}
