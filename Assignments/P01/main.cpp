///////////////////////////////////////////////////////////////////////////////
//                   
// Author:           John Williamson
// Email:            john.c.williamson88@gmail.com
// Label:            P01
// Title:            Array Based Stack Example
// Course:           2143
// Semester:         Fall 2020
//
// Description:
//       Example implementation of an array based stack that holds integers.
//
// Usage:
//       Nothing special right now.
//
// Files:            
//       None
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/**
 * Stack
 *
 * Description:
 *      Integer array based stack implementation
 *
 * Public Methods:
 *      - Stack()
 *      - Stack(int)
 *      - void Push()
 *      - int Pop()
 *      - bool empty()
 *      - bool full()
 *      - void Print()
 *
 * Private Methods:
 *      - None
 *
 * Usage:
 *
 *  Stack S;
 *  S.Push(80);
 *  S.Push(90);
 *  S.Print();
 *  int x = S.Pop();
 *
 */
class Stack 
{
private:
    int* stack;       //array pointer
    int capacity;     //max stack size
    int top;          //current top (index)
    int size;        //current num items
    int minimumSize;  //minimum size of array
    int maximumSize;  //maximum size of array
public:
    /**
     * Stack:
     *    Constructor.
     * Params:
     *    void
     *
     * Returns:
     *     Void
     */
    Stack() 
    {
        capacity = 10;          // set array size
        stack = new int[capacity];  // allocate new memory
        top = -1;               // initialize top of stack
        size = 0;               // set stack to empty
        minimumSize = 10;
        maximumSize = 0;
    }

    /**
     * Stack:
     *    Constructor.
     * Params:
     *    int : capacity
     *
     * Returns:
     *     Void
     */
    Stack(int cap) 
    {
        capacity = cap;             // set array size      
        stack = new int[capacity];  // allocate new memory
        top = -1;                  // initialize top of stack
        size = 0;                  // set stack to empty
        minimumSize = 10;         // minmum size of array
        maximumSize = 0;          // maximum size of array
    }

    /**
     * Push:
     *    Push item onto stack.
     * Params:
     *    int : data
     *
     * Returns:
     *     Void
     */
    void Push(int data) 
    {
        if (top==capacity-1)                        //checking if array is already full
        //resizes if array full
        {
            cout << " + : " << capacity << "->" << capacity *2 <<endl;
            int* newStack = new int[capacity * 2];
            for (int i = 0; i < capacity; i++)
            {
                newStack[i] = stack[i];     //copy old array items to new array
            }
            delete[] stack;                    //delete old array
            stack = newStack;               //adjust pointer to new array
            capacity = capacity * 2;           //change capacity to twice original size
            if (maximumSize < capacity)
            {
                maximumSize = capacity;   //set new max size of array
            }
        }
        //normal action if array isn't full
        top++;              // move top of stack up
        size++;             // increment size
        stack[top] = data;      // add item to array
    }

    /**
     * Pop:
     *    remove item from stack.
     * Params:
     *    void
     *
     * Returns:
     *     int
     */
    int Pop()
    {
        if (top==-1)
        {
            cout << "Error: Stack empty!\n";
                return -1;
        }
        if (capacity != minimumSize && size <= capacity / 2)
        {
            cout << " - : " << capacity << "->" << capacity / 2 << endl;
            int* newStack = new int[capacity * 2];
            for (int i = 0; i < capacity; i++)
            {
                newStack[i] = stack[i];     //copy old array items to new array
            }
            delete[] stack;                    //delete old array
            stack = newStack;               //adjust pointer to new array
            capacity = capacity / 2;
        }
        int data = stack[top];  // pull item from stack
        top--;              // shrink the stack
        size--;             // update our size  
        return data;        // send item back
    }

    /**
     * Print:
     *    Used so we can inspect our stack.
     * Params:
     *    void
     *
     * Returns:
     *     void
     */
    void Print() {
        for (int i = top; i >= 0; i--) {
            cout << stack[i] << endl;
        }
    }

    /**
 * Output:
 *    Outputs starting, max, and ending size of array
 * Params:
 *    void
 *
 * Returns:
 *     void
 */

    void Output()
    {
        ofstream outfile;                       //Create ouput file
        outfile.open("output.txt");

        outfile << "Name: John Williamson" << endl;
        outfile << "Program : P01" << endl;
        outfile << "Date : 15 Sep 2020\n" << endl;

        outfile << "Starting size: " << minimumSize << endl;
        outfile << "Max size: " << maximumSize << endl;
        outfile << "Ending size: " << capacity << endl;

        outfile.close();

    }

    /**
     * Overloaded ostream <<
     *    Lets us print a stack using cout
     * Params:
     *    ostream &os   : instance of ostream passed in by reference
     *    const Stack   : instance of stack passed in using const so
     *                    it cannot be changed
     *
     * Returns:
     *     ostream
     */
    friend ostream& operator<<(ostream& os, const Stack s) {
        for (int i = s.top; i >= 0; i--) {
            os << s.stack[i] << endl;
        }
        return os;
    }
};

int main()
{
    cout << "Name: John Williamson" <<endl;
    cout << "Program : P01" << endl;
    cout << "Date : 15 Sep 2020" << endl;

    Stack Stack_1;           // calls default constructor
    ifstream infile;                        //read input file
    infile.open("input.txt");
    string PushOrPop;                    
    int value;                              
    while (infile >> PushOrPop)            
    {
        if (PushOrPop == "push")            //reads push
        {
            infile >> value;                 
            Stack_1.Push(value);            //pushes value to stack
        }
        if (PushOrPop == "pop")            //reads pop
        {
            Stack_1.Pop();                 //pops that shit
        }
    }
   
    infile.close();                         //close file

    Stack_1.Output();



    return 0;
}
