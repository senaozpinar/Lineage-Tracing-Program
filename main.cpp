#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Individual
{
public:
	int idOfIndvl;
	int idOfParent;
	int levelOfIndvl;
	Individual(int idOfIndvl, int idOfParent){
		this->idOfIndvl = idOfIndvl;
		this->idOfParent = idOfParent;
	}	
};

int main(int argc, char const *argv[])
{
	//input and output file names
	string infile_name = argv[1];
	string outfile_name = argv[2];


	//opening input file
	ifstream infile;
	infile.open(infile_name); 

	//reading file
	int numOfIndvls;
	infile >> numOfIndvls;

	int idOfParent;
	infile >> idOfParent;

	vector<Individual> indvls;
	indvls.push_back(Individual(0, idOfParent));

	vector<vector<int>> tree;
	vector<int> firstLevel;
	firstLevel.push_back(0);
	tree.push_back(firstLevel);
	indvls[0].levelOfIndvl = 1;

	for(int i = 1; i < numOfIndvls; i++){
		infile >> idOfParent;
		indvls.push_back(Individual(i, idOfParent));

		for(int j = 0;  j < tree.size(); j++){
			for(int k = tree[j].size()-1; k>= 0; k--){
				if(tree[j][k] < idOfParent){
					break;
				}
				if(tree[j][k] == idOfParent){
					if(tree.size() == j+1){
						vector<int> newLevel;
						newLevel.push_back(i);
						tree.push_back(newLevel);
						indvls[i].levelOfIndvl = j+2;

						j = tree.size();
						break;
					}
					else{
						tree[j+1].push_back(i);
						indvls[i].levelOfIndvl = j+2;

						j = tree.size();
						break;
					}
				}
			}
		}
	}

	/*for(int i = 0 ; i < tree.size(); i++){
		for(int k = 0 ; k < tree[i].size(); k++){
			cout << tree[i][k] << " ";
		}
		cout << endl;
	}*/

	ofstream outfile;
	outfile.open(outfile_name);

	int numOfQueries;
	infile >> numOfQueries;

	for(int i = 0; i < numOfQueries; i++){
		int idOfIndvl, ancestor;
		infile >> idOfIndvl >> ancestor;

		int a = indvls[idOfIndvl].levelOfIndvl;

		for(int j = 1; j < tree[a - ancestor - 1].size(); j++){
			if(a-ancestor-1 < 0){
				outfile << -1 << endl;
				break;
			}
			if(tree[a - ancestor - 1][j] > idOfIndvl){
				outfile << 0 << endl;
				break;
			}
			else if(indvls[idOfIndvl].levelOfIndvl == a - ancestor + 1){
				for(int k = 0; k < tree[a - ancestor - 1].size(); k++){
					if(tree[a - ancestor - 1][k] < idOfIndvl){
						continue;
					}
					else{
						outfile << tree[a - ancestor - 1][k] << endl;
						j = tree[a - ancestor - 1].size();
						break;
					}
				}
			}
			else{
				idOfIndvl = indvls[idOfIndvl].idOfParent;
			}
		}
		//tree[indvls[idOfIndvl].levelOfIndvl - ancestor - 1]

	}

	infile.close();
	outfile.close();

	return 0;
}