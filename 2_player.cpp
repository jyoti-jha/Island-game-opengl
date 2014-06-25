#include<stdio.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "imageloader.h"
typedef struct Tile{
	int missing;
	int moving;
	int robo;
	float x_cor;
	float y_cor;
	float z_cor;
	float curr_y;
	int spring;
	int fire;
}Tile;
Tile tile[8][8];
typedef struct Robot{
	float x_cor;
	float y_cor;
	float z_cor;
}Robot;
Robot robot;
typedef struct Ball{
	float x;
	float y;
	float z;
	float deltay;
	float y_fac;
}Ball;
Ball ball[8];
int spring_counter=0,enter=0,robot_score=0,enemy_score=0;
int keep=0,win=0;
int set_flag=-1,tile_view=0,cursorx,cursory,x_new,y_new,look=0;
int v2=rand()%7;
int sound=0,spot_counter=0;
int t=0,y1_rate=0,jp;
int x=1.5,y=0,munni=0;
int counter=0;
using namespace std;
float _angle = 0,dv1=0.5,deltax=0.0,deltaz=0.0;
float y_rate=0.0,red=0.0,blue=0.0,green=0.0;
int k=0,row=0,pappu=1;
int enemy_up_flag=0,enemy_down_flag=0,enemy_right_flag=0,enemy_left_flag=0,left_flag=0,right_flag=0,up_flag=0,down_flag=0;
float cx=0.2,ex=0.5;      //tt[cp.t_r][cp.t_c].llx+5;
float cz=-0.1,ez=-0.1; //tt[cp.t_r][cp.t_c].llz+5;
float cy=0.9,ey=0.9;      //tt[cp.t_r][cp.t_c].h;
float fac=0.0,dv=0.1,enemy_fac=0.0;
int fl=0,jump=0;
int dir=0,fall_counter=0,spot=0;
float co=0;	
int fire_no=rand()%64,fire_flag=0;
int block_count=0;
float yy=0.0,vely=0.0;
int ran=0;
int factor=0,tower=0,first=0,tower_view=0,first_person_view=0,projectile_front=0,ck_flag=0,third=0;
int cl=0,cv=0,level=1;
float fx,fy,fz;
/*float v4=rand()%10;// missing
float fx=cx+(v4/20),fy=4+(v4/20),fz=cz-(v4/20);*/
GLuint _textureId[6]; //The id of the texture
GLuint textureId[6];
void drawBitmapText(char *string,float x,float y,float z) 
{  
	char *c;
	glRasterPos3f(x, y,z);
	for (c=string; *c != '\0'; c++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}
void drawScene();
void drawenemy_robot(float ex,float ey,float ez);
//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture1(Image* image) {
	glGenTextures(1, &textureId[0]); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId[0]); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId[0]; //Returns the id of the texture
}
GLuint loadTexture2(Image* image) {
	glGenTextures(1, &textureId[1]); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId[1]); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId[1]; //Returns the id of the texture
}
GLuint loadTexture3(Image* image) {
	glGenTextures(1, &textureId[2]); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId[2]); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId[2]; //Returns the id of the texture
}
GLuint loadTexture4(Image* image) {
	glGenTextures(1, &textureId[3]); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId[3]); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId[3]; //Returns the id of the texture
}
GLuint loadTexture5(Image* image) {
	glGenTextures(1, &textureId[4]); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId[4]); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId[4]; //Returns the id of the texture
}
GLuint loadTexture6(Image* image) {
	glGenTextures(1, &textureId[5]); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId[5]); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId[5]; //Returns the id of the texture
}

