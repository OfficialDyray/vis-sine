using namespace std;

float readf(string location, unsigned int divideby=1){
    ifstream file;
    file.open(location, ios::in);
    string str;	

    for(int lineno=1; getline(file, str)&& lineno <= 1; lineno++){
	if(lineno==1){
	    break;
	}
    }	
    file.close();
    return stoi(str)/divideby;
}

short unsigned int readmem(){
    ifstream file;
    file.open("/proc/meminfo", ios::in);
    int totalmem;
    int usedmem;
    string str;	

    for(int lineno=1; getline(file, str)&& lineno <= 3; lineno++){
	if(lineno==1){
            totalmem = stoi(str.erase(23,str.size()-1).erase(0,str.size()-8));
	}
        if(lineno==3){
            usedmem = stoi(str.erase(23,str.size()-1).erase(0,str.size()-8));
        }
    }	
    file.close();
    return 100-(usedmem*100/totalmem);
}
