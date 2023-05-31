#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <sstream>

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

string getCommand()
{
    string commandInput;
    cout << "$ ";
    getline(cin, commandInput); // gets command
    return commandInput;
}

int modeFinder(string command)
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

void load(vector<string> commandWords, int numWords, vector<vector<string>> &fileData)
{

    if (numWords != 2) // load requires exactly 2 words
    {
        system("Color 04");
        cout << "syntax error\nload requires file name\n";
    }
    else
    {
        string argument = commandWords[1];
        bool hasFileType = false;
        for (int charCounter = 0; charCounter < argument.length(); charCounter++) // iterates through every character of argument
        {
            if (argument[charCounter] == '.') // if the argument has a full stop,
            {
                hasFileType = true;
                if (argument[charCounter + 1] == 'c' && argument[charCounter + 2] == 's' && argument[charCounter + 3] == 'v') // check if it is a csv file
                {
                    system("Color 02");
                    cout << argument << " has been loaded\n";
                    return;
                }
                else // if it isnt a csv file
                {
                    system("Color 04");
                    cout << "syntax error\nload requires a csv file\n";
                    return;
                }
            }
        }
        if (!(hasFileType)) // if np full stop
        {
            system("Color 04");
            cout << "syntax error\nload requires a valid file name with a file type\n";
        }
    }
}

void store(vector<string> commandWords, int numWords, vector<vector<string>> &fileData)
{

    if (numWords != 2)
    {
        system("Color 04");
        cout << "syntax error\nstore requires file name\n";
    }
    else
    {
        string argument = commandWords[1];
        bool hasFileType = false;
        for (int charCounter = 0; charCounter < argument.length(); charCounter++)
        {
            if (argument[charCounter] == '.')
            {
                hasFileType = true;
                if (argument[charCounter + 1] == 'c' && argument[charCounter + 2] == 's' && argument[charCounter + 3] == 'v')
                {

                    system("Color 02");
                    cout << argument << " has been stored\n";
                }
                else
                {
                    system("Color 04");
                    cout << "syntax error\nstore requires a csv file\n";
                }
            }
        }
        if (hasFileType == false)
        {
            system("Color 04");
            cout << "syntax error\nstore requires a valid file name with a file type\n";
        }
    }
}

// [CLONE]
void clone(vector<string> commandWords, int numWords, vector<vector<string>> &fileData)
{

    if (numWords != 3)
    {
        system("Color 04");
        cout << "syntax error\nclone requires two csv files\n";
    }
    else
    {

        string argument = commandWords[1];
        bool hasFileType = false;
        for (int charCounter = 0; charCounter < argument.length(); charCounter++)
        {
            if (argument[charCounter] == '.')
            {
                hasFileType = true;
                if (argument[charCounter + 1] == 'c' && argument[charCounter + 2] == 's' && argument[charCounter + 3] == 'v')
                {

                    system("Color 02");
                    cout << argument << " has been cloned\n";
                }
                else
                {
                    system("Color 04");
                    cout << "syntax error\nclone requires two csv files\n";
                }
            }
        }
        if (hasFileType == false)
        {
            system("Color 04");
            cout << "syntax error\nclone requires two valid file names with file types\n";
        }
    }
}