void initialise_tile_array()
{
	for(int i=0;i<=7;i++)
	{
		for(int j=0;j<=7;j++)
		{
			block_count++;
			tile[i][j].fire=0;
			tile[i][j].missing=0;
			tile[i][j].moving=0;
			tile[i][j].spring=0;
			tile[i][j].x_cor=j*1.5;
			tile[i][j].z_cor=(-1.0)*(1.5)*i;
			tile[1][1].moving=1;
			tile[5][2].moving=1;
			tile[6][3].moving=1;
			tile[0][1].spring=1;
			tile[2][0].fire=1;
			tile[3][2].fire=1;
			tile[4][5].fire=1;
			tile[i][j].robo=0;
//			tile[i][j].enemy=0;
		}
	}
	
}
void initialise_ball_array()
{
	float v4=rand()%10;// missing
		fx=cx+(v4/20);
		fy=4+(v4/20);
		fz=cz-(v4/20);


	for(int i=0;i<8;i++)
	{
			
		if(i==1)
		{

			ball[i].x=fx+1.5;
			ball[i].z=fz-0.5;
		}
		if(i==2)
		{
			ball[i].x=fx+2.5;
			ball[i].z=fz-7.0;
//			ball[i].y=
		}
		if(i==3)
		{	
			ball[i].x=fx+6.8;
			ball[i].z=fz-2.0;
		}
		if(i==4)
		{	
			ball[i].x=fx+3.8;
			ball[i].z=fz-8.8;
		}
		if(i==5)
		{
			ball[i].x=fx+4.5;
			ball[i].z=fz-6.0;

		}
		if(i==6)
		{
			ball[i].x=fx+3.2;
			ball[i].z=fz-1.9;

		}
		if(i==7)
		{
			ball[i].x=fx+7.5;
			ball[i].z=fz-5.5;
		}
		if(i==0)
		{
			ball[i].x=fx;
			ball[i].z=fz;

		}
		ball[i].y=fy;
		ball[i].deltay=0.0;
		ball[i].y_fac=-0.05;
	}
}
void position_of_robot(float xxx,float yyy,float zzz)
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{	
			if(xxx>=tile[i][j].x_cor && xxx<=tile[i][j].x_cor+1.5)
			{
				if(zzz>=tile[i][j].z_cor-1.5 && zzz<=tile[i][j].z_cor)
				{
						tile[i][j].robo=1;
				}
			}
		}
	}

}
void sonaa(int value)
{
	cy = 1;
	cz = cz -2.0;
}
void sona1(int value)
{
		cz=cz-0.75;
		cy=1.5;
		glutTimerFunc(400,sonaa,0);
}
void sonac(int value)
{
	cz=cz+1.5;
	cy=1.0;
}
void sona3(int value)
{
		cz=cz+0.75;
		cy=1.5;
		glutTimerFunc(400,sonac,0);
}
void sonab(int value)
{
	cx=cx-1.5;
	cy=1.0;
}
void sona2(int value)
{
	cx=cx-0.75;
	cy=1.5;
	glutTimerFunc(400,sonab,0);
}
void sonad(int value)
{
	cx=cx+1.5;
	cy=1.0;
}
void sona4(int value)
{
	cx=cx+0.75;
	cy=1.5;
	glutTimerFunc(400,sonad,0);
}
void new_func()
{
	drawScene();
}
void stop_func(int value)
{
	set_flag=1;
	drawScene();
}
void e_sonaa(int value)
{
	ey = 1;
	ez = ez -2.0;
}
void e_sona1(int value)
{
		ez=ez-0.75;
		ey=1.5;
		glutTimerFunc(400,e_sonaa,0);
}
void e_sonac(int value)
{
	ez=ez+1.5;
	ey=1.0;
}
void e_sona3(int value)
{
		ez=ez+0.75;
		ey=1.5;
		glutTimerFunc(400,e_sonac,0);
}
void e_sonab(int value)
{
	ex=ex-1.5;
	ey=1.0;
}
void e_sona2(int value)
{
	ex=ex-0.75;
	ey=1.5;
	glutTimerFunc(400,e_sonab,0);
}
void e_sonad(int value)
{
	ex=ex+1.5;
	ey=1.0;
}
void e_sona4(int value)
{
	ex=ex+0.75;
	ey=1.5;
	glutTimerFunc(400,e_sonad,0);
}
void handleKeypress(unsigned char key,int x,int y)
{	
	if (key == 'h')
		{
			if(level==2)
			{
				enter=enter+1;
			}
			enemy_left_flag=1;
			enemy_right_flag=0;
			enemy_down_flag=0;
			enemy_up_flag=0;
			dir=(dir+1)%4;
			enemy_fac=enemy_fac+0.1;
			ex=ex-enemy_fac;
			drawenemy_robot(ex,ey,ez);
		}
		if (key == 'k')
		{	if(level==2)
			{
				enter=enter+1;
			}

			enemy_right_flag=1;
			enemy_left_flag=0;
			enemy_up_flag=0;
			enemy_down_flag=0;
			dir=(dir+1)%4;
			enemy_fac=enemy_fac+0.1;
			ex=ex+enemy_fac;
			drawenemy_robot(ex,ey,ez);
		}
			
		if (key == 'j')
		{	if(level==2)
			{
				enter=enter+1;
			}

			enemy_down_flag=1;
			enemy_up_flag=0;
			enemy_left_flag=0;
			enemy_right_flag=0;
			enemy_fac=enemy_fac+0.1;
			ez=ez+enemy_fac;
			drawenemy_robot(ex,ey,ez);
		}

	if(key==27)

	{
		sound=1;
		//system("killall 9 aplay");
//		system("aplay Lost.wav &");
		exit(0);

	}
	if(key=='t')
	{
		tower=(tower+1)%2;
		set_flag=0;
		first=0;
		tile_view=0;
		look=0;
		third=0;
	}
	if(key=='f')
	{
		first=(first+1)%2;
		set_flag=0;
		tower=0;
		tile_view=0;
		third=0;
		look=0;
	}
	if(key==56)  // forward jump
	{
		//printf("lalalalal\n");
		glutTimerFunc(400,sona1,0);
	}
	if(key==52)  // right jump
	{
		glutTimerFunc(400,sona2,0);
	}	
	if(key==53) // backward jump 
	{
		glutTimerFunc(400,sona3,0);
	}
	if(key==54)  // left jump 
	{
		glutTimerFunc(400,sona4,0);
	}	
	if(key=='d')
	{
		glutTimerFunc(400,e_sona1,0);
	}
	if(key=='z')
	{
		glutTimerFunc(400,e_sona2,0);
	}	
	if(key=='x')
	{
		glutTimerFunc(400,e_sona3,0);
	}
	if(key=='c')
	{
		glutTimerFunc(400,e_sona4,0);
	}

	if(key=='v')
	{
		third=(third+1)%2;
		set_flag=0;
		first=0;
		tower=0;
		tile_view=0;
		look=0;
	}
	if(key=='g')
	{
		tile_view=(tile_view+1)%2;
		first=0;
		tower=0;
		third=0;
		look=0;
	}
	if(key=='s')
	{
		set_flag=0;
	}
	if(key=='l')
	{
		level=level+1;
		if(level==2)
		{
			set_flag=0;
		}
		if(level==3)
		{
			set_flag=4;
			//printf("in level 4\n");
			 cx=0.2;     //tt[cp.t_r][cp.t_c].llx+5;
			 cz=-0.1; //tt[cp.t_r][cp.t_c].llz+5;
			 cy=0.9; 
			 t=0;
			//enter=0;
			//cx=
		}
		drawScene();
	}
	if(key=='u')
	{	
			enemy_up_flag=1;
			enemy_left_flag=0;
			enemy_right_flag=0;
			enemy_down_flag=0;
			if(first==1){
			co=co+0.5;
			drawScene();}
			enemy_fac=enemy_fac+0.1;
			ez=ez-enemy_fac;
			drawenemy_robot(ex,ey,ez);
	}
	if(key=='o')
	{
		spot=(spot+1)%2;
	}


}
void draw_BlackArea()
{	
	glBegin(GL_QUADS);
        // front
	glColor3f(0.0f,0.5f,0.0f); //red
	glTranslatef(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(1.50f,0.0f,0.0f);
	glVertex3f(1.5f,0.3f+yy,0.0f);
	glVertex3f(0.0f,0.3f+yy,0.0f);
	glEnd();
	glBegin(GL_QUADS);
	// left face
	glColor3f(0.0f,0.5f,0.0f); //yellow
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,-1.5f);
	glVertex3f(0.0f,0.3f+yy,-1.5f);
	glVertex3f(0.0f,0.3f+yy,0.0f);
	glEnd();
	glBegin(GL_QUADS);
	// right
	glColor3f(0.0f,0.5f,0.0f); //green
	glVertex3f(1.5f,0.0f,0.0f);
	glVertex3f(1.5f,0.0f,-1.5f);
	glVertex3f(1.5f,0.3f+yy,-1.5f);
	glVertex3f(1.5f,0.3f+yy,0.0f);
	glEnd();
	glBegin(GL_QUADS);
        // back face
	glVertex3f(0.0f,0.0f,-1.5f);
	glVertex3f(1.50f,0.0f,-1.5f);
	glVertex3f(1.5f,0.3f+yy,-1.5f);
	glVertex3f(0.0f,0.3f+yy,-1.5f);
	glEnd();
/*
	glBegin(GL_QUADS);
//	glColor3f(0.05f,0.05f,0.05f);
	glColor3f(0.0f,0.0f,1.0f); //blue
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(1.50f,0.0f,0.0f);
	glVertex3f(1.5f,0.0f,-1.5f);
	glVertex3f(0.0f,0.0f,-1.5f);
	glEnd();*/
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId[0]);
	// isse upar waale black squares ban rhe hain
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f,0.3f+yy,0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.50f,0.3f+yy,0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5f,0.3f+yy,-1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f,0.3f+yy,-1.5f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void draw_whiteArea()
{	
	if(fire_flag==1)
	{
		glColor3f(1.0f,1.0f,0.0f);
	}
	else if(fire_flag==0)
	{
		glColor3f(1.0f,1.0f,1.0f);
	}
	else if(fire_flag==2)	
	{
		glColor3f(1.0f,0.0f,0.0f);
	}
	
	//green
	glBegin(GL_QUADS);
	glTranslatef(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(1.50f,0.0f,0.0f);
	glVertex3f(1.5f,0.3f,0.0f);
	glVertex3f(0.0f,0.3f,0.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,-1.5f);
	glVertex3f(0.0f,0.3f,0.0f);
	glVertex3f(0.0f,0.3f,-1.5f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(1.5f,0.0f,0.0f);
	glVertex3f(1.5f,0.0f,-1.5f);
	glVertex3f(1.5f,0.3f,-1.5f);
	glVertex3f(1.5f,0.3f,0.0f);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(0.0f,0.0f,-1.5f);
	glVertex3f(1.50f,0.0f,-1.5f);
	glVertex3f(1.5f,0.3f,-1.5f);
	glVertex3f(0.0f,0.3f,-1.5f);
	glEnd();
/*
	glBegin(GL_QUADS);
	glColor3f(0.05f,0.05f,0.05f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(1.50f,0.0f,0.0f);
	glVertex3f(1.5f,0.0f,-1.5f);
	glVertex3f(0.0f,0.0f,-1.5f);
	glEnd();*/
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId[0]);
	// isse upar waale white squares ban rhe hain
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f,0.3f,0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.50f,0.3f,0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.5f,0.3f,-1.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.0f,0.3f,-1.5f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void initRendering(){

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
//	glEnable(GL_LIGHTING);
//	glDisable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	Image* image1 = loadBMP("pink.bmp");
	_textureId[0] = loadTexture1(image1);
	delete image1;
	Image* image2 = loadBMP("images.bmp");
	_textureId[1] = loadTexture2(image2);
	delete image2;	
	Image* image3 = loadBMP("congo.bmp");
	_textureId[2] = loadTexture3(image3);
	delete image3;	
	Image* image4 = loadBMP("mario.bmp");
	_textureId[3] = loadTexture4(image4);
	delete image4;
	Image* image5 = loadBMP("image.bmp");
	_textureId[4] = loadTexture5(image5);
	delete image5;
	Image* image6 = loadBMP("YIPPEE_.bmp");
	_textureId[5] = loadTexture6(image6);
	delete image6;



	glClearColor(1.0, 1.0, 1.0, 0.0);
//	glClearColor(0.05f,0.1f,0.1f,1.0f);
//	glClearColor(0.50, 0.6, 0.7, 0.5);
//	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	//Set up a display list for drawing a cube
/*	_displayListId_blackArea = glGenLists(1); //Make room for the display list
	glNewList(_displayListId_blackArea, GL_COMPILE); //Begin the display list
	draw_BlackArea(); //Add commands for drawing a black area to the display list
	glEndList(); //End the display list
	//Set up a display list for drawing a cube
	_displayListId_whiteArea = glGenLists(2); //Make room for the display list
	glNewList(_displayListId_whiteArea, GL_COMPILE); //Begin the display list
	draw_whiteArea(); //Add commands for drawing a black to the display list
	glEndList();*/ //End the display list
}
int check_falls(float xxx,float yyy,float zzz)
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{	
			if(xxx>=tile[i][j].x_cor && xxx<=tile[i][j].x_cor+1.5)
			{
				if(zzz>=tile[i][j].z_cor-1.5 && zzz<=tile[i][j].z_cor)
					if(tile[i][j].missing==1){
					return 1;}
					else{
					return 0;
					}
			}
		}
	}

	return 0;
}	

