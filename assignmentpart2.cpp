#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>

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
    vector<string> modeList = {"load", "store", "clone", "html", "min", "max",
                               "median", "mean", "variance", "stdv", "add",
                               "sub", "corr", "regression", "show", "titles",
                               "report", "rows", "columns", "vhisto", "hhisto",
                               "sort", "help", "oddrows", "evenrows", "primes",
                               "man", "delete", "insert", "replace",
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

bool checkSyntax(vector<string> commandWords, int modeNumber, int numColumns)
{
    // serves to check if the number of words is correct for each command.
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
    case 14: // regression
        return (numWords == 3);
    default:
        return false;
    }
}
bool checkSyntax2(vector<string> commandWords, int modeNumber, int numColumns)
{
    int numWords = commandWords.size();
    switch (modeNumber)
    {
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
    case 27: // man
        return (numWords == 2);
    case 28: // delete
        if (commandWords[1] == "occurrence") return (numWords == 4);
        else if (commandWords[1] == "column" || commandWords[1] == "row") return (numWords == 3);
        else return false;
    case 29: // insert
        return (numWords == numColumns);
    case 30: // replace
        return (numWords == 3 || numWords == 4);
    }
    return false;
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

float findMin(vector<vector<string>> table, int columnNumber, int numRows){
    float min = stoi(table[0][columnNumber]); // sets the minimum to the first value in the column
    for (int j = 1; j < numRows; j++)
    { //loops through the column
        if (stoi(table[j][columnNumber]) < min)
        { // if the value is less than the current minimum, set the minimum to that value
            min = stoi(table[j][columnNumber]);
        }
    }
    return min; // returns the minimum
}

float findMax(vector<vector<string>> table, int columnNumber, int numRows){
    float max = stoi(table[0][columnNumber]); // sets the maximum to the first value in the column
    for (int j = 1; j < numRows; j++)
    { //loops through the column
        if (stoi(table[j][columnNumber]) > max)
        { // if the value is more than the current maximum, set the maximum to that value
            max = stoi(table[j][columnNumber]);
        }
    }
    return max; // returns the maximum
}

int findMax(vector<int>table, int numRows){ //function overloaded for histogram
    int max = table[0]; // sets the maximum to the first value in the column
    for (int j = 1; j < numRows; j++)
    {  //loops through the column
        if (table[j] > max)
        { // if the value is more than the current maximum, set the maximum to that value
            max = table[j]; 
        }
    }
    return max;
}

float findMean(vector<vector<string>> table, int columnNumber)
{
    // finds the mean of a column
    float sum = 0;
    for (int i = 0; i < table.size(); i++)
    { // loops through the column
        sum += stoi(table[i][columnNumber]); // adds each value to the sum
    }
    return sum / table.size(); // returns the sum divided by the number of values
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
    { // loops through the column
        min = (column[i]); // sets the minimum to the first value in the column
        minIndex = i; // sets the minimum index to the first index in the column
        for (int j = i + 1; j < column.size(); j++)
        {
            if ((column[j]) < min)
            { // if the value is less than the current minimum, set the minimum to that value and update the index
                min = (column[j]);
                minIndex = j;
            }
        }
        sortedColumn.push_back(min); // adds the minimum value to the sorted column
        column[minIndex] = column[i]; // swaps the minimum value with the current value
    }
    return sortedColumn;
}

bool checkCSV(string argument){
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
                cout << "\a";
                cout << "invalid file type" << endl
                    << "load <filename.csv>" << endl;
                return false;
            }
            else
            {
                // if the file is a csv file, break out of the loop
                return true;
            }
        }
    }
    return false;
}

bool checkHTML(string argument){
    for (int i = 0; i < argument.length(); i++)
    {
        // checks if a file was given
        if (argument[i] == '.')
        {
            // checks if the file is a html file
            string extension = argument.substr(i, argument.length()); // gets the extension of the file
            if (extension != ".html")
            {
                // outputs error if not a html file
                system("Color 04");
                cout << "\a";
                cout << "invalid file type" << endl;
                return false;
            }
            else
            {
                // if the file is a html file, break out of the loop
                return true;
            }
        }
    }
    return false;
}

void errorPrinter(string str){
    system("Color 04"); // sets the colour to red
    cout << "\a"; // makes a beep sound
    cout << str << endl; //outputs the error message
}

void dataLoader(ifstream &inputFile, int &numColumns, int &numRows, vector<string> &columnNames, vector<string> &columnTypes, vector<vector<string>> &table){
    inputFile >> numColumns >> numRows; // gets the number of columns and rows
    string row;
    int rowCounter = -1;
    while (getline(inputFile, row)) // gets each row
    {
        vector<string> rowVector;
        stringstream rowStream(row);
        string word;
        while (getline(rowStream, word, ','))
        { // gets each word, seperates the words by commas
            makeLower(word); // makes the word lower case
            if (word[0] == ' ') word = word.substr(1, word.length()); // removes the space at the beginning of the word                    
            if (rowCounter == 0) columnNames.push_back(word);// if it is the first row, save the column names
            else if (rowCounter == 1) columnTypes.push_back(word); // if it is the second row, save the column types
            else rowVector.push_back(word); // if it is any other row, save the data
        }
        if (rowCounter > 1) table.push_back(rowVector); 
        rowCounter++;
    }
}