// [CHECKHTML]
void checkhtml(vector<string> commandWords, int numWords, vector<vector<string>> &fileData)
{
    if (numWords < 2)
    {
        system("Color 04");
        cout << "Syntax error; html requires file name.\n";
    }
    else
    {
        string argument = commandWords[1];
        bool hasFileType = false;
        for (int charCounter = 0; charCounter < argument.length(); charCounter++)
        {
            if (argument[charCounter] == '.')
            {
                hasFileType = true;
                if (numWords == 3)
                {
                    if (argument[charCounter + 1] == 'c' && argument[charCounter + 2] == 's' && argument[charCounter + 3] == 'v')
                    {
                        string argument2 = commandWords[2];
                        if (argument2[charCounter + 1] == 'h' && argument2[charCounter + 2] == 't' && argument2[charCounter + 3] == 'm' && argument2[charCounter + 4] == 'l')
                        {
                            system("Color 02");
                            cout << argument2 << " has been generated\n";
                        }
                        else
                        {
                            system("Color 04");
                            cout << "File requires filetype \".html\" .\n";
                        }
                    }
                    else
                    {
                        cout << "File requires filetype \".csv\"\n";
                    }
                }
                else
                {
                    if (argument[charCounter + 1] == 'h' && argument[charCounter + 2] == 't' && argument[charCounter + 3] == 'm' && argument[charCounter + 4] == 'l')
                    {
                        system("Color 02");
                        cout << argument << " has been generated\n";
                    }
                    else
                    {
                        system("Color 04");
                        cout << "It is missing html/csv file for conversion.\n";
                    }
                }
            }
        }
        if (hasFileType == false)
        {
            system("Color 04");
            cout << "html requires a valid file name with \".html\".\n";
        }
    }
}

void findMin(vector<string> commandWords, int numWords)
{

    if (numWords == 1) // min has two modes, one word for all columns
    {
        system("Color 02");
        cout << "minimum for all columns has been found.\n";
    }
    else if (numWords == 2) // and two words for one column
    {
        system("Color 02");
        cout << "minimum for " << commandWords[1] << " has been found.\n";
    }
    else
    {
        system("Color 04");
        cout << "minimum requires up to one column name\n";
    }
}

void findMax(vector<string> commandWords, int numWords)
{

    if (numWords == 1) // one for all columns
    {
        system("Color 02");
        cout << "maximum for all columns has been found.\n";
    }
    else if (numWords == 2) // and two words for one column
    {
        system("Color 02");
        cout << "maximum for " << commandWords[1] << " has been found.\n";
    }
    else
    {
        system("Color 04");
        cout << "maximum requires up to one column name\n";
    }
}

void findMedian(vector<string> commandWords, int numWords)
{

    if (numWords == 1) // one for all column
    {
        system("Color 02");
        cout << "median for all columns has been found.\n";
    }
    else if (numWords == 2) // and two words for one column
    {
        system("Color 02");
        cout << "median for " << commandWords[1] << " has been found.\n";
    }
    else
    {
        system("Color 04");
        cout << "median requires up to one column name\n";
    }
}

void findMean(vector<string> commandWords, int numWords)
{

    if (numWords == 1) // one for all
    {
        system("Color 02");
        cout << "mean for all columns has been found.\n";
    }
    else if (numWords == 2) // and two words for one column
    {
        system("Color 02");
        cout << "mean for " << commandWords[1] << " has been found.\n";
    }
    else
    {
        system("Color 04");
        cout << "mean requires up to one column name\n";
    }
}

void findVariance(vector<string> commandWords, int numWords)
{

    if (numWords == 1)
    {
        system("Color 02");
        cout << "variance for all columns has been found.\n";
    }
    else if (numWords == 2)
    {
        system("Color 02");
        cout << "variance for " << commandWords[1] << " has been found.\n";
    }
    else
    {
        system("Color 04");
        cout << "variance requires up to one column name\n";
    }
}

void findStdv(vector<string> commandWords, int numWords)
{

    if (numWords == 1)
    {
        system("Color 02");
        cout << "standard deviation for all columns has been found.\n";
    }
    else if (numWords == 2)
    {
        system("Color 02");
        cout << "standard deviation for " << commandWords[1] << " has been found.\n";
    }
    else
    {
        system("Color 04");
        cout << "standard deviation requires up to one column name\n";
    }
}

void findSum(vector<string> commandWords, int numWords)
{

    if (numWords == 3)
    {
        system("Color 02");
        cout << "displaying a column resulted from adding columns "
             << commandWords[1] << " and " << commandWords[2] << endl;
    }
    else
    {
        system("Color 04");
        cout << "syntax error\n  add requires two columns\n";
    }
}

