#include <iostream>
#include <sstream>
#include <fstream>


int  main(int _argc , char** _argv)
{
    // constructor for the gazebo node
    std::cout<<_argc << _argv <<std::endl;
    // constructor for the gazebo node
    // here I have to read the file and create points in the for 
    std::string filename = "pose2path.csv";
    std::ifstream myFile(filename);
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    std::string line,line2, column;
    double x,y,z;
    char c;

    if(myFile.good())
    {
        std::getline(myFile,line);
        std::cout<<line<<std::endl;
        std::getline(myFile,line2);
        std::stringstream ss(line2);
        // std::cout<<ss<<std::endl;
        while(ss >> c )
        {
            std::cout<<c <<std::endl;

        }

        while(std::getline(myFile,line))
        {
            std::stringstream ss(line);
            while(ss >> x)
            {
                ss >> y;
                std::cout<<x << "\t"<< y<< std::endl;
            }

        }

        

        
        myFile.close();

    }
    return 0;

}