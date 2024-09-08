This is a cpp program to create a schedule based off of the information included in the worker.txt file
Info in worker.txt:
Name, gender, days needed off

Data is read line by line from the text file, deliniated by spaces.
The first item is the name, then gender where 0 is female and 1 is male, and the rest are days off

There are a few rules when assigning shifts:
a) A worker may not work two shifts in a row
b) Any shift may not consist of just one gender

After worker info is read in, the program creates a schedule object. The schedule object consists of Shift objects, 
and some info about how it is structured (starting day, amount of days, holidays, etc)
Each Shift object contains its amount of hours and a vector of who is assigned to that shift.
When the Schedule object is made, it is then looped through and for each day in the schedule, the correct amount/type of shifts are added
After this, the Schedule is then looped through again, this time though each Shift is stopped at and workers are assigned
If there are not enough avaliable workers on a day, a message is printed to the user along with a list of who can still work that day.
For the shift with not enough workers, an empty set of brackets is left in its place.

When the program is assigning workers to a shift, it takes a few logical steps.
a) Remove any workers who requested the day off from avaliable workers
b) Reomve any workers who worked the previous shift form avaliable workers
c) Split avaliable workers into two groups, boys and girls
d) Sort each group by amount of hours worked, low to high (workers with the lowest hours are prioritized)
d) Depending on the size of these two groups, assign boys/girls to shifts as necessary
e) The program will do its best to alternate between 2 boys and 1 girl and vice versa

After all possible shifts have been assigned workers, the schedule is printed out
Informationa about each worker is also printed, like shifts working and hours working
