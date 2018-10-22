#include<fstream>
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
int start = 0;
int end = 0; 
const int maxtrains = 30;
const int maxstations = 100;
const int infin = 700;
const int MIN_MENU = 0;    
const int MAX_MENU = 4;
const int blanks = 30;
int stationcount = 0;		
const int y = 100;
int x = 0, hourNormal, minuteNormal, pHour, pMinute, mornnight, printampm, a[y], b[y], arrl, dep;



struct TRAINSSTRUCT
{
	int DStat;
	int AStat;
	int Dtime;
	int Atime;
	int travel;
};

TRAINSSTRUCT trains[maxstations][maxstations];
string stations[maxstations];
int A[maxstations][maxstations];
int P[maxstations][maxstations];
int hourmin[maxstations];

int PK[maxstations];
int PKcount = 0;


int printtime ( int mytime )
{
	TRAINSSTRUCT train[maxtrains][maxtrains];
	int time;
	int a[x];
	int b[x];


	time = mytime;
	
	pHour = time/60;
	pMinute = time%60;
	
	if( time < 1200)
		mornnight = 1; 
	else
	{
		mornnight = 0; 
	}
	
	if( pHour > 12 )
		pHour = pHour-12;

}

int printHM ( int gettime )
{
	int thetime;
	int i = 0;
	
	
	thetime = gettime;

		hourNormal = gettime/60;
		minuteNormal = gettime%60;

}

void readinStations ( void )
{
	
 	int count = 0;
 
 
	ifstream infile;
	infile.open("stations.dat");
	
	if(!infile)
	{
		cout<<"dat file not found"<<endl;
		return;
	}
	count = -1;

	int num;
	string name;	
	
	while(!infile.eof())
	{
		infile>>num;
		infile>>name;
		stations[num] = name;
		count++;
	}	
	infile.close();
	
	for (int i = 0; i < count; i++)
		cout << i << ": " << stations[i] << endl;
	

	stationcount = count;
}



int shortest ( int a[maxstations][maxstations], TRAINSSTRUCT c[maxstations][maxstations], int p[maxstations][maxstations] )
{
	int i;
	int k;
	int j; 
	
	
	for( int i = 0; i < stationcount; i++ )
	{
		for( int j = 0; j <stationcount; j++ )
		{
			a[i][j] = c[i][j].travel;
			p[i][j] = -1;
		}
	}
	
	for( int i = 0; i < stationcount; i++ ) 
	{
		a[i][i] = 0; 
	}
	
	
	for( int k = 0; k < stationcount; k++ )
	{
		for( int i = 0; i < stationcount; i++ )
		{
			for( int j = 0; j <stationcount; j++ )
			{
				if( a[i][k] + a[k][j] < a[i][j] )
				{
					a[i][j] = a[i][k] + a[k][j];
					p[i][j] = k;
				}	
			}
		}
	}
	

}

void path ( int i, int j )  
{
	int k;
	k = P[i][j];
	
	if( k == -1 )
	{
		
		return;			
	}

		
	path( i, k );			
	PK[PKcount++] = k;		
	path( k, j );			
	
	
}


void readinTrainInfo( void )
{
	TRAINSSTRUCT train[maxtrains][maxtrains];
	int a, b;
	ifstream infile; 
	
	for (int i = 0; i < maxtrains; i++)
		for (int j = 0; j < maxtrains; j++)
			trains[i][j].travel = infin;
			

	infile.open("trains.dat");
	if(!infile)
	{
		cout<<"dat file not found"<<endl;
		return;
	}
	
	while(!infile.eof())
	{
		infile>>a;
		infile>>b;
	
		infile>>trains[a][b].Dtime;
		infile>>trains[a][b].Atime;
		trains[a][b].DStat = a;
		trains[a][b].AStat = b;
		trains[a][b].travel = trains[a][b].Atime - trains[a][b].Dtime;
	
	}
	
}

void timetotravel ( int ds, int as )
{
	int i = 0;
	
	
	hourmin[x] = A[ds][as];
	
	int gettime = A[ds][as];
		
	cout << endl;
	cout << "==============================================" << endl;
	cout << endl;
	
	cout << "To go from " << stations[start] << " to " << stations[end] << ", you will need to ride on a train for " << endl;
		printHM( gettime ); 
		cout << hourNormal << " hours and " << minuteNormal << " minutes" << endl;
		cout << endl;
		cout << endl;
}

