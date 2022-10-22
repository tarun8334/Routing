## First run the makefile.

## Then use ./maps to run the code.

## Instructions after Compilation:-
 
1. After the compilation of the program ,user first need to enter the input in the first line I  the form of :-
(Integer1) (integer2)  -- format of input
Here, Integer1 = number of places.
     	Integer2 = number of street.

         
2. Then user has to enter number of inputs corresponding to the number of streets .
Inputs must be in form of (integer2) separated lines.
Each line has format-
(string) (string) (float) (int) (int) (int) (int)
(Maximum string length = 50)
Format is:- (source_vertexName)  (dest_vertexName) (street length) (numLanes)  (num_cars)  (num_accidents)  (speed_limit)


Assuming the Graph (City map) is connected and undirected.


3.User enters one of the following choices
   1.FIND THE SAFEST PATH
   2.FIND THE FASTEST PATH
   3.DELETE STREET IN THE CITY MAP
   4.CHANGE THE STREET DATA FOR ANY STREET
   5.EXIT
   Enter you choice(1/2/3/4/5/6)

4. If user enters choice 1 
User now need the enter from where he has to start and where he has to go .
The input format would be:-
(string) (string)
*/
(starting_location) (ending_location)
*/
 The program will give the fastest path between the entered locations

5. If user enters choice 2 
User now need the enter from where he has to start and where he has to go .
The input format would be:-
(string) (string)
*/
(starting_location) (ending_location)
*/
 The program will give the safest path between the entered locations

6. If the user enters choice 3
Now the user enters the starting and ending point of the street he wishes to delete

The input format will be
*/
(starting_location) (ending_location)
*/

The program will remove the street from the city map if any such street exists, if not it prints "no such street exits"
and continues.

7. If the user enters choice 4
Now the user enters the starting and ending point of the street he wishes to change data for and the only data he can change
for a street will be the average number of cars on the street per hour (that can change with time maybe due to some procession/accident/construction work etc.)

The input format will be
*/
(starting_location) (ending_location) (num_cars)
*/

The program will change the data for the street in the city map if any such street exists, if not it prints "no such street exits" and continues.

8.If the user enters choice 5
The user exits from the program


For the test cases we use a testcase generator that is a block of code which when given the numPlaces and numStreets gives us
the paramters for numStreets different streets in appropriate range.


Here is a sample test case 
9 14
home b 625 4 137 6 93
b c 126 1 185 9 23
c d 961 4 22 9 95
d exam 590 2 92 4 98
exam f 957 2 167 9 62
f g 886 4 127 5 56
g h 246 1 275 9 64
h home 123 4 247 3 70
h b 578 1 188 3 83
h i 765 2 225 2 100
g i 733 3 119 1 75
i c 119 2 98 2 45
f c 659 1 275 9 57
f d 385 1 113 9 61
1
home exam
2
home exam
3
f g
4
h i 500
1
home exam
5


