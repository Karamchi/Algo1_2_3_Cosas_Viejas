#include <fstream> // for file I/O

using namespace std;
typedef unsigned char unchar; 

class MImage {

public:
	MImage();
    MImage(char const* fileName); //Constructor
    ~MImage(); //Deconstructor
    void write(char const* fileName);
private:
    ifstream* pInFile; 
    ofstream* pOutFile;
    unchar imageHeaderData[1078]; //.bmp header data with offset 1078.
    unchar** imageData;
    unchar**  filteredData;
};
