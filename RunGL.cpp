#define var GLfloat
//####################################################################################################################

#ifdef WIN32
        #define   glGenerateMipmap       glGenerateMipmapEXT
        #define   glGenFramebuffers      glGenFramebuffersEXT
        #define   glBindFramebuffer      glBindFramebufferEXT
        #define   glFramebufferTexture2D glFramebufferTexture2DEXT
         
        #define   STRICT
        #define   WIN32_LEAN_AND_MEAN
        #include <windows.h>
        #include <iostream.h>
        #include <fstream.h>
        //using namespace std; //___used for string object

        //-----------------------------------------------------------------------------

        #include <GL/gl.h>

        #include "headerFiles/glext.h"
        #include "headerFiles/glext_Init_A.cpp"

        void InitGL(void);
        void RenderGL(void);
        void shutDownGL(void);
        void ProcessKeyboard(void);
                
        var  viewWidth;
        var  viewHeight;
        
        //----------------------------------------------------------------------
        GLfloat  PassMouseMovement[2];
        //-------------------------------
        var keys[256], keypressed[256];

        
        //=================================        
        bool zKeyIsReset          = true;        
        bool xKeyIsReset          = true;            
        bool cKeyIsReset          = true;    
        bool vKeyIsReset          = true;        
        bool nKeyIsReset          = true;            
        bool mKeyIsReset          = true;  
        bool homeKeyIsReset       = true;            
        bool endKeyIsReset        = true;  
       
        bool lKeyIsReset          = true;         
        bool jKeyIsReset          = true;        
        bool iKeyIsReset          = true;          
        bool kKeyIsReset          = true;  
        bool oKeyIsReset          = true;          
        bool uKeyIsReset          = true;          
                   
        bool spaceBarIsPressed    = false;                         
                   
                   
        //=================================

        //----------------------------------
        #include "cpp/WGL_ARB_multisample.h"
        //=====================================

        #include "headerFiles/VSync.h"
        
        #include <windows.h>

        void      ConfigureAndLoadTexture(GLubyte *textureData, GLint texWidth, GLint texHeight );
        #include "headerFiles/glaux.h"
        #include "headerFiles/FreeImage.h"
        #include "cpp/freeImage.cpp"
        //------------------------------------------
 
#endif

//####################################################################################################################


//####################################################################################################################        
        
        
        
        GLfloat  PassTouchMovement[3];

//####################################################################################################################

#include <math.h>
  
//####################################################################################################################

#include "MATRIX_MATH.cpp"

//####################################################################################################################

//--------------------------------------------------------------------------------------------------------------
#define BUFFER_OFFSET(i) ((char *)0 + (i))
//----------------------------------------------------------------------------------------

        extern GLuint msaaFramebuffer;

        void RenderGL(void);
        void InitGL  (void);
        void shutDownGL(void);
      
        #ifdef __APPLE__
               var viewWidth;
               var viewHeight;
               GLuint  viewFramebuffer;
        #endif
          
        //-------------------------------------------------------------------------------


GLuint m_uiShadowMapTexture;
GLuint m_uiFrameBufferObject;

int fileName = 0;

//#########################################################################################################



void ConfigureAndLoadTexture(GLubyte *textureData, GLint texWidth, GLint texHeight )
{

        #ifdef __APPLE__
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        #endif
        
        #ifdef WIN32
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE );
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, textureData);
        #endif
}

//===============================================================================================================================


var     modelView[16];
var     projection[16];
var     mvpMatrix[16];
var     mvpMatrixInverse[16];
var     lightMatrix[16];
var     moveSetMatrix[16];
var     ProjectionShadow[16];
var     modelViewShadow[16];
var     viewMatrix[16];

var     LightModelViewMatrix[16];


float   modelWorld[16];
float   LightView[16];
float   LightProjection[16];
float   modelViewInverse[16];

float   tempMatrix[16];

var     textureMatrix[16] = {   0.5f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.5f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.5f, 0.0f,
                                0.5f, 0.5f, 0.5f, 1.0f   };

var     inverseMatrix[16];


//============================================================================================================================

var     moveShadowPivot_Z = 0.0;



//---------------------------------------------------------------------------------------
var           fieldOfView                                      =    30.0;
var           adjustNearFar[]                                  =  {  0.1, 250.0 };
//---------------------------------------------------------------------------------------
var           moveSet[]                                        =  {  0.0, 0, 0.0, 1.0};
//---------------------------------------------------------------------------------------
var           eyepositionCamera[]                              =  {  0, 0.0, 0.0, 0.0};
//---------------------------------------------------------------------------------------
var           eyeposition[]                                    =  {  0, 0.0, 30.2, 0.0};
var           lookAt[]                                         =  {  0,  0.0, 0, 0.0};
var           rotateModelWithLeftMouse[]                       =  {  0, 0};
//---------------------------------------------------------------------------------------
var           upVector[]             	                       =  {  0.0, 1.0, 0.0};
//---------------------------------------------------------------------------------------



//===========================================================================================================================================

