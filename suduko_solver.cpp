#include<bits/stdc++.h>
using namespace std;

class Suduko
{
    private:
        int row, col;
        vector<vector<int> >a;

    public:
        Suduko(); //constructor for initialization
        void getInputs(); //get dimensions and entries of suduko from the user
        bool findUnassigned(int&, int&); //finds the empty places in the suduko
        bool checkSafe(int, int, int); //checks that is the passed digit is present in particular row, col, box or not;
        bool solver(); //a recursive function which puts the expected value in empty places and backtracks if after continuing with this value doesn't able to solve suduko
        void print(); //printing the solved suduko
};

Suduko::Suduko()
{
    row=0, col=0;
}

void Suduko:: getInputs()
{
    cout<< "\n Enter the dimensions of the suduko: ";
    // dim=1 => row=1, col=1
    // dim=2 => row=4, col=4
    // dim=3 => row=9, col=9
    int dim;
    cin>>dim;
    row = pow(dim,2);
    col = pow(dim,2);

    a = vector<vector<int> >(row, vector<int> (col));
    cout<<"\n Enter the values in the suduko row-wise(put 0 for empty places): \n";
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            cin>>a[i][j]; 
}

bool Suduko::findUnassigned(int &i, int &j)
{
    for(i=0;i<row;i++)
        for(j=0;j<col;j++)
            if(a[i][j]==0)
                return true;
    return false;
}

bool Suduko::checkSafe(int r, int c, int n)
{
    bool ans1=false, ans2=false, ans3=false;

    // checking the digit n in theh particular row
    for(int i=0;i<col;i++)
        if(a[r][i]==n)
        {
            ans1=true;
            break;
        }
    
    // checking the digit n in theh particular col
    for(int i=0;i<row;i++)
        if(a[i][c]==n)
        {
            ans2=true;
            break;
        }
    
    // checking the digit n in theh particular 3x3 box
    for(int i=0;i<sqrt(row);i++)
        for(int j=0;j<sqrt(col);j++)
            if(a[i+r-r%((int)sqrt(row))][j+c-c%((int)sqrt(col))]==n)
            {
                ans3=true;  
                break;
            }
    
    // doing 'not' as true values of these ans means that values are present in particular row, col or box which means its isn't safe to go with that digit
    return !ans1 && !ans2 && !ans3;
}

bool Suduko::solver()
{
    int i,j;
    if(!findUnassigned(i,j))  //i, j will have coordinates of empty places in the suduko
        return true;   

    for(int n=1; n<=row; n++)
        if(checkSafe(i,j,n)) //checks if putting n at (i, j) will be valid or not
        {
            a[i][j]=n;
            if(solver()) //recursive call
                return true;

            //backtracking statement
            a[i][j]=0;
        }     
    return false; //no digit can be filled at empty place (i,j) some previous assumption is wrong or no solution exists for given suduko
}

void Suduko::print()
{
    // added some -, | and + for clear visualization
    string s(2*(int)sqrt(row)+1,'-');
    s+='+';
    cout<<'+';
    for(int i=0;i<sqrt(row);i++)
        cout<<s;
    cout<<'\n';
    for(int i=0;i<row;i++)
    {
        cout<<"| ";
        for(int j=0;j<col;j++)
            cout<<a[i][j]<<(j%((int)sqrt(col))==((int)sqrt(col-1))?" | ":" ");
        if(i%((int)sqrt(row))==(int)sqrt(row)-1)
        {
            cout<<"\n+";
            for(int i=0;i<sqrt(row);i++)
                cout<<s;
        }
        cout<<'\n';
    }
}


int main()
{
    Suduko s;
    s.getInputs();
    if(s.solver())
    {
        cout<<"\nSolved suduko\n";
		s.print();
    }
    else
        cout<<"No solution exists";

    cerr<<"[Execution : "<<(1.0*clock())/CLOCKS_PER_SEC<<"s]\n";
    return 0;
}

// test case 1
// 2
// 1 0 0 4
// 3 0 0 2
// 0 1 4 0
// 0 3 0 1

// Expected output 1
// +-----+-----+
// | 1 2 | 3 4 | 
// | 3 4 | 1 2 | 
// +-----+-----+
// | 2 1 | 4 3 | 
// | 4 3 | 2 1 | 
// +-----+-----+


// test input 2
// 3
// 3 0 6 5 0 8 4 0 0 
// 5 2 0 0 0 0 0 0 0 
// 0 8 7 0 0 0 0 3 1 
// 0 0 3 0 1 0 0 8 0 
// 9 0 0 8 6 3 0 0 5 
// 0 5 0 0 9 0 6 0 0 
// 1 3 0 0 0 0 2 5 0 
// 0 0 0 0 0 0 0 7 4
// 0 0 5 2 0 6 3 0 0

// Expected output 2
// +-------+-------+-------+
// | 3 1 6 | 5 7 8 | 4 9 2 | 
// | 5 2 9 | 1 3 4 | 7 6 8 | 
// | 4 8 7 | 6 2 9 | 5 3 1 | 
// +-------+-------+-------+
// | 2 6 3 | 4 1 5 | 9 8 7 | 
// | 9 7 4 | 8 6 3 | 1 2 5 | 
// | 8 5 1 | 7 9 2 | 6 4 3 | 
// +-------+-------+-------+
// | 1 3 8 | 9 4 7 | 2 5 6 | 
// | 6 9 2 | 3 5 1 | 8 7 4 | 
// | 7 4 5 | 2 8 6 | 3 1 9 | 
// +-------+-------+-------+
