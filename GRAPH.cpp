#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//1.shortest path problem
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        queue<pair<pair<int,int>,int>>q; 
        q.push({{0,0},1});

        if (grid[0][0]==1) return -1; 
        if(grid[0][0]==0 && grid.size()==1 && grid[0].size()) return 1;


        vector<vector<bool>>visited(grid.size(),vector<bool>(grid.size(),false ));
         visited[0][0]=true; 
         while(!q.empty()){

            pair<int,int>p = q.front().first;
            int x=p.first;
            int y=p.second;
            int lengthofpath = q.front().second;
            q.pop();

            vector<pair<int,int>>neighbours = {{0,1},{0,-1},{1,0},{-1,0},{1,1},
                                               {-1,-1},{1,-1},{-1,1}};

            for(pair<int,int>neighbour : neighbours ){
               int newx = neighbour.first + x; 
               int newy = neighbour.second + y; 

               if(newx>=0 && newy>=0 && newx<grid.size() && newy<grid[0].size() && 
                 grid[newx][newy]==0 && !visited[newx][newy]){
                    q.push({{newx,newy},lengthofpath+1});
                    visited[newx][newy]= true;

                    if(newx==grid.size()-1 && newy==grid[0].size()-1) 
                             return lengthofpath+1;
                 }
                 
        }
             
  }
         return -1;

    }
};

//2.keys and rooms___________________________________________________________________________________________


class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        vector<bool> visited(n, false);
        dfs(rooms, visited, 0); 
        
        
        for (bool roomVisited : visited) {
            if (!roomVisited) return false;
        }
        return true;
    }
    
private:
    void dfs(const vector<vector<int>>& rooms, vector<bool>& visited, int currentRoom) {
        visited[currentRoom] = true; 
        for (int key : rooms[currentRoom]) {
            if (!visited[key]) {
                dfs(rooms, visited, key);
            }
        }
    }
};

//3.open the lock_____________________________________________________________________________________________________________________

class Solution {
public:
   
    string moveUp(string lock, int i) {
        string next = lock;
        next[i] = (lock[i] == '9') ? '0' : lock[i] + 1;
        return next;
    }

    
    string moveDown(string lock, int i) {
        string next = lock;
        next[i] = (lock[i] == '0') ? '9' : lock[i] - 1;
        return next;
    }

    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> dead(deadends.begin(), deadends.end());
        unordered_set<string> visited;
        queue<string> q;

        string start = "0000";

        if (dead.count(start)) return -1; 

        q.push(start);
        visited.insert(start);

        int steps = 0;

        while (!q.empty()) {
            int levelSize = q.size(); 

            for (int i = 0; i < levelSize; i++) {
                string current = q.front();
                q.pop();

                if (current == target) return steps;

                for (int j = 0; j < 4; j++) {
                    string up = moveUp(current, j);
                    string down = moveDown(current, j);

                    if (!dead.count(up) && !visited.count(up)) {
                        q.push(up);
                        visited.insert(up);
                    }

                    if (!dead.count(down) && !visited.count(down)) {
                        q.push(down);
                        visited.insert(down);
                    }
                }
            }

            steps++; 
        }

        return -1; 
    }
};

//4.01 matrix______________________________________________________________________________________________________________________________

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int rows = mat.size();
        int cols = mat[0].size();
        queue<pair<int, int>> q;
        vector<vector<int>> dist(rows, vector<int>(cols, -1)); 

      
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (mat[i][j] == 0) {
                    q.push({i, j});
                    dist[i][j] = 0;
                }
            }
        }

        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

     
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();

            for (auto [dx, dy] : directions) {
                int newRow = row + dx;
                int newCol = col + dy;

                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                    if (dist[newRow][newCol] == -1) {
                        dist[newRow][newCol] = dist[row][col] + 1;
                        q.push({newRow, newCol});
                    }
                }
            }
        }

        return dist;
    }
};

//5.Map of highest peak________________________________________________________________________________________________________________________

class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        int m = isWater.size(), n = isWater[0].size();
        vector<vector<int>> height(m, vector<int>(n, -1));
        queue<pair<int, int>> q;
        int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

       
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (isWater[i][j] == 1) {
                    height[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

       
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (auto& dir : directions) {
                int newx = x + dir[0], newy = y + dir[1];
                if (newx >= 0 && newx < m && newy >= 0 && newy < n && height[newx][newy] == -1) {
                    height[newx][newy] = height[x][y] + 1;
                    q.push({newx, newy});
                }
            }
        }

        return height;
    }
};