void setupTransforms_MainColor(void)
{
        LoadIdentity(modelView);
        LookAt(modelView,    eyeposition[0],
                             eyeposition[1],
                             eyeposition[2],
                             lookAt[0],
                             lookAt[1],
                             lookAt[2],
                             upVector[0],
                             upVector[1],
                             upVector[2]);
        
        //--------------------------------------------------------------------------------------
        LoadIdentity(viewMatrix);
        AssignMatrix(viewMatrix, modelView);
        InvertMatrix(viewMatrix, viewMatrix);
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        //Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        //Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]);
        Rotate(modelView, 1.0, 0.0, 0.0, PassMouseMovement[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, PassMouseMovement[1]);        
        
}
                               
//===========================================================================================================================================                               
                            

//===========================================================================================================================================

void CollisionCheck(GLfloat X1, GLfloat X2, GLfloat Y1, GLfloat Y2,GLfloat Z2,GLfloat Z2, GLfloat model_ID);
void CollisionCheck_CHARACTER(GLfloat X1, GLfloat X2, GLfloat Y1, GLfloat Y2, GLfloat Z2, GLfloat Z2, GLfloat model_ID);
var  collisionBoxArray[5000][20];                            
                            
//===========================================================================================================================================
                            
                               //#####################################___SHADERS___######################################################                            
                               //====================================================================================
                               #include "_SHADERS/basic/collisionColors/collisionColors_SHADER_GLOBALS.cpp"
                               //====================================================================================
                               //#####################################___MODELS___#######################################################
                               //====================================================================================
                               #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Globals.cpp"                                                                
                               //====================================================================================   
                               
                               
                               //====================================================================================                                                                
                               GLfloat     model_01_collisionInfo[20];
                               GLfloat     model_01_POSITION[]                  =  {  0.0, 0.0,  0.0, 1.0};
                               GLfloat     model_01_VELOCITY[]                  =  {  0.05, 0.05,  0.05, 1.0};
                               bool        model_01_skipNextTest                =    false;
                               //====================================================================================
                               const GLint NUMBER_OF_BACKGROUND_MODELS          =  50;
                               GLuint      boxCount                             =  0;
                               GLuint      selectedModel                        =  0;                               
                               
                               GLfloat     backGroundModel[NUMBER_OF_BACKGROUND_MODELS];
                               GLfloat     backGroundModel_POSITION[NUMBER_OF_BACKGROUND_MODELS][3]; 
                               GLfloat     backGroundModel_VELOCITY[NUMBER_OF_BACKGROUND_MODELS][3];                                                                          
                               GLfloat     backGroundModel_SCALE[NUMBER_OF_BACKGROUND_MODELS][3];
                          
                               //====================================================================================                             
                               GLfloat     character_collisionInfo[20];
                               GLfloat     character_POSITION[]                 = {  0.0,  0.0,  0.0, 1.0};
                               GLfloat     character_VELOCITY[]                 = {  0.3,  0.3,  0.0, 1.0};
                               GLfloat     character_SCALE[]                    = {  1.0,  1.0,  1.0, 1.0};

                               //bool        characterCanMoveDOWN                 =  true;
                               //bool        characterCanMoveUP                   =  true;
                               //bool        characterCanMoveLEFT                 =  true;
                               //bool        characterCanMoveRIGHT                =  true;                               
                               GLfloat     gravity                              =  0.0;
                               GLfloat     jumpVelocity                         =  5.0; 
                               bool        characterJumpReset                   =  true;
                               GLuint      characterModel_ID                    =  0;



//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################


var shaderNumber = 0;

void SelectShader(var shaderNumber)
{
        
        //--------------------------------------------------------------------------------------
        if(shaderNumber == 26)
        {
                #include "_SHADERS/basic/collisionColors/collisionColors_SHADER_RENDER.cpp"
        }
        //--------------------------------------------------------------------------------------
    
   
}

//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################


void InitGL( void )
{//__BEGIN_INIT__@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        //==========================================================================
        #ifdef WIN32
            #include "cpp/setPixelFormat.cpp"
            #include "headerFiles/glext_Init_B.cpp"
            //-------------------------------------
            SetVSyncState(true);
            //-------------------------------------
            PassMouseMovement[0]        = rotateModelWithLeftMouse[0];
            PassMouseMovement[1]        = rotateModelWithLeftMouse[1];
        #endif
                   



        //############################################################################
        character_POSITION[1] = 6.0;
        collisionBoxArray[boxCount][0]      = character_POSITION[0];
        collisionBoxArray[boxCount][1]      = character_POSITION[1];
        collisionBoxArray[boxCount][2]      = character_POSITION[2];
        //----------------------------
        collisionBoxArray[boxCount][3]      = character_SCALE[0];        
        collisionBoxArray[boxCount][4]      = character_SCALE[1];
        collisionBoxArray[boxCount][5]      = character_SCALE[2];   
        //----------------------------
        collisionBoxArray[boxCount][6]      = character_VELOCITY[0];        
        collisionBoxArray[boxCount][7]      = character_VELOCITY[1];
        collisionBoxArray[boxCount][8]      = character_VELOCITY[2];         
        collisionBoxArray[boxCount][9]      = 0.0;
        collisionBoxArray[boxCount][10]     = 0.0;    
        collisionBoxArray[boxCount][11]     = 0.0;    
        collisionBoxArray[boxCount][12]     = boxCount;//CharacterModel_ID
        collisionBoxArray[boxCount][13]     = 0.0;     //generic_collision 
        collisionBoxArray[boxCount][14]     = 0.0;     //bounce_VELOCITY[0];    
        collisionBoxArray[boxCount][15]     = 0.0;     //bounce_VELOCITY[1];            
        collisionBoxArray[boxCount][16]     = 0.0;     //bounce_VELOCITY[2]; 
        collisionBoxArray[boxCount][17]     = 1.0;     //collisionColors_SHININESS;              
        //--------------------------------------------------------------------        
        
                  
        
        //=====================================================
     /* character_collisionInfo[0]   = collisionBoxArray[boxCount][0];//_POSITION[0]  //_leftEdge           
        character_collisionInfo[1]   = collisionBoxArray[boxCount][1];  //_POSITION[0]  //_rightEdge    
        character_collisionInfo[2]   = collisionBoxArray[boxCount][2];  //_POSITION[1]  //_bottomEdge       
        character_collisionInfo[3]   = collisionBoxArray[boxCount][3];  //_POSITION[1]  //_topEdge     
        character_collisionInfo[4]   = collisionBoxArray[boxCount][4];  //_POSITION[2]  //_nearEdge       
        character_collisionInfo[5]   = collisionBoxArray[boxCount][5];  //_POSITION[2]  //_farEdge       
        //------------------------
        character_collisionInfo[6]   = collisionBoxArray[boxCount][6];  //_VELOCITY[0]      
        character_collisionInfo[7]   = collisionBoxArray[boxCount][7];  //_VELOCITY[1]
        character_collisionInfo[8]   = collisionBoxArray[boxCount][8];  //_VELOCITY[2]       
        //------------------------
        character_collisionInfo[9]   = collisionBoxArray[boxCount][9];  //_SCALE[0]
        character_collisionInfo[10]   = collisionBoxArray[boxCount][10];// _SCALE[1]     
        character_collisionInfo[11]   = collisionBoxArray[boxCount][11];//_SCALE[2]
        //------------------------
        character_collisionInfo[12]   = collisionBoxArray[boxCount][12];//CharacterModel_ID     
        character_collisionInfo[13]   = collisionBoxArray[boxCount][13];//generic_collision 
        character_collisionInfo[14]   = collisionBoxArray[boxCount][14];//          
    */    //---------------------------------
        characterModel_ID       = boxCount;
        boxCount++; 
        //=============================================================================================
         
srand(time(0));


        for(int i = 1; i < NUMBER_OF_BACKGROUND_MODELS+1; i++)
        {
              //--------------------------------------------------------------------------------------------                   
              collisionBoxArray[i][0]          =  float((rand()% 10)-5) *1.1;  //_POSITION[0]
              collisionBoxArray[i][1]          =  float((rand()% 10)-5) *1.1;  //_POSITION[1]
              collisionBoxArray[i][2]          =  float((rand()% 10)-5) *1.1;  //_POSITION[2]
              //----------------------------              
              collisionBoxArray[i][3]          =  1.0;                         //_SCALE[0];
              collisionBoxArray[i][4]          =  1.0;                         //_SCALE[1];
              collisionBoxArray[i][5]          =  1.0;                         //_SCALE[2];
              //----------------------------          
              collisionBoxArray[i][6]          =  float((rand()% 10)-5) *.01;  //_VELOCITY[0];
              collisionBoxArray[i][7]          =  float((rand()% 10)-5) *.01;  //_VELOCITY[1];     
              collisionBoxArray[i][8]          =  float((rand()% 10)-5) *.01;  //_VELOCITY[2];               
              //----------------------------
              collisionBoxArray[i][9]          =  0.0;
              collisionBoxArray[i][10]         =  0.0;
              collisionBoxArray[i][11]         =  0.0;
              //--------------------------------------------------------------------------------------------
              collisionBoxArray[i][12]         =  boxCount;                    //CharacterModel_ID
              collisionBoxArray[i][13]         =  0.0;                         //generic_collision
              //-----------------------------
              collisionBoxArray[i][14]         =  0.0;                         //bounce_VELOCITY[0];
              collisionBoxArray[i][15]         =  0.0;                         //bounce_VELOCITY[1];
              collisionBoxArray[i][16]         =  0.0;                         //bounce_VELOCITY[2];
              collisionBoxArray[i][17]         =  1.0;                         //collisionColors_SHININESS;
              //--------------------------------------------------------------------------------------------              
              
              boxCount++;      
        } 
        

                 
        //=================================================================================================================
        #include "_SHADERS/basic/collisionColors/collisionColors_SHADER_INIT.cpp"
        //====================================================================================
        #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Init.cpp"                                                                   
        //------------------------------------------------------- 
        //#include "settings_BackgroundModels.cpp" 
        //==================================================================================== 
        //#################################################################################################################
        srand(time(0));


        //#################################################################################################################

    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glDisable(GL_BLEND);
        
//====================================================================================================================================

    



}//__END_INIT__@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################



void RenderGL(void)
{
 
        //========================================================================================================================================================        
        //---------------------------------------------------RETURN_TO_MAIN_FRAMEBUFFER____________________!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //---------------------------------------------------RETURN_TO_MAIN_FRAMEBUFFER____________________!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //========================================================================================================================================================        
        #ifdef __APPLE__    
             glBindFramebuffer(GL_FRAMEBUFFER, msaaFramebuffer);
        #endif    
        //========================================================================================================================================================        
        //---------------------------------------------------RETURN_TO_MAIN_FRAMEBUFFER____________________!!!!!!!!!!!!!!!!!!!!!!!!!!!!        
        //---------------------------------------------------RETURN_TO_MAIN_FRAMEBUFFER____________________!!!!!!!!!!!!!!!!!!!!!!!!!!!!          
        //========================================================================================================================================================
        
        
        //=======================================================================================================================
        glClearColor( 0.0f, 0.0f, 0.0f, 1.0 );
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glViewport(0, 0, (GLsizei)viewWidth, (GLsizei)viewHeight);
        PerspectiveMatrix(projection, fieldOfView, (GLfloat)viewWidth / (GLfloat)viewHeight, adjustNearFar[0],  adjustNearFar[1]);
        //-------------------------------------------------------------------------------------------------------          

        
        //====================================================================================================================================                 
        //====================================================================================================================================                           
        //====================================================================================================================================
               
                if(collisionBoxArray[0][13] == 1.0)
                {
                        collisionBoxArray[0][17] = 2.0;
                }
                if(collisionBoxArray[0][17] > 1.0)
                {
                        collisionBoxArray[0][17] -= 0.05; 
                                            
                } 
                  
        shaderNumber = 26;//plastic/collisionColors/
        setupTransforms_MainColor();        
        Translate(modelView, collisionBoxArray[0][0], collisionBoxArray[0][1], collisionBoxArray[0][2]);                           
        #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Character_Render.cpp"                                                                 
        //====================================================================================================================================                 
        //====================================================================================================================================                           
        //====================================================================================================================================

        for(int i = 1; i < NUMBER_OF_BACKGROUND_MODELS+1; i++)
        {
                
                if(collisionBoxArray[i][13] == 1.0)
                {
                        collisionBoxArray[i][17] = 2.0;
                       
                }
                if(collisionBoxArray[i][17] > 1.0)
                {
                        collisionBoxArray[i][17] -= 0.05;  
                                            
                }
                
                collisionBoxArray[i][13] = 0.0;//generic_collision    // RESET COLLISION                              
                //==================================================================

                collisionBoxArray[i][0]        += collisionBoxArray[i][6];
                collisionBoxArray[i][1]        += collisionBoxArray[i][7];                
                collisionBoxArray[i][2]        += collisionBoxArray[i][8];                 
                //=================================================================================================================
                
                setupTransforms_MainColor(); 
                Translate(modelView, collisionBoxArray[i][0], collisionBoxArray[i][1], collisionBoxArray[i][2]);                           
                Scale(modelView,     collisionBoxArray[i][3],    collisionBoxArray[i][4],    collisionBoxArray[i][5]);                   
                #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Render.cpp"  
                //================================================================================================================
                                    
                                    
                                    if(collisionBoxArray[i][0] < -11.0)//WALL_TESTS
                                    {
                                            collisionBoxArray[i][0] += 0.1;   
                                            collisionBoxArray[i][6] *= -1.0;                                         
                                    }
                                    if(collisionBoxArray[i][0] > 11.0)
                                    {
                                            collisionBoxArray[i][0] -= 0.1;   
                                            collisionBoxArray[i][6] *= -1.0;
                                    }
                                    //----------------------------------------------
                                    if(collisionBoxArray[i][1] <  -7.5)//WALL_TESTS
                                    {
                                            collisionBoxArray[i][1] += 0.1;   
                                            collisionBoxArray[i][7] *= -1.0;                                         
                                    }
                                    if(collisionBoxArray[i][1] > 7.5)
                                    {
                                            collisionBoxArray[i][1] -= 0.1;   
                                            collisionBoxArray[i][7] *= -1.0;
                                    } 
                                    //----------------------------------------------
                                    if(collisionBoxArray[i][2] <  -7.5)//WALL_TESTS
                                    {
                                            collisionBoxArray[i][2] += 0.1;   
                                            collisionBoxArray[i][8] *= -1.0;                                         
                                    }
                                    if(collisionBoxArray[i][2] > 7.5)
                                    {
                                            collisionBoxArray[i][2] -= 0.1;   
                                            collisionBoxArray[i][8] *= -1.0;
                                    }                                     
                                                 
                //================================================================================================================
                if(collisionBoxArray[i][13] == 0.0)
                {
                       CollisionCheck(collisionBoxArray[i][0]-collisionBoxArray[i][3]*0.5, collisionBoxArray[i][0]+collisionBoxArray[i][3]*0.5, collisionBoxArray[i][1]-collisionBoxArray[i][4]*0.5, collisionBoxArray[i][1]+collisionBoxArray[i][4]*0.5, collisionBoxArray[i][2]-collisionBoxArray[i][5]*0.5, collisionBoxArray[i][2]+collisionBoxArray[i][5]*0.5, collisionBoxArray[i][12]);
                }
                //================================================================================================================
                if(collisionBoxArray[i][13] == 1.0)
                {
                        collisionBoxArray[i][17] = 2.0;
                       
                }
                if(collisionBoxArray[i][17] > 1.0)
                {
                        collisionBoxArray[i][17] -= 0.05;  
                                            
                }    
        }

       
        //####################################################################################################################  
}//_END_RenderGL()


//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################



#ifdef WIN32
void ProcessKeyboard(void)
{
    
    
    //======================================__SELECT_MODEL__======================================        
    //#######################################################################################################
    //======================================__ADD_MODEL__=========================================      
    
    //##############################################################################################################################################    
    if (keys[VK_F8])
    {
         //=========================================================================================================================================
         ofstream outSettings("settings_BackgroundModels.cpp");
         //----------------------------------------------------
        
             outSettings << "character_POSITION[0]      =  " <<  character_POSITION[0]                                 <<  ";\n";                                                
             outSettings << "character_POSITION[1]      =  " <<  character_POSITION[1]                                 <<  ";\n\n"; 
             
             outSettings << "collisionBoxArray[0][0]    =  " <<  collisionBoxArray[0][0]                               <<  ";\n";          
             outSettings << "collisionBoxArray[0][1]    =  " <<  collisionBoxArray[0][1]                               <<  ";\n";                 
             outSettings << "collisionBoxArray[0][2]    =  " <<  collisionBoxArray[0][2]                               <<  ";\n";               
             outSettings << "collisionBoxArray[0][3]    =  " <<  collisionBoxArray[0][3]                               <<  ";\n"; 
             
             outSettings << "collisionBoxArray[0][6]" << " =  " <<   collisionBoxArray[0][6]  <<  ";\n";                       
             outSettings << "collisionBoxArray[0][7]" << " =  " <<   collisionBoxArray[0][7]  <<  ";\n";                 
             outSettings << "collisionBoxArray[0][8]" << " =  " <<   collisionBoxArray[0][8]  <<  ";\n";                 
             outSettings << "collisionBoxArray[0][12]" << " =  " <<   collisionBoxArray[0][12]  <<  ";\n";                 
             outSettings << "collisionBoxArray[0][10]" << " =  " <<   collisionBoxArray[0][10]  <<  ";\n";                       
             outSettings << "collisionBoxArray[0][11]" << " =  " <<   collisionBoxArray[0][11]  <<  ";\n";                 
             outSettings << "collisionBoxArray[0][12]" << " =  " <<   collisionBoxArray[0][12]  <<  ";\n";                 
             outSettings << "collisionBoxArray[0][13]" << " =  " <<   collisionBoxArray[0][13]  <<  ";\n";               
             outSettings << "collisionBoxArray[0][14]" << " =  " <<   collisionBoxArray[0][14]  <<  ";\n";                         
             outSettings << "collisionBoxArray[0][15]" << " =  " <<   collisionBoxArray[0][15]  <<  ";\n";                 
             outSettings << "collisionBoxArray[0][16]" << " =  " <<   collisionBoxArray[0][16]  <<  ";\n";                 
             outSettings << "collisionBoxArray[0][17]" << " =  " <<   collisionBoxArray[0][17]  <<  ";\n";               
             outSettings << "collisionBoxArray[0][18]" << " =  " <<   collisionBoxArray[0][18]  <<  ";\n";               
             outSettings << "collisionBoxArray[0][19]" << " =  " <<   collisionBoxArray[0][19]  <<  ";\n";               
                   
             
             outSettings << "//==========================================================================================  "     <<  ";\n\n";          
        
        
         for(int i = 1; i < NUMBER_OF_BACKGROUND_MODELS+1; i++)
         {
             outSettings << "//==========================================================================================  "             <<  "\n";            
             outSettings << "backGroundModel_POSITION[" << i << "][0] =  " <<  backGroundModel_POSITION[i][0]                            <<  ";\n";         
             outSettings << "backGroundModel_POSITION[" << i << "][1] =  " <<  backGroundModel_POSITION[i][1]                            <<  ";\n";          
             outSettings << "backGroundModel_POSITION[" << i << "][2] =  " <<  backGroundModel_POSITION[i][2]                            <<  ";\n";          
             outSettings << "//------------------------------------------------------------------------------  "                         <<  "\n"; 
             outSettings << "backGroundModel_SCALE[" << i << "][0]    =  " <<  backGroundModel_SCALE[i][0]                               <<  ";\n";           
             outSettings << "backGroundModel_SCALE[" << i << "][1]    =  " <<  backGroundModel_SCALE[i][1]                               <<  ";\n";          
             outSettings << "backGroundModel_SCALE[" << i << "][2]    =  " <<  backGroundModel_SCALE[i][2]                               <<  ";\n";          
             outSettings << "//==========================================================================================  "             <<  "\n";         
             //=======================================================================================================================================
             outSettings << "collisionBoxArray[" << i << "][0]" << " =  " <<  collisionBoxArray[i][0]     <<  ";";  
             outSettings << "//__collisionBoxArray[i][0] is the left edge"                                                                          <<  "\n";              
             outSettings << "collisionBoxArray[" << i << "][1]" << " =  " <<  collisionBoxArray[i][1]     <<  ";";          
             outSettings << "//__collisionBoxArray[i][0] is the right edge"                                                                         <<  "\n";         
         
             outSettings << "collisionBoxArray[" << i << "][2]" << " =  " <<  collisionBoxArray[i][2]     <<  ";";  
             outSettings << "//__collisionBoxArray[i][0] is the botton edge"                                                                        <<  "\n";              
             outSettings << "collisionBoxArray[" << i << "][3]" << " =  " <<  collisionBoxArray[i][3]     <<  ";";          
             outSettings << "//__collisionBoxArray[i][0] is the top edge"                                                                           <<  "\n\n";
             
             outSettings << "collisionBoxArray[" << i << "][6]" << " =  " <<    collisionBoxArray[i][6]   <<  ";\n";                       
             outSettings << "collisionBoxArray[" << i << "][7]" << " =  " <<    collisionBoxArray[i][7]   <<  ";\n";                 
             outSettings << "collisionBoxArray[" << i << "][8]" << " =  " <<    collisionBoxArray[i][8]   <<  ";\n";                 
             outSettings << "collisionBoxArray[" << i << "][9]" << " =  " <<    collisionBoxArray[i][9]   <<  ";\n";                 
             outSettings << "collisionBoxArray[" << i << "][10]" << " =  " <<   collisionBoxArray[i][10]  <<  ";\n";                       
             outSettings << "collisionBoxArray[" << i << "][11]" << " =  " <<   collisionBoxArray[i][11]  <<  ";\n";                 
             outSettings << "collisionBoxArray[" << i << "][12]" << " =  " <<   collisionBoxArray[i][12]  <<  ";\n";                 
             outSettings << "collisionBoxArray[" << i << "][13]" << " =  " <<   collisionBoxArray[i][13]  <<  ";\n";               
             outSettings << "collisionBoxArray[" << i << "][14]" << " =  " <<   collisionBoxArray[i][14]  <<  ";\n";               
             outSettings << "collisionBoxArray[" << i << "][15]" << " =  " <<   collisionBoxArray[i][15]  <<  ";\n";                 
             outSettings << "collisionBoxArray[" << i << "][16]" << " =  " <<   collisionBoxArray[i][16]  <<  ";\n";                 
             outSettings << "collisionBoxArray[" << i << "][17]" << " =  " <<   collisionBoxArray[i][17]  <<  ";\n";               
             outSettings << "collisionBoxArray[" << i << "][18]" << " =  " <<   collisionBoxArray[i][18]  <<  ";\n";                
             outSettings << "collisionBoxArray[" << i << "][19]" << " =  " <<   collisionBoxArray[i][19]  <<  ";\n";             
             
             //=======================================================================================================================================         
             outSettings << "//boxCount                =  " <<  i                                                                   <<  ";\n";             
             outSettings << "boxCount++;"                                                                                                <<  "\n";           
         }    
             outSettings << "//==========================================================================================  "             <<  "\n"; 
             outSettings << "selectedModel           =  " <<  selectedModel                                                              <<  ";\n";          
             //-----------------------------------------------------------
             outSettings << "eyeposition[0]          =  " <<  eyeposition[0]                                                             <<  ";\n";           
             outSettings << "eyeposition[1]          =  " <<  eyeposition[1]                                                             <<  ";\n";          
             outSettings << "eyeposition[2]          =  " <<  eyeposition[2]                                                             <<  ";\n";             
             //-----------------------------------------------------------
             outSettings << "lookAt[0]               =  " <<  lookAt[0]                                                                  <<  ";\n";           
             outSettings << "lookAt[1]               =  " <<  lookAt[1]                                                                  <<  ";\n";          
             outSettings << "lookAt[2]               =  " <<  lookAt[2]                                                                  <<  ";\n";          
         
             outSettings << "NUMBER_OF_BACKGROUND_MODELS               =  " <<  NUMBER_OF_BACKGROUND_MODELS                                                                  <<  ";\n";          
         
         //=========================================================================================================================================   


    }
    //##############################################################################################################################################    


    //##############################################################################################################################################    
    
    //======================================__ADD_MODEL__=========================================   
    //#######################################################################################################
    //======================================__UPDATE_SET__========================================   
  
    
    //======================================__UPDATE_SET__========================================      
    //#######################################################################################################
    
    
    //####################################################################################################### 
    


    //====================================================================================================================================
    if (keys[VK_LEFT])
    {     
          
          if(collisionBoxArray[0][13] == 0.0)  
          {

                collisionBoxArray[0][0]  -= collisionBoxArray[0][6];

          }
         CollisionCheck_CHARACTER(collisionBoxArray[0][0]-collisionBoxArray[0][3]*0.5, collisionBoxArray[0][0]+collisionBoxArray[0][3]*0.5, collisionBoxArray[0][1]-collisionBoxArray[0][4]*0.5, collisionBoxArray[0][1]+collisionBoxArray[0][4]*0.5, collisionBoxArray[0][2]-collisionBoxArray[0][5]*0.5, collisionBoxArray[0][2]+collisionBoxArray[0][5]*0.5, collisionBoxArray[0][12]);
 
             
    }  
    //========================================================================================================================
    if (keys[VK_RIGHT])
    {
           
          if(collisionBoxArray[0][13] == 0.0)  
          {            

                collisionBoxArray[0][0]  += collisionBoxArray[0][6];
         
          } 
          CollisionCheck_CHARACTER(collisionBoxArray[0][0]-collisionBoxArray[0][3]*0.5, collisionBoxArray[0][0]+collisionBoxArray[0][3]*0.5, collisionBoxArray[0][1]-collisionBoxArray[0][4]*0.5, collisionBoxArray[0][1]+collisionBoxArray[0][4]*0.5, collisionBoxArray[0][2]-collisionBoxArray[0][5]*0.5, collisionBoxArray[0][2]+collisionBoxArray[0][5]*0.5, collisionBoxArray[0][12]);
 
          
                              
    }  
    //========================================================================================================================
    if (keys[VK_DOWN])
    {
          
          if(collisionBoxArray[0][13] == 0.0)  
          {

                collisionBoxArray[0][1]  -= collisionBoxArray[0][7];

          } 
          CollisionCheck_CHARACTER(collisionBoxArray[0][0]-collisionBoxArray[0][3]*0.5, collisionBoxArray[0][0]+collisionBoxArray[0][3]*0.5, collisionBoxArray[0][1]-collisionBoxArray[0][4]*0.5, collisionBoxArray[0][1]+collisionBoxArray[0][4]*0.5, collisionBoxArray[0][2]-collisionBoxArray[0][5]*0.5, collisionBoxArray[0][2]+collisionBoxArray[0][5]*0.5, collisionBoxArray[0][12]);
 
  
          
    }  
    //========================================================================================================================
    if (keys[VK_UP])
    {
          
          if(collisionBoxArray[0][13] == 0.0)  
          {

                collisionBoxArray[0][1]  += collisionBoxArray[0][7];

          }  
          CollisionCheck_CHARACTER(collisionBoxArray[0][0]-collisionBoxArray[0][3]*0.5, collisionBoxArray[0][0]+collisionBoxArray[0][3]*0.5, collisionBoxArray[0][1]-collisionBoxArray[0][4]*0.5, collisionBoxArray[0][1]+collisionBoxArray[0][4]*0.5, collisionBoxArray[0][2]-collisionBoxArray[0][5]*0.5, collisionBoxArray[0][2]+collisionBoxArray[0][5]*0.5, collisionBoxArray[0][12]);
 
                      
    }  
    //========================================================================================================================

//##########################################################################################################################   
    if (keys['D'] && !keys[VK_SHIFT])
    {
             eyeposition[0]         +=  0.15;
             lookAt[0]              +=  0.15;    
    }
    if (keys['A'] && !keys[VK_SHIFT])
    {
             eyeposition[0]         -=  0.15;
             lookAt[0]              -=  0.15;    
    }    
    if (keys['W'] && !keys[VK_SHIFT])
    {
             eyeposition[1]         +=  0.15;
             lookAt[1]              +=  0.15;     
    } 
    if (keys['S'] && !keys[VK_SHIFT])
    {
             eyeposition[1]         -=  0.15;
             lookAt[1]              -=  0.15;    
    }
    if (keys['E'] && !keys[VK_SHIFT])
    {
             eyeposition[2]         +=  0.15;
             lookAt[2]              +=  0.15;    
    }
    if (keys['Q'] && !keys[VK_SHIFT])  
    {
             eyeposition[2]         -=  0.15;
             lookAt[2]              -=  0.15;     
    }
//##########################################################################################################################

}//_END_ProcessKeyboard()
#endif




//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################



void CollisionCheck(float X1, float X2, float Y1, float Y2, float Z1, float Z2, GLfloat model_ID)           //////*****************************************
{   
     
    //==============================================================

     for(int i = (int)model_ID-1; i != -1; i--)
     {

          //---------------------------------------------------------------

          
          if((X2 >= collisionBoxArray[i][0]-collisionBoxArray[i][3]*0.5) && (collisionBoxArray[i][0]+collisionBoxArray[i][3]*0.5 >= X1) && (Y2 >= collisionBoxArray[i][1]-collisionBoxArray[i][4]*0.5) && (collisionBoxArray[i][1]+collisionBoxArray[i][4]*0.5 >= Y1)&& (Z2 >= collisionBoxArray[i][2]-collisionBoxArray[i][5]*0.5) && (collisionBoxArray[i][2]+collisionBoxArray[i][5]*0.5 >= Z1))
          {       
                    collisionBoxArray[(int)model_ID][13] = 1.0;//generic_collision   
                    collisionBoxArray[i][13]             = 1.0;//generic_collision 

                    //=============================================================================
                    collisionBoxArray[(int)model_ID][6] *= -1.0;//reverseVelocity_X_testingObject
                    if(i != 0)
                    collisionBoxArray[i][6]             *= -1.0;//reverseVelocity_X_testedObject
                    //------------------------------------------
                    collisionBoxArray[(int)model_ID][7] *= -1.0;//reverseVelocity_Y_testingObject
                    if(i != 0)
                    collisionBoxArray[i][7]             *= -1.0;//reverseVelocity_Y_testedObject
                    //------------------------------------------
                    collisionBoxArray[(int)model_ID][8] *= -1.0;//reverseVelocity_Y_testingObject
                    if(i != 0)
                    collisionBoxArray[i][8]             *= -1.0;//reverseVelocity_Y_testedObject                    
                    
                    //=============================================================================
                    if(collisionBoxArray[(int)model_ID][12] == i)
                    {
                        collisionBoxArray[(int)model_ID][13] = 0.0; //not neccessary with the loop being initialized with (model_ID-1)
                    }
                    //================================================================================================================================
                    float overX = ((collisionBoxArray[(int)model_ID][3] + collisionBoxArray[i][3]) / 2.0) - fabs(collisionBoxArray[(int)model_ID][0] - collisionBoxArray[i][0]);
                    float overY = ((collisionBoxArray[(int)model_ID][4] + collisionBoxArray[i][4]) / 2.0) - fabs(collisionBoxArray[(int)model_ID][1] - collisionBoxArray[i][1]);
                    float overZ = ((collisionBoxArray[(int)model_ID][5] + collisionBoxArray[i][5]) / 2.0) - fabs(collisionBoxArray[(int)model_ID][2] - collisionBoxArray[i][2]);
                                 
                                
                                if(collisionBoxArray[(int)model_ID][0] > collisionBoxArray[i][0])
                                    collisionBoxArray[(int)model_ID][0] += overX*0.1;
                                else
                                    collisionBoxArray[(int)model_ID][0] -= overX*0.1;
                            
                                if(collisionBoxArray[(int)model_ID][1] > collisionBoxArray[i][1])
                                    collisionBoxArray[(int)model_ID][1] += overY*0.1;
                                else
                                    collisionBoxArray[(int)model_ID][1] -= overY*0.1;
                    
                                if(collisionBoxArray[(int)model_ID][2] > collisionBoxArray[i][2])
                                    collisionBoxArray[(int)model_ID][2] += overZ*0.1;
                                else
                                    collisionBoxArray[(int)model_ID][2] -= overZ*0.1;                    
                    //================================================================================================================================
                    
                    break; 
                              
          }   
                  collisionBoxArray[(int)model_ID][13] = 0.0;//generic_collision 
                  //collisionBoxArray[i][13] = 0.0;//generic_collision   <- This prevents coloring from working on both objects/but prevents cube 0 from working
      }        
}
//###############################################################################################################################
void CollisionCheck_CHARACTER(float X1, float X2, float Y1, float Y2, float Z1, float Z2, GLfloat model_ID)        
{   
     
    //==============================================================

     for(int i = 1; i < boxCount; i++)
     {


          //---------------------------------------------------------------
          if((X2 >= collisionBoxArray[i][0]-collisionBoxArray[i][3]*0.5) && (collisionBoxArray[i][0]+collisionBoxArray[i][3]*0.5 >= X1) && (Y2 >= collisionBoxArray[i][1]-collisionBoxArray[i][4]*0.5) && (collisionBoxArray[i][1]+collisionBoxArray[i][4]*0.5 >= Y1))
          {       

                    collisionBoxArray[0][13] = 1.0;//generic_collision 
                    
                    //================================================================================================================================
                    float overX = ((collisionBoxArray[0][3] + collisionBoxArray[i][3]) / 2.0) - fabs(collisionBoxArray[0][0] - collisionBoxArray[i][0]);
                    float overY = ((collisionBoxArray[0][4] + collisionBoxArray[i][4]) / 2.0) - fabs(collisionBoxArray[0][1] - collisionBoxArray[i][1]);
                            
                                
                                
                                if(collisionBoxArray[0][0] > collisionBoxArray[i][0])
                                    collisionBoxArray[0][0] += overX*0.1;
                                else
                                    collisionBoxArray[0][0] -= overX*0.1;
                            
                                if(collisionBoxArray[0][1] > collisionBoxArray[i][1])
                                    collisionBoxArray[0][1] += overY*0.1;
                                else
                                    collisionBoxArray[0][1] -= overY*0.1;
                    //================================================================================================================================                                             
                    
                    break; 
                              
          }   
          collisionBoxArray[0][13] = 0.0;//generic_collision
      }        
}

//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################


void shutDownGL( void )
{
     //#####################################___SHADERS___######################################################      
     #include "_SHADERS/basic/collisionColors/collisionColors_SHUTDOWN.cpp"
     //====================================================================================     
     //#####################################___MODELS___#######################################################      
     #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Shutdown.cpp"                                                               
     //====================================================================================  
  
   
}



