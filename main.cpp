#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	
	// input the data

	int nodes = 0;
	int edges = 0;
	
	cin >> nodes >> edges;
	
	int adjacency_matrix[100][100];
	
	for(int i = 0; i < nodes; i++){
		for(int j = 0; j < nodes; j++){
			adjacency_matrix[i][j] = 0;
		}
	}
	
	int road1 = 0;
	int road2 = 0;
	
	for(int i = 0; i < edges; i++){
		cin >> road1 >> road2;
		adjacency_matrix[road1-1][road2-1] = 1;
	}
	
	int select_numbers = 0;
	cin >> select_numbers;

	int* selected_array = new int[select_numbers];
	for(int i = 0; i < select_numbers; i++){
		cin >> selected_array[i];
	}
	
	sort(selected_array, selected_array + select_numbers);

	// Algorithms : DFS(Depth-First Search) to detect the cycle
	// Create three structures: white_set, gray_set and black_set respectively
	// The nodes in white_set are which wasn`t explored.
	// The nodes in gray_set are which are exploring.
	// The nodes in black_set are which don`t need to explore again. = couldn`t be a cycle
	
	// 憒??曉撠?閮芸????舫?暺撠曹???閬赤??
	// 暺?銵函內?嗆??eighbors(摮拙?)?賢歇蝬xplore??瘝?曄嚗”蝷箏neighbors(摮拙?)?賢??舫?暺?
 
	// 憒??曉撠?閮芸????舐暺撠梯”蝷箇?曆???
	// 撠?閮芸????舐暺”蝷箔??舀??????舀??酋摮?
	
	// 憒??曉撠?閮芸????舐暺撠勗??嗆?箇暺??頝臬?銋葉
	// 憒?撠????eighbors(摮拙?)?質摰?雿???曄嚗停撠迨暺?粹?暺?
	
	int* black_set = new int[nodes];
	int* gray_set = new int[nodes];
	int* white_set = new int[nodes];
	
	for(int i = 0; i < nodes; i++){
		black_set[i] = 0;
		gray_set[i] = 0;
		white_set[i] = 0;
	}
	
	for(int i = 0; i < select_numbers; i++){
		white_set[selected_array[i] - 1] = 1;
	}
	
	for(int i = 0; i < nodes; i++){
		if(white_set[i] != 1){
			black_set[i] = 1;
		}
	}
	
	int* path = new int[nodes]; // Creating the path array
	for(int i = 0; i < nodes; i++){ // Initialization
		path[i] = -1;
	} 
	int path_flag = 0; // ?曉甇??曄?銝????券楝敺???蝵?
	
	bool cycle = false; // ????啁
	int neighbor = false; // 甇日????撅?摮重)
	
	int i = 0; // ?曉甇??亦??芯?暺?
	while(cycle == false or i >= nodes){ // The source node
	
		if(select_numbers < 2 or edges < 2 or nodes < 2){
			break;
		}

		// ?亦??券?臭??舫?舫?暺?
		bool black_flag = true;
		for(int b = 0; b < nodes; b++){
			if(black_set[b] == 0){
				black_flag = false;
				break;
			}
		}
		if(black_flag == true){
			break;
		}

		// ????臭?暻潮???
		if((white_set[i] == 0 and gray_set[i] == 0) or black_set[i] == 1){ // 甇日??曉?舫?暺?
			i++;
			continue;
		}
		if(white_set[i] == 1 and gray_set[i] == 0){ // 甇日??曉?舐暺?
			// 敺暺?箇暺?
			white_set[i] = 0; 
			gray_set[i] = 1;
			path[path_flag] = i;
			path_flag++;
		}
		
		// ?斗銝???蝬???鞊⊥暺?賢????
		for(int x = 0; x < nodes; x++){

			neighbor = false;
			
			if(i == x){ // 銝?芸楛 
				continue;
			}
			
			if(adjacency_matrix[i][x] == 0){ // 銝甇餉楝 
				continue;
			}
			
			if(black_set[x] == 1){ // 銝暺? 
				continue;
			}
			
			// 銝?菟??ㄐ銵函內?舫?暺??舀香頝?
			
			neighbor = true;
			
			if(gray_set[x] == 1){ // ?舐
				cycle = true;
			}
			else{ // ?賣?ㄐ銵函內銝???蝬???鞊∠?賡?
				// 撠迨暺?箇暺?
				white_set[x] = 0;
				gray_set[x] = 1;
				i = x; // 撠迨暺?箔?銝??隢?
				path[path_flag] = i;
				path_flag++;
			}
			
			break;
		}
		
		if(neighbor == false){ // 甇日?neighbor?暺??甇餉楝嚗?粹?暺?
			white_set[i] = 0;
			gray_set[i] = 0;
			black_set[i] = 1;

			path_flag--;
			path[path_flag] = -1;
			
//			if(path_flag == 0){
//				i = 0;
//				continue;
//			}

			for(int g = nodes - 1; g >= 0; g--){
				if(path[g] != -1 and gray_set[path[g]] == 1){
					i = path[g];
					break;
				}
			}
			
		}		
	}
	
	cout << cycle;
	 
	 
	return 0;
}
