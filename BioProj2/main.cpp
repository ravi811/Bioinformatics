#include <iostream>
#include <fstream>
#include <istream>

int main() {
    std::ifstream file;

    file.open("2.txt");
    if(file.is_open()){
        std::cout<<"File is open"<<std::endl;
    }

    int length1, length2;
    std::string line1,line2;
    ////Part A start
   std::getline(file,line1);
   std::getline(file,line2);
   //std::cout<<line1<<std::endl<<line2<<std::endl;

   length1=line1.length();
   length2=line2.length();


    file.close();
    std::ofstream outputFile("2A.txt");
    if (length1>length2){
        outputFile << length2;
        //std::cout<< "Writing complete Length2"<<std::endl;
    }
    else{
        outputFile << length1;
        //std::cout<< "Writing complete Length1"<<std::endl;
    }
    ////part A done
    //line1 and line2 are string variables, with respective lengths
    //length1 and length2, integer values

    ////Part B start



    ////Part C start
    

    return 0;
}