void falling_robot(int value)
{
		y_rate=y_rate-1.5;
		if(y_rate==-4.5)
	{
		set_flag=1;

	}
		fall_counter=fall_counter+1;
		cy=cy+y_rate;
		//draw face
		glColor3f(0.8f,0.0f,0.6f);
		glPushMatrix();
		glTranslatef(cx,cy+0.2,cz);
		glutSolidSphere(0.1,20,20); //0.1
		glPopMatrix();
		//drawing cuboidal torso
		glColor3f(0.0f,0.5f,0.5f);
		glPushMatrix();
		glTranslatef(cx,cy,cz);
		glutSolidCube(0.2);    //0.2
		glPopMatrix();
		// draw right leg 
		glColor3f(1.0f,1.0f,0.0f);
		glPushMatrix();
		glTranslatef(cx-0.05,cy-0.01,cz);
		GLUquadricObj* quadratic;
		quadratic = gluNewQuadric();
		glRotatef(90,1.0f,0.0f,0.0f);
		glPushMatrix();
		gluCylinder(quadratic,0.02,0.02,0.6,32,32);
		glPopMatrix();
		glPopMatrix();
		//draw left leg
		glColor3f(1.0f,0.5f,0.0f);
		glPushMatrix();
		glTranslatef(cx+0.05,cy-0.01,cz);
		glPushMatrix();
		glRotatef(90,1.0f,0.0f,0.0f);
		gluCylinder(quadratic,0.02,0.02,0.6,32,32);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		glutTimerFunc(500,falling_robot,0);
}
void falling_enemy(int value)
{
		y_rate=y_rate-1.5;
		if(y_rate==-4.5)
	{
		set_flag=1;

	}
		fall_counter=fall_counter+1;
		ey=ey+y_rate;
		//draw face
		glColor3f(0.8f,0.0f,0.6f);
		glPushMatrix();
		glTranslatef(ex,ey+0.2,ez);
		glutSolidSphere(0.1,20,20); //0.1
		glPopMatrix();
		//drawing cuboidal torso
		glColor3f(0.0f,0.5f,0.5f);
		glPushMatrix();
		glTranslatef(ex,ey,ez);
		glutSolidCube(0.2);    //0.2
		glPopMatrix();
		// draw right leg 
		glColor3f(1.0f,1.0f,0.0f);
		glPushMatrix();
		glTranslatef(ex-0.05,ey-0.01,ez);
		GLUquadricObj* quadratic;
		quadratic = gluNewQuadric();
		glRotatef(90,1.0f,0.0f,0.0f);
		glPushMatrix();
		gluCylinder(quadratic,0.02,0.02,0.6,32,32);
		glPopMatrix();
		glPopMatrix();
		//draw left leg
		glColor3f(1.0f,0.5f,0.0f);
		glPushMatrix();
		glTranslatef(ex+0.05,ey-0.01,ez);
		glPushMatrix();
		glRotatef(90,1.0f,0.0f,0.0f);
		gluCylinder(quadratic,0.02,0.02,0.6,32,32);
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();
		glutTimerFunc(500,falling_enemy,0);
}

void check_collision(float xxx,float yyy,float zzz)
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{	
			if(xxx>=tile[i][j].x_cor && xxx<=tile[i][j].x_cor+1.5)
			{
				if(zzz>=tile[i][j].z_cor-1.5 && zzz<=tile[i][j].z_cor)
					if(tile[i][j].moving==1){
						set_flag=1;
					if(tile[i][j].curr_y<=yyy){
				//	printf("cy=%f tile[%d][%d].curr_y=%f yyy=%f\n",cy,i,j,tile[i][j].curr_y,yyy);
				//	cy=tile[i][j].curr_y+0.5;
				//		set_flag=1;
					
					}
				//	else{
				//		set_flag=1;
				//	}
					}
					else{
					}
			}
		}
	}

}
void check_winning_positiion(float xxx,float yyy,float zzz)
{	
	if(xxx>=tile[7][7].x_cor && xxx<=tile[7][7].x_cor+1.5)
			{
				if(zzz>=tile[7][7].z_cor-1.5 && zzz<=tile[7][7].z_cor)
				{
					if(level==1)
					{
						set_flag=2;
					}
					else if(level==2)
					{
						//check_who_wins();
						if(xxx==cx && yyy== cy && zzz==cz && win==0)
						{
							win=1;
						//	printf("A wins\n");
							set_flag=3;
						//	return;
						}
						else if( xxx==ex && yyy== ey && zzz==ez && win==0)
						{
							win=2;	
						//	printf("B wins\n");
							set_flag=3;
							//return;

						}
						
						//set_flag=3;
					}
				}
				
			}
	if(win==1)
	{
		//printf("A wins\n");
	}
	else if(win==2)
	{
		//printf("B wins\n");
	}
}

int check_fire(float xxx,float yyy,float zzz)
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{	
			if(xxx>=tile[i][j].x_cor && xxx<=tile[i][j].x_cor+1.5)
			{
				if(zzz>=tile[i][j].z_cor-1.5 && zzz<=tile[i][j].z_cor)
				{
					if(tile[i][j].fire==1)
					{
						return 1;
					}
					else
					{
						return 0;
					}
				}
			}
		}
	}
	return 0;

}
void check_boundary(float xxx,float yyy,float zzz)
{
	if( xxx<0.2||xxx>12.2)
	{
		set_flag=1;
	}
	if(zzz>0.2||zzz<-12.0)
	{
		set_flag=1;
	}
}
void new_scene(int px,int py)
{                              
				
				glColor3f(0.0f,1.0f,1.0f);

				//green
				glBegin(GL_QUADS);
				glTranslatef(0.0f,0.0f,0.0f);
				glVertex3f(0.0f,0.0f,0.0f);
				glVertex3f(1.50f,0.0f,0.0f);
				glVertex3f(1.5f,0.3f,0.0f);
				glVertex3f(0.0f,0.3f,0.0f);
				glEnd();
				glBegin(GL_QUADS);
				glVertex3f(0.0f,0.0f,0.0f);
				glVertex3f(0.0f,0.0f,-1.5f);
				glVertex3f(0.0f,0.3f,0.0f);
				glVertex3f(0.0f,0.3f,-1.5f);
				glEnd();
				glBegin(GL_QUADS);
				glVertex3f(1.5f,0.0f,0.0f);
				glVertex3f(1.5f,0.0f,-1.5f);
				glVertex3f(1.5f,0.3f,-1.5f);
				glVertex3f(1.5f,0.3f,0.0f);
				glEnd();
				glBegin(GL_QUADS);
				glVertex3f(0.0f,0.0f,-1.5f);
				glVertex3f(1.50f,0.0f,-1.5f);
				glVertex3f(1.5f,0.3f,-1.5f);
				glVertex3f(0.0f,0.3f,-1.5f);
				glEnd();
				/*
				   glBegin(GL_QUADS);
				   glColor3f(0.05f,0.05f,0.05f);
				   glVertex3f(0.0f,0.0f,0.0f);
				   glVertex3f(1.50f,0.0f,0.0f);
				   glVertex3f(1.5f,0.0f,-1.5f);
				   glVertex3f(0.0f,0.0f,-1.5f);
				   glEnd();*/
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, _textureId[0]);
				// isse upar waale white squares ban rhe hain
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(0.0f,0.3f,0.0f);
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(1.50f,0.3f,0.0f);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(1.5f,0.3f,-1.5f);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(0.0f,0.3f,-1.5f);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			
			//	glCallList(_displayListId_whiteArea);
			//glPopMatrix();
			

}
void check_spot_light()
{
	cv=0;
	for(float j=0.0;j>(-8*1.5);j-=1.5)
	{
		cl=0;
		for(float i=0.0;i<=(7*1.5);i+=1.5)
		{	
			if(cx>=tile[cv][cl].x_cor && cx<=tile[cv][cl].x_cor+1.5)
			{
				if(cz>=tile[cv][cl].z_cor-1.5 && cz<=tile[cv][cl].z_cor)
				{
					glPushMatrix();
					glTranslatef(i,0.0,j);
					fire_flag=2;
					draw_whiteArea();
					glPopMatrix();
				}

			}
			cl++;
		}
		cv++;
	}
}
void initialise_tile_with_robo(float xxx,float yyy,float zzz)
{	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{	
			tile[i][j].robo=0;
		
		}
	}
}
void make_spring_jump()
{
	/*if((spring_counter%2)==0)
	{
		cy=1.5;
	}	
	if((spring_counter%2)!=0)
	{
		cy=1.0;
	}*/

}

