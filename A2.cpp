/*
will make environment of the game to see the state
the environment will have 2d vector
will store the vector of soldiers and cannon
and cannon of players

the current player:
					1 - we are
					-1 - the other
					
the 2d vector of board:
						the int vector of two
						our townhall will be shaown as 1
						our soldier will have 2
						their townhall will have -1
						their soldier will have -2

the vector of our soldier:
							the pair of int	vector
							v[i] = v[2,3] ; the ith soldier has (2,3)
							
the time left:
				float time
				
the vector of cannon:
					the vector of vector
					vector[i] = vector[0,1,-1] the mid point is 0,1 and direction is -45
					2: verticle
					1: +45
					0: horizontal
					-1: -45
*/
#include<bits/stdc++.h>
using namespace std;
		
//the helper function for sorting
bool sortdesc(tuple<float, vector<int> > a, tuple<float,  vector<int> > b) { 
    		
	return (get<0>(a) > get<0>(b)); 
}
class environment{
	
	public:
		
		//the current player
		int current_player;
		
		//the color of our player:
		//       -1: black
		//        1: white
		int color;
		
		//define 2d vector of board
		vector< vector<int> > board;
		
		//define 2d vector of our soldiers
		vector< vector<int> > our_soldiers;
		
		//define 2d vector of our townhall
		vector< vector<int> > our_townhall;
		
		//define 2d vector of our soldiers
		vector< vector<int> > opp_soldiers;
		
		//define 2d vector of our townhall
		vector< vector<int> > opp_townhall;
		
		//define 2d vector of our cannon
		vector< vector<int> > our_cannon;
		
		//define 2d vector of opp cannon
		vector< vector<int> > opp_cannon;
		
		//the time left
		float time_left;
		
