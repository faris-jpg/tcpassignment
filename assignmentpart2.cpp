#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>

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
    // returns a number corresponding to the mode, to allow for switches instead of if else
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
    // serves to check if the number of words is correct for each command.
    //  leaves error message to the command to output
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

int checkColumn(string column, vector<string> columnNames)
{
    // loops through all the column names to find one that matches, and returns the index.
    //  if it doesnt exist in the list, return -1
    for (int i = 0; i < columnNames.size(); i++)
    {
        if (column == columnNames[i])
        {
            return i;
        }
    }
    return -1;
}

float findMean(vector<vector<string>> table, int columnNumber)
{
    // finds the mean of a column
    float sum = 0;
    for (int i = 0; i < table.size(); i++)
    {
        sum += stoi(table[i][columnNumber]);
    }
    return sum / table.size();
}

float findVariance(vector<vector<string>> table, int columnNumber)
{
    // finds the variance of a column
    //  finds the mean of the column
    //  finds the difference between each number and the mean
    //  squares that
    //  finds the mean of the squared differences
    float mean, sum = 0;
    mean = findMean(table, columnNumber);
    sum = 0;
    for (int i = 0; i < table.size(); i++)
    {
        sum += pow(stoi(table[i][columnNumber]) - mean, 2);
    }
    return sum / table.size();
}

