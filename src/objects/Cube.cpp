#include "Cube.h"

ModelData* Cube::getModelData(unsigned int& size){
  size = 14;
  if(mModel != nullptr){
      return mModel;
  }
  ModelData* model= new ModelData[14];

  {
      model[0] = ModelData();
      model[0].x = 1.0f;
      model[0].y = 1.0f;
      model[0].z = 1.0f;
      model[0].u = 0.75f;
      model[0].v = 0.25f;
  }
  {
      model[1] = ModelData();
      model[1].x =  1.0f;
      model[1].y =  1.0f;
      model[1].z = -1.0f;
      model[1].u = 0.75f;
      model[1].v = 0.0f;
  }
  {
      model[2] = ModelData();
      model[2].x = -1.0f;
      model[2].y =  1.0f;
      model[2].z =  1.0f;
      model[2].u = 0.5f;
      model[2].v = 0.25f;
  }
  {
      model[3] = ModelData();
      model[3].x = -1.0f;
      model[3].y =  1.0f;
      model[3].z = -1.0f;
      model[3].u = 0.5f;
      model[3].v = 0.0f;
  }
  {
      model[4] = ModelData();
      model[4].x =  1.0f;
      model[4].y = -1.0f;
      model[4].z =  1.0f;
      model[4].u = 0.75f;
      model[4].v = 0.5f;
  }
  {
      model[5] = ModelData();
      model[5].x =  1.0f;
      model[5].y = -1.0f;
      model[5].z = -1.0f;
      model[5].u = 0.75f;
      model[5].v = 0.75f;
  }
  {
      model[6] = ModelData();
      model[6].x = -1.0f;
      model[6].y = -1.0f;
      model[6].z =  1.0f;
      model[6].u = 0.5f;
      model[6].v = 0.5f;
  } 
  {
      model[7] = ModelData();
      model[7].x = -1.0f;
      model[7].y = -1.0f;
      model[7].z = -1.0f;
      model[7].u = 0.5f;
      model[7].v = 0.75f;
  }
  {
      model[8] = ModelData();
      model[8].x =  1.0f;
      model[8].y =  1.0f;
      model[8].z = -1.0f;
      model[8].u = 1.0f;
      model[8].v = 0.25f;
  }
  {
      model[9] = ModelData();
      model[9].x = -1.0f;
      model[9].y =  1.0f;
      model[9].z = -1.0f;
      model[9].u = 0.25f;
      model[9].v = 0.25f;
  }
  {
      model[10] = ModelData();
      model[10].x =  1.0f;
      model[10].y = -1.0f;
      model[10].z = -1.0f;
      model[10].u = 1.0f;
      model[10].v = 0.5f;
  }
  {
      model[11] = ModelData();
      model[11].x = -1.0f;
      model[11].y = -1.0f;
      model[11].z = -1.0f;
      model[11].u = 0.25f;
      model[11].v = 0.5f;
  }
  {
      model[12] = ModelData();
      model[12].x =  1.0f;
      model[12].y =  1.0f;
      model[12].z = -1.0f;
      model[12].u = 0.75f;
      model[12].v = 1.0f;
  }
  {
      model[13] = ModelData();
      model[13].x = -1.0f;
      model[13].y =  1.0f;
      model[13].z = -1.0f;
      model[13].u = 0.5f;
      model[13].v = 1.0f;
  }

  mModel = model;
  return model;
}
/*
     3/9/13_____________1/8/12
          /|           /|
         / |          / |
       2/__|________0/  |
        |  |        |   | 
        |  |7/11____|___|5/10
        |  /        |  /
        | /         | /
        |/__________|/
        6           4

                    3____________1
                    |           |
                    |           |
                    |           |
                    |           |
       9 __________2|___________|0___________8
        |           |           |           |
        |           |           |           |
        |           |           |           |
        |           |           |           |
        |___________|___________|___________|
        11         6|           |4          10
                    |           |
                    |           |
                    |           |
                   7|___________|5
                    |           |
                    |           |
                    |           |
                    |           |
                  13|___________|12

*/
unsigned short* Cube::getIndexData(unsigned int& size){
    size = 12*3;
    if(mIndexdata != nullptr){
        return mIndexdata;
    }
    unsigned short* indexData = new unsigned short[12*3];
    //up
    {
        
        indexData[0] = 0;//( 1,1, 1)
        indexData[1] = 1;//( 1,1,-1)
        indexData[2] = 2;//(-1,1, 1)

        indexData[3] = 2;//(-1,1, 1)
        indexData[4] = 1;//( 1,1,-1)
        indexData[5] = 3;//(-1,1,-1)
    }
    //right
    {
        
        indexData[6] = 0;
        indexData[7] = 4;
        indexData[8] = 8;

        indexData[9] = 4;
        indexData[10] = 8;
        indexData[11] = 10;
    }
    //front
    {
        
        indexData[12] = 2;
        indexData[13] = 0;
        indexData[14] = 6;

        indexData[15] = 0;
        indexData[16] = 6;
        indexData[17] = 4;
    }
    //left
    {
        
        indexData[18] = 2;
        indexData[19] = 9;
        indexData[20] = 6;

        indexData[21] = 9;
        indexData[22] = 6;
        indexData[23] = 11;
    }
    //back
    {
        
        indexData[24] = 13;
        indexData[25] = 12;
        indexData[26] = 7;

        indexData[27] = 12;
        indexData[28] = 7;
        indexData[29] = 5;
    }
    //bottom
    {
        indexData[30] = 7;
        indexData[31] = 6;
        indexData[32] = 4;

        indexData[33] = 4;
        indexData[34] = 7;
        indexData[35] = 5;
    }
    
    mIndexdata = indexData;

    return indexData;
}