void findDifference(vector<string> commandWords, int numWords)
{

    if (numWords == 3)
    {
        system("Color 02");
        cout << " displaying a column resulted from subtracting columns "
             << commandWords[1] << " and " << commandWords[2] << endl;
    }
    else
    {
        system("Color 04");
        cout << "syntax error\n  subtract requires two columns\n";
    }
}

void findCorrelation(vector<string> commandWords, int numWords)
{

    if (numWords == 3)
    {
        system("Color 02");
        cout << "computing correlation between columns " << commandWords[1]
             << " and " << commandWords[2] << " using Pearson correlation.\n";
    }
    else
    {
        system("Color 04");
        cout << "syntax error\ncorrelate requires two columns\n";
    }
}

void findRegression(vector<string> commandWords, int numWords)
{

    if (numWords == 2)
    {
        system("Color 02");
        cout << "computing linear regression line formula for column " << commandWords[1] << endl;
    }
    else
    {
        system("Color 04");
        cout << "syntax error\nregression requires a column name\n";
    }
}

// 3.DISPLAY COMMANDS
// [SHOW]
void show(vector<string> commandWords, int numWords)
{

    if (numWords == 1)
    {
        system("Color 02");
        cout << "Displaying data from the file\n";
    }
    else if (numWords == 2)
    {
        system("Color 02");
        cout << "Displaying data from the " << commandWords[1] << " column" << endl;
    }
    else
    {
        system("Color 04");
        cout << "Syntax Error\n Please only input one catergory of data that you wish to display\n";
    }
}

// [TITTLES]
void titles(vector<string> commandWords, int numWords)
{
    if (numWords == 1)
    {
        system("Color 02");
        cout << "Displaying tittles of the column\n";
    }
}

// [REPORT]
void report(vector<string> commandWords, int numWords)
{
    if (numWords == 1)
    {
        system("Color 02");
        cout << "Displaying all satistics of all column\n";
    }
}

// [ROWS]
void rows(vector<string> commandWords, int numWords)
{
    if (numWords == 1)
    {
        system("Color 02");
        cout << "Displaying number of rows loaded\n";
    }
}

// [COLUMNS]
void columns(vector<string> commandWords, int numWords)
{
    if (numWords == 1)
    {
        system("Color 02");
        cout << "Displaying number of columns loaded\n";
    }
}

// [VERTICAL HISTO]
void vhisto(vector<string> commandWords, int numWords)
{
    if (numWords == 2)
    {
        system("Color 02");
        cout << "Displaying a histogram for the " << commandWords[1] << " column\n"
             << "[Frequency of the data is the y-axis]\n";
    }
    else if (numWords == 1)
    {
        system("Color 04");
        cout << "Syntax Error\nColumn name is needed for the function to search the data\n";
    }
    else
    {
        system("Color 04");
        cout << "Syntax Error\nPlease only input one catergory of data that you wish to display as histogra\n";
    }
}

// [HORIZONTAL HISTO]
void hhisto(vector<string> commandWords, int numWords)
{
    if (numWords == 2)
    {
        system("Color 02");
        cout << "Displaying a histogram for the " << commandWords[1] << " column\n"
             << "[Frequency of the data is the x-axis]\n";
    }
    else if (numWords == 1)
    {
        system("Color 04");
        cout << "Syntax Error\nColumn name is needed for the function to search the data\n";
    }
    else
    {
        system("Color 04");
        cout << "Syntax Error\nPlease only input one catergory of data that you wish to display as histogram\n";
    }
}