vector<int> sortColumn(vector<int> &column)
{ // as some functions need a sorted column (median) this function sorts a column
    // sorts it by going through each index,
    //  finding the minimum value in the rest of the column,
    //  and adding it to a new vector
    // selection sort (kinda)
    vector<int> sortedColumn;
    int min, minIndex;
    for (int i = 0; i < column.size(); i++)
    {
        min = (column[i]);
        minIndex = i;
        for (int j = i + 1; j < column.size(); j++)
        {
            if ((column[j]) < min)
            {
                min = (column[j]);
                minIndex = j;
            }
        }
        sortedColumn.push_back(min);
        column[minIndex] = column[i];
    }
    return sortedColumn;
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
        getline(cin, command);                                             // gets command
        seperateWords(command, commandWords);                              // seperates words by spaces and saves them in a vector
        numWords = commandWords.size();                                    // saves the number of words in the command
        modeNumber = findMode(commandWords[0]);                            // finds the mode number of the command
        correctSyntax = checkSyntax(commandWords, modeNumber, numColumns); // checks if the syntax is correct
    }

    void runner()
    {
        // uses mode number to run the correct function
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
            mean();
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
        case -1:
            system("Color 04");
            cout << "invalid command" << endl;
            break;
        }
    }
    void load()
    {
        if (!correctSyntax)
        {
            // if the syntax is incorrect, output error message
            system("Color 04");
            cout << "syntax error" << endl
                 << "load <filename.csv>" << endl;
            return;
        }
        string argument = commandWords[1];
        for (int i = 0; i < argument.length(); i++)
        {
            // checks if a file was given
            if (argument[i] == '.')
            {
                // checks if the file is a csv file
                string extension = argument.substr(i, argument.length()); // gets the extension of the file
                if (extension != ".csv")
                {
                    // outputs error if not a csv file
                    system("Color 04");
                    cout << "invalid file type" << endl
                         << "load <filename.csv>" << endl;
                    return;
                }
                else
                {
                    // if the file is a csv file, break out of the loop
                    break;
                }
            }
        }
        ifstream inputFile(argument);
        if (!inputFile.is_open())
        {
            // if the file cannot be opened, output error message
            system("Color 04");
            cout << "file cannot be opened" << endl;
            return;
        }
        else
        {
            inputFile >> numColumns >> numRows; // gets the number of columns and rows
            string row;
            int rowCounter = -1;
            while (getline(inputFile, row))
            {
                vector<string> rowVector;
                stringstream rowStream(row);
                string word;
                while (getline(rowStream, word, ','))
                { // seperates the words by commas
                    if (word[0] == ' ')
                        word = word.substr(1, word.length()); // removes the space at the beginning of the word
                    makeLower(word);
                    if (rowCounter == 0)
                    { // if it is the first row, save the column names
                        columnNames.push_back(word);
                    }
                    else if (rowCounter == 1)
                    { // if it is the second row, save the column types
                        columnTypes.push_back(word);
                    }
                    else
                    { // if it is any other row, save the data
                        rowVector.push_back(word);
                    }
                }
                if (rowCounter > 1)
                { // if it is any other row, save the data
                    table.push_back(rowVector);
                }
                rowCounter++;
            }
            system("Color 02");
            cout << argument << " has been loaded" << endl;
            inputFile.close(); // closes the file
        }
    }
    void show() {}
    void store() {}
    void clone() {}
    void html() {}
    void findMin()
    {
        if (!correctSyntax)
        { // if the syntax is incorrect, output error message
            system("Color 04");
            cout << "syntax error" << endl
                 << "min <column> (optional)" << endl;
            return;
        }
        int min;
        if (numWords == 1)
        {
            for (int i = 0; i < numColumns; i++)
            {
                if (columnTypes[i] == "number")
                { // checks if the column is of type number
                    min = stoi(table[0][i]);
                    for (int j = 1; j < numRows; j++)
                    {
                        if (stoi(table[j][i]) < min)
                        {
                            min = stoi(table[j][i]);
                        }
                    }
                    cout << "minimum of column " << columnNames[i]
                         << " is " << min << endl;
                }
            }
        }
        else
        {
            int columnNumber = checkColumn(commandWords[1], columnNames);
            if (columnNumber == -1)
            { // checks if the column exists
                system("Color 04");
                cout << "column does not exist" << endl;
                return;
            }
            else if (columnTypes[columnNumber] != "number")
            { // checks if the column is of type number
                system("Color 04");
                cout << "column is not of type number" << endl;
                return;
            }
            else
            {
                min = stoi(table[0][columnNumber]);
                for (int j = 1; j < numRows; j++)
                {
                    if (stoi(table[j][columnNumber]) < min)
                    {
                        min = stoi(table[j][columnNumber]);
                    }
                }
                cout << "minimum of column " << columnNames[columnNumber]
                     << " is " << min << endl;
            }
        }
    }
    void findMax()
    {
        if (!correctSyntax)
        {
            system("Color 04");
            cout << "syntax error" << endl
                 << "max <column> (optional)" << endl;
            return;
        }
        int max;
        if (numWords == 1)
        {
            for (int i = 0; i < numColumns; i++)
            {
                if (columnTypes[i] == "number")
                {
                    max = stoi(table[0][i]);
                    for (int j = 1; j < numRows; j++)
                    {
                        if (stoi(table[j][i]) > max)
                        {
                            max = stoi(table[j][i]);
                        }
                    }
                    cout << "maximum of column " << columnNames[i]
                         << " is " << max << endl;
                }
            }
        }
        else
        {
            int columnNumber = checkColumn(commandWords[1], columnNames);
            if (columnNumber == -1)
            {
                system("Color 04");
                cout << "column does not exist" << endl;
                return;
            }
            else if (columnTypes[columnNumber] != "number")
            {
                system("Color 04");
                cout << "column is not of type number" << endl;
                return;
            }
            else
            {
                max = stoi(table[0][columnNumber]);
                for (int j = 1; j < numRows; j++)
                {
                    if (stoi(table[j][columnNumber]) > max)
                    {
                        max = stoi(table[j][columnNumber]);
                    }
                }
                cout << "maximum of column " << columnNames[columnNumber]
                     << " is " << max << endl;
            }
        }
    }
    void findMedian()
    {
        if (!correctSyntax)
        {
            system("Color 04");
            cout << "syntax error" << endl
                 << "median <column> (optional)" << endl;
            return;
        }
        if (numWords == 1)
        {
            for (int i = 0; i < numColumns; i++)
            {
                vector<int> column, sortedColumn;
                if (columnTypes[i] == "number")
                {
                    for (int j = 0; j < numRows; j++)
                    {
                        column.push_back(stoi(table[j][i]));
                    }

                    sortedColumn = sortColumn(column);
                    if (numRows % 2)
                    {
                        cout << "median of column " << columnNames[i]
                             << " is " << sortedColumn[numRows / 2] << endl;
                    }
                    else
                    {
                        cout << "median of column " << columnNames[i]
                             << " is " << (sortedColumn[numRows / 2] + sortedColumn[numRows / 2 - 1]) / 2 << endl;
                    }
                }
            }
        }
        else
        {
            int columnNumber = checkColumn(commandWords[1], columnNames);
            if (columnNumber == -1)
            {
                system("Color 04");
                cout << "column does not exist" << endl;
                return;
            }
            else if (columnTypes[columnNumber] != "number")
            {
                system("Color 04");
                cout << "column is not of type number" << endl;
                return;
            }
            else
            {
                vector<int> column, sortedColumn;
                for (int j = 0; j < numRows; j++)
                {
                    column.push_back(stoi(table[j][columnNumber]));
                }
                sortedColumn = sortColumn(column);
                if (numRows % 2)
                {
                    cout << "median of column " << columnNames[columnNumber]
                         << " is " << sortedColumn[numRows / 2] << endl;
                }
                else
                {
                    cout << "median of column " << columnNames[columnNumber]
                         << " is " << (sortedColumn[numRows / 2] + sortedColumn[numRows / 2 - 1]) / 2 << endl;
                }
            }
        }
    }
    void mean()
    {
        cout << setprecision(4) << fixed;
        if (!correctSyntax)
        {
            system("Color 04");
            cout << "syntax error" << endl
                 << "mean <column> (optional)" << endl;
            return;
        }
        if (numWords == 1)
        {
            for (int i = 0; i < numColumns; i++)
            {
                if (columnTypes[i] == "number")
                {
                    
                    cout << "mean of column " << columnNames[i]
                         << " is " << findMean(table, i) << endl;
                }
            }
        }
        else
        {
            int columnNumber = checkColumn(commandWords[1], columnNames);
            if (columnNumber == -1)
            {
                system("Color 04");
                cout << "column does not exist" << endl;
                return;
            }
            else if (columnTypes[columnNumber] != "number")
            {
                system("Color 04");
                cout << "column is not of type number" << endl;
                return;
            }
            else
            {
                
                cout << "mean of column " << columnNames[columnNumber]
                     << " is " << findMean(table, columnNumber) << endl;
            }
        }
    }
    void variance()
    {
        /*
        to find variance
        find mean of the numbers
        find the difference between each number and the mean
        square that
        find the mean of the squared differences
        */
        cout << setprecision(4) << fixed;
        float mean, variance, sum = 0;
        if (!correctSyntax)
        {
            system("Color 04");
            cout << "syntax error" << endl
                 << "variance <column> (optional)" << endl;
            return;
        }
        if (numWords == 1)
        {
            for (int i = 0; i < numColumns; i++)
            { // for eahc column
                if (columnTypes[i] == "number")
                {
                    variance = findVariance(table, i);
                    cout << "variance of column " << columnNames[i]
                         << " is " << variance << endl;
                }
            }
        }
        else
        {
            int columnNumber = checkColumn(commandWords[1], columnNames);
            if (columnNumber == -1)
            {
                system("Color 04");
                cout << "column does not exist" << endl;
                return;
            }
            else if (columnTypes[columnNumber] != "number")
            {
                system("Color 04");
                cout << "column is not of type number" << endl;
                return;
            }
            else
            {
                variance = findVariance(table, columnNumber);
                cout << "variance of column " << columnNames[columnNumber]
                     << " is " << variance << endl;
            }
        }
    }
    void stdv()
    {
        /*
        to find stdv
        find variance
        square root that
        */
        cout << setprecision(4) << fixed;
        float mean, variance, sum = 0;
        if (!correctSyntax)
        {
            system("Color 04");
            cout << "syntax error" << endl
                 << "stdv <column> (optional)" << endl;
            return;
        }
        if (numWords == 1)
        {
            for (int i = 0; i < numColumns; i++)
            { // for eahc column
                if (columnTypes[i] == "number")
                {
                    variance = findVariance(table, i);
                    cout << "standard deviation of column " << columnNames[i]
                         << " is " << sqrt(variance) << endl;
                }
            }
        }
        else
        {
            int columnNumber = checkColumn(commandWords[1], columnNames);
            if (columnNumber == -1)
            {
                system("Color 04");
                cout << "column does not exist" << endl;
                return;
            }
            else if (columnTypes[columnNumber] != "number")
            {
                system("Color 04");
                cout << "column is not of type number" << endl;
                return;
            }
            else
            {
                variance = findVariance(table, columnNumber);
                cout << "standard deviation of column " << columnNames[columnNumber]
                     << " is " << sqrt(variance) << endl;
            }
        }
    }
    void sum()
    {
        if (!correctSyntax)
        {
            system("Color 04");
            cout << "syntax error" << endl
                 << "sum <column1> <column2>" << endl;
            return;
        }
        int columnNumber1 = checkColumn(commandWords[1], columnNames);
        int columnNumber2 = checkColumn(commandWords[2], columnNames);
        if (columnNumber1 == -1 || columnNumber2 == -1)
        {
            system("Color 04");
            cout << "one of the columns does not exist" << endl;
            return;
        }
        else if (columnTypes[columnNumber1] != "number" || columnTypes[columnNumber2] != "number")
        {
            system("Color 04");
            cout << "one of the columns is not of type number" << endl;
            return;
        }
        else
        {
            int add, sum = 0;
            for (int j = 0; j < numRows; j++)
            {
                add = stoi(table[j][columnNumber1]) + stoi(table[j][columnNumber2]);
                cout << add << endl;
                sum += add;
            }
            cout << "total sum of columns " << columnNames[columnNumber1] << " and " << columnNames[columnNumber2]
                 << " is " << sum << endl;
        }
    }
    void difference()
    {
        if (!correctSyntax)
        {
            system("Color 04");
            cout << "syntax error" << endl
                 << "sum <column1> <column2>" << endl;
            return;
        }
        int columnNumber1 = checkColumn(commandWords[1], columnNames);
        int columnNumber2 = checkColumn(commandWords[2], columnNames);
        if (columnNumber1 == -1 || columnNumber2 == -1)
        {
            system("Color 04");
            cout << "one of the columns does not exist" << endl;
            return;
        }
        else if (columnTypes[columnNumber1] != "number" || columnTypes[columnNumber2] != "number")
        {
            system("Color 04");
            cout << "one of the columns is not of type number" << endl;
            return;
        }
        else
        {
            int diff, sum = 0;
            for (int j = 0; j < numRows; j++)
            {
                diff = stoi(table[j][columnNumber1]) - stoi(table[j][columnNumber2]);
                cout << diff << endl;
                sum += diff;
            }
            cout << "total difference of columns " << columnNames[columnNumber1] << " and " << columnNames[columnNumber2]
                 << " is " << sum << endl;
        }
    }
    void corr()
    {
        /*
        based on formula from wikipedia
        find mean for each column
        numerator = sum of (x - mean1) * (y - mean2)
        denominator1 = sum of (x - mean1)^2
        denominator2 = sum of (y - mean2)^2
        denominator = root of (denominator1 * denominator2)
        correlation = numerator / denominator
        */
        if (!correctSyntax)
        {
            system("Color 04");
            cout << "syntax error" << endl
                 << "corr <column1> <column2>" << endl;
            return;
        }
        int columnNumber1 = checkColumn(commandWords[1], columnNames);
        int columnNumber2 = checkColumn(commandWords[2], columnNames);
        float mean1 = findMean(table, columnNumber1);
        float mean2 = findMean(table, columnNumber2);
        float numerator = 0, denominator1 = 0, denominator2 = 0, denominator = 0;
        for (int i = 0; i < numRows; i++)
        {
            numerator += (stoi(table[i][columnNumber1]) - mean1) * (stoi(table[i][columnNumber2]) - mean2);
            denominator1 += pow(stoi(table[i][columnNumber1]) - mean1, 2);
            denominator2 += pow(stoi(table[i][columnNumber2]) - mean2, 2);
        }
        denominator = sqrt(denominator1 * denominator2);
        cout << "correlation between columns " << columnNames[columnNumber1] << " and " << columnNames[columnNumber2]
             << " is " << numerator / denominator << endl;

    }
    void regression() 
    {

    }
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
    void man() {}
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