//6.As Far from Land as possible_____________________________________________________________________________________________________________

class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> q;
        int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int maxDist = -1;

        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                }
            }
        }

        
        if (q.empty() || q.size() == m * n) return -1;

    
        while (!q.empty()) {
            pair<int, int> front = q.front();
            q.pop();
            int x = front.first, y = front.second;

            for (int i = 0; i < 4; ++i) {
                int newx = x + directions[i][0], newy = y + directions[i][1];
                if (newx >= 0 && newx < m && newy >= 0 && newy < n && grid[newx][newy] == 0) {
                    grid[newx][newy] = grid[x][y] + 1;
                    maxDist = max(maxDist, grid[newx][newy] - 1);
                    q.push({newx, newy});
                }
            }
        }

        return maxDist;
    }
};

//7. All Nodes Distance K in Binary Tree_______________________________________________________________________________________________

class Solution {
public:
    
    unordered_map<int, vector<int>> graph;

    
    void buildGraph(TreeNode* node, TreeNode* parent) {
        if (!node) return;
        if (parent) {
            graph[node->val].push_back(parent->val);
            graph[parent->val].push_back(node->val);
        }
        buildGraph(node->left, node);
        buildGraph(node->right, node);
    }

    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        buildGraph(root, nullptr);  

        
        queue<int> q;
        unordered_set<int> visited;
        q.push(target->val);
        visited.insert(target->val);

        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            if (level == k) break;
            for (int i = 0; i < size; ++i) {
                int curr = q.front(); q.pop();
                for (int neighbor : graph[curr]) {
                    if (!visited.count(neighbor)) {
                        visited.insert(neighbor);
                        q.push(neighbor);
                    }
                }
            }
            level++;
        }

       
        vector<int> result;
        while (!q.empty()) {
            result.push_back(q.front()); q.pop();
        }
        return result;
    }
};

//8. Nearest Exit from Entrance in Maze____________________________________________________________________________________________________

class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m = maze.size(), n = maze[0].size();
        queue<pair<int, int>> q;
        q.push({entrance[0], entrance[1]});
        maze[entrance[0]][entrance[1]] = '+'; 

        int steps = 0;
        vector<vector<int>> directions = {{0,1},{1,0},{0,-1},{-1,0}};

        while (!q.empty()) {
            int size = q.size();
            steps++;
            for (int i = 0; i < size; ++i) {
                auto [row, column] = q.front(); q.pop();
                for (auto& dir : directions) {
                    int newr = row + dir[0];
                    int newc = column + dir[1];
                    if (newr >= 0 && newc >= 0 && newr < m && newc < n && maze[newr][newc] == '.') {
                        
                        if (newr == 0 || newc == 0 || newr == m-1 || newc == n-1) return steps;
                        maze[newr][newc] = '+'; 
                        q.push({newr, newc});
                    }
                }
            }
        }

        return -1; 
    }
};

//9. Snakes and Ladders____________________________________________________________________________________________________________________

class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int size = board.size();
        vector<int> path(size * size + 1, -1);

       
        int num = 1;
        bool leftToRight = true;
        for (int row = size - 1; row >= 0; row--) {
            if (leftToRight) {
                for (int col = 0; col < size; col++) {
                    path[num++] = board[row][col];
                }
            } else {
                for (int col = size - 1; col >= 0; col--) {
                    path[num++] = board[row][col];
                }
            }
            leftToRight = !leftToRight;
        }

        
        queue<int> toVisit;
        vector<bool> visited(size * size + 1, false);

        toVisit.push(1);      
        visited[1] = true;
        int steps = 0;

        while (!toVisit.empty()) {
            int levelSize = toVisit.size();
            for (int i = 0; i < levelSize; i++) {
                int current = toVisit.front();
                toVisit.pop();

                if (current == size * size) return steps;

               
                for (int dice = 1; dice <= 6; dice++) {
                    int next = current + dice;
                    if (next > size * size || visited[next]) continue;

                    visited[next] = true;

                    
                    if (path[next] != -1)
                        toVisit.push(path[next]);
                    else
                        toVisit.push(next);
                }
            }
            steps++;
        }

        return -1; 
    }
};