void check_spring(float cx,float cy,float cz)
{	
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{	
			if(tile[i][j].spring==1)
			{
				if(cx>=tile[i][j].x_cor && cx<=tile[i][j].x_cor+1.5)

				{
					if(cz>=tile[i][j].z_cor-1.5 && cz<=tile[i][j].z_cor)
					{
						make_spring_jump();
					//	if(tile[i][j].fire==1)
					//	{
							//set_flag=1;
					//		return 1;
					//	}
					//	else
					//	{
					//		return 0;
					//	}
					}
				}

			}

		}
	}
}
int check_collision_with_other()
{
	if(level > 1)
	{
		if(fabs(cx-ex)<=0.2)
		{
			if(fabs(cy-ey)<=0.2)
			{
				if(fabs(cz-ez)<=0.2)
				{

					return 1;
				}
			}
		}
	}
	return 0;
}
void check_collision_with_ball(float xxx,float yyy,float zzz)
{
/*	if(xxx>=fx-0.3 && xxx <=fx+0.3)
		{
		//	printf("cx=%f fx-0.3=%f fx+0.3=%f ",cx,f_x-0.3,f_x+0.3);
			//		printf("yy\n");
			if(zzz>=fz-0.3 && zzz<=fz+0.3)
			{
		//		printf("cz=%f fz-0.3=%f fz+0.3=%f ",cz,f_z-0.3,f_z+0.3);
				//			printf("in z\n");
				if((cy+0.2)>=fy-0.3 )
				{
		//			printf("here\n");
		//			printf("cy+0.2=%f f_y=%f\n",cy+0.2,f_y);
				//	printf("cy+0.2=%f fy-0.3=%f ",cy+0.2,f_y-0.3);
					//check_flag=1;
					//				printf("in y\n");
					set_flag=1;
				}
			}

		}*/


	for(int i=0;i<1;i++)
	{
		int check_flag=0;
		float f_x=ball[i].x;
		float f_y=ball[i].y;
		float f_z=ball[i].z;
		if((cy+0.2)>=f_y-0.3 )

				{
					printf("here ");
				//	printf("cy+0.2=%f f_y=%f\n",cy+0.2,f_y);
					printf("cy+0.2=%f fy-0.3=%f\n",cy+0.2,f_y-0.3);
				//	check_flag=1;
					//				printf("in y\n");
				//	set_flag=1;
				}

		if(xxx>=f_x-0.3 && xxx <=f_x+0.3)
		{
		//	printf("cx=%f fx-0.3=%f fx+0.3=%f ",cx,f_x-0.3,f_x+0.3);
			//		printf("yy\n");
			if(zzz>=f_z-0.3 && zzz<=f_z+0.3)
			{
		//		printf("cz=%f fz-0.3=%f fz+0.3=%f ",cz,f_z-0.3,f_z+0.3);
				//			printf("in z\n");
				if((cy+0.2)>=f_y-0.3 )
				{
		//			printf("here\n");
		//			printf("cy+0.2=%f f_y=%f\n",cy+0.2,f_y);
				//	printf("cy+0.2=%f fy-0.3=%f ",cy+0.2,f_y-0.3);
					check_flag=1;
					//				printf("in y\n");
					set_flag=1;
				}
			}

		}
//		printf("cy+0.2=%f fy-0.3=%f  ",cy+0.2,fy-0.3);
		if(check_flag==0)
		{	
		//	printf("not coliding\n");
		}
		else
		{
		//	printf("colliding\n");
		}
	}
}



void drawenemy_robot(float ex,float ey,float ez)
{

	int collision_with_other=check_collision_with_other();
	if(collision_with_other==1)
	{
		set_flag=1;
	}

	check_boundary(ex,ey,ez);
	position_of_robot(ex,ey,ez);
	check_spring(ex,ey,ez);
//	check_spot_light();
	int ret=check_fire(ex,ey,ez);
	int jump_counter=0;
	yy=0;
	jp=check_falls(ex,ey,ez);
	check_collision(ex,ey,ez);
	check_winning_positiion(ex,ey,ez);
	if(jp==0)
	{
		if(jump==1)
		{
		
		//	cy=1.5;
		//	cy=0;
		}
		     if(ret==1)
		     {
			     glColor3f(0.0f,0.0f,0.0f);
		     }
		     else
		     {
		     	glColor3f(0.5f,0.9f,0.6f);
		     }
		     glPushMatrix();
		     glTranslatef(ex,ey+0.2,ez);
		     glutSolidSphere(0.1,20,20); //0.1
		     glPopMatrix();
			     //drawing cuboidal torso
		     if(ret==1)
		     {
		     	glColor3f(0.0f,0.0f,0.0f);
		     }
		     else
		     {
		     	glColor3f(1.0f,0.5f,0.5f);
		     }
//		     glPushMatrix();
		 
		 
//		     glPopMatrix();
			     glPushMatrix();
			    glTranslatef(ex,ey,ez);
		     glutSolidCube(0.2);    //0.2
//			     glTranslatef(0.75,0.6,0.0);
//			     gluCylinder(quad,0.4,0.4,0.6,100,100);
			     glPopMatrix();
		     if(ret==1)
		     {
		     	glColor3f(0.0f,0.0f,0.0f);
		     }
		     else{
	             glColor3f(1.0f,1.0f,0.5f);}
		     glPushMatrix();
		     glTranslatef(ex-0.05,ey-0.01,ez);
		     GLUquadricObj* quadratic;
		     quadratic = gluNewQuadric();
//		     if(left_flag==0 && right_flag==0 && up_flag==0 && down_flag==0)
		     if(enemy_fac<=0)
		     {
		    		glPushMatrix();
		     		//glRotatef(-90,0.0f,1.0f,0.0f);
		     		glRotatef(90,1.0f,0.0f,0.0f);
		     		gluCylinder(quadratic,0.02,0.02,0.6,32,32);
				glPopMatrix();
		     glPopMatrix();
		     if(ret==1)
		     {
		     	glColor3f(0.0f,0.0f,0.0f);
		     }
		     else{
	             glColor3f(1.0f,1.0f,0.1f);}
		     glPushMatrix();
		     glTranslatef(ex+0.05,ey-0.01,ez);
		     glPushMatrix();
		     glRotatef(90,1.0f,0.0f,0.0f);
		     	gluCylinder(quadratic,0.02,0.02,0.6,32,32);
		     	glPopMatrix();
			glPopMatrix();
			glPopMatrix();
		   return;	
		    
		     }
		     if(t%2==0)
		     {
			glRotatef(9,1.0f,0.0f,0.0f);
			
		     	glRotatef(90,1.0f,0.0f,0.0f);
		    	glPushMatrix();
		     	gluCylinder(quadratic,0.02,0.02,0.6,32,32);
			glPopMatrix();

		     	glPopMatrix();
		     }
		     else
		     {
		     	//	glRotatef(-90,0.0f,0.0f,1.0f);
		    		glPushMatrix();
		     		//glRotatef(-90,0.0f,1.0f,0.0f);
		     		glRotatef(90,1.0f,0.0f,0.0f);
		     		gluCylinder(quadratic,0.02,0.02,0.6,32,32);
				glPopMatrix();
		     glPopMatrix();
		     }
		     if(ret==1)
		     {
		     	glColor3f(0.0f,0.0f,0.0f);
		     }
                     else
		     {
	             	glColor3f(0.5f,0.5f,0.5f);
		     }
		     glPushMatrix();
		    
		     glTranslatef(ex+0.05,ey-0.01,ez);
//		     glRotatef(-90,1.0f,0.0f,0.0f);
		     if(t%2!=0)
		     {
		     	glRotatef(9,1.0f,0.0f,0.0f);
			glRotatef(90,1.0f,0.0f,0.0f);
			glPushMatrix();
		     	gluCylinder(quadratic,0.02,0.02,0.6,32,32);
		     	glPopMatrix();

		        glPopMatrix();
		     }
		     
		     else
		     {
			glPushMatrix();
			glRotatef(90,1.0f,0.0f,0.0f);
		     	gluCylinder(quadratic,0.02,0.02,0.6,32,32);
		     	glPopMatrix();

		     glPopMatrix;
		    
		     }
		     glPopMatrix();
	}
	
	if(ret==1)
	{

		glColor3f(1.0f,1.0f,1.0f);
		glutTimerFunc(500,stop_func,0);
	}
	if(jp==1)
	{

		glutTimerFunc(25,falling_enemy,0);
	}

}

