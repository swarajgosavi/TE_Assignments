#include <bits/stdc++.h>
#include <sstream>
#include <fstream>

using namespace std;

class Macro {
private:

    vector<tuple<string, int, int, int, int>> mntab ;
    vector<tuple<string, string>> kpdtab ;
    vector<string> pntab ; 
    vector<string> aptab ; 
    vector<vector<string>> tokens ;
    vector<vector<string>> mdtab;

    fstream outfile;


public:

    Macro(string filepath) {
        fstream infile( filepath, ios::in);
        string str;
        while (getline(infile, str)) {
            stringstream ss(str);
            string s;
            vector<string> temp;
            while (getline(ss, s, ' ')) {
                temp.push_back(s);
            }
            tokens.push_back(temp);
        }
    }

    void Pass1() {
    	int MDTP = 1, KPDTP = 1;
    	fstream mdtfile;
    	mdtfile.open("MDT.txt", ios::out);
        for(int i=1; i<tokens.size(); i++) {
            vector<string> line = tokens[i];
            string pntabName = "PNTAB_";
//            pntab.clear();
            if(tokens[i-1][0] == "MACRO") {
                string macroName = line[0];
                pntabName += macroName;
                int KP = 0, PP = 0;
                for(int j=1; j<line.size(); j++) {
                    string parameter = line[j];
                    if(parameter.find("=") != string::npos) {
                        KP++;
                        string name = parameter.substr(0, parameter.find("="));
                        string defaultValue = parameter.substr(parameter.find("=")+1, parameter.length());
                        kpdtab.push_back({name, defaultValue});
                        pntab.push_back(name);
                    }
                    else {
                        PP++;
                        pntab.push_back(parameter);
                    }
                }
                printPNTAB(pntabName);
                mntab.push_back({macroName, PP, KP, MDTP, KPDTP});
                KPDTP += KP;
            }
            else {
                if(line[0] != "MACRO") {
                	mdtfile << line[0] << " ";
                    for(int j=1; j<line.size(); j++) {
                        if(line[j][0] == '&') {
                            int index = find(pntab.begin(), pntab.end(), line[j]) - pntab.begin();
                            if(index >= 0) {
                            	mdtfile << "(P," << index+1 << ")" << " ";
                            }
                        }
                    }
                    mdtfile << "\n";
                    MDTP++;
                }
            }
        }
        mdtfile.close();
        printMNTAB() ; 
        printKPDTAB() ;
    }

    void printMNTAB() {
        outfile.open("MNT.txt", ios::out);
        for( const tuple<string,int,int,int,int>& entry : mntab ) {
            outfile << get<0>( entry ) << ' ' ; 
            outfile << get<1>( entry ) << ' ' ; 
            outfile << get<2>( entry ) << ' ' ; 
            outfile << get<3>( entry ) << ' ' ; 
            outfile << get<4>( entry ) << ' ' ; 
            outfile << "\n" ; 
        }
        outfile.close();
    }

     void printPNTAB(string macrofile) {
        outfile.open(macrofile, ios::out);
        for( const string entry : pntab ) {
            outfile << entry << "\n" ; 
        }
        outfile.close();
    }

    void printKPDTAB() {
        outfile.open("KPDTAB.txt", ios::out);
        for( const tuple<string,string>& entry : kpdtab ) {
            outfile << get<0>( entry ) << ' ' ; 
            outfile << get<1>( entry ) << ' ' ; 
            outfile << "\n" ; 
        }
        outfile.close();
    }

    void Pass2() {
        fstream infile, macroCall;
        infile.open("MDT.txt", ios::in);
        string _str;
		while (getline(infile, _str)) {
			stringstream ss(_str);
			string s;
			vector<string> temp;
			while (getline(ss, s, ' ')) {
				temp.push_back(s);
			}
			mdtab.push_back(temp);
		}
		infile.close();

        macroCall.open("macro_call.txt", ios::app | ios::in);
        tokens.clear();
        string str;
		while (getline(macroCall, str)) {
			stringstream ss(str);
			string s;
			vector<string> temp;
			while (getline(ss, s, ' ')) {
				temp.push_back(s);
			}
			tokens.push_back(temp);
		}
		macroCall.close();

		string macroName;
		int MDTP, KPDTP, PP, KP;

		for(int i=0; i<tokens.size(); i++) {
            vector<string> line = tokens[i];
            int index ;
			for(int i=0; i<mntab.size(); i++) {
				if(get<0>(mntab[i]) == line[0]) {
					index = i;
				}
			}
			macroName = get<0>(mntab[index]);
			PP = get<1>(mntab[index]);
			KP = get<2>(mntab[index]);
			MDTP = get<3>(mntab[index]);
			KPDTP = get<4>(mntab[index]);

			string pntabName = "PNTAB_" + macroName;
			string aptabName = "APTAB_" + macroName;

			vector<string> aptab(PP+KP);
			for(int i=1; i<line.size(); i++) {
				if(i < PP)
					aptab.push_back(line[i+1]);
				else {
					if(index >= 0) {
						int index = find(pntab.begin(), pntab.end(), line[i]) - pntab.begin();
						cout << line[i] << "\n";
//						aptab.insert(aptab.begin() + index, line[i].substr(line[i].find("=")+1, line[i].lenght()));
					}
				}

			}

//			while(mdtab[MDTP][0] != "MEND") {
//				for(auto i : mdtab[MDTP]) {
//					cout << i << " ";
//				}
//				cout << "\n";
//				MDTP++;
//			}
		}
        
    }
};

int main() {
    Macro macro = Macro("testcase_01.txt");
    macro.Pass1();
    macro.Pass2();
    return 0;
}