		/*write function to take move
		the move is of 6 length with 
			0: move
			1: bombard
		I am assuming all actions are valid only
		*/ 
		
			
		/*   --------------|THE MOVE TAKING FUNCTION|-------------------------  
		 */
		void take_action(vector<int> action){
			
			//the first will always be the selecting the soldiers so i am dropping the first value
			//just check the soldier which is selected
			//the atack only
			if (current_player == 1){
					
				//just go on end location
				if(board[action[3]][action[4]] == current_player*(-1)){
						
						
					//the index of value can be find by iterator at that
					vector<int> y = vector<int>({action[3], action[4]});

					//just delete the element
					opp_soldiers.erase(find(opp_soldiers.begin(), opp_soldiers.end(),y));
					
					//change the opponent directory
					//just change cannon of the opp team
					//use temporary vector
					vector<int>  temp;
					//the int i keeps track of elements deleted
					int i = 0;
					for(int j = 0; j < opp_cannon.size(); j++){
						
						//update temp
						temp = opp_cannon[j-i];
						//check for possible things
						if (temp[2] == 2 && temp[0] == action[3] && (temp[1] - action[4])*(temp[1] - action[4]) <= 1){
							
							opp_cannon.erase(opp_cannon.begin() + j - i);
							i++;
							
						}
						else if (temp[2] == 0 && temp[1] == action[4] && (temp[0] - action[3])*(temp[0] - action[3]) <= 1){
							
							opp_cannon.erase(opp_cannon.begin() + j - i);
							i++;	
						}
						else if ((temp[2] == 1 || temp[2]==-1) && (temp[1] - action[4])*(temp[1] - action[4]) <= 1 && (temp[0] - action[3])*(temp[0] - action[3]) <= 1){
							
							opp_cannon.erase(opp_cannon.begin() + j - i);
							i++;
							
						}
					}
				}
				
				//check the action as followa
				//this is just bombarding
				if(action[2] == 1){
					
					//just change the board position as
					board[action[3]][action[4]]  = 0;
				}
				//else if we just have movement we have to see new things
				else{
					
					//just change the board position as
					board[action[3]][action[4]]  = 1;
					board[action[0]][action[1]]  = 0;
			
					//will need to see new canon forms or not and also delete old cannon
					//the index of value can be find by iterator at that
					vector<int> x = vector<int>({action[0], action[1]});

					//just delete the element and add new position of soldier
					our_soldiers.erase(find(our_soldiers.begin(), our_soldiers.end(),x));
					our_soldiers.push_back(vector<int>({action[3], action[4]}));
					
					//just change cannon of the our team
					//use temporary vector
					vector<int> temp2;
					//the int i keeps track of elements deleted
					int i = 0;
					for(int j = 0; j < our_cannon.size(); j++){
						
						//update temp
						temp2 = our_cannon[j-i];
					
						//check for possible things
						if (temp2[2] == 2 && temp2[0] == action[0] && (temp2[1] - action[1])*(temp2[1] - action[1]) <= 1){
							
							our_cannon.erase(our_cannon.begin() + j - i);
							i++;
						}
						else if (temp2[2] == 0 && temp2[1] == action[1] && (temp2[0] - action[0])*(temp2[0] - action[0]) <= 1){
							
							our_cannon.erase(our_cannon.begin() + j - i);
							i++;	
						}
						else if ((temp2[2] == 1 || temp2[2]==-1) && (temp2[1] - action[1])*(temp2[1] - action[1]) <= 1 && (temp2[0] - action[0])*(temp2[0] - action[0]) <= 1){
							
							our_cannon.erase(our_cannon.begin() + j - i);
							i++;	
						}
						else{	
						}
					}
					
					//to find new cannon just iterate over all directions
					for(int i = -1; i < 3; i++){
						
						//now if i = 2 it is verticle then
						if (i == 2){
							//just run for loop as
							for(int j = -2; j < 1 ; j++){
								if(action[4]+j >= 0 && action[4] + 2 + j <= 7){
									if(board[action[3]][action[4] + j] == 1 && board[action[3]][action[4] + j+1] == 1 && board[action[3]][action[4] + j+2] == 1){
										our_cannon.push_back(vector<int>({action[3], action[4]+j+1, 2}));
									}
								}
							}	
						}
						//now if i = 1 it is diagonal then
						else if (i == 1){
							//just run for loop as
							for(int j = -2; j < 1 ; j++){
								if(action[4] + j >= 0 && action[4] + j + 2 <= 7 && action[3] + j >= 0 && action[3] + j + 2 <= 7){
									if(board[action[3]+j][action[4] + j] == 1 && board[action[3]+j+1][action[4] + j+1] == 1 && board[action[3]+j+2][action[4] + j+2] == 1){
										our_cannon.push_back(vector<int>({action[3]+j+1, action[4]+j+1, 1}));
									}
								}
							}	
						}
						//now if i = 0 it is horizontal then
						else if (i == 0){
							//just run for loop as
							for(int j = -2; j < 1 ; j++){
								
								if(action[3]+j >= 0 && action[3] + 2 + j <= 7){
									if(board[action[3]+j][action[4]] == 1 && board[action[3]+j+1][action[4]] == 1 && board[action[3]+j+2][action[4]] == 1){
										our_cannon.push_back(vector<int>({action[3]+j+1, action[4], 0}));
									}
								}
							}	
						}
						//now if i = 1 it is diagonal then
						else if (i == -1){		
							//just run for loop as
							for(int j = -2; j < 1 ; j++){
								if(action[3] - j <= 7 && action[3] - j -2>= 0 && action[4] + j >= 0 && action[4] + j + 2 <= 7){
									if(board[action[3]-j][action[4] + j] == 1 && board[action[3]-j-1][action[4] + j+1] == 1 && board[action[3]-j-2][action[4] + j+2] == 1){
										our_cannon.push_back(vector<int>({action[3]-j-1, action[4]+j+1, 1}));
									}
								}
							}	
						}
					}	
				}
			}
					
			else{
				//just go on end location
				if(board[action[3]][action[4]] == current_player*(-1)){
					 
					
					//the index of value can be find by iterator at that
					vector<int> y = vector<int>({action[3], action[4]});

					//just delete the element
					our_soldiers.erase(find(our_soldiers.begin(), our_soldiers.end(),y));
					
					//change the opponent directory
					//just change cannon of the opp team
					//use temporary vector
					vector<int> temp;
					//the int i keeps track of elements deleted
					int i = 0;
					for(int j = 0; j < opp_cannon.size(); j++){
						
						//update temp
						temp = opp_cannon[j-i];
						//check for possible things
						if (temp[2] == 2 && temp[0] == action[3] && (temp[1] - action[4])*(temp[1] - action[4]) <= 1){
							
							opp_cannon.erase(opp_cannon.begin() + j - i);
							i++;
							
						}
						else if (temp[2] == 0 && temp[1] == action[4] && (temp[0] - action[3])*(temp[0] - action[3]) <= 1){
							
							opp_cannon.erase(opp_cannon.begin() + j - i);
							i++;	
						}
						else if ((temp[2] == 1 || temp[2]==-1) && (temp[1] - action[4])*(temp[1] - action[4]) <= 1 && (temp[0] - action[3])*(temp[0] - action[3]) <= 1){
							
							opp_cannon.erase(opp_cannon.begin() + j - i);
							i++;
							
						}
					}
				}
				
				//check the action as followa
				//this is just bombarding
				if(action[2] == 1){
					
					//just change the board position as
					board[action[3]][action[4]]  = 0;
				}
				//else if we just have movement we have to see new things
				else{
					//just change the board position as
					board[action[3]][action[4]]  = -1;
					board[action[0]][action[1]]  = 0;
					
					//will need to see new canon forms or not and also delete old cannon
					//the index of value can be find by iterator at that
					vector<int> x = vector<int>({action[0], action[1]});

					//just delete the element and add new position of soldier
					opp_soldiers.erase(find(opp_soldiers.begin(), opp_soldiers.end(),x));
					opp_soldiers.push_back(vector<int>({action[3], action[4]}));

					//just change cannon of the our team
					//use temporary vector
					vector<int> temp2;
					//the int i keeps track of elements deleted
					int i = 0;
					for(int j = 0; j < opp_cannon.size(); j++){
						//update temp
						temp2 = opp_cannon[j-i];
						//check for possible things
						if (temp2[2] == 2 && temp2[0] == action[0] && (temp2[1] - action[1])*(temp2[1] - action[1]) <= 1){
							
							opp_cannon.erase(opp_cannon.begin() + j - i);
							i++;
							
						}
						else if (temp2[2] == 0 && temp2[1] == action[1] && (temp2[0] - action[0])*(temp2[0] - action[0]) <= 1){
							
							opp_cannon.erase(opp_cannon.begin() + j - i);
							i++;	
						}
						else if ((temp2[2] == 1 || temp2[2]==-1) && (temp2[1] - action[1])*(temp2[1] - action[1]) <= 1 && (temp2[0] - action[0])*(temp2[0] - action[0]) <= 1){
							
							opp_cannon.erase(opp_cannon.begin() + j - i);
							i++;
							
						}
					}
					
						//to find new cannon just iterate over all directions
					for(int i = -1; i < 3; i++){
						//now if i = 2 it is verticle then
						if (i == 2){
							//just run for loop as
							for(int j = -2; j < 1 ; j++){
								if(action[4]+j >= 0 && action[4] + 2 + j <= 7){
									if(board[action[3]][action[4] + j] == -1 && board[action[3]][action[4] + j+1] == -1 && board[action[3]][action[4] + j+2] == -1){
										opp_cannon.push_back(vector<int>({action[3], action[4]+j+1, 2}));
									}
								}
							}	
						}
						//now if i = 1 it is diagonal then
						else if (i == 1){
							//just run for loop as
							for(int j = -2; j < 1 ; j++){
								if(action[4] + j >= 0 && action[4] + j + 2 <= 7 && action[3] + j >= 0 && action[3] + j + 2 <= 7){
									if(board[action[3]+j][action[4] + j] == -1 && board[action[3]+j+1][action[4] + j+1] == -1 && board[action[3]+j+2][action[4] + j+2] == -1){
										opp_cannon.push_back(vector<int>({action[3]+j+1, action[4]+j+1, 1}));
									}
								}
							}	
						}
						//now if i = 0 it is horizontal then
						else if (i == 0){
							//just run for loop as
							for(int j = -2; j < 1 ; j++){
								if(action[3]+j >= 0 && action[3] + 2 + j<= 7){
									if(board[action[3]+j][action[4]] == -1 && board[action[3]+j+1][action[4]] == -1 && board[action[3]+j+2][action[4]] == -1){
										opp_cannon.push_back(vector<int>({action[3]+j+1, action[4], 0}));
									}
								}
							}	
						}
						//now if i = 1 it is diagonal then
						else if (i == -1){		
							//just run for loop as
							for(int j = -2; j < 1 ; j++){
								if(action[3] - j <= 7 && action[3] - j - 2>= 0 && action[4] + j >= 0 && action[4] + j + 2 <= 7){
									if(board[action[3]-j][action[4] + j] == -1 && board[action[3]-j-1][action[4] + j+1] == -1 && board[action[3]-j-2][action[4] + j+2] == -1){
										opp_cannon.push_back(vector<int>({action[3]-j-1, action[4]+j+1, 1}));
									}
								}
							}	
						}
					}	
				}
			}
			current_player = -1*current_player;
		}	