void drawrobot(float cx,float cy,float cz)
{	
	if(spot==0) //&& level==2 )
		{
			//	printf("in enablin\n");
				if(level==1){
				glDisable(GL_LIGHTING);}
				if(level==2){
				glEnable(GL_LIGHTING);}
				glEnable(GL_LIGHT0);


			GLfloat ambientColor[] = {red, green, blue, 1.0f}; //Color(0.2, 0.2, 0.2)
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
		}
		if(spot==1 && level==1)
		{
			glEnable(GL_LIGHTING);
			glDisable(GL_LIGHT0);

//			GLfloat light6_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
			GLfloat light6_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
			GLfloat light6_specular[] = { 1.0, 1.0, 1.0, 1.0 };
			GLfloat light6_position[] = { cx, cy+2.0, cz, 1.0 };
			GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };

//			glLightfv(GL_LIGHT6, GL_AMBIENT, light6_ambient);
			glLightfv(GL_LIGHT6, GL_DIFFUSE, light6_diffuse);
			glLightfv(GL_LIGHT6, GL_SPECULAR, light6_specular);
			glLightfv(GL_LIGHT6, GL_POSITION, light6_position);
			glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, 1.5);
			glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, 0.5);
			glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, 0.2);

			glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 10.0);
			glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spot_direction);
			glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 2.0);

			glEnable(GL_LIGHT6);
		//	glDisable(GL_LIGHTING);
		}

/*	if(spot==1 && level==1)
	{

//	GLfloat light6_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light6_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light6_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light6_position[] = { cx, cy+2.0, cz, 1.0 };
	GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
	
//	glLightfv(GL_LIGHT6, GL_AMBIENT, light6_ambient);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, light6_diffuse);
	glLightfv(GL_LIGHT6, GL_SPECULAR, light6_specular);
	glLightfv(GL_LIGHT6, GL_POSITION, light6_position);
	glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, 1.5);
	glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, 0.5);
	glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, 0.2);
	
	glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 10.0);
	glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 2.0);
	
	glEnable(GL_LIGHT6);
	glEnable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	}*/
	initialise_tile_with_robo(cx,cy,cz);
	if(level==2)
	{
	int collision_with_other=check_collision_with_other();
	if(collision_with_other==1)
	{
		set_flag=1;
	}}
	if(level==3)
	{
		check_collision_with_ball(cx,cy,cz);
	}
	check_boundary(cx,cy,cz);
	position_of_robot(cx,cy,cz);
	check_spring(cx,cy,cz);
//	check_spot_light();
	int ret=check_fire(cx,cy,cz);
	int jump_counter=0;
	yy=0;
	jp=check_falls(cx,cy,cz);
	check_collision(cx,cy,cz);
	check_winning_positiion(cx,cy,cz);
	if(jp==0){
	if(jump==1)
	{
		
		cy=1.5;
		cy=0;
	}
		     if(ret==1)
		     {
			     glColor3f(0.0f,0.0f,0.0f);
		     }
		     else
		     {
		     	glColor3f(0.8f,0.0f,0.6f);
		     }
		     glPushMatrix();
		     glTranslatef(cx,cy+0.2,cz);
		     glutSolidSphere(0.1,20,20); //0.1
		     glPopMatrix();
			     //drawing cuboidal torso
		     if(ret==1)
		     {
		     	glColor3f(0.0f,0.0f,0.0f);
		     }
		     else
		     {
		     	glColor3f(0.0f,0.5f,0.5f);
		     }
//		     glPushMatrix();
		 
		 
//		     glPopMatrix();
			     glPushMatrix();
			    glTranslatef(cx,cy,cz);
		     glutSolidCube(0.2);    //0.2
//			     glTranslatef(0.75,0.6,0.0);
//			     gluCylinder(quad,0.4,0.4,0.6,100,100);
			     glPopMatrix();
		     if(ret==1)
		     {
		     	glColor3f(0.0f,0.0f,0.0f);
		     }
		     else{
	             glColor3f(1.0f,1.0f,0.0f);}
		     glPushMatrix();
		     glTranslatef(cx-0.05,cy-0.01,cz);
		     GLUquadricObj* quadratic;
		     quadratic = gluNewQuadric();
//		     if(left_flag==0 && right_flag==0 && up_flag==0 && down_flag==0)
		     if(fac<=0)
		     {
		    		glPushMatrix();
		     		//glRotatef(-90,0.0f,1.0f,0.0f);
		     		glRotatef(90,1.0f,0.0f,0.0f);
		     		gluCylinder(quadratic,0.02,0.02,0.6,32,32);
				glPopMatrix();
		     glPopMatrix();
		     if(ret==1)
		     {
		     	glColor3f(0.0f,0.0f,0.0f);
		     }
		     else
		     {
	             	glColor3f(1.0f,0.5f,0.0f);
		     }
		     glPushMatrix();
		     glTranslatef(cx+0.05,cy-0.01,cz);
		     glPushMatrix();
		     glRotatef(90,1.0f,0.0f,0.0f);
		     	gluCylinder(quadratic,0.02,0.02,0.6,32,32);
		     	glPopMatrix();
			glPopMatrix();
			glPopMatrix();
		   return;	
		    
		     }
		     if(t%2==0)
		     {
			glRotatef(9,1.0f,0.0f,0.0f);
			
		     	glRotatef(90,1.0f,0.0f,0.0f);
		    	glPushMatrix();
		     	gluCylinder(quadratic,0.02,0.02,0.6,32,32);
			glPopMatrix();

		     	glPopMatrix();
		     }
		     else
		     {
		     	//	glRotatef(-90,0.0f,0.0f,1.0f);
		    		glPushMatrix();
		     		//glRotatef(-90,0.0f,1.0f,0.0f);
		     		glRotatef(90,1.0f,0.0f,0.0f);
		     		gluCylinder(quadratic,0.02,0.02,0.6,32,32);
				glPopMatrix();
		     glPopMatrix();
		     }
		     if(ret==1)
		     {
		     	glColor3f(0.0f,0.0f,0.0f);
		     }
                     else{
	             glColor3f(1.0f,0.5f,0.0f);}
		     glPushMatrix();
		    
		     glTranslatef(cx+0.05,cy-0.01,cz);
//		     glRotatef(-90,1.0f,0.0f,0.0f);
		     if(t%2!=0)
		     {
		     	glRotatef(9,1.0f,0.0f,0.0f);
			glRotatef(90,1.0f,0.0f,0.0f);
			glPushMatrix();
		     	gluCylinder(quadratic,0.02,0.02,0.6,32,32);
		     	glPopMatrix();

		        glPopMatrix();
		     }
		     
		     else
		     {
			glPushMatrix();
			glRotatef(90,1.0f,0.0f,0.0f);
		     	gluCylinder(quadratic,0.02,0.02,0.6,32,32);
		     	glPopMatrix();

		     glPopMatrix;
		    
		     }
		     glPopMatrix();
	}
	
	if(ret==1)
	{

		glColor3f(1.0f,1.0f,1.0f);
		glutTimerFunc(500,stop_func,0);
	}
	if(jp==1)
	{

		glutTimerFunc(25,falling_robot,0);
	}

}
void s()
{
		glColor3f(1.8f,0.0f,0.6f);
		//glPushMatrix();
		//glTranslatef(cx,cy+0.2,cz);
		//glColor3f(0,0,0);
		glutSolidSphere(-10.5,20,-20);
		glutSolidSphere(0.2,-0.1,0.9); //0.1
		//glPopMatrix();
}
void sample(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId[4]);
	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
	/*glBegin(GL_QUADS);
		glNormal3f(0.0, 1.0f, 0.0f);
		glColor3f(0,0.1,0.1);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f,0.51f,-0.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f,0.51f,0.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5f,0.51f,0.5f);
		glTexCoord2f(0.0f, 1.0f);	
		glVertex3f(-0.5f,0.51f,-0.5f);
	glEnd();
*/
	glColor3f(0.749f,0.847f,1.847f);
	//glEnable(GL_LIGHTING);
	//glColor3f(0,0,1);