void shorttime( int ds, int as )
{	
	int i = 0;
	

		
	a[x] = trains[ds][as].Dtime;
	b[x] = trains[ds][as].Atime;
		
	arrl = a[x];
	dep = b[x];
	

		cout << "Leave " << stations[ds] << " at ";
		printtime( arrl );
		cout << pHour << ":";
		if( pMinute < 10)
			cout << "0" << pMinute;
		else
			cout << pMinute;
		if( mornnight == 1)
	 	cout << "AM" ;
		else
	 	cout << "PM" ;
		cout << " and arrive at " << stations[as] << " at ";
		printtime( dep ); 
		cout << pHour << ":" ;
		if( pMinute < 10)
			cout << "0" << pMinute;
		else
			cout << pMinute;
		if( mornnight == 1)
	 	cout << "AM";
		else 
	 	cout << "PM";
		cout << endl;

		
	
}


void clearFunc(void)
{
  int i;
  for (i=0;i<blanks;i++)
  {
    cout << endl;
  }
}

void pauseFunc(void)
{
  int key;
  printf("\nEnter a number to continue:       ");
  scanf("%i",&key);
  printf("\n");
}


int menu ( void )
{
	int key=-1;
  	while ((key < MIN_MENU) || (key > MAX_MENU))
    {
    clearFunc();
    		cout << "\n\n==================================================\n";
    		cout << "\n\n======= Author: Michael Maldonado ================\n";
    		cout << "\n\n==================================================\n";
			cout << "Menu \n\n" ;
			cout << "1. List Stations and Numbers\n";
			cout << "2. Find Shortest Travel Time on Trains\n";
			cout << "3. Find Shortest Time Overall\n";
			cout << "0. Exit Program\n";
			cout << "==================================================\n";
			cout << "Enter your choice: " << endl;
    scanf("%i",&key);
    clearFunc();
  	
    }
  return key;
}

int main ( void )
{
	int key = -1;
	int count = 0;


	readinStations ( );
	readinTrainInfo ( );	
	shortest ( A, trains, P );


	
  while (key != 0)
  {
  	int bigkey = -1;
  
    key=menu();
	
    switch (key)	
    {
    case 0:

	  	break;
	  	
    case 1:
    	cout << "View the Stations Numbers" << endl;
		readinStations();   
		pauseFunc();
    	break;	
    	
    case 2:
    	cout << "Where would you like to go?" <<endl;
    	printf(" Enter a starting point: ");
    	scanf("%i", &start);
    	printf(" Enter a ending point: ");
    	scanf("%i", &end);
    	
    	
    	
    	
    	if ( start == end )
    	{
    		cout << "SAME START AND END POINTS" << endl;
    		pauseFunc();
    		break;
    	}
		
		PKcount = 0;
    	for (int i =0; i< maxtrains; i++)
    	{
    	  PK[i] = -1;
		}
		
		path (start, end);
			
    	if(A[start][end] == infin)
		{				
    		cout << "There is no path between " << start << " and " << end  << endl;
    		pauseFunc();
    		break;
    	}
    		   		
    	if (PK[0] == -1)  
		{
			cout << endl;
			cout << A[start][end] << endl;
			timetotravel( start, end );  
			cout << "You will take the following trains:" << endl;
			shorttime( start, end );
		}
 		else
		  {	
		    PKcount = 1;
		    cout << A[start][end] << endl;
			timetotravel( start, end); 
			cout << "You will take the following trains:" << endl;
			shorttime(start, PK[0] );
			
		    while( PK[PKcount] != -1)
    	    {
		      shorttime(PK[PKcount-1], PK[PKcount]);
    	      PKcount++;
			}  
    	    shorttime( PK[PKcount-1] ,end); 		
		  } 
		
		
    	
    	pauseFunc();
    	break;
    	
    case 3:
    
    	cout << "this was the optional function :D " <<endl;
    	
    	
    	pauseFunc();
    	break;
		
	}
	}

}
