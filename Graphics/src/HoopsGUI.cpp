#include <iostream>
//add stuff for HOOPS viewer compilation

int main()
{
      float pts[4][3] = {{-0.5, -0.5, 0.0}, 
                    {0.5, -0.5, 0.0}, 
                    {0.5, 0.5, 0.0}, 
                    {-0.5, 0.5, 0.0}};   
                    
    HC_Insert_Polygon(4, pts);

    return 0;
}