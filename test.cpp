//Name: Muhammad Zabil Mehboob, Course: BESE 28-C
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;


void conversion(string &Str, double Real[], double Imaginary[], int index)   //We pass by reference so values can be sent to main
{
    stringstream ss(Str);  //Used to change string to num
    string real, imag;     //Save the string parts
    
    // Real part comes before '+' and imaginary part comes before 'i'
    getline(ss, real, '+');
    getline(ss, imag, 'i');
    
    // Converting to nubmers
    Real[index] = stod(real);
    Imaginary[index] = stod(imag);
}

void sort(double Re1[], double Im1[], double Re2[], double Im2[])
{
	/*The criteria for sorting is that the value with highest real part of number 1 
	  has been put last. 
	  In other words, it is sorted in ascending order of Re1 (real part of complex number 1)
	*/
	
	double temp;      //Needed to swap elements
	for(int i=0; i<500; i++)
	{
		for(int j=i+1; j<500; j++)
		{
			if(Re1[i]>Re1[j])
			{
				temp=Re1[i];       //Sorting the real parts of first numbers
				Re1[i]=Re1[j];
				Re1[j]=temp;
				
				temp=Im1[i];      //Sorting the imaginary parts of first numbers
				Im1[i]=Im1[j];
				Im1[j]=temp;
				
				temp=Re2[i];      //Sorting the real parts of second numbers
				Re2[i]=Re2[j];
				Re2[j]=temp;
				
				temp=Im2[i];      //Sorting the imaginary parts of second numbers
				Im2[i]=Im2[j];
				Im2[j]=temp;
			}
		}
	}
}

int main()
{
	double Re1[500], Im1[500], Re2[500], Im2[500];       //Used to store the parts of the complex numbers
	int index=0;             //Used to control the array indexes
    string str;                      //Used to store the whole line of file
    ifstream fin("InputData.txt");   //Used to read files
    ofstream fout("Complexresult.txt");   //Used to write files
	getline(fin,str);   //As first line of file is useless
	
	fout<<"Z1,  Z2,  Z1+Z2,  Z1-Z2,  Z1Z2,  Z1/Z2,  Z1_1,  Z2_1,  Z1`,  Z2`"<<endl;
	
    while (getline(fin, str))   //Gets the whole line from file and keeps running till no more lines
    {	
        stringstream ss(str);        //Used to convert strings to numbers
        string str1, str2;           //To store the complex numbers as strings

        // Separating both complex numbers as strings
        getline(ss, str1, ',');
        getline(ss, str2, ',');
		
		// In case of error in reading string value, restart loop
        if (ss.fail())
        {
            continue;
        }
		
        // Extracting real and imaginary parts of the strings
        conversion(str1, Re1, Im1, index);
        conversion(str2, Re2, Im2, index);
        index++;
	}
	
	//Used to sort the arrays
    sort(Re1,Im1,Re2,Im2);
    
    //Outputing to file
	for(int i=0; i<500; i++)
	{
		//Z1
		fout<<Re1[i]<<"+"<<Im1[i]<<"i,  ";
		
		//Z2
		fout<<Re2[i]<<"+"<<Im2[i]<<"i,  ";
		
        //Addition
        fout<<Re1[i] + Re2[i]<<"+"<<Im1[i] + Im2[i]<<"i,  ";
        
        //Subtraction
        fout<<Re1[i] - Im1[i];
        //Exception handling for negative numbers
        if(Im1[i]-Im2[i]>0)
        fout<<"+";
        fout<<Im1[i] - Im2[i]<<"i,  ";
        
        //Setprecision is used to match significant figures of the numbers in the question
        //Multipication
        fout<<setprecision(3)<<(Re1[i] * Re2[i]) - (Im1[i] * Im2[i])<<"+"<<setprecision(3)<<(Re1[i] * Im2[i]) + (Re2[i] * Im1[i]) <<"i,  ";
        
        //Division
        fout<<setprecision(3)<<(Re1[i] * Re2[i] + Im1[i] * Im2[i]) / (Re2[i] * Re2[i] + Im2[i] * Im2[i]);
        //Exception handling for negative numbers
        if ((Im1[i] * Re2[i] - Re1[i] * Im2[i]) > 0)
        fout<< "+";
        fout<<setprecision(3)<<(Im1[i] * Re2[i] - Re1[i] * Im2[i]) / (Re2[i] * Re2[i] + Im2[i] * Im2[i])<<"i,  ";
        
        // Multiplicative Inverse of Z1
        fout<<setprecision(3)<<Re1[i] / (Re1[i] * Re1[i] + Im1[i] * Im1[i])<<"-"<<setprecision(3)<< Im1[i] / (Re1[i] * Re1[i] + Im1[i] * Im1[i])<<"i,  ";
        
        // Multiplicative Inverse of Z2
        fout<<setprecision(3)<<Re2[i] / (Re2[i] * Re2[i] + Im2[i] * Im2[i])<<"-"<<setprecision(3)<< Im2[i] / (Re2[i] * Re2[i] + Im2[i] * Im2[i])<<"i,  ";
        
        // Z1 Conjugate
        fout<<Re1[i]<<"-"<<Im1[i]<<"i,  ";
        // Z2 Conjugate
        fout<<Re2[i]<<"-"<<Im2[i]<<"i,  "<<endl;
    }
    //Closing Files
    fin.close();
    fout.close();
}

/*The criteria for sorting is that the value with highest real part of number 1 has been put last. 
	In other words, it is sorted in ascending order of Re1 (real part of complex number 1)
*/