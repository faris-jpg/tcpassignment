#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <sstream>
#include <fstream>

using namespace std;

void makeLower(string &str)
{

    for (int i = 0; i < str.length(); i++) // iterates through characters in string
    {
        str[i] = tolower(str[i]); // converts each to lower case
    }
}

void seperateWords(string str, vector<string> &commandWords)
{
    stringstream inputStream(str);
    string word;
    while (inputStream >> word) // seperates words by spaces
    {
        makeLower(word);              // so the program will not be case sensitive
        commandWords.push_back(word); // save all the commands in a vector
    }
}

int findMode(string command)
{
    vector<string> modeList = {"load",
                               "store",
                               "clone",
                               "html",
                               "min",
                               "max",
                               "median",
                               "mean",
                               "variance",
                               "stdv",
                               "add",
                               "sub",
                               "corr",
                               "regression",
                               "show",
                               "titles",
                               "report",
                               "rows",
                               "columns",
                               "vhisto",
                               "hhisto",
                               "sort",
                               "help",
                               "oddrows",
                               "evenrows",
                               "primes",
                               "man",
                               "delete",
                               "insert",
                               "replace",
                               "exit"};

    // check if command == any of the modes,
    //  if it does, return the index of the mode + 1
    //  if it doesnt, return -1
    for (int i = 0; i < modeList.size(); i++)
    {
        if (command == modeList[i])
        {
            return i + 1;
        }
    }
    return -1;
}

bool checkSyntax(vector<string> &commandWords, int modeNumber, int numColumns)
{
    int numWords = commandWords.size();
    switch (modeNumber)
    {
    case 1: // load
    case 2: // store
        return (numWords == 2);
    case 3: // clone
        return (numWords == 3);
    case 4: // html
        return (numWords == 2 || numWords == 3);
    case 5:  // min
    case 6:  // max
    case 7:  // median
    case 8:  // mean
    case 9:  // variance
    case 10: // stdv
        return (numWords == 1 || numWords == 2);
    case 11: // sum
    case 12: // diff
    case 13: // corr
        return (numWords == 3);
    case 14: // regression
        return (numWords == 2);
    case 15: // show
        return (numWords == 1 || numWords == 2);
    case 16: // titles
    case 17: // report
    case 18: // rows
    case 19: // columns
        return (numWords == 1);
    case 20: // vhisto
    case 21: // hhisto
    case 22: // sort
        return (numWords == 2);
    case 23: // help
        return (numWords == 1);
    case 24: // oddrows
    case 25: // evenrows
        return (numWords == 1);
    case 26: // primes
        return (numWords == 2);
    case 27: // delete
        if (commandWords[1] == "occurrence")
            return (numWords == 4);
        else if (commandWords[1] == "column" || commandWords[1] == "row")
            return (numWords == 3);
        else
            return false;
    case 28: // insert
        return (numWords == numColumns);
    case 29: // replace
        return (numWords == 3 || numWords == 4);
    default:
        return false;
    }
}

struct myProgram
{
    int numWords, numColumns, numRows, modeNumber;
    string command;
    vector<string> commandWords, columnNames, columnTypes, modeList;
    vector<vector<string>> table;
    bool correctSyntax;

    void get()
    {
        commandWords = {};
        cout << "$ ";
        getline(cin, command); // gets command
        seperateWords(command, commandWords);
        numWords = commandWords.size();
        modeNumber = findMode(commandWords[0]);
        correctSyntax = checkSyntax(commandWords, modeNumber, numColumns);
    }

    void runner()
    {
        switch (modeNumber)
        {
        case 1: // load
            load();
            break;
        case 2: // store
            store();
            break;
        case 3: // clone
            clone();
            break;
        case 4: // html
            html();
            break;
        case 5: // min
            findMin();
            break;
        case 6: // max
            findMax();
            break;
        case 7: // median
            findMedian();
            break;
        case 8: // mean
            findMean();
            break;
        case 9: // variance
            variance();
            break;
        case 10: // stdv
            stdv();
            break;
        case 11: // sum
            sum();
            break;
        case 12: // diff
            difference();
            break;
        case 13: // corr
            corr();
            break;
        case 14: // regression
            regression();
            break;
        case 15: // show
            show();
            break;
        case 16: // titles
            titles();
            break;
        case 17: // report
            report();
            break;
        case 18: // rows
            rows();
            break;
        case 19: // columns
            columns();
            break;
        case 20: // vhisto
            vhisto();
            break;
        case 21: // hhisto
            hhisto();
            break;
        case 22: // sort
            sort();
            break;
        case 23: // help
            help();
            break;
        case 24: // oddrows
            oddrows();
            break;
        case 25: // evenrows
            evenrows();
            break;
        case 26: // primes
            primes();
            break;
        case 27:
            man();
            break;
        case 28: // delete
            delete_();
            break;
        case 29: // insert
            insert();
            break;
        case 30: // replace
            replace();
            break;
        case 31: // exit
            cout << "exiting..." << endl;
            break;
        }
    }
    void load()
    {
        if (!correctSyntax)
        {
            system("Color 04");
            cout << "syntax error" << endl
                 << "load <filename.csv>" << endl;
            return;
        }
        string argument = commandWords[1];
        for (int i = 0; i < argument.length(); i++)
        {
            if (argument[i] == '.')
            {
                string extension = argument.substr(i, argument.length());
                if (extension != ".csv")
                {
                    system("Color 04");
                    cout << "invalid file type" << endl
                         << "load <filename.csv>" << endl;
                    return;
                }
                else
                {
                    break;
                }
            }
        }
        ifstream inputFile(argument);
        if (!inputFile.is_open())
        {
            system("Color 04");
            cout << "file cannot be opened" << endl;
            return;
        }
        else
        {
            inputFile >> numColumns >> numRows;
            string row;
            int rowCounter = 0;
            while (getline(inputFile, row))
            {
                vector<string> rowVector;
                stringstream rowStream(row);
                string word;
                while (getline(rowStream, word, ','))
                {
                    if (word[0] == ' ')
                        word = word.substr(1, word.length());
                    makeLower(word);
                    if (rowCounter == 0)
                    {
                        columnNames.push_back(word);
                    }
                    else if (rowCounter == 1)
                    {
                        columnTypes.push_back(word);
                    }
                    else
                    {
                        rowVector.push_back(word);
                    }
                }
                if (rowCounter > 1)
                {
                    table.push_back(rowVector);
                }
                rowCounter++;
            }
            system("Color 02");
            cout << argument << " has been loaded" << endl;
            // print all data
            for (auto a : table)
            {
                for (auto b : a)
                {
                    cout << b << " ";
                }
                cout << endl;
            }
        }
    }
    void show() {}
    void store() {}
    void clone() {}
    void html() {}
    void findMin() {}
    void findMax() {}
    void findMedian() {}
    void findMean() {}
    void variance() {}
    void stdv() {}
    void sum() {}
    void difference() {}
    void corr() {}
    void regression() {}
    void titles() {}
    void report() {}
    void rows() {}
    void columns() {}
    void vhisto() {}
    void hhisto() {}
    void sort() {}
    void help() {}
    void oddrows() {}
    void evenrows() {}
    void primes() {}
    void man(){}
    void delete_() {}
    void insert() {}
    void replace() {}
};
int main()
{
    myProgram program;
    while (program.command != "exit")
    {
        program.get();
        program.runner();
    }
    return 0;
}