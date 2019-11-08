#include <iostream>
#include <fstream>
#include <istream>
using namespace std;
#include <bits/stdc++.h>

using namespace std;

// function to find out the minimum penalty
void getMinimumPenalty(string line1, string line2, int mismatchNum, int gap)
{
    ofstream PartB("2b.txt");
    ofstream PartC("2c.txt");
    int i, j; // intialising variables

    int m = line1.length(); // length of gene1
    int n =line2.length(); // length of gene2

    // table for storing optimal substructure answers
    int matrix
    [n+m+1][n+m+1] = {0};

    // intialising the table
    for (i = 0; i <= (n+m); i++)
    {
        matrix
        [i][0] = i * gap;
        matrix
        [0][i] = i * gap;
    }
      for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if ( line1[i - 1] ==line2[j - 1])
            {
                matrix
                [i][j] = matrix[i - 1][j - 1]+2;
            }
            else
            {
                matrix
                [i][j] = max({matrix[i - 1][j - 1] + mismatchNum ,
                                matrix
                                [i - 1][j] + gap ,
                                matrix
                                [i][j - 1] + gap });
            }
        }
    }
    

    // Reconstructing the solution
    int l = max(m,n); // maximum possible length

    i = m; j = n;

    int line1pos = l;
    int line2pos = l;

    // Final answers for the respective strings
    int line1ans[l+1],line2ans[l+1];

    while ( !(i == 0 || j == 0))
    {
        if (matrix
            [i-1][j-1]+2==matrix
        [i][j] && line1[i - 1] ==line2[j - 1]  )
        {
            cout << line1[i-1] <<line2[j-1] << endl;
            line1ans[line1pos--] = (int)line1[i - 1];
           line2ans[line2pos--] = (int)line2[j - 1];
            i--; j--;
        }
        else if (matrix
                 [i - 1][j - 1] + mismatchNum == matrix[i][j])
        {
            line1ans[line1pos--] = (int)line1[i - 1];
           line2ans[line2pos--] = (int)line2[j - 1];
            i--; j--;
        }
        else if (matrix
                 [i - 1][j] + gap == matrix[i][j])
        {
            cout << line1[i-1] << endl;
            line1ans[line1pos--] = (int)line1[i - 1];
           line2ans[line2pos--] = (int)'-';
            i--;
        }
        else if (matrix
                 [i][j - 1] + gap == matrix[i][j])
        {
            cout <<line2[j-1] << endl;
            line1ans[line1pos--] = (int)'-';
           line2ans[line2pos--] = (int)line2[j - 1];
            j--;
        }
    }
    while (line1pos > 0)
    {
        if (i > 0) line1ans[line1pos--] = (int)line1[--i];
        else line1ans[line1pos--] = (int)'_';
    }
    while (line2pos > 0)
    {
        if (j > 0)line2ans[line2pos--] = (int)line2[--j];
        else line2ans[line2pos--] = (int)'_';
    }

    int startNum = 1;
    for (i = l; i >= 1; i--)
    {
        if ((char)line2ans[i] == '_' && (char)line1ans[i] == '_')
        {
            startNum = i + 1;
            break;
        }
    }



    // Printing the answer
    cout << "Minimum Penalty in aligning the genes = ";
    cout << matrix
    [m][n] << "\n";
    cout << "The aligned genes are :\n";
    for (i = startNum; i <= l; i++)
    {
        cout<<(char)line1ans[i];
        PartC<<(char)line1ans[i];
    }
    cout << "\n";
    PartC<<"\n";
    for (i = startNum; i <= l; i++)
    {
        cout << (char)line2ans[i];
        PartC<<(char)line2ans[i];
    }

//getting the num from were the string actually starts to store it in our file.

    for(int count=m;count>=1;count--){
        if(line1ans[count]=='-'&& line2ans[count]=='-'){
            startNum=count+1;
            break;
        }
    }
    fstream fileC("2C.txt");
    string stringAns;
    for (int i = startNum; i <= m; i++)
    {
        stringAns+=line1ans[i];
    }
    fileC<<stringAns<<"\n";
    stringAns="";
    for (int i = startNum; i <= m; i++)
    {
        stringAns+=line2ans[i];
    }
    fileC<<stringAns;
    cout << endl;
    for(int i=0;i<m+1;i++)
    {
        for(int j=0;j<n+1;j++)
        {
            cout << matrix
            [i][j] << "\t";
            PartB << matrix
            [i][j] << "\t";
        }
        cout << endl;
        PartB<< "\n";
    }
    cout << endl<< m<<" "<< n;

    return;
}

// Driver code
int main(){
    // input strings

    std::ifstream file;

    file.open("2.txt");
    if(file.is_open()){
        std::cout<<"File is open"<<std::endl;
    }

    int length1, length2;
    std::string line1,line2;
    ////Part A start
    std::getline(file,line1);
    std::getline(file,line2);
    //std::cout<<line1<<std::endl<<line2<<std::endl;

    length1=line1.length();
    length2=line2.length();


    file.close();
    std::ofstream outputFile("2A.txt");
    if (length1>length2){
        outputFile << length2;
        //std::cout<< "Writing complete Length2"<<std::endl;
    }
    else{
        outputFile << length1;
        //std::cout<< "Writing complete Length1"<<std::endl;
    }

    // intialsing penalties of different types
    int misMatchPenalty = -1;
    int gapPenalty = -2;

    // calling the function to calculate the result and output results into files
    getMinimumPenalty(line1, line2,
                      misMatchPenalty, gapPenalty);
    return 0;
}