//glVertexf(-10 ,-0.5,-10);
/*glBegin(GL_QUADS);
glNormal3f(0.0,1.0f,0.0f);
glTexCoord2f(0.0f,0.0f);
glVertex3f(-240.0f ,-80.0f,-14000.0f);
 glTexCoord2f(1.0f,0.0f);
glVertex3f(240.0f ,-80.0f,-14000.0f);
 glTexCoord2f(0.0f,1.0f);
glVertex3f(-240.f,-80.0f,20000.0f);
glTexCoord2f(1.0f,1.0f);
glVertex3f(240.0f ,-80.0f,20000.0f);
glEnd();
*/
glBegin(GL_QUADS);
glNormal3f(0.0,1.0f,0.0f);
glTexCoord2f(0.0f,0.0f);
glVertex3f(-100.0f ,-40.0f,140.0f);
 glTexCoord2f(1.0f,0.0f);
glVertex3f(-100.f,-40.0f,-1000.0f);
 glTexCoord2f(0.0f,1.0f);
glVertex3f(120.0f ,-40.0f,-1000.0f);
glTexCoord2f(1.0f,1.0f);
glVertex3f(120.0f ,-40.0f,140.0f);
glEnd();
	glDisable(GL_TEXTURE_2D);
}
void play()
{

	//	system("aplay Lost.wav &");
}
void drawballs()
{
//	fy=fy+deltay;
	for(int i=0;i<8;i++)
	{
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		//	printf("fx=%f fy=%f fz=%f deltay=%f\n",fx,fy,fz,deltay);
		glPushMatrix();
		glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
		fy=ball[i].y+ball[i].deltay;
		fx=ball[i].x;
		fz=ball[i].z;
//		printf("fy=%f deltay=%f\n",fy,ball[i].deltay);
		glTranslatef(fx,fy,fz);
		glutSolidSphere(0.3,20,20); //0.1
		glPopMatrix();
		glDisable(GL_BLEND);
	}
}
void drawScene()
{
	if(set_flag==0)
	{
	/*	if(spot==0) //&& level==2 )
		{
			//eckprintf("in enablin\n");
				if(level==1){
				glDisable(GL_LIGHTING);}
				if(level==2){
				glEnable(GL_LIGHTING);}
				glEnable(GL_LIGHT0);


			GLfloat ambientColor[] = {red, green, blue, 1.0f}; //Color(0.2, 0.2, 0.2)
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
		}
		if(spot==1 && level==1)
		{
			glEnable(GL_LIGHTING);
			glDisable(GL_LIGHT0);

//			GLfloat light6_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
			GLfloat light6_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
			GLfloat light6_specular[] = { 1.0, 1.0, 1.0, 1.0 };
			GLfloat light6_position[] = { cx, cy+2.0, cz, 1.0 };
			GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };

//			glLightfv(GL_LIGHT6, GL_AMBIENT, light6_ambient);
			glLightfv(GL_LIGHT6, GL_DIFFUSE, light6_diffuse);
			glLightfv(GL_LIGHT6, GL_SPECULAR, light6_specular);
			glLightfv(GL_LIGHT6, GL_POSITION, light6_position);
			glLightf(GL_LIGHT6, GL_CONSTANT_ATTENUATION, 1.5);
			glLightf(GL_LIGHT6, GL_LINEAR_ATTENUATION, 0.5);
			glLightf(GL_LIGHT6, GL_QUADRATIC_ATTENUATION, 0.2);

			glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 10.0);
			glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spot_direction);
			glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 2.0);

			glEnable(GL_LIGHT6);
		//	glDisable(GL_LIGHTING);
		}*/
   
	//		GLfloat ambientColor[] = {red, green, blue, 1.0f}; //Color(0.2, 0.2, 0.2)
	//		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);


		initialise_tile_with_robo(cx,cy,cz);
		initialise_tile_with_robo(cx,cy,cz);
		glViewport(0,0,1366,768);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0,(double)1366/(double)768,1.0,200); // first 90

		if(tower==1)
		{
			gluLookAt(0.0f,5.5f, 15.0f,
					0.0f,0.0f,0.0f,
					0.0f,1.0f,0.0f);
		}
		else if (first==1)
		{
			gluLookAt(cx-6.0,cy+0.5, cz+6.85,   
					cx-6.0,cy+0.5,cz-1.0+6.85,
					0.0f,1.0f,0.0f);}
		else if (third==1){
			gluLookAt(cx-6.0,cy+0.5, cz+7.0,   
					cx-6.0,cy+0.2,cz-0.5+7.0,
					0.0f,1.0f,0.0f);}
		else if (tile_view==1){	
			gluLookAt(-2.0,1.0f, 1.0f,  
					1.5f,1.0f,-4.0f,
					0.0f,1.0f,0.0f);}
		else if(look==4){		
			gluLookAt(x_new,15, y_new,  
					0.0f,0.0f,0.0f,
					0.0f,1.0f,0.0f);}

		initialise_tile_array();
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(-_angle, 1.0f, 0.0f, 0.0f);
		glTranslatef(-4*1.5, 0.0, 4*1.5);	
		/*glBegin(GL_QUADS);
		  glColor3f(0.0f, 0.0f, 0.0f);
		//glColor3f(0.005f, 0.005f, 0.005f);
		glVertex3f(-105.0f,-20.0f,-120.0f);
		glVertex3f(105.0f,-20.0f,-120.0f);
		glVertex3f(105.0f,12.0f,-120.0f);
		glVertex3f(-105.0f,12.0f,-120.0f);
		glEnd();*/
		if(level==2 && enter==0)
		{ 
		cx=0.2;
		cy=0.9;
		cz=-0.1;
	}
	drawrobot(cx,cy,cz);
	if(level==2)
	{
		drawenemy_robot(ex,ey,ez);		
	}
	cv=0;
	for(float j=0.0;j>(-8*1.5);j-=1.5)
	{
		k++;
		int v1;
		int v2=0;
		cl=0;
		v1=rand()%10+2; // missing
		//printf("missing tile is %d\n",v1);
		for(float i=0.0;i<=(7*1.5);i+=1.5)
		{	
			if(v1==cl && tile[cv][cl].moving!=1)
			{
			//	printf("v1=%d cl=%d,tile[%d][%d].robo=%d ",v1,cl,cv,cl,tile[cv][cl].robo);
				
				if(tile[cv][cl].robo==1){
			//	printf("drawing the missing tile on which the robot is there\n");
				tile[cv][cl].missing=0;	
				yy=0.0;
				glPushMatrix();
				glTranslatef(i,0.0,j);
				draw_whiteArea();
			//	glCallList(_displayListId_whiteArea);
				glPopMatrix();}
				else if(tile[cv][cl].robo!=1)
				{
			//	printf("not drawing the missing tile since robot is not there\n");
					tile[cv][v1].missing=1;
				}
			}

			if(v1!=cl || tile[cv][cl].moving==1  )
			{
				if(tile[cv][cl].fire==1){
				//	//glColor3f(1.0f,1.0f,1.0f);
				//	ran=1;
					fire_flag=1;}
				if((cl==1 && cv==1) ||(cl==2 && cv==5)||(cl==6 && cv==3)){	
				yy=vely;
				tile[cv][cl].curr_y=0.3+yy;
				glPushMatrix();
				glTranslatef(i,0.0,j);
				draw_BlackArea();
				glPopMatrix();}	
				else{
				yy=0.0;
				glPushMatrix();
				glTranslatef(i,0.0,j);
				draw_whiteArea();
			//	glCallList(_displayListId_whiteArea);
				glPopMatrix();}
			}
					cl++;
			k++;
			fire_flag=0;
		}
		cv++;	

	}	char file[20];
		int ms=0;
		int d,n=ms;
		int p=n,no=0,num;
		while(n!=0)
		{
			d=n%10;
			no++;
			n=n/10;
		}
		num=no;
		file[num]='\0';
		while(p!=0)
		{
			d=p%10;
			file[no-1]=d+'0';
			p=p/10;
			no--;
		}

drawBitmapText("LEVEL 1",3.0f,4.0f,-0.1f);
drawBitmapText("SCORE:",7.0f,4.0f,-0.1f);
if(ms ==0) drawBitmapText("0",8.0f,4.0f,-0.1f);
else drawBitmapText(file,12.0f,4.0f,-0.1f);
sample();
}