// [SORT]
void sort(vector<string> commandWords, int numWords)
{
    if (numWords == 2)
    {
        system("Color 02");
        cout << "Sorting the data using the " << commandWords[1] << " column value\n";
    }
    else if (numWords == 1)
    {
        system("Color 04");
        cout << "Syntax Error\nColumn name is needed for the function to search the data\n";
    }
    else
    {
        system("Color 04");
        cout << "Syntax Error\nPlease only input one catergory of data that you wish to sort\n";
    }
}

// [HELP]
void help(vector<string> commandWords, int numWords)
{
    if (numWords == 1)
    {
        system("Color 01");
        cout << "Commands:- [Type 'man (command)' to look up for its usage and format\n"
             << " 1. load\n 2. store\n 3. clone\n 4. html\n 5. min\n 6. max\n 7. median\n 8. mean\n"
             << " 9. variance\n10. stdv\n11. add\n12. sub\n13. corr\n14. regression\n15. show\n"
             << "16. titles\n17. report\n18. rows\n19. columns\n20. vhistomath\n"
             << "21. hhistomath\n22. sorthmath\n23. help [you're here]\n24. oddrows\n"
             << "25. evenrows\n26. primesmath\n27. delete\n28. insert\n29. replace\n";
    }
}

// [ODD ROWS]
void oddrows(vector<string> commandWords, int numWords)
{
    if (numWords == 1)
    {
        system("Color 02");
        cout << "Displaying the odd rows of the data\n";
    }
}

// [EVEN ROWS]
void evenrows(vector<string> commandWords, int numWords)
{
    if (numWords == 1)
    {
        system("Color 02");
        cout << "Displaying the even rows of the data\n";
    }
}

// [PRIMES NUMBER]
void primes(vector<string> commandWords, int numWords)
{
    if (numWords == 2)
    {
        system("Color 02");
        cout << "Displaying the prime numbers in the " << commandWords[1] << " column\n";
    }
    else if (numWords == 1)
    {
        system("Color 04");
        cout << "Syntax Error\nColumn name is needed for the function to search the data\n";
    }
    else
    {
        system("Color 04");
        cout << "Syntax Error\nPlease only input one catergory of data that you wish to display the prime numbers\n";
    }
}

// 4. ADD/DELETE COMMANDS [DELETE/INSERT/REPLACE]
//  [DELETE COMMANDS]
bool numVerify(string str) // to verify whether the last char in string is a number
{
    for (int i = 0; i < str.length(); i++)
    {
        if (isalpha(str[i]))
        {
            return false;
        }
    }
    return true;
}

// delete occurrence
void delocc(vector<string> commandWords, int numWords)
{
    if (numWords != 4)
    {
        system("Color 04");
        cout << "Syntax error; requires column and value to be deleted."
             << endl;
    }
    else
    {
        if (numVerify(commandWords[3]))
        {
            system("Color 02");
            int numverify = stoi(commandWords[3]);
            cout << "Each row containing value " << commandWords[3]
                 << " in " << commandWords[2]
                 << " has been deleted.\n";
        }
        else
        {
            system("Color 04");
            cout << "Row should be in digits.\n";
        }
    }
}

// delete row
void delrow(vector<string> commandWords, int numWords)
{
    if (numWords != 3)
    {
        system("Color 04");
        cout << "Syntax error; requires row.\n";
    }
    else if (numVerify(commandWords[2]))
    {
        system("Color 02");
        int numverify = stoi(commandWords[2]);
        cout << "Row " << commandWords[2] << " has been deleted.\n";
    }
    else
    {
        system("Color 04");
        cout << "Row should be in digits.\n";
    }
}
// delete column
void delcol(vector<string> commandWords, int numWords)
{
    if (numWords != 3)
    {
        system("Color 04");
        cout << "Syntax error; requires column name.\n";
    }
    else
    {
        system("Color 02");
        cout << commandWords[2] << " column has "
             << "been deleted.\n";
    }
}