		/*   --------------|THE POSSIBLE MOVEMENTS|-------------------------  
		 */      
		                                 
		//define function to give vector of possible movements
		vector<tuple<float, vector<int> > > possible_moves(){
			
			//the ans vector
			vector< vector<int> > ans;
			
			//the temporary varaibles
			vector<vector <int> >z;
			vector<vector <int> >a;
			int p, o, c;
			//first will work on our soldiers
			if(current_player == 1){
				//just define z and a
				z = our_soldiers;
				a = our_cannon;
				p = 1;
				o = -1;
				c = color;
			
			}
			
			else{
				
				//just define z and a
				z = opp_soldiers;
				a = opp_cannon;
				p = -1;
				o = 1;
				c = -1*color;
				
			}
			
			//work on soldier
			for(int i =0; i < z.size(); i++){
				//just using x and y as to use in future
				int x = z[i][0];
				int y = z[i][1];
				//checking daigonl condition
				
				if ((x -6)*(x + 1 )<= 0 && (y + c - 7)*(y + c ) <= 0 && board[x+1][y+c] != p){
					
					//just add the given action to ans
					ans.push_back(vector<int>({x,y,0,x+1,y+c}));
				}
				
				//checking verticle condition
				if ((y + c - 7)*(y + c )<= 0 && board[x][y+c] != p){
					
					//just add the given action to ans
					ans.push_back(vector<int>({x,y,0,x,y+c}));
				}
				//checking horizontal condition right
				if ((x -6)*(x + 1 )<= 0 && board[x+1][y] == o){
					
					//just add the given action to ans
					ans.push_back(vector<int>({x,y,0,x+1,y}));
				}
				//checking horizontal condition left
				if ((x -8)*(x - 1 )<= 0 && board[x-1][y] == o){
					
					//just add the given action to ans
					ans.push_back(vector<int>({x,y,0,x-1,y}));
				}
				//checking daigonl condition negative the x decreases
				if ((x -8)*(x - 1 )<= 0 && (y -7 + c)*(y + c )<= 0 && board[x-1][y+c] != p){
					
					//just add the given action to ans
					ans.push_back(vector<int>({x,y,0,x-1,y+c}));
				}
				//checking back track conditions
				if (((x+1)*(x-6) <= 0 && board[x+1][y] == o) || ((x-1)*(x-8) <= 0 && board[x-1][y] == o) || ( (y+c)*(y-7+c) <= 0 && board[x][y+c] == o)
				 || ((x -6)*(x + 1 )<= 0 && (y -7 +c)*(y + c ) <= 0 && board[x+1][y+c] == o)||((x -8)*(x - 1 )<= 0 && (y -7 +c)*(y + c )<= 0 && board[x-1][y+c] == o)){
				 	
					//neeed to check the backward conditions
					if((y-7 - 2*c)*(y - 2*c) <= 0 && (board[x][y-2*c] != p || board[x][y-2*c] != 2*p)){
						//just add the given action to ans
						ans.push_back(vector<int>({x,y,0,x,y-2*c}));			
					}
					//the diagonal condition backward
					if((y-7 - 2*c)*(y-2*c) <= 0 && (x-9)*(x-2) <= 0 && (board[x-2][y-2*c] != p || board[x-2][y-2*c] != 2*p)){
						//just add the given action to ans
						ans.push_back(vector<int>({x,y,0,x-2,y-2*c}));
					}
					//the diagonal condition forward
					if((y-7 - 2*c)*(y-2*c) <= 0 && (x-5)*(x+2) <= 0 && (board[x+2][y-2*c] != p || board[x+2][y-2*c] != 2*p)){
						//just add the given action to ans
						ans.push_back(vector<int>({x,y,0,x+2,y-2*c}));
					}
				}
			}
			//just need to go for cannon
			for(int i = 0; i < a.size(); i++){
				//the movement one first
				int x = a[i][0];
				int y = a[i][1];
				int d = a[i][2];
				
				//now check along the dierctions
				//this is verticle
				if(d == 2){
					//forward move
					if((y-5)*(y+2) <= 0 && board[x][y+2] == 0){
						//just add the element to ans
						ans.push_back({x,y-1,0,x,y+2});
						//add attack action
						if((y-4)*(y+3) <= 0 && board[x][y+3] != p && board[x][y+3] != p*2){
							//just add the element to ans
							ans.push_back({x,y+1,1,x,y+3});
			
						
						}
						//add attack action
						if((y-3)*(y+4) <= 0 && board[x][y+4] != p && board[x][y+4] != 2*p){
							//just add the element to ans
							ans.push_back({x,y+1,1,x,y+4});
						}
					}
						//backward move
						if((y-9)*(y-2) <= 0 && board[x][y-2] == 0){
							//just add the element to ans
							
								ans.push_back({x,y+1,0,x,y-2});
							//add attack action
							if((y-10)*(y-3) <= 0 && board[x][y-3] != p && board[x][y-3] != 2*p){
								//just add the element to ans
								ans.push_back({x,y-1,1,x,y-3});	
							
							}
							//add attack action
							if((y-11)*(y-4) <= 0 && board[x][y-4] != p && board[x][y-4] != 2*p){
								//just add the element to ans
								ans.push_back({x,y-1,1,x,y-4});
							}
						}
					}
					//this is verticle
				if(d == 0){
					//forward move
					if((x-5)*(x+2) <= 0 && board[x+2][y] == 0){
						//just add the element to ans
						ans.push_back({x-1,y,0,x+2,y});
						
						//add attack action
						if((x-4)*(x+3) <= 0 && board[x+3][y] != p && board[x+3][y] != 2*p){
							//just add the element to ans
							ans.push_back({x+1,y,1,x+3,y});
						}
						//add attack action
						if((x-3)*(x+4) <= 0 && board[x+4][y] != p && board[x+4][y] != 2*p){
							//just add the element to ans
							ans.push_back({x+1,y,1,x+4,y});
						}
					}
						//backward move
						if((x-9)*(x-2) <= 0 && board[x-2][y] == 0){
							//just add the element to ans
							ans.push_back({x+1,y,0,x-2,y});
							
							//add attack action
							if((x-10)*(x-3) <= 0 && board[x-3][y] != p && board[x-3][y] != 2*p){
								//just add the element to ans
								ans.push_back({x-1,y,1,x-3,y});
							}
							//add attack action
							if((x-11)*(x-4) <= 0 && board[x-4][y] != p && board[x-4][y] != 2*p){
								//just add the element to ans
								ans.push_back({x-1,y,1,x-4,y});
							}
						}
					}
						//this is verticle
				if(d == 1){
					//forward move
					if((x-5)*(x+2) <= 0 && (y-5)*(y+2) <= 0 && board[x+2][y+2] == 0){
						//just add the element to ans
						ans.push_back({x-1,y-1,0,x+2,y+2});
						
						//add attack action
						if((x-4)*(x+3) <= 0 && (y-4)*(y+3) <= 0 && board[x+3][y+3] != p && board[x+3][y+3] != 2*p){
							//just add the element to ans
							ans.push_back({x+1,y+1,1,x+3,y+3});
						}
						//add attack action
						if((x-3)*(x+4) <= 0 && (y-3)*(y+4) <= 0 && board[x+4][y+4] != p && board[x+4][y+4] != 2*p){
							//just add the element to ans
							ans.push_back({x+1,y+1,1,x+4,y+4});
						}
					}
					//backward move
					if((x-9)*(x-2) <= 0 && (y-9)*(y-2) <= 0 && board[x-2][y-2] == 0){
						//just add the element to ans
						ans.push_back({x+1,y+1,0,x-2,y-2});
						
						//add attack action
						if((x-10)*(x-3) <= 0 && (y-10)*(y-3) <= 0 && board[x-3][y-3] != p && board[x-3][y-3] != 2*p){
							//just add the element to ans
							ans.push_back({x-1,y-1,1,x-3,y-3});
						}
						//add attack action
						if((x-11)*(x-4) <= 0 && (y-11)*(y-4) <= 0 && board[x-4][y-4] != p && board[x-4][y-4] != 2*p){
							//just add the element to ans
							ans.push_back({x-1,y-1,1,x-4,y-4});
							}
						}
					}
					if(d == -1){
					//forward move
					if((x-5)*(x+2) <= 0&& (y-9)*(y-2) <= 0&& board[x+2][y-2] == 0){
						//just add the element to ans
						ans.push_back({x-1,y+1,0,x+2,y-2});
						
						//add attack action
						if((x-4)*(x+3) <= 0 && (y-10)*(y-3) <= 0 && board[x+3][y-3] != p && board[x+3][y-3] != 2*p){
							//just add the element to ans
							ans.push_back({x+1,y-1,1,x+3,y-3});
						}
						//add attack action
						if((x-3)*(x+4) <= 0 && (y-4)*(y-11) <= 0 && board[x+4][y-4] != p && board[x+4][y-4] != 2*p){
							//just add the element to ans
							ans.push_back({x+1,y-1,1,x+4,y-4});
						}
					}
					//backward move
					if((x-9)*(x-2) <= 0 && (y-5)*(y+2) <= 0 && board[x-2][y+2] == 0){
						//just add the element to ans
						ans.push_back({x+1,y-1,0,x-2,y+2});
						
						//add attack action
						if((x-10)*(x-3) <= 0 && (y-4)*(y+3) <= 0 && board[x-3][y+3] != p && board[x-3][y+3] != 2*p){
							//just add the element to ans
							ans.push_back({x-1,y+1,1,x-3,y+3});
						}
						//add attack action
						if((x-11)*(x-4) <= 0 && (y-3)*(y+4) <= 0 && board[x-4][y+4] != p && board[x-4][y+4] != 2*p){
							//just add the element to ans
							ans.push_back({x-1,y+1,1,x-4,y+4});
						}
					}
				}
			}  
			//the final vector
			vector <tuple<float, vector<int> > >ansf;
			//now need to go for best actions
			vector<vector<float> > score;
			//for 
		
			score = vector< vector<float> >(8 , vector<float>(8, -1*0.01));
			score[0][0] = -1;
			score[2][0] = -1;
			score[4][0] = -1;
			score[6][0] = -1;
			score[1][7] = -1;
			score[3][7] = -1;
			score[5][7] = -1;
			score[7][7] = -1;
	
			//just do the dot product
			for (int i = 0; i < ans.size(); i++){
				vector< vector<int> > temp2 = board;
				if(ans[i][2] == 0){
					temp2[ans[i][0]][ans[i][1]] = 0;
					temp2[ans[i][3]][ans[i][4]] = current_player;
				}
				else{
					temp2[ans[i][3]][ans[i][4]] = 0;
				}
				float temp = 0.0;
				for (int j = 0 ; j < 8 ; j++){
					for(int k = 0; k < 8 ; k++){
						temp = temp + temp2[j][k]*score[j][k];
					}
				}
				ansf.push_back(make_tuple(temp, ans[i]));
			}
			if (current_player == 1){
			sort(ansf.begin(), ansf.end(), sortdesc);}
			else{
			sort(ansf.begin(), ansf.end());	
			}
			return(ansf); 
		}
	
			
		/*   --------------|THE CONSTRUCTOR|-------------------------  
		 */
		//the environment takes the board size n*m and the first chance and float time value
		environment(int n, int m, int chance, float t){
			
			current_player = chance;
			time_left = t;
			board.assign(n, vector<int>(m,0));
			if (chance == 1){
				color = -1;
			for (int i = 0; i < n-1; i+=2){
				board[i+1][m-1] = 2;
				board[i][0] = -2;
				our_cannon.push_back(vector<int>({i,m-2,2}));
				opp_cannon.push_back(vector<int>({i+1,1,2}));
				
				for (int j = 0 ; j < 3; j++){
					board[i][m-1 - j] = 1;
					board[i+1][j] = -1;
					our_soldiers.push_back(vector<int>({i,m-1 - j}));
					opp_soldiers.push_back(vector<int>({i+1,j}));
					
				}			
			}
		}
		else {
			color = 1;
			for (int i = 0; i < n-1; i+=2){
				
				board[i+1][m-1] = -2;
				board[i][0] = 2;
				our_cannon.push_back(vector<int>({i+1,1,2}));
				opp_cannon.push_back(vector<int>({i,m-2,2}));
				
				for (int j = 0 ; j < 3; j++){
					board[i][m-1 - j] = -1;
					board[i+1][j] = 1;
					opp_soldiers.push_back(vector<int>({i,m-1 - j}));
					our_soldiers.push_back(vector<int>({i+1,j}));
					
				}			
			}
		}
	}
	environment(){
	}
	
};