//10. Rotting Oranges_________________________________________________________________________________________________________________

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int rows = grid.size();
        int columns = grid[0].size();
        
        queue<pair<int, int>> q;
        int fresh = 0;
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                } else if (grid[i][j] == 1) {
                    fresh++;
                }
            }
        }
        
        if (fresh == 0) return 0;

        int time = 0;
        vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        while (!q.empty()) {
            int size = q.size();
            bool rotted = false;
            
            for (int i = 0; i < size; i++) {
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                
                for (auto d : directions) {
                    int newx = x + d.first;
                    int newy = y + d.second;
                    
                    if (newx >= 0 && newy >= 0 && newx < rows && newy < columns && grid[newx][newy] == 1) {
                        grid[newx][newy] = 2;
                        q.push({newx, newy});
                        fresh--;
                        rotted = true;
                    }
                }
            }
            if (rotted) time++;
        }

        return (fresh == 0) ? time : -1;
    }
};

//11.Race car_____________________________________________________________________________________________________________________

class Solution {
public:
    int racecar(int target) {
        queue<tuple<long long, long long, int>> q;
        q.push({0, 1, 0});
        unordered_set<string> visited;

        while (!q.empty()) {
            auto [pos, speed, step] = q.front();
            q.pop();

            if (pos == target) return step;

            string key = to_string(pos) + "," + to_string(speed);
            if (visited.count(key)) continue;
            visited.insert(key);

            q.push({pos + speed, speed * 2, step + 1});

            
            if ((speed > 0 && pos + speed > target) || (speed < 0 && pos + speed < target)) {
                q.push({pos, speed > 0 ? -1 : 1, step + 1});
            }
        }

        return -1;
    }
};

//12.BUS Routes___________________________________________________________________________________________________________________________________

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;

        unordered_map<int, vector<int>> stopToBus;
        for (int i = 0; i < routes.size(); i++) {
            for (int stop : routes[i]) {
                stopToBus[stop].push_back(i);
            }
        }

        queue<int> q;
        unordered_set<int> visitedStop;
        unordered_set<int> visitedBus;

        q.push(source);
        int count = 0;

        while (!q.empty()) {
            int size = q.size();
            count++;
            for (int i = 0; i < size; i++) {
                int curr = q.front(); q.pop();
                for (int bus : stopToBus[curr]) {
                    if (visitedBus.count(bus)) continue;
                    visitedBus.insert(bus);

                    for (int stop : routes[bus]) {
                        if (stop == target) return count;
                        if (!visitedStop.count(stop)) {
                            visitedStop.insert(stop);
                            q.push(stop);
                        }
                    }
                }
            }
        }

        return -1;
    }
};

//13.word Ladder_____________________________________________________________________________________________________________________________

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dictionary(wordList.begin(), wordList.end());
        if (!dictionary.count(endWord)) return 0;

        queue<pair<string, int>> q;
        q.push({beginWord, 1});
        unordered_set<string> seen;
        seen.insert(beginWord);

        while (!q.empty()) {
            auto [word, steps] = q.front(); q.pop();

            if (word == endWord) return steps;

            for (int i = 0; i < word.size(); i++) {
                string temp = word;
                for (char c = 'a'; c <= 'z'; c++) {
                    temp[i] = c;
                    if (dictionary.count(temp) && !seen.count(temp)) {
                        seen.insert(temp);
                        q.push({temp, steps + 1});
                    }
                }
            }
        }

        return 0;
    }
};
//14. EMPLOYEE IMPORTANCE______________________________________________________________________________________________________________

class Employee {
    public:
        int id;
        int importance;
        vector<int> subordinates;
    };
class Solution {
public:
    int totalImportance = 0;

    void DFSImportance(vector<Employee*> employeeList, int targetId) {
        for(int i = 0; i < employeeList.size(); i++) {
            if(employeeList[i]->id == targetId) {
                totalImportance += employeeList[i]->importance;
                if(employeeList[i]->subordinates.size() == 0)
                    return;
                for(int j = 0; j < employeeList[i]->subordinates.size(); j++)
                    DFSImportance(employeeList, employeeList[i]->subordinates[j]);
            }
        }
    }