//		drawrobot(cx,cy,cz);}
       else if(set_flag==1){	

		//system("killall 9 aplay");
		play();
	       glViewport(0,0,1366,768);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(double)1366/(double)768,1.0,200);	
	gluLookAt(0.0f,5.5f, 15.0f,
			0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f);
	       glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//	glClearColor(
	glClearColor(1.00, 1.00, 1.00, 0.0);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(-2*1.5, 0.0, 2*1.5); 

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId[1]);
	// isse upar waale white squares ban rhe hain
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
	glBegin(GL_QUADS);
//	glColor3f(0.0f,0.0f,0.0f);
//		glColor3f(0.0f,1.0f,1.0f); //cyan
	/*glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.0f,-2.0f,0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.0f,-2.0f,0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.0f,2.0f,0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.0f,2.0f,0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);*/	
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.0f,-5.0f,0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f,-5.0f,0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f,5.0f,0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.0f,5.0f,0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
		
	
       }
       else if( set_flag==2){  
	       glViewport(0,0,1366,768);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(double)1366/(double)768,1.0,200);	
	gluLookAt(0.0f,5.5f, 15.0f,
			0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f);
	       glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//	glClearColor(
	glClearColor(1.00, 1.00, 1.00, 0.0);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-2*1.5, 0.0, 2*1.5); 
	
/*	glTranslatef(-3.2*1.5, 0.0, 4*1.5);	
	drawrobot(cx,cy,cz);
//	drawrobot(ex,ey,ez);
	cv=0;
	for(float j=0.0;j>(-8*1.5);j-=1.5)
	{
		k++;
		int v1;
		int v2=0;
		cl=0;
		v1=rand()%10+2; // missing
		//printf("missing tile is %d\n",v1);
		for(i=0.0;i<=(7*1.5);i+=1.5)
		{	
			if(v1==cl && tile[cv][cl].moving!=1)
			{
				if(tile[cv][cl].robo==1){
				tile[cv][cl].missing=0;	
				yy=0.0;
				glPushMatrix();
				glTranslatef(i,0.0,j);
				draw_whiteArea();
			//	glCallList(_displayListId_whiteArea);
				glPopMatrix();}
				else
				{
				tile[cv][v1].missing=1;
				}
			}

			if(v1!=cl || tile[cv][cl].moving==1  )
			{
				if(tile[cv][cl].fire==1){
				//	//glColor3f(1.0f,1.0f,1.0f);
				//	ran=1;
					fire_flag=1;}
				if((cl==1 && cv==1) ||(cl==2 && cv==5)||(cl==6 && cv==3)){	
				yy=vely;
				tile[cv][cl].curr_y=0.3+yy;
				glPushMatrix();
				glTranslatef(i,0.0,j);
				draw_BlackArea();
				glPopMatrix();}	
				else{
				yy=0.0;
				glPushMatrix();
				glTranslatef(i,0.0,j);
				draw_whiteArea();
			//	glCallList(_displayListId_whiteArea);
				glPopMatrix();}
			}
					cl++;
			k++;
			fire_flag=0;
		}
		cv++;	

	}	char file[20];
		int ms=0;
		int d,n=ms;
		int p=n,no=0,num;
		while(n!=0)
		{
			d=n%10;
			no++;
			n=n/10;
		}
		num=no;
		file[num]='\0';
		while(p!=0)
		{
			d=p%10;
			file[no-1]=d+'0';
			p=p/10;
			no--;
		}

drawBitmapText("LEVEL 1",3.0f,4.0f,-0.1f);
drawBitmapText("SCORE:",7.0f,4.0f,-0.1f);
if(ms ==0) drawBitmapText("0",8.0f,4.0f,-0.1f);
else drawBitmapText(file,12.0f,4.0f,-0.1f);
sample();*/


		glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId[2]);
	// isse upar waale white squares ban rhe hain
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.0f,-5.0f,0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f,-5.0f,0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f,5.0f,0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.0f,5.0f,0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D); 
       } 
	else if( set_flag==-1){  
	       glViewport(0,0,1366,768);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(double)1366/(double)768,1.0,200);	
	gluLookAt(0.0f,5.5f, 15.0f,
			0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f);
	       glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(-2*1.5, 0.0, 2*1.5);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId[3]);
	// isse upar waale white squares ban rhe hain
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
//	glColor3f(0.0f,0.0f,0.0f);
//	glColor3f(0.0f,1.0f,1.0f); //cyan
	/*glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.0f,-2.0f,0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.0f,-2.0f,0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.0f,2.0f,0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.0f,2.0f,0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);*/	
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.0f,-5.0f,0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f,-5.0f,0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f,5.0f,0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.0f,5.0f,0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);}
	else if(set_flag==3){	

		//system("killall 9 aplay");
		play();
	       glViewport(0,0,1366,768);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(double)1366/(double)768,1.0,200);	
	gluLookAt(0.0f,5.5f, 15.0f,
			0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f);
	       glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//	glClearColor(
	glClearColor(1.00, 1.00, 1.00, 0.0);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(-2*1.5, 0.0, 2*1.5); 

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId[5]);
	// isse upar waale white squares ban rhe hain
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
	glBegin(GL_QUADS);