//the node of search tree is as follows
//it will consist of same elements as environment so i will store just the environmnet 
class node{
	
	//the environment
	environment element;
	
	//the parent
	node* parent;
	
	//the number of visited 
	int visited;
	
	//the alpha and beta value
	float alpha;
	float beta;
	
	//the optimal action till now
	vector<int> action;
	
	//the score of the node
	float score;
	
	//the childrens of node are as
	vector<tuple<vector <int>, node*> > children;
	
	//the constructor is
	node(environment env){
		element = env;
		visited = 0;
		alpha = FLT_MIN;
		beta = FLT_MAX;
		score = 0.0;
	}
	
	//the constructor is
	node(environment env, node* p){
		element = env;
		parent = p;
		visited = 0;
		alpha = (*p).alpha;
		beta = (*p).beta;
		score = 0.0;
	}
};

	
//define function to see the state 
void render(environment e){
	vector<vector<int> >board = e.board;
	//just run for loop
	cout << "--------------------------"<<endl;
	for(int i = 0; i < board.size() ; i++){
		for(int j = 0; j < board[0].size(); j++){
			if(board[j][i] == 1){
			cout <<"|"<<"AS";}
			else if(board[j][i] == -1){
			cout <<"|"<<"OS";}
			else if(board[j][i] == 2){
			cout <<"|"<<"AT";}
			else if(board[j][i] == -2){
			cout <<"|"<<"OT";}
			else{
				cout <<"|  "; 
			}
		}
		cout <<"|"<<endl<< "--------------------------"<<endl;
	}
}
void render2(environment e){
	vector<vector<int> >board = e.board;
	//just run for loop
	cout << "--------------------------"<<endl;
	for(int i = 0; i < board.size() ; i++){
		for(int j = 0; j < board[0].size(); j++){
			
			cout <<"|"<<board[j][i];
		}
		cout <<"|"<<endl<< "--------------------------"<<endl;
	}
}

