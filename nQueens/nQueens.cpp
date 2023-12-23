#include <iostream>
#include <vector>

bool isvalid(std::vector<std::vector<bool>> &board, int row, int col) {
	for (int rows = 0; rows < row; rows++) {
		if (board[rows][col] == 1)
			return false;
	}

	int i = row - 1, j = col - 1;
	while (i >= 0 && j >= 0) {
		if (board[i--][j--] == 1)
			return false;
	}

	i = row - 1, j = col + 1;
	while (i >= 0 && j < board.size()) {
		if (board[i--][j++] == 1)
			return false;
	}

	return true;
}

template <typename T>
void print(std::vector<std::vector<T>> vec) {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec[i].size(); j++) {
			std::cout << vec[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}



void backtrack(std::vector<std::vector<bool>> board, int row, int& count) {
	if (row == board.size()) {
		++count;
		print(board);
		std::cout << std::endl << "                                      " << count << std::endl;
		return;
	}


	for (int col = 0; col < board.size(); col++) {
		if (isvalid(board, row, col)) {
			board[row][col] = 1;
			backtrack(board, row + 1, count);
			board[row][col] = 0;
		}
	}
}



int nqueens(int n) {
	std::vector<std::vector<bool>> board(n, std::vector<bool>(n,0));
	int count = 0;
	backtrack(board, 0, count);
	std::cout << std::endl << "count is " << count;
	return count;
 }


void backtracksubset(std::vector<int> &nums, int target,
	std::vector<std::vector<int>> &ans, std::vector<int> curr) {
	if (target == 0) {
		ans.push_back(curr);
	}

	for (int num : nums) {
		if (target - num >= 0) {
			curr.push_back(num);
			backtracksubset(nums, target - num, ans, curr);
			curr.pop_back();
		}
	}
}


void subsetsumdup(std::vector<int> nums, int target) {//allows use one element multiple times
	std::vector<std::vector<int>> answer;
	std::vector<int> curr;
	backtracksubset(nums, target, answer, curr);
	print(answer);
}

bool subsetsum(std::vector<int> nums, int index, int sum) {

	if (!sum) 
		return true;

	if (index == -1)
		return false;

	if (nums[index] > sum)
		subsetsum(nums, index - 1, sum);

	return subsetsum(nums, index - 1, sum) || subsetsum(nums, index - 1, sum - nums[index]);
}

void print(std::vector<int> vec) {
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

void subsetsumanswers(std::vector<int> nums, int index, int sum, std::vector<int> curr) {

	if (!sum) {
		print(curr);// prints in reverse order
		return;
	}

	if (index == -1)
		return;

	if (nums[index] > sum) {
		subsetsumanswers(nums, index - 1, sum, curr);
		return;
	}

	subsetsumanswers(nums, index - 1, sum, curr);

	curr.push_back(nums[index]);
	subsetsumanswers(nums, index - 1, sum - nums[index], curr);
	curr.pop_back();

}

bool isvalidmaze(std::vector<std::vector<bool>> maze, int r, int c) {
	return r >= 0 && c >= 0 && r < maze.size() && c < maze[0].size() && maze[r][c] == 0;
} 

void mazesolver(std::vector<std::vector<bool>> &maze, int i, int j, int m, int n, std::vector<std::vector<bool>> &path,
	int arri[], int arrj[]) {
	if (i == m - 1 && j == n - 1 && maze[i][j] == 1) {
		print(path);
		return;
	}

	for (int k = 0; k < 4; k++) {
			print(path);
			int newi = i + arri[k];
			int newj = j + arrj[k];
			if (isvalidmaze(maze, newi, newj)) {
				if (path[newi][newj] == 0)
					return;
				path[newi][newj] = 0;
				mazesolver(maze, newi, newj, m, n, path, arri, arrj);
				path[newi][newj] = 1;
				
				break;
			}
	}	
	
}

void maze(std::vector<std::vector<bool>> maze) {
	if (maze[maze.size() - 1][maze[0].size() - 1] == 1)
		return;

	std::vector<std::vector<bool>> path(maze.size(), std::vector<bool>(maze[0].size(), 1));
	int arri[4] = {-1,  0, 1,  0};
	int arrj[4] = { 0,  1, 0, -1};
	path[0][0] = 0;
	mazesolver(maze, 0, 0, maze.size(), maze[0].size(),path, arri, arrj);
}


int main(){
	int n;
	std::cout << "Type the board size " << std::endl;
	std::cin >> n;
	nqueens(n);

	//std::vector<int> nums = { 2, 3, 5, 7};
	//std::vector<int> curr;
	//subsetsumdup(nums, 14);
	//std::cout << subsetsum(nums, nums.size() - 1, 7);
	//subsetsumanswers(nums, nums.size() - 1, 14, curr);

	//maze test
	//std::vector<std::vector<bool>> mymaze = { {0, 0, 0, 1, 0, 0, 0, 0, 0}, {1, 1, 0, 1, 0, 1, 0, 1, 0}, {0, 0, 0, 1, 0, 1, 1, 1, 0},
	//{0, 1, 0, 1, 0, 0, 0, 1, 0}, {0, 1, 1, 1, 0, 1, 0, 1, 0}, {0, 0, 0, 0, 0, 1, 0, 1, 0}};
	//print(mymaze);
	//maze(mymaze);
	return 0;
}

