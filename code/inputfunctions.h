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
