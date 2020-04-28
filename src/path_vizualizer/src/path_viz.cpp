#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <iostream>
#include <fstream>
#include <path_vizualizer/path_viz.h>

namespace gazebo
{
    
        // constructor and distructor
         Gazebo_Path_Viz::Gazebo_Path_Viz()
        {
             gazebo::transport::NodePtr node(new gazebo::transport::Node());
                this->gznode = node;
                this->gznode->Init();

        }

        Gazebo_Path_Viz::~Gazebo_Path_Viz()
        {
            // deletes all the connections on destroying this object
            this->connections.clear();

        }

        void Gazebo_Path_Viz::Load(int /*_argc*/ , char ** /*_argv*/)
        {
            // the connections or pushed and bind with inclass funciton
            this->connections.push_back(rendering::Events::ConnectCreateScene(
                boost::bind(&Gazebo_Path_Viz::Init, this)));
            
            this->connections.push_back(event::Events::ConnectPreRender(
                boost::bind(&Gazebo_Path_Viz::Update, this)));

        }



         void Gazebo_Path_Viz::DrawLineAdd(rendering::DynamicLines *l1, double x ,double y , double z)
        {
            l1->AddPoint(x,y,z,common::Color::Red);
        }
        void Gazebo_Path_Viz::Init(){

                std::cout<<"the init is called"<<std::endl;
                
                
        }


        rendering::DynamicLines* Gazebo_Path_Viz::createline()
        {
            rendering::DynamicLines *line1 = visual->CreateDynamicLine(
                gazebo::rendering::RENDERING_LINE_STRIP
            );
            line1->setMaterial(this->color);
            line1->setVisibilityFlags(GZ_VISIBILITY_GUI);
            return line1;
                
        }

        void Gazebo_Path_Viz::InitScene()
        {
            std::cout<< "the scene init is running"<<std::endl;
            this->scene = rendering::get_scene();
            std::cout<< "the scene is here"<<std::endl;
            if (!scene || !scene->Initialized())
            {
                std::cout<<"the scene is puttin scene"<<std::endl;
                return;
            }

            if (scene->GetVisual("groundplane"))
            {
               std::cout<<"pah para the scene has ground visuals kalura"<<std::endl; 
            }

            visual = gazebo::rendering::VisualPtr(
                new gazebo::rendering::Visual("groundplane", scene)
            );
            visual->Load();
            visual->SetVisible(true);
        }
        void Gazebo_Path_Viz::Update()
        {
            std::cout<< "this update is running "<<std::endl;
            
            this->InitScene();
                
            
           
            if ((this->scene || scene->Initialized()) && (this->visual)&&(!this->is_pathDRWANcomplete))
            {
                this->line = this->createline();
                // constructor for the gazebo node
                // here I have to read the file and create points in the for 
                this->csvpath2gazebo(this->filename);
                // this->gzposeSub = this->gznode->Subscribe(this->topicTogetpose, &Gazebo_Path_Viz::pose_callback, this);
                // this->Fonce_done = true;
                // std::cout<<"the scenen and visual are both there"<<std::endl;
                
                // uncomment to check
                // this->DrawLineAdd(this->line, 0,0,0);
                // this->DrawLineAdd(this->line, 10,3,5);
                // this->DrawLineAdd(this-> line ,2,-12,6);
                this->is_pathDRWANcomplete = true;
            }

        }

       void Gazebo_Path_Viz::pose_callback(ConstPoseStampedPtr &msg)
       {
           std::cout<<"the msg"<<msg<<std::endl;

       }

       bool Gazebo_Path_Viz::csvpath2gazebo(std::string filename)
       {
            // constructor for the gazebo node
            // std::cout<<_argc << _argv <<std::endl;
            // constructor for the gazebo node
            // here I have to read the file and create points in the for 
            // std::string filename = "pose2path.csv";
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
                        this->DrawLineAdd(this->line, x,y,2);
                    }

                }
                myFile.close();
            }

            return true;
       }




GZ_REGISTER_SYSTEM_PLUGIN(Gazebo_Path_Viz)

}

