#include <iostream>
//#include "Values.h"
using namespace std;

class Values {
private:
 int NrValues;
static const int MaxValues=100;
	int t, j;
	float values[MaxValues];
	float smallest;
	float largest;
	float sum;
	float temp;
float clone_values[MaxValues];
public:
	Values() {
		NrValues = 0;
		t = 0;
		j = 0;
		for (int i = 0; i < MaxValues; i++) {
			values[i] = 0.0;
		}
		smallest = 0;
		largest = 0;
		sum = 0;
		temp=0;
	}
	Values(float array[], int size) {
		NrValues = size;
		for (int i = 0; i < NrValues; i++) {
			values[i] = array[i];
		}
		t = 0;
		j = NrValues;
		smallest = 0;
		largest = 0;
		sum = 0;
		for (int i = 0; i < NrValues; i++) {
			clone_values[i] = array[i];
		}
		temp=0;
	}

	void add( float value) {
		if (NrValues == MaxValues) {
			cout << "Cannot add" << endl;
		}
		else {
			values[NrValues] = value;
			clone_values[NrValues]=value;
			NrValues++;
			j++;
		}
	}

	void display_forward() {
		if (t == NrValues) {
			t = 0;
			return;
		}
		else {
			cout << values[t] << endl;
			t++;
			display_forward();
		}
	}

	void display_reverse() {
		if (j ==0) {
			j = NrValues;
			return;
		}
		else {
			cout << values[j-1] << endl;
			j--;
			display_reverse();
		}

	}
	float find_smallest() {
		if (t == 0) {
			 smallest = values[0];
		}
		else;
		if (t>= NrValues-1) {
			t = 0;
			return smallest;
		}
		else {
			if (smallest > values[t+1]) {
				smallest = values[t+1];
				t++;
				find_smallest();
			}
			else {
				t++;
				find_smallest();
			}
		}
	
	}
	float find_largest() {
		if (t == 0) {
			largest= values[0];
		}
		else;
		if (t >= NrValues - 1) {
			t = 0;
			return largest;
		}
		else {
			if (largest < values[t + 1]) {
				largest = values[t + 1];
				t++;
				find_largest();
			}
			else {
				t++;
				find_largest();
			}
		}
	}

	float sum_values() {
		if (t == NrValues) {
			t = 0;
			return sum;
		}
		else {
			sum = sum + values[t];
			t++;
			sum_values();
		}
	}
      bool exists(float value) {
		if (values[t]==value) {
			t = 0;
			return 1;
		}
		else {
			t++;
			if (t == NrValues) {
				t = 0;
				return 0;
			}
			else exists(value);
		}
	}
	  int  num_pos() {
		  if (t == 0) {
			  sum = 0;
		  }
		  if (t == NrValues) {
			  t = 0;
			  return sum;
		  }
		  if (values[t] > 0) {
			  sum++;
			  t++;
			  num_pos();
		  }
		  else {
		  t++;
		  num_pos();
	  }
	}
	//exercise 3 of hw
	void five_largest(){
		if(clone_values[0]>=clone_values[1] && clone_values[1]>=clone_values[2] &&
		clone_values[2]>=clone_values[3] &&clone_values[3]>=clone_values[4]){
			t=0;
			cout<<clone_values[0]<<" "<<clone_values[1]<<" "<<clone_values[2]<<" "<<clone_values[3]<<" "<<clone_values[4]<<endl;
			exit(1);
		}
		if(t==NrValues){
			t=0;
			five_largest();
		}
		if(clone_values[t]<clone_values[t+1]){
			temp=clone_values[t+1];
			clone_values[t+1]=clone_values[t];
			clone_values[t]=temp;
			t++;
			five_largest();
		}
		else {
		t++;
		five_largest();
	}
	
}};
int main() {
	
	float valuelist[] = {1,-2.3,3,4.92,5,4.5,0.2};
	int size= sizeof(valuelist) / sizeof(valuelist[0]);
	Values object(valuelist, size);

	cout << "Does the array contain 3?: "<<object.exists(3) << endl;
	cout << "Does the array contain -2?: " <<object.exists(-2) << endl;
	
	cout<<"The array displayed forward: "<<endl;
	object.display_forward();
	cout << endl;
	cout<<"The array displayed reverse: "<<endl;
	object.display_reverse();
	cout << endl;
	cout<<"The largest value: "<<endl;
	cout << object.find_largest() << endl;
	cout<<"The smallest value: "<< endl;
	cout << object.find_smallest() << endl;
	cout<<"The sum of the values: "<< endl;
	cout << object.sum_values() << endl;
	cout<<"The number of positive values: "<< endl;
	cout << object.num_pos()<< endl;
	//I also added this to test the code
	cout<<"The five largest values are: "<<endl;
	object.five_largest();
}

