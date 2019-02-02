//1346 Brincadeira de Criança

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdio>
using namespace std;

bool cmp(const pair<int,int> &p1, const pair<int,int>&p2) {
	if(p1.first+p1.second == p2.first+p2.second)
		return min(p1.first,p1.second) < min(p2.first,p2.second);// + p1.second < p2.first + p2.second;
	else
		return p1.first+p1.second < p2.first+p2.second;
	/*
	if( p1.second - p1.first == p2.second - p2.first )
		return p1.first > p2.first;
	else 
		return p1.second - p1.first < p2.second - p2.first;
	*/
}

int backtracking(int discard, int idx, int sum, int out,
				 vector< pair<int,int> > &v, vector<int> &sumV) 
{
	int n = v.size();
	int piece = v[idx].first - v[idx].second;
	if(idx==n-1) {
		if(idx==discard) //piece to discard
			return sum==0 ? out : -1; //return out if sum is zero
		else if(piece == -sum )
			return out + v[idx].first; // return out if last piece equals sum
		else if(piece == sum)
			return out + v[idx].second; // return out if last piece equals sum
		else
			return -1;
	}
	else {
		if(idx==discard) //ignore this piece
			return backtracking(discard, idx+1, sum, out, v, sumV);
		
		int maxSum = sumV[idx];
		if(discard>idx && discard<n) maxSum -= (v[discard].first - v[discard].second);
		if(maxSum<abs(sum)) {
			//cout << "stopping idx=" << idx << " sum=" << sum << " maxSum=" << maxSum << " discard="<< discard << endl;
			return -1;
		}

		int opt1 = backtracking(discard, idx+1, sum+piece, out+v[idx].first, v, sumV);

		if(opt1>0 || sum==0) return opt1;
		//if(sum-piece<0) return opt1;
		return backtracking(discard, idx+1, sum-piece, out+v[idx].second, v, sumV);
	}
}

int main() {
	int n;
	while( true ) {
		cin >> n;
		if(!n) break;

		vector< pair<int,int> > v(n);
		vector< int > sum(n);

		int totalSum = 0;
		for(int i=0; i<n; i++) {
			cin >> v[i].first >> v[i].second;
			if(v[i].first < v[i].second) 
				swap(v[i].first, v[i].second);
			assert(totalSum <= totalSum + v[i].first + v[i].second);
			totalSum += v[i].first + v[i].second;
		}

		sort(v.begin(), v.end(), cmp);

		sum[n-1] = v[n-1].first - v[n-1].second;
		for(int i=n-2; i>=0; i--) {
			sum[i] = sum[i+1] + v[i].first - v[i].second;
		}

		
		//for(int i=0; i<n; i++) {
		//	cout << v[i].first << "/" << v[i].second << " sum=" << sum[i] << endl;
		//}
		


		int pieceToDiscard = -10;
		int output;

		if(totalSum==0) pieceToDiscard=-1;
		else
		for(int i=-1; i<n; i++) {
			if(i==-1 && totalSum%2==1) continue;
			if(i>-1 && (totalSum - v[i].first - v[i].second)%2==1) continue;
			
			if(i>-1 && totalSum - v[i].first -v[i].second == 0) {
				pieceToDiscard = i;
				output = 0;
				break;
			}

			int atual = backtracking(i, 0, 0, 0, v, sum);
			if(atual>0) {
				pieceToDiscard = i;
				output = atual;
				break;
			}
		}

		if(pieceToDiscard==-10)
			cout << "impossible" << endl;
		else if(pieceToDiscard==-1)
			cout << output << " discard none" << endl;
		else
			cout << output << " discard " << v[pieceToDiscard].second << " " 
				 << v[pieceToDiscard].first << endl;

	}
}