// DELETE FUNCTION FOR ALL
void del(vector<string> commandWords, int numWords)
{
    if (numWords == 1)
    {
        cout << "Syntax error; requires occurrence, row, or column.\n";
    }
    else if (commandWords[1] == "occurrence")
        delocc(commandWords, numWords);

    else if (commandWords[1] == "row")
        delrow(commandWords, numWords);

    else if (commandWords[1] == "column")
        delcol(commandWords, numWords);

    else
    {
        system("Color 04");
        cout << "No such command exists."
             << " Maybe check your spelling and input entered.\n";
    }
}

// [INSERT COMMAND]
void insertrow(vector<string> commandWords, int numWords)
{
    int j = 3;
    if (commandWords[0] == "insert")
    {
        if (numWords < 4)
        {
            system("Color 04");
            cout << "Syntax error; requires data to be stored.\n";
        }
        else if (numVerify(commandWords[j]))
        {
            for (; j < commandWords.size(); j++)
            {
                int numverify = stoi(commandWords[j]);
            }
            system("Color 02");
            cout << "All values have been stored for "
                 << commandWords[2] << endl;
        }
        else
        {
            system("Color 04");
            std::cout << "The values entered should be in digits.\n";
        }
    }
}

// [REPLACE COMMAND]
void repall(vector<string> commandWords, int numWords)
{
    if (commandWords[0] == "replace")
    {
        if (numWords == 3)
            if (numVerify(commandWords[1]) && numVerify(commandWords[2]))
            {
                system("Color 02");
                cout << commandWords[1] << " has been replaced with "
                     << commandWords[2] << " in all columns.\n";
            }
            else
                cout << "Syntax error; input digit you want to replace with.\n";

        else if (numWords > 2 && numWords < 5)
        {
            if (!(numVerify(commandWords[1])))
            {
                if (numVerify(commandWords[2]) && numVerify(commandWords[3]))
                {
                    system("Color 02");
                    cout << commandWords[2] << " has been replaced with "
                         << commandWords[3] << " in the "
                         << commandWords[1] << " column." << endl;
                } 
                else
                {
                    system("Color 04");
                    cout << "The values entered should be in digits.\n";
                }
            }
        }
        else
        {
            system("Color 04");
            cout << "Syntax error; Enter values to replace "
                 << "and be replaced. Or if you want to replace values "
                 << "in a sepcific column, enter column name first.\n";
        }
    }
}