float findMedian(vector<vector<string>> table, int columnNumber, int numRows)
{
    vector<int> column, sortedColumn;
    for (int j = 0; j < numRows; j++)
    { // loops through the column
        column.push_back(stoi(table[j][columnNumber])); // adds each value to a vector
    }
    sortedColumn = sortColumn(column); // sorts the column
    if (numRows%2) return sortedColumn[numRows/2]; // if the number of rows is odd, return the middle value
    else return (float)(sortedColumn[numRows/2] + sortedColumn[numRows/2 - 1])/2; // if the number of rows is even, return the average of the two middle values
}

struct Program
{
    int numWords, numColumns, numRows, modeNumber;
    string command;
    vector<string> commandWords, columnNames, columnTypes, modeList;
    vector<vector<string>> table;
    bool correctSyntax, dataLoaded = false;

    Program()
    { // constructor
        system("cls");
        system("Color 02");
        cout << "Program activated. Key in 'help' to check available command.\n";
    }

    ~Program()
    { // destructor
        system("Color 02");
        cout << "\a";
        cout << "Program terminated.";
    }
    void get()
    {
        commandWords = {};
        cout << "$ ";
        getline(cin, command);                                             // gets command
        seperateWords(command, commandWords);                              // seperates words by spaces and saves them in a vector
        numWords = commandWords.size();                                    // saves the number of words in the command
        modeNumber = findMode(commandWords[0]);                            // finds the mode number of the command
        if(modeNumber < 15) correctSyntax = checkSyntax(commandWords, modeNumber, numColumns);
        else correctSyntax = checkSyntax2(commandWords, modeNumber, numColumns);
    }
    void runner(){ // runs the correct function based on the mode number, seperated into four functions to be compact
        if(!dataLoaded && (modeNumber != 4 && modeNumber != 23 && modeNumber != 27 && modeNumber != 31)) errorPrinter("no data loaded"); // checks if data is loaded
        else if (modeNumber == -1) errorPrinter("invalid command");
        else if (modeNumber <= 8) runner1();
        else if (modeNumber <= 17) runner2();
        else if (modeNumber <= 26) runner3();
        else runner4();
    }
    void runner1()
    {// uses mode number to run the correct function
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
            min();
            break;
        case 6: // max
            max();
            break;
        case 7: // median
            median();
            break;
        case 8: // mean
            mean();
            break;
        }
    }
    void runner2(){
        switch(modeNumber){
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
        }
    }
    void runner3(){
        switch(modeNumber){
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
        }
    }
    void runner4(){
        switch(modeNumber){
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
    { // loads a csv file
        if (!correctSyntax) errorPrinter("syntax error\nload <filename.csv>"); // checks if the syntax is correct
        else if(checkCSV(commandWords[1])){ // checks if the file is a csv file
            ifstream inputFile(commandWords[1]);
            if (!inputFile.is_open()) errorPrinter("file does not exist"); // checks if the file exists
            else
            {
                dataLoader(inputFile, numColumns, numRows, columnNames, columnTypes, table); // loads the data
                system("Color 02");
                cout << commandWords[1] << " has been loaded" << endl;
                inputFile.close(); // closes the file
            }
        }
        else errorPrinter("Invalid file type");
    }

    //STORE
    void store() {
        if (!correctSyntax) errorPrinter("syntax error\nstore <filename.csv>");
        else if(checkCSV(commandWords[1])){
            ofstream inputFile(commandWords[1]);
            if (!inputFile.is_open()) errorPrinter("file does not exist");
            else{
                system("Color 02");
                inputFile << numColumns << endl << numRows << endl;
                for (const string& columnName : columnNames) {
                    inputFile << columnName << ' ';}
                inputFile << endl;
                for (const string& columnType : columnTypes) {
                    inputFile << columnType << ' ';}
                inputFile << endl;
                for (int i = 0; i < numRows; i++){
                    for (int j = 0; j < numColumns; j++){
                        system("Color 02");
                        inputFile << table[i][j] << " ";}
                inputFile << endl;}
                inputFile.close(); // closes the file
                cout << "File successfully stored, the name of the file is " << commandWords[1] << endl;}
        }
        else errorPrinter("Invalid file type");
    }

    //CLONE
    void clone() {
        if (!correctSyntax) errorPrinter("syntax error\nclone <filename.csv> <filename.csv>");
        else if(checkCSV(commandWords[1]) && checkCSV(commandWords[2])){
            ifstream inputFile(commandWords[1]);
            if (!inputFile.is_open()) errorPrinter("file does not exist");
            else{
                system("Color 02");
                string cloneFileName = commandWords[2];
                ofstream cloned(cloneFileName);
                string line;
                while (getline(inputFile, line)) cloned << line << endl;
                cout << "File successfully cloned, the clone file is named: " << commandWords[2] << endl;
            }
        }
        else  errorPrinter("syntax error\nclone <filename.csv> <filename.csv>");
    }

    void html() 
    {
            if (!correctSyntax) errorPrinter("syntax error\nclone <filename.csv> <filename.csv>");
            else if(numWords == 2) 
            {
                if (!checkHTML(commandWords[1])) errorPrinter("syntax error\nhtml <filename.html>");
                else if (!dataLoaded)
                errorPrinter("no data loaded");
                else {
                    system("Color 02");
                    constructHTML(commandWords[1]);
                    cout << "html file successfully generated, the name of the file is " << commandWords[1] << endl; 
                }
            }
            else if (numWords == 3)
            {
                if (!checkCSV(commandWords[1]) && !checkHTML(commandWords[2])) errorPrinter("syntax error\nhtml <filename.csv> <filename.html>");
                else {
                    ifstream inputFile(commandWords[1]);
                    if (!inputFile.is_open()) errorPrinter("file does not exist");
                    else 
                    {
                        system("Color 02");
                        dataLoader(inputFile, numColumns, numRows, columnNames, columnTypes, table);
                        constructHTML(commandWords[2]);
                        cout << "html file successfully generated, the name of the file is " << commandWords[2] << endl; 
                    }
                }
            }
        }

    void constructHTML(string file)
    {
        int x = (numWords - 1); 
        ofstream MyFile(file); 

        MyFile << ("<table>\n"); 
        for (int z = 0; z < numColumns; z++)
        {
            MyFile << "<td>" << columnNames[z] << "</td>";
        }
        for (int i = 0; i < numRows; i++)
        {
            MyFile << ("<tr>\n");
            for (int j = 0; j < numColumns; j++)
            {  
                MyFile << "<td>" << table[i][j] << "</td>";
                MyFile << endl;  
            }
            MyFile << ("</tr>\n");
        }
        MyFile << ("</table>\n");
        MyFile.close();
    }
        
    void min()
    {
        if (!correctSyntax) errorPrinter("syntax error\nmin <column> (optional)"); // checks if the syntax is correct
        else if (numWords == 1)
        { // if no column is specified, find the minimum of all the columns
            for (int i = 0; i < numColumns; i++)
            { // loops through columns
                if (columnTypes[i] == "number")
                { // checks if the column is of type number
                    system("Color 02");
                    cout << "minimum of column " << columnNames[i] << " is " << findMin(table, i, numRows) << endl; // outputs the minimum of the column
                }
            }
        }
        else
        { // if a column is specified, find the minimum of that column
            int columnNumber = checkColumn(commandWords[1], columnNames); // checks if the column exists
            if (columnNumber == -1 || columnTypes[columnNumber] != "number")
                errorPrinter("column must exist and must be of type number"); // checks if the column exists and is of type number
            else
            {                
                system("Color 02");
                cout << "minimum of column " << columnNames[columnNumber] << " is " << findMin(table, columnNumber, numRows) << endl; // outputs the minimum of the column
            }
        }
    }
    void max()
    { // same as min, but with max
        if (!correctSyntax) errorPrinter("syntax error\nmax <column> (optional)");
        else if (numWords == 1)
        {
            for (int i = 0; i < numColumns; i++)
            { // for each column
                if (columnTypes[i] == "number")
                { // checks if the column is of type number
                    system("Color 02");
                    cout << "maximum of column " << columnNames[i] << " is " << findMax(table, i, numRows) << endl;
                }
            }
        }
        else
        { 
            int columnNumber = checkColumn(commandWords[1], columnNames);
            if (columnNumber == -1 || columnTypes[columnNumber] != "number")
                errorPrinter("column does not exist and must be of type number"); // checks if the column exists and is of type number
            else
            {                
                system("Color 02");
                cout << "maximum of column " << columnNames[columnNumber] << " is " << findMax(table, columnNumber, numRows) << endl; // outputs the maximum of the column
            }
        }

    }
    void median()
    { // same as min, but with median
        if (!correctSyntax) errorPrinter("syntax error\nmedian <column> (optional)");
        else if (numWords == 1)
        { // if no column is specified, find the median of all the columns
            for (int i = 0; i < numColumns; i++)
            {
                vector<int> column, sortedColumn;
                system("Color 02");
                if (columnTypes[i] == "number")
                    cout << "median of column " << columnNames[i] << " is " 
                         << findMedian(table, i, numRows) << endl; // outputs the median of the column
            }
        }
        else
        { // if a column is specified, find the median of that column
            int columnNumber = checkColumn(commandWords[1], columnNames);
            if (columnNumber == -1 || columnTypes[columnNumber] != "number") errorPrinter("column must exist and be of type number");
            else
            {   
                system("Color 02");
                cout << "median of column " << columnNames[columnNumber] << " is " 
                     << findMedian(table, columnNumber, numRows) << endl; // outputs the median of the column
            }
        }
    }
    void mean()
    { // same as min, but with mean
        cout << setprecision(4) << fixed;
        if (!correctSyntax) errorPrinter("syntax error\nmean <column> (optional)");
        else if (numWords == 1)
        { // if no column is specified, find the mean of all the columns
            for (int i = 0; i < numColumns; i++)
            {
                if (columnTypes[i] == "number")
                {
                    system("Color 02");
                    cout << "mean of column " << columnNames[i]
                         << " is " << findMean(table, i) << endl;
                }
            }
        }
        else
        { // if a column is specified, find the mean of that column
            int columnNumber = checkColumn(commandWords[1], columnNames);
            if (columnNumber == -1 || columnTypes[columnNumber] != "number") 
            errorPrinter("column must exist and be of type number");
            else
            {
                system("Color 02");
                cout << "mean of column " << columnNames[columnNumber]
                     << " is " << findMean(table, columnNumber) << endl;
            }
        }
    }
    void variance()
    { // same as min, but with variance
        if(!correctSyntax) errorPrinter("syntax error\nvariance <column> (optional)");
        else if (numWords == 1)
        { // if no column is specified, find the variance of all the columns
            for (int i = 0; i < numColumns; i++)
            { // for eahc column
                if (columnTypes[i] == "number")
                {
                    system("Color 02");
                    cout << setprecision(4) << fixed << "variance of column " << columnNames[i] << " is " << findVariance(table, i) << endl;
                }
            }
        }
        else
        { // if a column is specified, find the variance of that column
            int columnNumber = checkColumn(commandWords[1], columnNames);
            if (columnNumber == -1|| columnTypes[columnNumber] != "number")
                errorPrinter("column must exist and be of type number");
            else
            {
                system("Color 02");
                cout << setprecision(4) << fixed << "variance of column " << columnNames[columnNumber] << " is " << findVariance(table, columnNumber) << endl;
            }
        }
    }
    void stdv()
    { // same as min, but with standard deviation
        if (!correctSyntax) errorPrinter("syntax error\nstdv <column> (optional)");
        else if (numWords == 1)
        { // if no column is specified, find the standard deviation of all the columns
            for (int i = 0; i < numColumns; i++)
            { // for eahc column
                if (columnTypes[i] == "number")
                {
                    system("Color 02");
                    cout << setprecision(4) << fixed << "standard deviation of column " << columnNames[i] << " is " << sqrt(findVariance(table, i)) << endl;
                }
            }
        }
        else
        { // if a column is specified, find the standard deviation of that column
            int columnNumber = checkColumn(commandWords[1], columnNames);
            if (columnNumber == -1 || columnTypes[columnNumber] != "number") 
                errorPrinter("column must exist and be of type number");
            else
            {
                system("Color 02");
                cout << setprecision(4) << fixed << "standard deviation of column " << columnNames[columnNumber] << " is " << sqrt(findVariance(table, columnNumber)) << endl;
            }
        }
    }
    void sum()
    {
        if (!correctSyntax) errorPrinter("syntax error\nsum <column1> <column2>");
        else{ 
            int columnNumber1 = checkColumn(commandWords[1], columnNames),  columnNumber2 = checkColumn(commandWords[2], columnNames);
            if (columnNumber1 == -1 || columnNumber2 == -1 || columnTypes[columnNumber1] != "number" || columnTypes[columnNumber2] != "number")
                errorPrinter("both columns must exist and be of type number"); // checks if both the columns exist and are of type number
            else
            {
                system("Color 02");
                int add, sum = 0;
                for (int j = 0; j < numRows; j++)
                {
                    add = stoi(table[j][columnNumber1]) + stoi(table[j][columnNumber2]); // adds the two values
                    cout << add << endl; // outputs the sum of the two values
                    sum += add;
                }
                cout << "total sum of columns " << columnNames[columnNumber1] << " and " << columnNames[columnNumber2]
                    << " is " << sum << endl; // outputs the total sum of the two columns
            }
        }
    }
    void difference()
    { // same as sum, but with difference
        if (!correctSyntax) errorPrinter("diff <column1> <column2>");
        else
        {
            int columnNumber1 = checkColumn(commandWords[1], columnNames);
            int columnNumber2 = checkColumn(commandWords[2], columnNames);
            if (columnNumber1 == -1 || columnNumber2 == -1 || columnTypes[columnNumber1] != "number" || columnTypes[columnNumber2] != "number")
                errorPrinter("both columns must exist and be of type number");
            else
            {
                system("Color 02");
                int diff, sum = 0;
                for (int j = 0; j < numRows; j++)
                {
                    diff = stoi(table[j][columnNumber1]) - stoi(table[j][columnNumber2]); // finds the difference between the two values
                    cout << diff << endl; // outputs the difference
                    sum += diff; // adds the difference to the sum
                }
                cout << "total difference of columns " << columnNames[columnNumber1] << " and " << columnNames[columnNumber2] << " is " << sum << endl;
            }
        }
    }
    void corr()
    { // finds the correlation between two columns
        if (!correctSyntax) errorPrinter("corr <column1> <column2>");
        else {
            int columnNumber1 = checkColumn(commandWords[1], columnNames);
            int columnNumber2 = checkColumn(commandWords[2], columnNames);
            if (columnNumber1 == -1 || columnNumber2 == -1 || columnTypes[columnNumber1] != "number" || columnTypes[columnNumber2] != "number")
                errorPrinter("both columns must exist and be of type number"); // checks if both the columns exist and are of type number
            else
            {
            float mean1 = findMean(table, columnNumber1); // finds the mean of the first column
            float mean2 = findMean(table, columnNumber2); // finds the mean of the second column
            float numerator = 0, denominator1 = 0, denominator2 = 0, denominator = 0;
            for (int i = 0; i < numRows; i++)
            {
                numerator += (stoi(table[i][columnNumber1]) - mean1) * (stoi(table[i][columnNumber2]) - mean2); // finds the numerator of the correlation formula
                denominator1 += pow(stoi(table[i][columnNumber1]) - mean1, 2); // finds the first part of the denominator of the correlation formula
                denominator2 += pow(stoi(table[i][columnNumber2]) - mean2, 2); // finds the second part of the denominator of the correlation formula
            }
            denominator = sqrt(denominator1 * denominator2); 
            system("Color 02");
            cout << "correlation between columns " << columnNames[columnNumber1] << " and " << columnNames[columnNumber2]
                << " is " << numerator / denominator << endl; // outputs the correlation

            }
        }
    }
    void regression() 
    { // finds the regression line between two columns
        if(!correctSyntax)
        {
            errorPrinter("syntax error\nregression <column1> <column2>");
            return;
        }
        int columnNumber1 = checkColumn(commandWords[1], columnNames);
        int columnNumber2 = checkColumn(commandWords[2], columnNames);
        if (columnNumber1 == -1 || columnNumber2 == -1 || columnTypes[columnNumber1] != "number" || columnTypes[columnNumber2] != "number")
            errorPrinter("both columns must exist and be of type number"); // checks if both the columns exist and are of type number
        else
        {
            float sumX = 0, sumX2 = 0, sumY = 0, sumXY = 0;
            for (int i = 0; i < numRows; i++)
            {
                sumX += stoi(table[i][columnNumber1]); // finds the sum of the first column
                sumX2 += pow(stoi(table[i][columnNumber1]), 2); // finds the sum of the squares of the first column
                sumY += stoi(table[i][columnNumber2]);   // finds the sum of the second column
                sumXY += stoi(table[i][columnNumber1]) * stoi(table[i][columnNumber2]); // finds the sum of the product of the two columns
            }
            float b1 = (numRows * sumXY - sumX * sumY) / (numRows * sumX2 - pow(sumX, 2));
            float b0 = (sumY - b1 * sumX) / numRows;
            system("Color 02");
            cout << "regression line for columns " << columnNames[columnNumber1] << " and " << columnNames[columnNumber2]
                << " is " << b0 << " + " << b1 << "x" << endl;
        }
    }

    void show() { //SHOW
        if (!correctSyntax) errorPrinter("syntax error\nshow <column> (optional)");
        else if (numWords == 1)
        {
            for (int i = 0; i < numRows; i++)
            {
                for (int j = 0; j < numColumns; j++)
                {
                    system("Color 02");
                    cout << table[i][j] << " ";
                }
                cout << endl;
            }
        }
        else
        {
            int columnNumber = checkColumn(commandWords[1], columnNames);
            if (columnNumber == -1) errorPrinter("column does not exist");
            else
            {
                for (int i = 0; i < numRows; i++)
                {
                    system("Color 02");
                    cout << table[i][columnNumber] << endl;
                }
            }
        }
    }

    // TITLES
    void titles() {
    if (!correctSyntax) errorPrinter("syntax error\nCommand: titles");
    else if (numWords == 1)
        {
            cout << "The titles in the files are: ";
            for (int i = 0; i < columnNames.size(); ++i)
    {
        cout << columnNames[i];
        if (i != columnNames.size() - 1)
            cout << " , ";
    }
        }
        cout << endl;
    }

    //REPORT
    void report() {
    if (!correctSyntax) errorPrinter("syntax error\nCommand: report");
    else if (numWords == 1){
        cout << "MINIMUM:-\n" << endl; min(); 
        cout << "\nMAXIMUM:-\n"; max(); 
        cout << "\nMEDIAN:-\n"; median();  
        cout << "\nMEAN:-\n"; mean();
        cout <<"\nVARIANCE:-\n"; variance(); 
        cout <<"\nSTANDARD DEVIATION:-\n"; stdv();}
    }


    //ROWS
    void rows() {
    if (!correctSyntax) errorPrinter("syntax error\nCommand: rows");
    else if (numWords == 1)
        {   
            cout << numRows << endl;
        }
    }

    //COLUMNS
    void columns() {
    if (!correctSyntax) errorPrinter("syntax error\nCommand: columns");
    else if (numWords == 1)
        {   
            cout << numColumns << endl;
        }
    }

    //VHISTO
    void vhisto() 
    {
        vector<int> numbersCounter, numbers;
        if(!correctSyntax) errorPrinter("syntax error\nCommand: hhisto <column>");
        else if (numWords == 2)
        { // counts the occurences of each number in a column, and then prints a vertical histogram
            int columnNumber = checkColumn(commandWords[1], columnNames);
            if (columnNumber == -1 || columnTypes[columnNumber] != "number") errorPrinter("column must exist and be of type number");
            else
            {
                countOccurences(numbers, numbersCounter, columnNumber); //counts the number of occurences of each number
                for (int i = findMax(numbersCounter, numbersCounter.size()); i > 0 ; i--){
                    cout.width(3); 
                    cout << right << i << '|'; // prints the y axis which is the frequency
                    for (int j = 0; j < numbers.size(); j++)
                    { // if the number of occurence of a number is greater or equal to the current level of frequency
                        if (numbersCounter[j] >= i)
                        {
                            system("Color 02"); 
                            cout << "  X  ";  //print an x
                        }
                        else cout << "     ";  // otherwise print a space
                    }
                    cout << endl;
                }
                cout << "    "; 
                for(int i = 0; i < numbers.size(); i++) cout << " " << numbers[i] << "  "; // prints the x axis which is the number
                cout << '\n';
            }
        }
    }

    //HHISTO
    void hhisto() 
    { // same as vhisto, but with a horizontal histogram
        vector<int> numbersCounter, numbers;
        if(!correctSyntax) errorPrinter("syntax error\nCommand: hhisto <column>");
        else if (numWords == 2)
        { // counts the occurences of each number in a column, and then prints a horizontal histogram
            int columnNumber = checkColumn(commandWords[1], columnNames);
            if (columnNumber == -1 || columnTypes[columnNumber] != "number") errorPrinter("column must exist and be of type number");
            else
            {
                countOccurences(numbers, numbersCounter, columnNumber);
                cout << "     ";
                for (int i = 1; i <= findMax(numbersCounter, numbersCounter.size()); i++){
                    cout << i << "   "; // prints the x axis which is the frequency
                    if (i < 10) cout << " "; // if the number is less than 10, print an extra space to make the histogram look better
                }
                cout << endl;
                for (int i = 0; i < numbers.size(); i++)
                { // for each number
                    if(numbers[i]<10) cout << ' '; // if the number is less than 10, print an extra space to make the histogram look better
                    cout << numbers[i] << "|"; // prints the y axis which is the number
                    for (int j = 0; j < numbersCounter[i]; j++)
                    {
                        system("Color 02");
                        cout << "  X  "; // prints an x for each occurence of the number
                    }
                    cout << endl;
                }
            }
        }
    }

    int countNumbers(int columnNumber, int n){ // takes an integer and counts the number of times it occurs in a column
        int count = 0;
        for (int i = 0; i < numRows; i++)
        {
            if (stoi(table[i][columnNumber]) == n) count++;
        }
        return count;
    }

    void countOccurences(vector<int>&numbers, vector<int>&numbersCounter, int columnNumber){
        for (int i = 0; i < numRows; i++){ // for each number in the column
            int number = stoi(table[i][columnNumber]);
            if (find(numbers.begin(), numbers.end(), number) == numbers.end()){ // if the number is not in the vector of numbers that were already counted
            numbers.push_back(number); // add the number to the vector of numbers
            numbersCounter.push_back(countNumbers(columnNumber, number)); // count the number of occurences of the number and add it to the vector of numbersCounter
            }
        }
    }

    //SORT
    void sort() {
        if (!correctSyntax) errorPrinter("syntax error\nCommand: sort <column>");
        else if (numWords == 2){
        int columnNumber = checkColumn(commandWords[1], columnNames);
        if (columnNumber == -1) errorPrinter("column does not exist");
        else{
                cout << "Successfully sort data according to " << commandWords[1] << " from ascending order\nType 'show' to see the result" << endl;
                for (int i = 0; i < numRows; i++){
                    for (int j = 0; j < numRows - i - 1; ++j) {
                        if (table[j][columnNumber] > table[j + 1][columnNumber]) {
                        swap(table[j], table[j + 1]);}}}
            }
        }
    }

    //HELP
    void help() {
    if (!correctSyntax) errorPrinter("syntax error\nCommand: help");
    else{
        system("Color 01");
        cout << "Command available:- \n-load \n-store \n-clone \n-html \n-min \n-max \n-median"
             << "\n-mean \n-variance \n-stdv \n-add \n-sub \n-corr \n-regression \n-show \n-titles \n-report" 
             << "\n-rows \n-columns \n-vhisto \n-hhisto \n-sort \n-oddrows \n-evenrows \n-primes \n-man \n-delete" 
             << "\n-insert \n-replace \n-exit \n<For more info about command,key in 'man (command)'>"<< endl;
        }
    }

    //MAN
    void man() { 
        system("Color 02");
        if (numWords < 2 || numWords > 2) errorPrinter("syntax error\nCommand: man <command>");
        else if (numWords == 2){
        int x = findMode(commandWords[1]);
        if ( x == 1){cout << "Command: load <csv file>\nReads the file named filename and "
        << "parses its contents and stores it into arrays or vectors."<< endl;}
        else if ( x== 2){cout <<"Command: store <csv file>\nSave the active array or vectors into "
        << "a csv formatted file with the name filename"<< endl;}
        else if ( x == 3){cout <<"Command: clone <csv file> <csv file>\nCreate a copy of file1 and name it file2." << endl;}
        else if ( x == 4){cout <<"Command: html <html file> Or html <csv file> <html file>\nGenerates an HTML document for the loaded data and "
        << " store it in the specific file.\n-Or-\nRead the a.csv file and convert it to an html table with proper column titles and format."  <<endl;}
        else if ( x == 5){cout <<"Command: min Or min <column name>\nShows the minimum of all the columns.\n-Or-\nDisplay the minimum of the "
        << "specific column." << endl;}
        else if ( x == 6){cout <<"Command: max Or max <column name>\nShows the maximum of all the columns.\n-Or-\nDisplay the maximum of the "
        << "specific column." << endl;}
        else if ( x == 7){cout <<"Command: median Or median <column name>\nShows the median of all the columns.\n-Or-\nDisplay the median of the "
        << "specific column." << endl;}
        else if ( x == 8){cout <<"Command: mean Or mean <column name>\nShows the mean of all the columns.\n-Or-\nDisplay the mean of the "
        << "specific column." << endl;}
        else if ( x == 9){cout <<"Command: variance Or variance <column name>\nShows the variance of all the columns.\n-Or-\nDisplay the "
        << "variance of the specific column." << endl;}
        else if ( x == 10){cout <<"Command: stdv Or stdv <column name>\nShows the standard division of all the columns.\n-Or-\nDisplay "
        << "the standard division of the specific column." << endl;}
        else if ( x == 11){cout <<"Command: add <column name 1> <column name 2>\nDisplays a column resulted from adding the "
        << "column name 1 and column name 2." << endl;}
        else if ( x == 12){cout <<"Command: sub <column name 1> <column name 2>\nDisplays a column resulted from subtracting the "
        << "column name 1 and column name 2." << endl;}
        else if (findMode(commandWords[1])>= 13 || findMode(commandWords[1]) == -1) {man2(x);}
            }
        }

        void man2(int x){ 
        system("Color 02");
        if ( x ==  13){cout <<"Command: corr <column name 1> <column name 2>\nComputes the correlation between the "
        << "column name 1 and the column name 2 using Pearson correlation." << endl;}
        else if ( x == 14){cout <<"Command: regression <column name>\nCompute the linear regression line formula for "
        << "a selected column." << endl;}
        else if( x == 15) cout << "Command: show or show <column>\n Displays data from file or column\n";
        else if ( x == 16) cout << "Command: titles\nDisplays titles of all columns\n"; //titles
        else if ( x == 17) cout << "Command: report\nDisplays a report that shows all statistics for all columns\n"; //report
        else if ( x == 18) cout << "Command: rows\nDisplay number of rows loaded.\n"; //rows 
        else if ( x == 19) cout << "Command: columns\nDisplay number of columns loaded.\n"; //columns
        else if ( x == 20) cout << "Command: vhisto <column>\nDisplays vertical histogram for the column.\n"; //vhisto
        else if ( x == 21) cout << "Command: hhisto <column>\nDisplays horizontal histogram for the column.\n"; //hhisto
        else if ( x == 22) cout << "Command: sort <column>\nSorts data in ascending order according to the column value\n"; //sort 
        else if ( x == 24) cout << "Command: oddrows\nDisplay odd rows from table\n"; //oddrows
        else if ( x == 25) cout << "Command: evenrows\nDisplay even rows from table\n"; // evenrows
        else if ( x == 26) cout << "Command: primes <column>\nShows prime numbers in the column.\n"; //primes
        else if ( x == 28) cout << "Command: delete occurance <column name> <integer> Or delete row <integer> Or delete column <column name> "
        << " \nDelete the row that contain the specific number in the specific column.\n-Or-\nDelete the specific row\n-Or-\nDelete the specific column.\n"; //delete
        else if ( x == 29) cout << "Command: insert row <data according to the column catergories.>\nAdd a new row of data.\n"; //insert
        else if ( x == 30) cout << "Command: replace <integer> <integer> Or replace <column name> <integer> <integer>\nReplace the specific value with the new specific value."
        << "\n-Or-\nReplace the specific value with the new specific value in the specific column"; //replace
        else errorPrinter("syntax error\nCommand: man <command>");
        }

    //ODDROWS
    void oddrows() {
    if (!correctSyntax) errorPrinter("syntax error\nCommand: oddrows");
    else if (numWords == 1)
    for (int i = 0; i < numRows; i++)
        {
            if ((i-1) % 2 != 0){
            cout << "This is row " << (i+1) << ", The content is: ";
            for (int j = 0; j < numColumns; j++)
                {
                system("Color 02");
                cout << table[i][j] << " ";
                }
            cout << endl;}
        }
    }

    //EVENROWS
    void evenrows() {
    if (!correctSyntax) errorPrinter("syntax error\nCommand: evenrows");
    else if (numWords == 1)
    for (int i = 0; i < numRows; i++)
        {
            if ((i-1) % 2 == 0){
            cout << "This is row " << (i+1) << ", The content is: ";
            for (int j = 0; j < numColumns; j++)
                {
                system("Color 02");
                cout << table[i][j] << " ";
                }
            cout << endl;}
        }
    }

    //PRIMEIDENTIFIER
    bool PrimeTester(int x) {
    if (x <= 1) // 0 is not a prime number
        return false;
    for (int i = 2; i <= sqrt(x); ++i) {
        if (x % i == 0)
            return false;
        }
    return true;
    }
    
    //PRIMES
    void primes() {
    if (!correctSyntax) errorPrinter("syntax error\nCommand: primes <column>");
        else if (numWords == 2)
        {
            int columnNumber = checkColumn(commandWords[1], columnNames);
            if (columnNumber == -1) errorPrinter("column does not exist");
            else
            {
                for (int i = 0; i < numRows; i++)
                {
                    system("Color 02");
                    int x = stoi(table[i][columnNumber]);
                    if (PrimeTester(x)) cout << x << endl;
                }
            }
        }
    }   
    
    void deloccur() //DELETE OCCURRENCE
    {
        string occurnum = commandWords[3]; 
        int columnNumber = checkColumn(commandWords[2], columnNames); //returns index of column
        int i = 0; 
        while (i < table.size())
        {
            if (table[i][columnNumber] == occurnum)
            {
                table.erase(table.begin() + i);
                numRows--;
            }
            i++; 
        } system("Color 02"); 
        cout << "Deleted row containing " << occurnum << endl;
    }

    void delrow() //DELETE ROW 
    {
        int rownum = stoi(commandWords[2]) - 1; 
        table.erase(table.begin() + rownum);
        numRows--; 
        system("Color 02");
        cout << "row successfully deleted" << endl;
    }

    void delcol() // DELETE COLUMN
    {
        int columnNumber = checkColumn(commandWords[2], columnNames); //returns index of column
        for (int i = 0; i < numRows; i++)
        {
            table[i].erase(table[i].begin() + columnNumber);
        }
        numColumns--;
        columnNames.erase(columnNames.begin() + columnNumber); 
        system("Color 02");
        cout << "column successfully deleted" << endl;
    }
    
    void delete_() // GENERAL DELETE FUNCTION
    {
        if (numWords == 3)
        {
            if (commandWords[1] == "row") delrow();  
            else if (commandWords[1] == "column") delcol(); 
        }
        else if (numWords == 4) deloccur(); 
        else errorPrinter("syntax error\ndelete requies valid parameter");
    }

    void insert() { //INSERT ROW 
            if (numWords - 2 == numColumns)
            {
                vector<string> VectorRow; 
                for (int i=2; i < numWords; i++)
                    VectorRow.push_back(commandWords[i]);
                table.push_back(VectorRow);
                numRows++;
                system("Color 02");
                cout << "Line successfully added, key in 'show' to check the result" << endl;
            } else errorPrinter("syntax error\ninsert <number of data must be equal to number of column>\n type 'show' to check the number of column");
            }

    void replace(){ //REPLACE
        string firstvalue = commandWords[1];
        string secondvalue = commandWords[2];
        if (numWords == 3){
        for (int i = 0; i < numRows; i++)
        {
            for (int z = 0; z < numColumns; z++){
                if (table[i][z] == firstvalue)
                    table[i][z] = secondvalue;}
        }   
        system("Color 02");
        cout << "replaced every number = " <<  firstvalue
        << " in all columns with " << secondvalue << "\n"; }
        else if (numWords == 4){
            int columnNumber = checkColumn(commandWords[1], columnNames);
            if (columnNumber == -1) errorPrinter("column does not exist");
            else
            {
                firstvalue = commandWords[2];
                secondvalue = commandWords[3];
                for (int i = 0; i < numRows; i++){
                    if (table[i][columnNumber] == firstvalue)
                        table[i][columnNumber] = secondvalue;}
                system("Color 02");
                cout << "Replaced all " << commandWords[2] << " to " << commandWords[3] << " for column " << commandWords[1] << endl;
            }
        }
        else errorPrinter("syntax error\nCommand: replace");
    }
};

int main()
{
    Program program;
    while (program.command != "exit")
    {
        program.get(); // gets the command
        program.runner(); // runs the command
    }
    return 0;
}