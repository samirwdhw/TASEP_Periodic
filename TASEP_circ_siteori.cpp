//This is the simulation of TASEP for periodic boundary conditions using a 
//site oriented approach and for Random Sequential Update

#include<iostream>
#include<stdlib.h>
#include<fstream>

using namespace std;

#define N 100		//To determine total size of circular track
#define P 0.5		//Probability of car moving
#define T_MAX 10000	//To determine max number of moves
#define CHECK_POINT 10 //Point where we check J
#define N_RUNS 100		//To define number of runs to take avg
#define FILE_NAME "results_siteori.dat"	//File to output data
#define WARM_UP 1000	//Time for which warmup is assumed

int track[N];   //To maintain the circular track 
int list[N];		//To maintain where the 1's are
int count;			//For calculating J later

struct check_list{

	int a[N];					//to store the ones that have changed
	int q;						//to append

	check_list(){
		
		q = 0; 


		for(int i = 0; i<N; i++){

			a[i] = -1;
		}
	}

	void append(int t){
		
		a[q] = t;
		q++; 
	}

	int check(int t){

		for(int i = 0; i<q; i++){

			if(a[i] == t){
				return 1;
			}

		}

		return 0;
	}	

};

void initialize(int a[]) {

	for(int i = 0; i<100; i++) {

		a[i] = 0;
	}
}

float rand1(){		//To generate values b/w 0,1

	float val = (float)rand()/RAND_MAX;

	return val;
}


int ret_rand(int a){	//To return int b/w 0,a

	int val = a*rand1();

	return val;

}

void fill(int n) {

	for(int i = 0; i<n; i++){

		int t = ret_rand(N);

		if( track[t] == 1){
			i--;
		}
		else{
			track[t] = 1;
			list[i] = t;
		}

	}

}





void move(int rho, int run_time){

	//check_list update; 		//To check if that car has moved

	//cout<<"From here: "<<endl;


	for(int i = 0; i<N; i++){

		if(track[i] == 0){
			continue;
		}

		int t = ret_rand(rho);

		//cout<<t<<endl;
		/*
		if(update.check(t) == 1){
			i--;
			continue;
		}*/

		int pos = list[t];
		int next_pos = (pos+1)%N;

		if(track[next_pos] == 0){

			float prob_check = rand1();
			
			if( prob_check <= P){

				track[pos] =  0;
				track[next_pos] = 1;

				if(pos == CHECK_POINT && run_time > WARM_UP){
					count++;
				}

				list[t] = next_pos;
			}

			//update.append(t);

		}

	}

	//cout<<"End here"<<endl;
}
	

int main(){
	
	int rho; 			//density
	float J_avg;	//To take average of many J's

	ofstream f1;
	f1.open(FILE_NAME);


	for(rho =  0; rho<= N; rho++){ 		//Must go from 0 to N

		J_avg = 0;

		for(int run = 0; run< N_RUNS; run++){

			srand(run);

			initialize(track);
			initialize(list);

			fill(rho);

			//print(list);

			count = 0;				//for calculating J later

			for(int t = 0; t< T_MAX; t++){		//change 1 to T_MAX

				move(rho, t);

			}

			float J = (float)(count)/(T_MAX - WARM_UP);
		
			J_avg += J;

			//f1<<J<<endl;

		}

		cout<<endl<<J_avg<<" "<<rho<<"/"<<endl;

		f1<<(float)rho/N<<" "<<J_avg/N_RUNS<<endl;

	}

	f1.close();

	//print(list);


	return 0;
}