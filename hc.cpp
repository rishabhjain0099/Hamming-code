#include<iostream>
#include<cmath>
using namespace std;


int parbit[100];
void paritybit(long dataSend[],int size , int parity)
{
int flag=parity;
int sum=0;
for(int i=parity;i<=size;)
	{	flag--;
		if(dataSend[i-1]==1)
			{sum+=1;
			}
		i++;
		if(flag==0)
			{flag+=parity;i+=parity;
			}
	}

	if(sum%2==1)
	{dataSend[parity-1]=1;
	parbit[parity-1]=1;

	}
	else {
		parbit[parity-1]=0;
		dataSend[parity-1]=0;		
		}
}


void Recievedparitybit(long dataSend[],int size , int parity)
{
int flag=parity;
int sum=0;
for(int i=parity;i<=size;)
	{	flag--;
		if(dataSend[i-1]==1)
			{sum+=1;
			}
		i++;
		if(flag==0)
			{flag+=parity;i+=parity;
			}
	}

	if(sum%2==1)
	{	if(dataSend[parity-1]==0)dataSend[parity-1]=1;
		else dataSend[parity-1]=0;

	parbit[parity-1]=1;

	}
	else parbit[parity-1]=0;      
}





int main()
{

	int n;



	//inputing data bits from the user.
	cout<<"Enter the no of data bits\n ";
	cin>>n;
	long databit[n];
	for(int i=0;i<n;i++)
		{
		cout<<"\nEnter bit "<<(i+1)<<"-";
		cin>>databit[i];
		}

	cout<<"DATA BITS ARE\n";



	//printing generated code.
	for(int i=0;i<n;i++)
	{
	cout<<databit[i]<<" ";
	}
	
	cout<<endl;

	//CAlculating the no of parity bits required.

	int r=0;
	for(int h=0;;h++)
	{	if(pow(2,h)>=(n+h+1))

		{
		r=h;
		break;
		}
	}
	cout<<"NO OF REDUNCY BITS REQUIRED : "<<r<<endl;

	//creating sender's side array.
	long dataSend[r+n];
	int k=0,j=0;

	for(int i=0;i<(r+n);i++)
	{
		if(i!=(pow(2,j)-1))
			{
			dataSend[i]=databit[k];
			k++;
			}
		else
			{dataSend[i]=0;	
			j++;	
			}
	
	
	}

	
// parity bit adjuster	

	for(int j=1;j<=r+n;j=j*2)
	{paritybit(dataSend,(r+n),j);}
	


	//printing the Encoded array.

	cout<<"TRANSMITTED ARRAY IS\n";
	for(int p=0;p<(r+n);p++)
	{
	cout<<dataSend[p]<<" ";
	}
	cout<<endl;



	
//inputing data bits from the user at reciever's End.
	cout<<"Enter recieved bits(ONLY 1 ERROR Is supposed to Enter at max)\n";

	long recbit[n];
	for(int i=0;i<n;i++)
		{
		cout<<"\nEnter bit "<<(i+1)<<"-";
		cin>>recbit[i];
		}

	cout<<"DATA BITS ARE\n";
//printing
for(int i=0;i<n;i++)
	{
	cout<<recbit[i]<<" ";
	}
	
	cout<<endl;

//creating Reciever's side array.
	long dataRec[r+n];
	k=0,j=0;int x=0;

	for(int i=0;i<(r+n);i++)
	{
		if(i!=(pow(2,j)-1))
			{
			dataRec[i]=recbit[k++];
			
			}
		else
			{dataRec[i]=parbit[i];	
			j++;	
			}
	
	
	}



//printing the Encoded array at reciever's End.

	cout<<"Recieved ARRAY IS\n";
	for(int p=0;p<(r+n);p++)
	{
	cout<<dataRec[p]<<" ";
	}


//make a copy

long copydataRec[r+n];
for(int i=0;i<r+n;i++)
{copydataRec[i]=dataRec[i];}




//check Parity bits are correct or not

int StoredParity[r];x=0;

for(int g=1;g<r+n;g=g*2)
{
Recievedparitybit(dataRec,r+n,g);

	if(dataRec[g-1]==copydataRec[g-1])
	StoredParity[x++]=0;
	else StoredParity[x++]=1;
	
}
cout<<"\nTmp";
for(int p=0;p<(r+n);p++)
	{
	cout<<dataRec[p]<<" ";
	}



cout<<"Error Code : ";
for(int i=0;i<r;i++)
{cout<<StoredParity[i];}
int sum=0;
for(int i=0;i<r;i++)
{
	if(StoredParity[i]==1){
				sum+=pow(2,i);}
}	
cout<<"\nError Found at position "<<sum;

cout<<"\nFinal Correct Array is ";
if(sum>0)
{
	if(copydataRec[sum-1]==1)copydataRec[sum-1]=0;
	else copydataRec[sum-1]=1;
	
	
	for(int p=0;p<(r+n);p++)
	{
	cout<<copydataRec[p]<<" ";
	}



}
else cout<<"\nERROR NOT FOUND!!";


return 0;
}









                          
