#include "BirdsEyeCAM.h"

BirdsEyeCAM::BirdsEyeCAM() {}

BirdsEyeCAM::~BirdsEyeCAM() {}

void BirdsEyeCAM::Update(ICameraSceneNode * pCamera, IrrlichtDevice * pDevice, IVideoDriver * pDriver) {
    
   dimension2d<u32> screenSize = pDriver -> getScreenSize();

   // make the camera look to a fixed point (45 degrees down) 
   // in front of it, so it wont stay locked on the old target. 
   vector3df cpos = pCamera -> getPosition(); 
   cpos.Z += 2; 
   cpos.Y -= 2;
   //pCamera -> setTarget(cpos); 

   // get the cursor positions 
   i32 x = pDevice -> getCursorControl() -> getPosition().X; 
   i32 y = pDevice -> getCursorControl() -> getPosition().Y; 

   // make the move distance the same for different frame rates 
   i32 fps = pDriver -> getFPS(); 
   f32 dist; 

   if (fps > 1) 
      dist = 200.0f / fps; 
   else 
      dist = 1.0f;    

   if (x > (screenSize.Width - 50)) 
   {    
      cout<<screenSize.Width<<endl;
      cout<<x<<endl;
      cout<<y<<endl;
      
      cpos = pCamera -> getPosition();       
      cpos.X += dist; 
      pCamera -> setPosition(cpos);                         
   } 
   else if (x < 50) 
   {    
      cpos = pCamera -> getPosition();       
      cpos.X -= dist; 
      pCamera -> setPosition(cpos);                      
   } 

   if (y < 50) 
   { 
      cpos = pCamera -> getPosition();       
      cpos.Z += dist; 
      pCamera -> setPosition(cpos);                         
   } 
   else if (y > (screenSize.Height - 50)) 
   {    
      cpos = pCamera -> getPosition();       
      cpos.Z -= dist; 
      pCamera -> setPosition(cpos);                      
   }
}