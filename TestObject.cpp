using namespace std;
#include<string>




class TestObject {
	


public:

	TestObject(const std::string FileName) : fileName(FileName) {}
	std::string fileName; 

	string GetFileName()  const{
		return fileName;
	}

};


string GetStringFromTest() {

	return "testString";
}