void information(environment e){
	cout << "------------------------------------------------------------------------------"<<endl;
	cout << "|                  THE INFORMATION ABOUT STATE IS AS FOLLOWS                  |"<<endl;
	cout << "------------------------------------------------------------------------------"<<endl;
	cout <<"| Our soldiers are at:"<<endl;
	cout <<"| X | Y |"<<endl;
	cout <<"---------"<<endl;
	for (int i = 0; i < e.our_soldiers.size(); i++){
		cout <<"| "<<e.our_soldiers[i][0] << " | "<<e.our_soldiers[i][1]<<" |"<<endl;
		cout <<"---------"<<endl;
	}
	cout <<"----------------------"<<endl;
	cout <<"| Our canons are at:"<<endl;
	cout <<"| X | Y | D |"<<endl;
	cout <<"-------------"<<endl;
	for (int i = 0; i < e.our_cannon.size(); i++){
		cout <<"| "<<e.our_cannon[i][0] << " | "<<e.our_cannon[i][1]<<" | "<<e.our_cannon[i][2]<<" |"<<endl;
		cout <<"-------------"<<endl;
	}
	cout <<"---------------------------------------"<<endl;
	cout <<"| Opponent soldiers are at:"<<endl;
	cout <<"| X | Y |"<<endl;
	cout <<"---------"<<endl;
	for (int i = 0; i < e.opp_soldiers.size(); i++){
		cout <<"| "<<e.opp_soldiers[i][0] << " | "<<e.opp_soldiers[i][1]<<" |"<<endl;
		cout <<"---------"<<endl;
	}
	cout <<"---------------------------"<<endl;
	cout <<"| Opponent canons are at:"<<endl;
	cout <<"| X | Y | D |"<<endl;
	cout <<"-------------"<<endl;
	for (int i = 0; i < e.opp_cannon.size(); i++){
		cout <<"| "<<e.opp_cannon[i][0] << " | "<<e.opp_cannon[i][1]<<" | "<<e.opp_cannon[i][2]<<" |"<<endl;
		cout <<"-------------"<<endl;
	}
}

