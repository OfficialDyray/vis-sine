using namespace std;

float readf(string location){
    ifstream cputemp;
    cputemp.open(location, ios::in);
    string str;	

    for(int lineno=1; getline(cputemp, str)&& lineno < 3; lineno++){
	if(lineno==1){
	    break;
	}
    }	
    cputemp.close();
    return stoi(str)/1000;
}