    int getImportance(vector<Employee*> employeeList, int targetId) {
        DFSImportance(employeeList, targetId);
        return totalImportance;
    }
};
//15.NUMBER OF PROVINCES_______________________________________________________________________________________________________________

class Solution {
    public:
        void DFS(vector<vector<int>>& connections, int row, int column) {
            connections[row][column] = 0;
    
            for (auto next = 0; next < connections.size(); next++) {
                if (connections[column][next] == 1) {
                    DFS(connections, column, next);
                }
            }
        }
    
        int findCircleNum(vector<vector<int>>& connections) {
            int provinceCount = 0;
    
            for (auto row = 0; row < connections.size(); row++) {
                for (auto column = 0; column < connections[0].size(); column++) {
                    if (connections[row][column] == 1) {
                        provinceCount++;
                        DFS(connections, row, column);
                    }
                }
            }
    
            return provinceCount;
        }
    };

 //16.SUM OF NODES WITH EVEN VALUED GRANDPARENT____________________________________________________________________________________________________

class Solution {
    public:
        int sumEvenGrandparent(TreeNode* root) {
            if(!root) return 0;
            int leftLeftVal = 0, leftRightVal = 0, rightLeftVal = 0, rightRightVal = 0;
            if(root->val % 2 == 0){
                if(root->left){
                    if(root->left->left){
                        leftLeftVal = root->left->left->val;
                    }
                    if(root->left->right){
                        leftRightVal = root->left->right->val; 
                    }
                }
                if(root->right){
                    if(root->right->left){
                        rightLeftVal = root->right->left->val;
                    }
                    if(root->right->right){
                        rightRightVal = root->right->right->val;
                    }
                }
            }
            return leftLeftVal + leftRightVal + rightLeftVal + rightRightVal + sumEvenGrandparent(root->left) + sumEvenGrandparent(root->right);
        }
    };

//17.MAXIMUM AREA OF ISLAND______________________________________________________________________________________________________________________________________________________

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int maxArea = 0;
        int rows = grid.size();
        int cols = grid[0].size();

        vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}}; 

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j] == 1) {
                    int area = 0;
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    grid[i][j] = 0; 

                    while (!q.empty()) {
                        auto [x, y] = q.front(); q.pop();
                        area++;

                        for (auto dir : directions) {
                            int newX = x + dir.first;
                            int newY = y + dir.second;

                            if (newX >= 0 && newY >= 0 && newX < rows && newY < cols && grid[newX][newY] == 1) {
                                q.push({newX, newY});
                                grid[newX][newY] = 0; 
                            }
                        }
                    }

                    maxArea = max(maxArea, area);
                }
            }
        }

        return maxArea;
    }
};

//18. EVALUATE DIVISION__________________________________________________________________________________________________________________________________________

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, vector<pair<string, double>>> graph;
        
        for (int i = 0; i < equations.size(); i++) {
            string a = equations[i][0];
            string b = equations[i][1];
            graph[a].push_back({b, values[i]});
            graph[b].push_back({a, 1.0 / values[i]});
        }
        
        vector<double> ans;
        
        for (auto& query : queries) {
            string s = query[0];
            string e = query[1];
            
           
            if (graph.find(s) == graph.end()  || graph.find(e) == graph.end()) {
                ans.push_back(-1.0);
                continue;
            }
            
            queue<pair<string, double>> q;
            q.push({s, 1.0});
            unordered_set<string> visited;
            visited.insert(s);
            bool hasAnswer = false;
            
            while (!q.empty()) {
                auto [node, value] = q.front();
                q.pop();
                
                if (node == e) {
                    ans.push_back(value);
                    hasAnswer = true;
                    break;
                }
                
                for (auto& [neighbor, factor] : graph[node]) {
                    if (visited.find(neighbor) == visited.end()) {
                        q.push({neighbor, value * factor});
                        visited.insert(neighbor);
                    }
                }
            }
            
            if (!hasAnswer) {
                ans.push_back(-1.0);
            }
        }
        
        return ans;
    }
};

