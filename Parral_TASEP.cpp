#include<iostream>
#include<stdlib.h>
#include<fstream>

using namespace std;

#define N 100		//To determine total size of circular track
#define P 0.1		//Probability of car moving
#define T_MAX 30000	//To determine max number of moves
#define CHECK_POINT 10 //Point where we check J
#define FILE_NAME "results(30).dat"	//Name of file where results are stored

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

void fill(int n) {

	for(int i = 0; i<n; i++){

		int t = rand()%N;

		if( track[t] == 1){
			i--;
		}
		else{
			track[t] = 1;
			list[i] = t;
		}

	}

}

void move(int rho){

	check_list update; 		//To check if that car has moved
	check_list moves;		//To store the moves of each car
	//cout<<"From here: "<<endl;


	for(int i = 0; i<rho; i++){

		int t = rand()%rho;			//Which car will be moves

		//cout<<t<<endl;
		if(update.check(t) == 1){
			i--;
			continue;
		}

		int pos = list[t];
		int next_pos = (pos+1)%N;

		if(track[next_pos] == 0){

			int prob_check = rand();
			
			if( prob_check < RAND_MAX*P){

				moves.append(pos);
			/*
				track[pos] =  0;
				track[next_pos] = 1;

				if(pos == CHECK_POINT){
					count++;
				}

				list[t] = next_pos;
			*/
			}

			update.append(t);

		}

		for(int i = 0; i<moves.q; i++){

			int pos = moves.a[i];
			int next_pos = (pos+1)%N;

			track[pos] =  0;
			track[next_pos] = 1;

			if(pos == CHECK_POINT){
				count++;
			}

			list[t] = next_pos;

		}

	}

	//cout<<"End here"<<endl;
}
	

int main(){
	
	int rho; 			//density

	ofstream f1;
	f1.open(FILE_NAME);

	for(rho =  0; rho<= N; rho++){ 		//Must go from 0 to N

		initialize(track);
		initialize(list);

		fill(rho);

		//print(list);

		count = 0;				//for calculating J later

		for(int t = 0; t< T_MAX; t++){		//change 1 to T_MAX

			move(rho);

		}

		float J = (float)(count)/T_MAX;
		
		f1<<J<<endl;

	}

	f1.close();

	//print(list);

	return 0;
}