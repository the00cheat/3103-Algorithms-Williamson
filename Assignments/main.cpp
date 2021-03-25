/**
 * This program uses a "getch" function which means "get character".
 * However, getch does not print the character to the terminal, it
 * lets you decide what to do based on what character you are pressing.
 *
 * You can test which characters are being pressed using thier ascii values.
 *
 * An ascii table here should be helpful
 *      http://www.asciitable.com/
 *
 * Some integer values for some keys:
 *      LowerCase Letters   = 97(a) -> 122(z)
 *      UpperCase Letters   = 65(A) -> 90(Z)
 *      Enter Key           = 10
 *      Space Bar           = 32
 *
 *      Arrow Keys          = Have same values as some letters
 *                            so we can't distinguish between
 *                            the two (in this context).
 *
 * Code below is a basic example of using a "getch" function along with
 * searching an array of words for partial matches.
 *
 * https://repl.it/@rugbyprof/getchexample#main.cpp
 */

//#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include <fstream>
#include <iostream>
#include <vector>

#include <string>
#include <stdio.h>
#include <conio.h>

using namespace std;

/**
 * Description:
 *      Originally wrote this to count size of input file so
 *      I could allocate enough memory for an array of strings
 *      but I went with a vector below. But I'm keeping it and
 *      using it anyway!
 * Params:
 *      string file_name - file to get the line count
 *
 * Returns:
 *      int - line count
 */
int CountLines(string file_name) {
    ifstream inFile(file_name);
    return count(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>(), '\n');
}

/**
 * Description:
 *      Loads a file of strings (words, names, whatever) reading them in
 *      with one word per line. So words must be delimited by newlines '\n'
 * Params:
 *      string file_name - file to get the line count
 *
 * Returns:
 *      int - line count
 */
vector<string> LoadDictionary(string file_name) {
    ifstream fin;                            // file to get animal names
    int count = (CountLines(file_name) + 1); // get size of input file
    vector<string> array(count);             // allocate vector of correct size

    fin.open("dictionary.txt"); // open file for reading

    // knowing the size of the file lets us treat
    // it like an array without using .push_back(value)
    for (int i = 0; i < count; i++) {
        fin >> array[i];           // read in animals
        for (auto& c : array[i]) { // c++ 11 style loop
            c = tolower(c);        // lowercase the animal name
        }
    }
    return array;
}

/**
 * Description:
 *      Finds partial matches in an array of strings and returns them. It
 *      doesn't matter where in the string the match is.
 * Params:
 *      vector<string>  array       - array to search
 *      string          substring   - substring to search for in each word
 *
 * Returns:
 *      vector<string> - holding all the matches to substring
 */
vector<string> FindWords(vector<string> array, string substring) {
    vector<string> matches; // to hold any matches
    size_t found;           // size_t is an integer position of
                            // found item. -1 if its not found.

    for (int i = 0; i < array.size(); i++) { // loop through array
        found = array[i].find(substring);    // check for substr match
        if (found != string::npos) {         // if found >= 0 (its found then)
            matches.push_back(array[i]);     // add to matches
        }
    }

    return matches;
}


/*
    Struct Name: wordNode

    Description:
        A node that holds a string for a dictionary
        word and a pointer to the next wordNode

    Public Methods:
        string 					word
        wordNode* 			    Next

    Private Methods:
        None

    Usage:
        - Creates node for a Linked List

 */

struct wordNode
{
    wordNode* Next;
    string word;

    wordNode()
    {
        Next = NULL;
        word = "";
    }

};


/*
    Class Name: LinkedList

    Description:
        This class implements a simple Linked List consisting of wordNodes.
        The class has both Head and Tail wordNode pointers and a Size variable
        to keep track of the size of the list. This will serve as the basis for
        how we load up our dictionary words to be utilized later.

    Public Methods:
        - LinkedList() - default constructor
        - int Get_Size()
        - void Insert_Data(wordNode* entry)
        - vector<string> Find(string typed)
        - void Print()

    Private Methods:
        - No Private or Protected methods

    Usage:
        - Load up a linked list of wordNodes holding dicitonary words
        - Hold the dictionary data for traversing and searching
        - Print the results
 */

typedef std::vector<std::string> vs;
class LinkedList
{
protected:
    wordNode* head;
    wordNode* tail;
    int size;


public:

    /**********************************************************************
    *                                                                     *
    * LinkedList                                                          *
    *                                                                     *
    * Description:                                                        *
    *        Default Constructor                                          *
    *        Node structure for a linked list, created using our struct   *
    *                                                                     *
    * Method Variables:                                                   *
    *        head                                                         *
    *        tail                                                         *
    *        size                                                         *
    *                                                                     *
    * Use:                                                                *
    *   Create a linked list within our class                             *
    *                                                                     *
    **********************************************************************/

    LinkedList()
    {
        head = NULL;
        tail = NULL;
        size = 0;
    }