//19. SUM ROOT TO LEAF NUMBERS_______________________________________________________________________________________________________________________

 class Solution {
    public:
        int sumNumbers(TreeNode* root) {
            if(!root) return 0;
            int totalSum = 0;
            calculateSum(root, 0, totalSum);
            return totalSum;
        }
        void calculateSum(TreeNode* node, int currentNumber, int& totalSum) {
            int newNumber = currentNumber * 10 + node->val;
            if(!node->left && !node->right){
                totalSum += newNumber;
                return;
            }
            if(node->left) calculateSum(node->left, newNumber, totalSum);
            if(node->right) calculateSum(node->right, newNumber, totalSum);
        }
    };
 
//20. DETONATE THE MAXIMUM BOMBS_________________________________________________________________________________________________________________________________

class Solution {
    int totalBombs;
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int maxDetonated = 0;
        totalBombs = bombs.size();

        for (int i = 0; i < totalBombs; i++) {
            vector<int> currentBomb = bombs[i]; 
            vector<bool> visited(totalBombs, false);
            visited[i] =
            true;
            int detonated = dfs(bombs, i, visited, 1);
            maxDetonated = max(maxDetonated, detonated); 
        }

        return maxDetonated;
    }

    int dfs(vector<vector<int>>& bombs, int currentIndex, vector<bool>& visited, int count) {
        vector<int> currentBomb = bombs[currentIndex]; 
        for (int i = 0; i < totalBombs; i++) {
            if (i == currentIndex || visited[i]) {
                continue;
            }

            vector<int> nextBomb = bombs[i]; 
            int x1 = currentBomb[0];
            int y1 = currentBomb[1];
            long radius = currentBomb[2];
            int x2 = nextBomb[0];
            int y2 = nextBomb[1];

            long dx = x1 - x2;
            long dy = y1 - y2;
            if (radius * radius >= dx * dx + dy * dy) {
                visited[i] = true;
                count += dfs(bombs, i, visited, 1);
            }
        }
        return count;
    }
};
 
//21.  SURROUNDED REGIONS____________________________________________________________________________________________________

 void floodFill(vector<vector<char>>& board, int x, int y)
{
    if(board[x][y] == 'O'){
        board[x][y] = '1';
        if(x + 1 < board.size()) floodFill(board, x + 1, y);
        if(x - 1 >= 0) floodFill(board, x - 1, y);
        if(y + 1 < board[x].size()) floodFill(board, x, y + 1);
        if(y - 1 >= 0) floodFill(board, x, y - 1);
    }
}

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if(board.empty())
            return;

        int rows = board.size(), cols = board[0].size();

        
        for(int i = 0; i < rows; i++){
            floodFill(board, i, 0);
            floodFill(board, i, cols - 1);
        }

        
        for(int j = 1; j < cols - 1; j++){
            floodFill(board, 0, j);
            floodFill(board, rows - 1, j);
        }

        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < cols; ++j){
                if(board[i][j] == 'O') board[i][j] = 'X';
                else if(board[i][j] == '1') board[i][j] = 'O';
            }
        }
    }
};

//22. MINESWEEPER__________________________________________________________________________________________________________________________________

class Solution {
private:
    const vector<pair<int, int>> moveOptions = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0},
        {-1, -1}, {1, 1}, {1, -1}, {-1, 1}
    };

