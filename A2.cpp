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

			
		/*   --------------|THE MOVE TAKING FUNCTION|-------------------------  
		 */
		void take_action(vector<int> action){
			
			//the first will always be the selecting the soldiers so i am dropping the first value
			//just check the soldier which is selected
			//the atack only
			board[action[3]][action[4]] = 0;
			if (action[2] == 0){
	
				board[action[0]][action[1]] = 0;
				if(current_player == 1){
					board[action[3]][action[4]] = 1;
				}
				else{
					board[action[3]][action[4]] = -1;
				}
			}		
			current_player = -1*current_player;
		}	

		/*   --------------|THE POSSIBLE MOVEMENTS|-------------------------  
		 */      
		                                 
		//define function to give vector of possible movements
		vector<tuple<float, vector<int> > > possible_moves(){
		
			//the temporary varaibles
			vector<vector <int> >so;
			vector<vector <int> >ca;
			//the ans vector
			vector< vector<int> > ans;
			if(current_player == 1){
				for(int i = 0; i < 8 ; i++){
					for(int j = 0 ; j < 8 ; j++){
						if (board[i][j] == 1){
							so.push_back(vector<int>({i,j}));
							if((i+1)*(i-6)<= 0 && (i-1)*(i-8)<= 0 && board[i+1][j] == 1 && board[i-1][j] == 1){
								ca.push_back(vector<int>({i,j,0}));
							}
							if((i+1)*(i-6)<= 0 && (i-1)*(i-8)<= 0 && (j+1)*(j-6)<= 0 && (j-1)*(j-8)<= 0 ){
								if (board[i+1][j+1] == 1 && board[i-1][j-1] == 1){
									ca.push_back(vector<int>({i,j,1}));
								}
								else if (board[i+1][j-1] == 1 && board[i-1][j+1] == 1){
									ca.push_back(vector<int>({i,j,-1}));
								}
							}
							if((j+1)*(j-6)<= 0 && (j-1)*(j-8)<= 0 && board[i][j+1] == 1 && board[i][j-1] == 1){
								ca.push_back(vector<int>({i,j,2}));
							}
						}
					}
				}
			} 
			else{
				for(int i = 0; i < 8 ; i++){
					for(int j = 0 ; j < 8 ; j++){
						if (board[i][j] == -1){
							so.push_back(vector<int>({i,j}));
							if((i+1)*(i-6)<= 0 && (i-1)*(i-8)<= 0 && board[i+1][j] == -1 && board[i-1][j] == -1){
								ca.push_back(vector<int>({i,j,0}));
							}
							if((i+1)*(i-6)<= 0 && (i-1)*(i-8)<= 0 && (j+1)*(j-6)<= 0 && (j-1)*(j-8)<= 0 ){
								if (board[i+1][j+1] == -1 && board[i-1][j-1] == -1){
									ca.push_back(vector<int>({i,j,1}));
								}
								else if (board[i+1][j-1] == -1 && board[i-1][j+1] == -1){
									ca.push_back(vector<int>({i,j,-1}));
								}
							}
							if((j+1)*(j-6)<= 0 && (j-1)*(j-8)<= 0 && board[i][j+1] == -1 && board[i][j-1] == -1){
								ca.push_back(vector<int>({i,j,2}));
							}
						}
					}
				}
			} 
		
			int p, o, c;
			//first will work on our soldiers
			if(current_player == 1){
				p = 1;
				o = -1;
				c = color;
			}
			
			else{
				p = -1;
				o = 1;
				c = -1*color;
			}
			
			//work on soldier
			for(int i =0; i < so.size(); i++){
				//just using x and y as to use in future
				int x = so[i][0];
				int y = so[i][1];
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
					if((y-7 - 2*c)*(y - 2*c) <= 0 && (board[x][y-2*c] != p && board[x][y-2*c] != 2*p)){
						//just add the given action to ans
						ans.push_back(vector<int>({x,y,0,x,y-2*c}));			
					}
					//the diagonal condition backward
					if((y-7 - 2*c)*(y-2*c) <= 0 && (x-9)*(x-2) <= 0 && (board[x-2][y-2*c] != p && board[x-2][y-2*c] != 2*p)){
						//just add the given action to ans
						ans.push_back(vector<int>({x,y,0,x-2,y-2*c}));
					}
					//the diagonal condition forward
					if((y-7 - 2*c)*(y-2*c) <= 0 && (x-5)*(x+2) <= 0 && (board[x+2][y-2*c] != p && board[x+2][y-2*c] != 2*p)){
						//just add the given action to ans
						ans.push_back(vector<int>({x,y,0,x+2,y-2*c}));
					}
				}
			}
			//just need to go for cannon
			for(int i = 0; i < ca.size(); i++){
				//the movement one first
				int x = ca[i][0];
				int y = ca[i][1];
				int d = ca[i][2];
				
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
		
			score = vector< vector<float> >(8 , vector<float>(8, 1));
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
				int temp = 0;
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
		environment(int n, int m, int chance){
			
			current_player = chance;
			board.assign(n, vector<int>(m,0));
			if (chance == 1){
				color = -1;
			for (int i = 0; i < n-1; i+=2){
				board[i+1][m-1] = 2;
				board[i][0] = -2;
				for (int j = 0 ; j < 3; j++){
					board[i][m-1 - j] = 1;
					board[i+1][j] = -1;
				}			
			}
		}
		else {
			color = 1;
			for (int i = 0; i < n-1; i+=2){
				
				board[i+1][m-1] = -2;
				board[i][0] = 2;
				for (int j = 0 ; j < 3; j++){
					board[i][m-1 - j] = -1;
					board[i+1][j] = 1;
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
	
	public:
		//the environment
		environment element;
		
		//the parent
		node *parent;
		
		//the action through it came
		vector<int> pa;
		
		//the number of visited 
		int visited;
		
		//the alpha and beta value
		float alpha;
		float beta;
		
		//the optimal action till now
		vector<int> action;
		
		//the depth
		int depth;
		
		//the childrens of node are as
		vector<node*> children;

		//the constructor is
		node(environment env, node *p, vector<int> ac){
			children = vector<node*>();
			element = env;
			parent = p;
			visited = 0;
			alpha = p->alpha;
			beta = p->beta;
			depth = p->depth + 1;
			pa = ac;
		}
		
		//the constructor is
		node(environment env){
			children = vector<node*>();
			element = env;
			visited = 0;
			alpha = -100;
			beta = 100;
			depth = 0;
		}
		node(){
		}
};

//the function for search is as follows
node *root;
	
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


void spa(environment e){
	vector<tuple<float ,vector<int> > > ans = e.possible_moves();
	cout << "------------------------------------------------------------------------------"<<endl;
	cout << "|                      THE POSSIBLE MOVES FOR PLAYER "<<e.current_player<<"                   |"<<endl;
	cout << "------------------------------------------------------------------------------"<<endl;
	cout << "| T | X | Y | T | X | Y |  V  |"<<endl;
	cout << "-------------------------"<<endl;
		for (int i = 0; i < ans.size(); i++){
		cout <<"| S |"<<get<1>(ans[i])[0] << " | "<<get<1>(ans[i])[1]<<" | ";
		if(get<1>(ans[i])[2] == 1){
			cout << "B |"<< get<1>(ans[i])[3] <<" | "<< get<1>(ans[i])[4] <<" | "<<get<0>(ans[i]) << " |"<<endl;
		}
		else{
			cout << "M |"<< get<1>(ans[i])[3] <<" | "<< get<1>(ans[i])[4] <<" | "<< get<0>(ans[i]) << " |"<<endl;
		}
		cout <<"-------------------------"<<endl;
	}
	
}
int d;
void search(node* f){
	if(f->beta > f->alpha){
		if (f->depth < d){
			if (f->visited < f->children.size() && f->visited != 0){
				f->visited += 1;
				(f->children[f->visited - 1])->alpha = f->alpha;
				(f->children[f->visited - 1])->beta = f->beta;
				search(f->children[f->visited - 1]);
			}
			else if (f->visited == 0){
				vector<tuple<float , vector<int> > >temp = f->element.possible_moves();
				for(int i = 0; i < temp.size(); i++){
					
					environment *temp2 = new environment();
					*temp2 = (f->element);
					(*temp2).take_action(get<1>(temp[i]));
					node *temp3 =new node(*temp2, f, get<1>(temp[i]));
					f->children.push_back(temp3);
				}
				f->element.board.clear();
				f->visited = 1;
				search(f->children[0]);
			}
		
			else if (f->visited == f->children.size()){
				//change in parent
				if (f != root){
					if (f->parent->element.current_player == 1){
						if (f->beta >= f->parent->alpha){
							f->parent->alpha = f->beta;
							f->parent->action = f->pa;
						}
					}
					else{
						if (f->alpha <= f->parent->beta){
							f->parent->beta = f->alpha;
							f->parent->action = f->pa;
						}
					}
					search(f->parent);
				}
			}
		}
		else if (f->depth == d){
				vector<tuple<float , vector<int> > >pa = f->element.possible_moves();
			if(pa.size()>0){
			
			if (f->parent->element.current_player == 1){
				f->beta = get<0>(pa[0]);
				if (f->beta >= f->parent->alpha){
					f->parent->alpha = f->beta;
					f->parent->action = f->pa;
			
				}
			}
			else{
				f->alpha = get<0>(pa[0]);
				if (f->alpha <= f->parent->beta){
					f->parent->beta = f->alpha;
					f->parent->action = f->pa;	
				}
			}
			f->element.board.clear();
		}
		search(f->parent);}
	}
	else{
		if (f != root){
			search(f->parent);
		}
	
	}
}




int main(){
	int temp = 0;
	char a1,a2;
	int x0,y0,x1,y1;
	int chance, n,m;
	int t;
	cin >> chance>>n>>m>>t;
	float p = 2*(1.5 - chance);
	chance = (int) p;
	environment e = environment(n,m,chance);
//	for(int h = 0; h < 5 ; h++){
//		if(e.current_player == -1){
//		cin>>a1>>x0>>y0>>a2>>x1>>y1;
//			if (a2 == 'M'){
//				e.take_action(vector<int>({x0,y0,0,x1,y1}));
//			}
//			else{
//				e.take_action(vector<int>({x0,y0,1,x1,y1}));
//			}
//		}
//		else{
//			vector<int> y = get<1>(e.possible_moves()[0]);
//			e.take_action(y);
//			if (y[2] == 0){
//				cout << "S "<<y[0]<<" "<<y[1]<<" "<<"M "<<y[3]<<" "<<y[4]<<endl;
//			}	
//			else{
//				cout << "S "<<y[0]<<" "<<y[1]<<" "<<"B "<<y[3]<<" "<<y[4]<<endl;
//			}
//		}
//	}
	while(temp < t){
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
			
			node r = node(e);
			root = &r;
			d = 3;
			search(root);
			vector<int> y = (*root).action;
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
