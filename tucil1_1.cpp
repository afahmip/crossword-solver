#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <cstring>

#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

int main(){
	//KAMUS
	char grid[100][100], tempGrid[100][100];
	int nInput, n;
	string kata[100], input;
	typedef pair<int,int> pii;
	vector<pair<pii,pii> >coord;
	bool vis[100];
	clock_t time;
	
	//INITIALIZATION
	
	ifstream tc("input.txt");
	tc>>n;
	for(int i=0;i<n;i++) tc>>grid[i];
	tc>>input;
	string tempInput="";
	nInput=0;
	for(int i=0;i<input.length();i++){
		if(input[i] != ';') tempInput += input[i];
		else{
			kata[nInput] = tempInput;
			tempInput = "";
			nInput++;
		}
	}

	cout<<n<<endl;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<grid[i][j];
		}
		cout<<endl;
	}
	for(int i=0;i<nInput;i++) cout<<kata[i]<<" ";
	cout<<endl;
	
	cout<<endl;
	
	//BRUTE FORCE STARTS HERE

	time = clock();

	int x=0,y=0,r,c;
	bool found = false;

	while(x<n){
		y=0;
		while(y<n){
			if(grid[x][y] == '-'){
				//cek horizontal
				if(grid[x][y+1] == '-'){
					r=x; c=y;
					while(grid[r][c] != '#' && c<n) c++;
					c--;
					//cout<<r<<","<<y<<" hingga "<<r<<","<<c<<endl;
					coord.pb(mp(mp(r,y), mp(r,c)));
					y=c-1;
				}
			}
			y++;
		}
		x++;
	}

	y=0;
	while(y<n){
		x=0;
		while(x<n){
			if(grid[x][y] == '-'){
				//cek vertikal
				if(grid[x+1][y] == '-'){
					r=x; c=y;
					while(grid[r][c] != '#' && r<n) r++;
					r--;
					//cout<<x<<","<<y<<" hingga "<<r<<","<<y<<endl;
					coord.pb(mp(mp(x,y), mp(r,y)));
					x=r-1;
				}
			}
			x++;
		}
		y++;
	}

	cout<<endl;

	while(next_permutation(kata,kata+nInput)){
		int len;
		bool hor, valid=true;
		memset(vis, 0, sizeof vis);
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				tempGrid[i][j] = grid[i][j];
			}
		}
		for(int i=0;i<coord.size();i++){
			if(coord[i].f.f == coord[i].s.f){ //jika horizontal
				len = coord[i].s.s - coord[i].f.s + 1;
				hor = true;
			}else{
				len = coord[i].s.f - coord[i].f.f + 1;
				hor = false;
			}
			for(int j=0;j<nInput;j++){
				if(kata[j].length() == len && vis[j] == false){
					vis[j] = true;
					int corIdx;
					if(hor){
						corIdx=0;
						for(int k=coord[i].f.s; k<=coord[i].s.s; k++){
							if(tempGrid[coord[i].f.f][k] != '-'){
								if(tempGrid[coord[i].f.f][k] != kata[j][corIdx]) valid=false;
							}
							tempGrid[coord[i].f.f][k] = kata[j][corIdx];
							corIdx++;
						}
					}else{
						corIdx=0;
						for(int k=coord[i].f.f; k<=coord[i].s.f; k++){
							if(tempGrid[k][coord[i].f.s] != '-'){
								if(tempGrid[k][coord[i].f.s] != kata[j][corIdx]) valid=false;
							}
							tempGrid[k][coord[i].f.s] = kata[j][corIdx];
							corIdx++;
						}
					}
					break;
				}
			}
		}
		if(!valid) break;
		bool finish = true;
		for(int i=0;i<nInput;i++) if(vis[i]==false) finish=false;
		if(finish)break;
	}
	
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<tempGrid[i][j];
		}
		cout<<endl;
	}

	time = clock() - time;
	cout<<endl<<"Lama algoritma berjalan : "<<((float)time)/CLOCKS_PER_SEC<<" detik"<<endl;
	return 0;
}