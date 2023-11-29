#include <stdlib.h>
#include "hc.h"


int main()
{
    // Initialize HOOPS/3dGS
    HC_Open_Segment("/segment");
    // HC_Set_Driver_Options("style=windows");
    HC_Set_Color("lines=white");

    // Create a sphere
    float center[] = {1, 1, 1};
    HC_Insert_Sphere(center, 2, NULL, NULL);

    HC_Close_Segment();


    return 0;
}