//	glColor3f(0.0f,0.0f,0.0f);
//		glColor3f(0.0f,1.0f,1.0f); //cyan
	/*glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.0f,-2.0f,0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.0f,-2.0f,0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.0f,2.0f,0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.0f,2.0f,0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);*/	
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.0f,-5.0f,0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f,-5.0f,0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f,5.0f,0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.0f,5.0f,0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	}
else if( set_flag==4)
{
	GLfloat ambientColor[] = {red, green, blue, 1.0f}; //Color(0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	glViewport(0,0,1366,768);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0,(double)1366/(double)768,1.0,200); // first 90

	if(tower==1)
	{
		gluLookAt(0.0f,5.5f, 15.0f,
				0.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f);
	}
	else if (first==1)
	{
		gluLookAt(cx-6.0,cy+0.5, cz+6.85,   
				cx-6.0,cy+0.5,cz-1.0+6.85,
				0.0f,1.0f,0.0f);}
	else if (third==1){
		gluLookAt(cx-6.0,cy+0.5, cz+7.0,   
				cx-6.0,cy+0.2,cz-0.5+7.0,
				0.0f,1.0f,0.0f);}
	else if (tile_view==1){	
		gluLookAt(-2.0,1.0f, 1.0f,  
				1.5f,1.0f,-4.0f,
				0.0f,1.0f,0.0f);}
	else if(look==4){		
		gluLookAt(x_new,15, y_new,  
				0.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f);}

	initialise_tile_array();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(-_angle, 1.0f, 0.0f, 0.0f);
	glTranslatef(-4*1.5, 0.0, 4*1.5);	
	drawrobot(cx,cy,cz);
	drawballs();

//	glutSolidSphere(0.1,20,20); //0.1
	cv=0;
	for(float j=0.0;j>(-8*1.5);j-=1.5)
	{
		k++;
		int v1;
		int v2=0;
		cl=0;
		v1=rand()%10+2; // missing
		for(float i=0.0;i<=(7*1.5);i+=1.5)
		{	
			if(v1==cl && tile[cv][cl].moving!=1)
			{
				//	printf("v1=%d cl=%d,tile[%d][%d].robo=%d ",v1,cl,cv,cl,tile[cv][cl].robo);

				if(tile[cv][cl].robo==1){
					//	printf("drawing the missing tile on which the robot is there\n");
					tile[cv][cl].missing=0;	
					yy=0.0;
					glPushMatrix();
					glTranslatef(i,0.0,j);
					draw_whiteArea();
					//	glCallList(_displayListId_whiteArea);
					glPopMatrix();}
				else if(tile[cv][cl].robo!=1)
				{
					//	printf("not drawing the missing tile since robot is not there\n");
					tile[cv][v1].missing=1;
				}
			}

			if(v1!=cl || tile[cv][cl].moving==1  )
			{
				if(tile[cv][cl].fire==1){
					//	//glColor3f(1.0f,1.0f,1.0f);
					//	ran=1;
					fire_flag=1;}
				if((cl==1 && cv==1) ||(cl==2 && cv==5)||(cl==6 && cv==3)){	
					yy=vely;
					tile[cv][cl].curr_y=0.3+yy;
					glPushMatrix();
					glTranslatef(i,0.0,j);
					draw_BlackArea();
					glPopMatrix();}	
				else{
					yy=0.0;
					glPushMatrix();
					glTranslatef(i,0.0,j);
					draw_whiteArea();
					//	glCallList(_displayListId_whiteArea);
					glPopMatrix();}
			}
			cl++;
			k++;
			fire_flag=0;
		}
		cv++;	

	}	char file[20];
	int ms=0;
	int d,n=ms;
	int p=n,no=0,num;
	while(n!=0)
	{
		d=n%10;
		no++;
		n=n/10;
	}
	num=no;
	file[num]='\0';
	while(p!=0)
	{
		d=p%10;
		file[no-1]=d+'0';
		p=p/10;
		no--;
	}

	drawBitmapText("LEVEL 1",3.0f,4.0f,-0.1f);
	drawBitmapText("SCORE:",7.0f,4.0f,-0.1f);
	if(ms ==0) drawBitmapText("0",8.0f,4.0f,-0.1f);
	else drawBitmapText(file,12.0f,4.0f,-0.1f);
	sample();
}
glutSwapBuffers();
}
void handleKeypress2(int key,int x,int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		if(level==2)
		{
			enter=enter+1;
		}
		left_flag=1;
		right_flag=0;
		down_flag=0;
		up_flag=0;
		dir=(dir+1)%4;
		fac=fac+0.1;
		cx=cx-fac;
		drawrobot(cx,cy,cz);
	}
	if (key == GLUT_KEY_RIGHT)
	{	if(level==2)
		{
			enter=enter+1;
		}

		right_flag=1;
		left_flag=0;
		up_flag=0;
		down_flag=0;
		dir=(dir+1)%4;
		fac=fac+0.1;
		cx=cx+fac;
		drawrobot(cx,cy,cz);
	}
	if (key == GLUT_KEY_UP)
	{	if(level==2)
		{
			enter=enter+1;
		}

		up_flag=1;
		left_flag=0;
		right_flag=0;
		down_flag=0;
		if(first==1){
			co=co+0.5;
			drawScene();}
		fac=fac+0.1;
		cz=cz-fac;
		drawrobot(cx,cy,cz);
	}
	if (key == GLUT_KEY_DOWN)
	{	if(level==2)
		{
			enter=enter+1;
		}

		down_flag=1;
		up_flag=0;
		left_flag=0;
		right_flag=0;
		fac=fac+0.1;
		cz=cz+fac;
		drawrobot(cx,cy,cz);
	}
}
void update(int value) 
{
	if(level>=2){
	if(red>4.75 && green>1.8 && blue>0.9){
		red=-0.05;
		green=-0.02;
		blue=-0.01;
	}
	red=red+0.05;
	blue=blue+0.01;
	green=green+0.02;}
	if(spot==1)
	{
		red=0.0;
		blue=0.0;
		green=0.0;
	}
	if(spot==0)
	{
		_angle += dv1;
		if(_angle >=0.3)
		{
			dv1=-dv1;
			pappu=1;
		}
		if(_angle<=0.0 && pappu==1)
		{
			dv1=-dv1;
		}
		if (_angle > 360) 
		{

			_angle -= 360;

		}
	}
	t++;
	vely=vely+dv;
	if(vely>=1.5)
	{
		munni=1;
		dv=-dv;
	}
	if(vely<= 0.0 && munni==1)
	{
		dv=-dv;
	}
	fac=fac-0.08;
	enemy_fac=enemy_fac-0.08;	
	if (enemy_fac<0)
	{
		enemy_fac=0;
	}

	if (fac<0)
	{
		fac=0;
	}
	if(set_flag==4)
	{
		float ran=rand()%10;// missing
		deltax=deltax+ran;
		for(int i=0;i<8;i++){
		if(ball[i].deltay<=-3.3)
		{
			ball[i].y_fac=(-1.0)*ball[i].y_fac;
		}
		if(ball[i].deltay>=1.0)
		{
			ball[i].y_fac=-0.05;
		}
		ball[i].deltay=ball[i].deltay+ball[i].y_fac;}
		deltaz=deltaz+ran;
		
	}
		spring_counter++;
	glutPostRedisplay();
	glutTimerFunc(500, update, 0);
}
void passive(int x1,int y1)
{
	x_new=x1-cursorx;
	y_new=y1-cursory;
}
void handleMouseclick(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON)
	{
		look=4;
		tower=0;
		first=0;
		third=0;
		tile_view=0;
		cursorx=x;
		cursory=y;

	}
}
int main(int argc,char** argv)
{
	//system("aplay mario.wav &");
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(800,800);
	glutCreateWindow("basic shape");
	initRendering();
	initialise_ball_array();
	glutFullScreen();
	 GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	 GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(handleMouseclick);
	glutMotionFunc(passive);
//	glutReshapeFunc(handleResize);
	glutTimerFunc(500, update, 0);
	glutMainLoop();
	return 0;
}

