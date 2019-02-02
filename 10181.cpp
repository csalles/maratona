//10181

#include <queue>
#include <map>
#include <iostream>

using namespace std;

int puzzle[4][4];

/*void printPuzzle() {
	cout << "---" << endl;
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			cout << puzzle[i][j] << " ";
		}
		cout << endl;
	}
	cout << "---" << endl;
}*/

bool solvable() {
    int sum = 0, row, i, j;
    for(i = 0; i < 16; i++) {
        if(puzzle[i/4][i%4] == 0) {
            row = i/4 + 1;
            continue;
        }
        for(j = i+1; j < 16; j++) {
            if(puzzle[j/4][j%4] < puzzle[i/4][i%4]) {
                if(puzzle[j/4][j%4])
                    sum++;
            }
        }
    }
    return 1-(sum+row)%2;
}

unsigned long long int convertToInteger() {
	unsigned long long int sum = 0;
	unsigned long long int base = 1;
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			sum += base*puzzle[i][j];
			//cout << "base = " << base << endl;
			base *= 16;
		}
	}
	return sum;
}

void convertToPuzzle(unsigned long long int t) {
	unsigned long long int base = 1;
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			puzzle[i][j] = (t/base)%16;
			base *= 16;
		}
	}
}

unsigned long long int move_up(unsigned long long int t) {
	convertToPuzzle(t);
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if(puzzle[i][j]==0) {
				if(i==0) return 0;
				puzzle[i][j] = puzzle[i-1][j];
				puzzle[i-1][j] = 0;
				return convertToInteger();
			}
		}
	}
	return convertToInteger();
}

unsigned long long int move_down(unsigned long long int t) {
	convertToPuzzle(t);
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if(puzzle[i][j]==0) {
				if(i==3) return 0;
				puzzle[i][j] = puzzle[i+1][j];
				puzzle[i+1][j] = 0;
				return convertToInteger();
			}
		}
	}
	return convertToInteger();
}

unsigned long long int move_left(unsigned long long int t) {
	convertToPuzzle(t);
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if(puzzle[i][j]==0) {
				if(j==0) return 0;
				puzzle[i][j] = puzzle[i][j-1];
				puzzle[i][j-1] = 0;
				return convertToInteger();
			}
		}
	}
	return convertToInteger();
}

unsigned long long int move_right(unsigned long long int t) {
	convertToPuzzle(t);
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if(puzzle[i][j]==0) {
				if(j==3) return 0;
				puzzle[i][j] = puzzle[i][j+1];
				puzzle[i][j+1] = 0;
				return convertToInteger();
			}
		}
	}
	return convertToInteger();
}

unsigned long long int finalState() {
	int c=1;
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			puzzle[i][j] = c++;
		}
	}
	puzzle[3][3] = 0;
	return convertToInteger();
}

int main() {
	unsigned long long int t = finalState();

	queue<unsigned long long int> q;

	map<unsigned long long int, string> result;

	q.push(t);
	result[t] = "";

	unsigned long long int st = 1;

	int inputCases;
	cin >> inputCases;

	while(inputCases--) {

		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
				cin >> puzzle[i][j];

		if(!solvable()) {
			cout << "This puzzle is not solvable." << endl;
			continue;
		}

		unsigned long long int consult = convertToInteger();
		if(result.count(consult)) {
			cout << consult << endl;
			continue;
		}

		while(!q.empty()) {
			t = q.front();
			q.pop();

			convertToPuzzle(t);
			//printPuzzle();

	 		string r = result[t];
/*			if(st%100000==0)
				cout << st++ << " := " << t << " r=" << r << "queue_size = " << q.size() << endl;
			else
				st++;
*/
			unsigned long long int novo = move_up(t);
			if(novo!=0 && result.count(novo)==0) {
				result[novo] = "D"+r;
				q.push(novo);
			}
			novo = move_down(t);
			if(novo!=0 && result.count(novo)==0) {
				result[novo] = "U"+r;
				q.push(novo);
			}
			novo = move_left(t);
			if(novo!=0 && result.count(novo)==0) {
				result[novo] = "R"+r;
				q.push(novo);
			}
			novo = move_right(t);
			if(novo!=0 && result.count(novo)==0) {
				result[novo] = "L"+r;
				q.push(novo);
			}

			if(result.count(consult)) {
				cout << result[consult] << endl;
				break;
			}

		}
	}
	//cout << "ok" << endl;

}