void spa(environment e){
	vector<tuple<float ,vector<int> > > ans = e.possible_moves();
	cout << "------------------------------------------------------------------------------"<<endl;
	cout << "|                      THE POSSIBLE MOVES FOR PLAYER "<<e.current_player<<"                   |"<<endl;
	cout << "------------------------------------------------------------------------------"<<endl;
	cout << "| T | X | Y | T | X | Y |"<<endl;
	cout << "-------------------------"<<endl;
		for (int i = 0; i < ans.size(); i++){
		cout <<"| S |"<<get<1>(ans[i])[0] << " | "<<get<1>(ans[i])[1]<<" | ";
		if(get<1>(ans[i])[2] == 1){
			cout << "B |"<< get<1>(ans[i])[3] <<" | "<< get<1>(ans[i])[4] <<" |"<<endl;
		}
		else{
			cout << "M |"<< get<1>(ans[i])[3] <<" | "<< get<1>(ans[i])[4] <<" |"<<endl;
		}
		cout <<"-------------------------"<<endl;
	}
	
}
environment create(){
	int chance, n,m;
	int t;
	cin >> chance>>n>>m>>t;
	float p = 2*(1.5 - chance);
	chance = (int) p;
	environment e = environment(n,m,chance,(float) t);
	return(e);
}