public:
    vector<vector<char>> updateBoard(vector<vector<char>>& field, vector<int>& press) {
        int x = press[0];
        int y = press[1];
        int totalRows = field.size();
        int columns = field[0].size();

        if (field[x][y] == 'M') {
            field[x][y] = 'X';
            return field;
        }

        int nearbyMines = 0;
        for (int i = 0; i < moveOptions.size(); i++) {
            int dx = moveOptions[i].first;
            int dy = moveOptions[i].second;
            int newx = x + dx;
            int newy = y + dy;
            if (newx >= 0 && newx < totalRows && newy >= 0 && newy < columns) {
                if (field[newx][newy] == 'M') {
                    nearbyMines++;
                }
            }
        }

        if (nearbyMines > 0) {
            char ch = nearbyMines + '0';
            field[x][y] = ch;
            return field;
        }

        field[x][y] = 'B';

        for (int i = 0; i < moveOptions.size(); i++) {
            int dx = moveOptions[i].first;
            int dy = moveOptions[i].second;
            int newx = x + dx;
            int newy = y + dy;

            if (newx >= 0) {
                if (newx < totalRows) {
                    if (newy >= 0 && newy < columns) {
                        if (field[newx][newy] == 'E') {
                            vector<int> nextClick = {newx, newy};
                            field = updateBoard(field, nextClick);
                        }
                    }
                }
            }
        }

        return field;
    }
};

 //23. LOWEST COMMON ANCESTOR OF DEEPEST LEAVES_______________________________________________________________________________________________________________________

     class Solution {
        private:
            unordered_map<TreeNode*, int> memo;
        
        public:
            TreeNode* lcaDeepestLeaves(TreeNode* node) {
                if (node == nullptr) {
                    return nullptr;
                }
        
                int leftDepth = findHeight(node->left);
                int rightDepth = findHeight(node->right);
        
                if (leftDepth == rightDepth) {
                    return node;
                } else {
                    if (leftDepth > rightDepth) {
                        return lcaDeepestLeaves(node->left); 
                    } else {
                        return lcaDeepestLeaves(node->right); 
                    }
                }
            }
        
            int findHeight(TreeNode* curr) {
                if (curr == nullptr) return 0;
        
                
                if (memo.count(curr)) return memo[curr];
        
                int leftSubtree = findHeight(curr->left);
                int rightSubtree = findHeight(curr->right);
        
                int total = max(leftSubtree, rightSubtree) + 1;
                memo[curr] = total;
                return total;
            }
        };

//24. RECOVOR BINARY SEARCH TREE_____________________________________________________________________________________________________________________________

class Solution {
private:
    TreeNode* firstNode = nullptr;
    TreeNode* secondNode = nullptr;
    TreeNode* prevNode = nullptr;
    void inorderTraversal(TreeNode* root) {
        if(root == nullptr)
            return;
        
        inorderTraversal(root->left);
        
        if(prevNode != nullptr && root->val < prevNode->val && firstNode == nullptr) {
            firstNode = prevNode;
        }
        if(prevNode != nullptr && root->val < prevNode->val && firstNode != nullptr) {
            secondNode = root;
        }
        prevNode = root;
        
        inorderTraversal(root->right);
    }

public:
    void recoverTree(TreeNode* root) {
        if(root == nullptr)
            return;
        
        inorderTraversal(root);
        
        if(firstNode != nullptr && secondNode != nullptr) {
            swap(firstNode->val, secondNode->val);
        }
    }
};

// 25. CHECK IF THERE IS A VALID PATH IN THE GRID______________________________________________________________________________________________________________

class Solution {
private:
    bool isConnected(vector<vector<int>>& directions, int prevStreet, int yDelta, int xDelta) {
        int baseIndex = prevStreet * 2;
        for (int i = 0; i < 2; i++) {
            int checkY = directions[baseIndex + i][0];
            int checkX = directions[baseIndex + i][1];
            if (checkY == yDelta && checkX == xDelta) {
                return true;
            }
        }
        return false;
    }

public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int rowCount = grid.size();
        int colCount = grid[0].size();

        vector<vector<int>> directions = {
            {0, -1}, {0, 1},
            {-1, 0}, {1, 0},
            {0, -1}, {1, 0},
            {0, 1}, {1, 0},
            {0, -1}, {-1, 0},
            {0, 1}, {-1, 0}
        };

        queue<int> toVisit;
        unordered_set<int> visited;
        toVisit.push(0);
        visited.insert(0);

        while (!toVisit.empty()) {
            int currentPos = toVisit.front();
            toVisit.pop();
            int currentY = currentPos / colCount;
            int currentX = currentPos % colCount;

            if (currentY == rowCount - 1 && currentX == colCount - 1) {
                return true;
            }

            int streetType = grid[currentY][currentX] - 1;
            int dirIndex = streetType * 2;

            for (int i = 0; i < 2; i++) {
                int nextY = currentY + directions[dirIndex + i][0];
                int nextX = currentX + directions[dirIndex + i][1];
                int nextPos = nextY * colCount + nextX;

                if (nextY >= 0 && nextY < rowCount && nextX >= 0 && nextX < colCount &&
                    visited.find(nextPos) == visited.end() &&
                    isConnected(directions, grid[nextY][nextX] - 1, -directions[dirIndex + i][0], -directions[dirIndex + i][1])) {
                    visited.insert(nextPos);
                    toVisit.push(nextPos);
                }
            }
        }

        return false;
    }
};


