# CS300-Week-8
Week 8 Portfolio Assignment

What was the problem you were solving in the projects for this course?

- This project required us to create a data structure that ABCU advisors could use to sort courses in numerical order, look up courses by course number, and to look at applicable prerequisites when necessary.
  We also had to do runtime analysis on the different data structures and using that analysis, select the best data structure to suit ABCU's requirements and explain why we think so. The specific requirements were:

  Input: Design code to correctly read the course data file. The program you submit should be a command-line program written in C++. The program should prompt the user to ask for the file name that contains the course data and read that file into course objects that are stored in your chosen data structure. Your data structure will hold course objects.

  
Menu: Design code to create a menu that prompts a user for menu options. The menu should include the following options:

Option 1: Load the file data into the data structure. Note that before you can print the course information or the sorted list of courses, you must load the data into the data structure. 
Option 2: Print an alphanumeric list of all the courses in the Computer Science department.
Option 3: Print the course title and the prerequisites for any individual course.
Option 9: Exit the program.


Loading Data Structure: Develop working code to load data from the file into the data structure.


Course List: Develop working code to sort and print out a list of the courses in the Computer Science program in alphanumeric order, including all math courses. To print out a course list, use the pseudocode you created previously to guide your work. Then create code that will allow advisers to print a course list in alphanumeric order. Remember that this code should do the following actions:


Sort the course information alphanumerically from lowest to highest.
Print the sorted list to a display.
Course Information: Develop working code to print course information. This code should allow users to look up a course and print out information about its title and prerequisites. Your program must prompt the user to enter the course number. You will then print the name of the course and the prerequisite course numbers and titles. See Project Two Sample Program Output in the Supporting Documents section.
Industry Standard Best Practices: Apply industry standard best practices in code design. Your program should display an error message when user input does not fall within the parameters. You should also use in-line comments and appropriate naming conventions to enhance readability and maintainability.

  
How did you approach the problem? Consider why data structures are important to understand.

- I honestly took what I could from my previous BST pseudocode assignment and built off of that based on the feedback I received. I selected the binary search tree data structure because of its key access to look up courses which performs faster than a linked list, and because each once the tree is implemented, you can use in-order traversal to print the courses alphabetically, saving you from having to create a separate sorting method.
  In hash tables you do have a "bucket" for courses to be assigned to, but in-order traversal is not implemented in a hash table as it is unsorted. A vector is just not as efficient as it would have to read through every entry to find our desired course, which is a hit to the program’s runtime.

  The number of objects you are working with makes a difference in which data structure you want to choose, as well as whether you plan to add or remove objects in the future, sorting, etc. The ABCU Advisor assignment guidelines seemed to be best implemented with a Binary Search Tree over a hash table or vector.
  
How did you overcome any roadblocks you encountered while going through the activities or project?

- Most of my roadblocks throughout this course I conquered by reviewing instructor feedback and re-referencing the Zybooks material when necessary. My largest roadblock, which has been ever present throughout my CS career, has been how my code interacts with files. I had a decent base in my pseudocode, and needed to watch some video tutorials and read up some more the figure out how to fill it in and get it working.

How has your work on this project expanded your approach to designing software and developing programs?

- Working on this project made me consider memory management and fastest runtime possible. Previously, I had never stopped to consider that; having the timers on our assignments adds a great visual element for me to help see the differences in using different data structures. After this class, I will definitely be thinking a bit more in detail on how I design my program instead of just “write code that does what I want”.
  
How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?

- I feel that I've become slightly better when it comes to writing adaptable code. My evidence from this project was implementing the toUpper function. Once the function was implemented at the very end, I only had to make minor changes to small portions of my code to make it all fit together with no issues. I think readability is sufficient for being packed into a single .cpp file, although I prefer using separate .cpp and header files myself. As for maintenance, courses can be added to the program by ABCU Advisors easily and will be automatically sorted into the binary tree (course list) upon insertion