int main(){
	int temp = 0;
	vector<int> y;
	environment e = create();
	char a1,a2;
	int x0,y0,x1,y1;
	while(temp < e.time_left){
		if(e.current_player == -1){
		cin>>a1>>x0>>y0>>a2>>x1>>y1;
			if (a2 == 'M'){
				e.take_action(vector<int>({x0,y0,0,x1,y1}));
			}
			else{
				e.take_action(vector<int>({x0,y0,1,x1,y1}));
			}
		}
		else{
			
			time_t t0 = time(NULL);
			y = get<1>(e.possible_moves()[0]);
			e.take_action(y);
			if (y[2] == 0){
				cout << "S "<<y[0]<<" "<<y[1]<<" "<<"M "<<y[3]<<" "<<y[4]<<endl;
			}	
			else{
				cout << "S "<<y[0]<<" "<<y[1]<<" "<<"B "<<y[3]<<" "<<y[4]<<endl;
			}
			time_t t1 = time(NULL);
			temp = temp + t1 - t0; 
		}
	}

	/*vector< tuple<float, vector<int> > > demo;
	demo.push_back(make_tuple(0.8, vector<int>({1,2,3})));
	demo.push_back(make_tuple(0.1, vector<int>({4,5,6})));
	sort(demo.begin(), demo.end(), sortdesc);
	cout << get<0>(demo[0]);*/

}