    /*******************************************************************
    *                                                                  *
    * print                                                            *
    *                                                                  *
    * Description:                                                     *
    *        Prints the linked list                                    *
    *                                                                  *
    * Method Variables:                                                *
    *        None                                                      *
    *                                                                  *
    * Return:                                                          *
    *   NULL                                                           *
    *                                                                  *
    *******************************************************************/

    void print()
    {

        wordNode* current = head;

        while (current)
        {
            cout << current->word;
            cout << std::endl;
            current = current->Next;
        }

    }

    /*******************************************************************
    *                                                                  *
    * getSize                                                          *
    *                                                                  *
    * Description:                                                     *
    *        Gets the size of the linked list                          *
    *                                                                  *
    * Method Variables:                                                *
    *        None                                                      *
    *                                                                  *
    * Return:                                                          *
    *   size                                                           *
    *                                                                  *
    *******************************************************************/

    int getSize()
    {
        return size;
    }

    /*******************************************************************
    *                                                                  *
    * insert                                                           *
    *                                                                  *
    * Description:                                                     *
    *        Adds a word to the linked list                            *
    *                                                                  *
    * Method Variables:                                                *
    *        None                                                      *
    *                                                                  *
    * Return:                                                          *
    *   NULL                                                           *
    *                                                                  *
    *******************************************************************/

    void insert(wordNode* word)
    {
        if (!head)
        {
            head = tail = word;
        }
        else
        {
            tail->Next = word;
            tail = word;
        }

        size++;
    }

    /*******************************************************************
    *                                                                  *
    * search                                                           *
    *                                                                  *
    * Description:                                                     *
    *        searches through the liked list to find a matching word   *
    *                                                                  *
    * Method Variables:                                                *
    *        vector <string> (vs) results                              *
    *                                                                  *
    * Return:                                                          *
    *   vector <string> (vs) results                                   *
    *                                                                  *
    *******************************************************************/

    vs search(string userInput)
    {
        cout << "Searching for match" << endl;

        vs results;


        wordNode* current = head;

        while (current)
        {
            string found = "";

            found = current->word;

            int length = userInput.length();

            if (found.substr(0, length) == userInput)
            {
                results.push_back(found);
            }

            current = current->Next;
        }

        return results;
    }
};





int main() {
    char k;                 // holder for character being typed
    string input = "";       // var to concatenate letters to
    vs wordList;           // Location to read words into 
    vs matches;            // Matches found in the dictionary
    LinkedList dictionary;


    ifstream fin;           // File in
    ofstream fout;          // File out
    fin.open("dictionary.txt");

    Timer timer;   // create a timer
    timer.Start(); // start it

    while (!fin.eof())
    {
        // Add words to the vector wordList
        string tempWord;
        fin >> tempWord;

        wordList.push_back(tempWord);

    }


    timer.End(); // end the current timer

    // print out how long it took to load the dictionary file
    cout << "It took " << timer.Seconds() << " seconds to read in the data" << endl;
    cout << "It took " << timer.MilliSeconds() << " milliseconds to read in the data" << endl << endl;

    

    timer.Start();      // start it

    // Add words to the linked list
    for (int i = 0; i < wordList.size(); i++)
    {
        wordNode* temp = new wordNode;
        temp->word = wordList[i];
        dictionary.insert(temp);
    }

    timer.End(); // end the current timer

    // print out how long it took to load the linked list dictionary
    cout << "It took " << timer.Seconds() << " seconds to read the data into the linked list" << endl;
    cout << "It took " << timer.MilliSeconds() << " milliseconds to read the data into the linked list" << endl << endl;
    cout << "Type keys and watch what happens. Type capital Z to quit." << endl << endl;

    // While capital Z is not typed keep looping
    while ((k = _getch()) != 'Z')
    {

        // Tests for a backspace and if pressed deletes
        // last letter from "word".
        if ((int)k == 127 || k == 8)
        {
            if (input.size() > 0)
            {
                input = input.substr(0, input.size() - 1);
            }
        }
        else
        {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k))
            {
                cout << "Letters only!" << endl;
                continue;
            }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97)
            {
                k += 32;
            }
            input += k; // append char to word
        }

        // Find any animals in the array that partially match
        // our substr word
        timer.Start(); // start it
        matches = dictionary.search(input);
        timer.End(); // end the current timer
        cout << timer.Seconds() << " seconds to read in and print" << endl;
        cout << timer.MilliSeconds() << " milli to read in and print" << endl;

        if (input == "")
        {
            // If "word" is empty, do not print the dictionary
        }
        else if ((int)k != 32)
        {
            // if k is not a space print it
            cout << "Keypressed: " << termcolor::on_yellow << termcolor::blue << k << " = " << (int)k << termcolor::reset << endl;
            cout << "Current Substr: " << termcolor::red << input << termcolor::reset << endl;
            cout << "Word found: ";
            cout << termcolor::green;
            // This prints out all found matches
            for (int i = 0; i <10; i++) {
                std::cout << matches[i] << " ";
            }
            std::cout << termcolor::reset << endl
                << std::endl;
        }

    }

    return 0;
}