void manual(vector<string> words, int numWords)
{
    if (numWords != 2)
    {
        cout << "manual requires a command name\n";
        return;
    }
    int commandMode = modeFinder(words[1]);
    switch (commandMode)
    {
    case 1:
        cout << "Load: loads a file from storage\n"
             << "      and stores it in arrays in\n"
             << "      memory.\n"
             << "Format: load filename\n";
        break;
    case 2:
        cout << "Store: saves the active arrays\n"
             << "       into a csv file with the"
             << "       given filename.\n"
             << "Format: store filename\n";
        break;
    case 3:
        cout << "Clone: creates a copy of file1\n"
             << "       with the name of file2.\n"
             << "Format: clone file1 file2\n";
        break;
    case 4:
        cout << "HTML: creates an html file with\n"
             << "      the given filename.\n"
             << "      or\n"
             << "      it reads a csv file1\n"
             << "      and converts it into a \n"
             << "      html file2 with the given\n"
             << "      filename.\n"
             << "Format: html filename\n"
             << "        html filename1 filename2\n";
        break;
    case 5:
        cout << "Min: finds the minimum value in\n"
             << "     the given column.\n"
             << "     or\n"
             << "     if no column is given, it\n"
             << "     finds the minimum value in\n"
             << "     all columns.\n"
             << "Format: min columnname\n"
             << "        min\n";
        break;
    case 6:
        cout << "Max: finds the maximum value in\n"
             << "     the given column.\n"
             << "     or\n"
             << "     if no column is given, it\n"
             << "     finds the maximum value in\n"
             << "     all columns.\n"
             << "Format: max columnname\n"
             << "        max\n";
        break;
    case 7:
        cout << "Median: finds the median value\n"
             << "        in the given column.\n"
             << "        or\n"
             << "        if no column is given,\n"
             << "        it finds the median\n"
             << "        value in all columns.\n"
             << "Format: median columnname\n"
             << "        median\n";
        break;
    case 8:
        cout << "Mean: finds the mean value in\n"
             << "      the given column.\n"
             << "      or\n"
             << "      if no column is given, it\n"
             << "      finds the mean value in\n"
             << "      all columns.\n"
             << "Format: mean columnname\n"
             << "        mean\n";
        break;
    case 9:
        cout << "Variance: finds the variance\n"
             << "          in the given column.\n"
             << "          or\n"
             << "          if no column is given,\n"
             << "          it finds the variance\n"
             << "          in all columns.\n"
             << "Format: variance columnname\n"
             << "        variance\n";
        break;
    case 10:
        cout << "Stdv: finds the standard\n"
             << "      deviation in the given\n"
             << "      column.\n"
             << "      or\n"
             << "      if no column is given, it\n"
             << "      finds the standard\n"
             << "      deviation in all columns.\n"
             << "Format: stdv columnname\n"
             << "        stdv\n";
        break;
    case 11:
        cout << "Add: adds two columns together\n"
             << "     and displays a column with\n"
             << "     the result.\n"
             << "Format: add column1 column2\n";
        break;

    case 12:
        cout << "Sub: subtracts two columns\n"
             << "     together and displays a\n"
             << "     column with the result.\n"
             << "Format: sub column1 column2\n";
        break;
    case 13:
        cout << "Corr: finds the correlation\n"
             << "      between two columns.\n"
             << "Format: corr column1 column2\n";
        break;
    case 14:
        cout << "Regression: finds the linear\n"
             << "            regression line\n"
             << "            formula for a\n"
             << "            column.\n"
             << "Format: regression columnname\n";
        break;

    case 15:
        cout << "Show:     displays data read\n"
             << "          from the file.\n"
             << "          or\n"
             << "          displays the desired column\n"
             << "Format: show\n"
             << "        show (column name)\n";
        break;

    case 16:
        cout << "Titles:     displays the titles\n"
             << "            of all the columns.\n"
             << "            for the files\n"
             << "Format: titles\n";
        break;
    case 17:
        cout << "Report:     displays a report\n"
             << "            that show all the\n"
             << "            satistics for all\n"
             << "            the columns\n"
             << "Format: report\n";
        break;
    case 18:
        cout << "Rows:     displays the number\n"
             << "          of rows loaded\n"
             << "Format: rows\n";
        break;
    case 19:
        cout << "Columns:     displays the number\n"
             << "             of columns loaded\n"
             << "Format: columns\n";
        break;
    case 20:
        cout << "Vertical Histogram:     displays a histogram for\n"
             << "                        the desired column. The histogram will be in form of text histogram\n"
             << "                        [Frequency of the data is the y-axis]\n"
             << "Format: vhisto (column name)\n";
        break;
    case 21:
        cout << "Horizontal Histogram:     displays a histogram for\n"
             << "                        the desired column. The histogram will be in form of text histogram\n"
             << "                        [Frequency of the data is the x-axis]\n"
             << "Format: hhisto (column name)\n";
        break;
    case 22:
        cout << "Sort:     sort the data using\n"
             << "          the desired column value.\n"
             << "Format: sort (column name)\n";
        break;
    case 23:
        cout << "Help:     displays the commands avaialable\n"
             << "Format: help\n";
        break;
    case 24:
        cout << "Odd rows:     displays the odd rows of\n"
             << "              the data.\n"
             << "Format: oddrows\n";
        break;
    case 25:
        cout << "Even rows:     displays the even rows of\n"
             << "               the data.\n"
             << "Format: evenrows\n";
        break;
    case 26:
        cout << "Primes:     displays the prime numbers in\n"
             << "            the desired column.\n"
             << "Format: prime (column name)\n";
        break;

    case 27:
        cout << "Manual:     displays the manual\n"
             << "            for a command.\n"
             << "Format: manual commandname\n";
        break;
    case 28:
        cout << "Delete:     deletes a row or\n"
             << "            column or occurrence\n"
             << "            of a value.\n"
             << "Format: delete row rownumber\n"
             << "        delete column columnname\n"
             << "        delete occurrence value\n";
        break;
    case 29:
        cout << "Insert:     inserts a row of\n"
             << "            values into a column.\n"
             << "Format: insert columnname value1 value2 ...\n";
        break;
    case 30:
        cout << "Replace:    replaces a value with\n"
             << "            another value in a\n"
             << "            column or all columns.\n"
             << "Format: replace value1 value2\n"
             << "        replace columnname value1 value2\n";
        break;
    default:
        system("Color 04");
        cout << "  no such command exists\n";
    }
}

void commandRunner(string command)
{
    int numWords, numColumns, numRows, commandMode;
    vector<string> commandWords;          // vector to store each word of command
    vector<vector<string>> fileData;      // 2d vector to store each row of data
    seperateWords(command, commandWords); // seperates command into words
    numWords = commandWords.size();       // gets number of words in command
    commandMode = modeFinder(commandWords[0]);
    switch (commandMode)
    {
    case -1:
        system("Color 04");
        cout << "invalid command, please try again\n";
        break;
    case 1:
        load(commandWords, numWords, fileData);
        break;
    case 2:
        store(commandWords, numWords, fileData);
        break;
    case 3:
        clone(commandWords, numWords, fileData);
        break;
    case 4:
        checkhtml(commandWords, numWords, fileData);
        break;
    case 5:
        findMin(commandWords, numWords);
        break;
    case 6:
        findMax(commandWords, numWords);
        break;
    case 7:
        findMedian(commandWords, numWords);
        break;
    case 8:
        findMean(commandWords, numWords);
        break;
    case 9:
        findVariance(commandWords, numWords);
        break;
    case 10:
        findStdv(commandWords, numWords);
        break;
    case 11:
        findSum(commandWords, numWords);
        break;
    case 12:
        findDifference(commandWords, numWords);
        break;
    case 13:
        findCorrelation(commandWords, numWords);
        break;
    case 14:
        findRegression(commandWords, numWords);
        break;

    case 15:
        show(commandWords, numWords);
        break;
    case 16:
        titles(commandWords, numWords);
        break;
    case 17:
        report(commandWords, numWords);
        break;
    case 18:
        rows(commandWords, numWords);
        break;
    case 19:
        columns(commandWords, numWords);
        break;
    case 20:
        vhisto(commandWords, numWords);
        break;
    case 21:
        hhisto(commandWords, numWords);
        break;
    case 22:
        sort(commandWords, numWords);
        break;
    case 23:
        help(commandWords, numWords);
        break;
    case 24:
        oddrows(commandWords, numWords);
        break;
    case 25:
        evenrows(commandWords, numWords);
        break;
    case 26:
        primes(commandWords, numWords);
        break;

    case 27:
        manual(commandWords, numWords);
        break;
    case 28:
        del(commandWords, numWords);
    case 29:
        insertrow(commandWords, numWords);
    case 30:
        repall(commandWords, numWords);
    }
}

void interpreterActivate()
{
    system("Color 01");
    cout << "program activated.\n";
}

void interpreterTerminate()
{
    system("Color 01");
    cout << "\a";
    cout << "program terminated.";
}

int main()
{
    interpreterActivate();
    string commandInput;
    do
    {
        commandInput = getCommand(); // gets command
        commandRunner(commandInput);
    } while (commandInput != "exit");
    interpreterTerminate();
}