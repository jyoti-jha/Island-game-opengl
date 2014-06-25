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
	float y_sor;
	float z_cor;
}Robot;
Robot robot;
int spring_counter=0,lev=1;
int keep=0;
int set_flag=-1,tile_view=0,cursorx,cursory,x_new,y_new,look=0;
int v2=rand()%7;
int sound=0;
int t=0,y1_rate=0,jp;
int x=1.5,y=0,munni=0;
int counter=0;
using namespace std;
float _angle = 0,dv1=0.5;
float y_rate=0.0;
float i;
int k=0,row=0,pappu=1;
int left_flag=0,right_flag=0,up_flag=0,down_flag=0;
float cx=0.2;      //tt[cp.t_r][cp.t_c].llx+5;
float cz=-0.1; //tt[cp.t_r][cp.t_c].llz+5;
float cy=0.9;      //tt[cp.t_r][cp.t_c].h;
float fac=0.0,dv=0.1;
int fl=0,jump=0;
int dir=0,fall_counter=0;
float co=0;	
int fire_no=rand()%64,fire_flag=0;
int block_count=0;
float yy=0.0,vely=0.0;
int ran=0;
int factor=0,tower=0,first=0,tower_view=0,first_person_view=0,projectile_front=0,ck_flag=0,third=0;
int cl=0,cv=0;
//GLuint _displayListId_blackArea; //The OpenGL id of the display list
//GLuint _displayListId_whiteArea; //The OpenGL id of the display list
GLuint _textureId[4]; //The id of the texture
GLuint textureId[4];
void drawScene();
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
		}
	}
	
}
void position_of_robot(float cx,float cy,float cz)
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{	
			if(cx>=tile[i][j].x_cor && cx<=tile[i][j].x_cor+1.5)
			{
				if(cz>=tile[i][j].z_cor-1.5 && cz<=tile[i][j].z_cor)
				{
					//if(tile[i][j].missing==1)
					//{
						tile[i][j].robo=1;
				//	}
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
void handleKeypress(unsigned char key,int x,int y)
{
	if(key==27)

	{
		sound=1;
		system("killall 9 aplay");
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
	if(key=='j')
	{
		jump=(jump+1)%2;
		
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
	if(key=='a')
	{
		glutTimerFunc(400,sona1,0);
	}
	if(key=='q')
	{
		glutTimerFunc(400,sona2,0);
	}	
	if(key=='w')
	{
		glutTimerFunc(400,sona3,0);
	}
	if(key=='e')
	{
		glutTimerFunc(400,sona4,0);
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
		printf("%d\n",keep);
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
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	Image* image1 = loadBMP("pink.bmp");
	_textureId[0] = loadTexture1(image1);
	delete image1;
	Image* image2 = loadBMP("images.bmp");
	_textureId[1] = loadTexture2(image2);
	delete image2;	
	Image* image3 = loadBMP("you_win.bmp");
	_textureId[2] = loadTexture3(image3);
	delete image3;	
	Image* image4 = loadBMP("mario.bmp");
	_textureId[3] = loadTexture4(image4);
	delete image4;


//	glClearColor(0.05f,0.1f,0.1f,1.0f);
	glClearColor(0.50, 0.6, 0.7, 0.5);
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
int check_falls(float cx,float cy,float cz)
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{	
			if(cx>=tile[i][j].x_cor && cx<=tile[i][j].x_cor+1.5)
			{
				if(cz>=tile[i][j].z_cor-1.5 && cz<=tile[i][j].z_cor)
					if(tile[i][j].missing==1){
				//	printf("landed on missing tile %f %f %f\n",tile[i][j].x_cor,tile[i][j].z_cor);
				//	printf("in drawrobot values of x,y,z are %f %f %f\n",cx,cy,cz);
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
void check_collision(float cx,float cy,float cz)
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{	
			if(cx>=tile[i][j].x_cor && cx<=tile[i][j].x_cor+1.5)
			{
				if(cz>=tile[i][j].z_cor-1.5 && cz<=tile[i][j].z_cor)
					if(tile[i][j].moving==1){
						set_flag=1;
					if(tile[i][j].curr_y<=cy){
					cy=tile[i][j].curr_y;
					}}
					else{
					}
			}
		}
	}

}
void check_winning_positiion(float cx,float cy,float cz)
{	
	if(cx>=tile[7][7].x_cor && cx<=tile[7][7].x_cor+1.5)
			{
				if(cz>=tile[7][7].z_cor-1.5 && cz<=tile[7][7].z_cor){
					lev=lev+1;
					//if(tile[7][7].moving==1){
					set_flag=2;}
				
			}
}

int check_fire()
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{	
			if(cx>=tile[i][j].x_cor && cx<=tile[i][j].x_cor+1.5)
			{
				if(cz>=tile[i][j].z_cor-1.5 && cz<=tile[i][j].z_cor)
				{
					if(tile[i][j].fire==1)
					{
						//set_flag=1;
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
void check_boundary()
{
	if( cx<0.2||cx>12.2)
	{
		set_flag=1;
	}
	if(cz>0.2||cz<-12.0)
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
	///for(int i=0;i<8;i++)
	cv=0;
	for(float j=0.0;j>(-8*1.5);j-=1.5)
	{
		cl=0;
		//v1=rand()%10+2; // missing
		for(float i=0.0;i<=(7*1.5);i+=1.5)
		//for(int j=0;j<8;j++)
		{	
			if(cx>=tile[cv][cl].x_cor && cx<=tile[cv][cl].x_cor+1.5)
			{
				if(cz>=tile[cv][cl].z_cor-1.5 && cz<=tile[cv][cl].z_cor)
				{
					glPushMatrix();
					glTranslatef(i,0.0,j);
//					printf("%d\n",keep++);
					fire_flag=2;
//					new_scene(cx,cz);
					draw_whiteArea();
			//	glCallList(_displayListId_whiteArea);
					glPopMatrix();
				}

			}
/*			else
			{
				break;
			}*/
			cl++;
		}
		cv++;
	}
//	fire_flag=0;
}
void initialise_tile_with_robo(float cx,float cy,float cz)
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
	if((spring_counter%2)==0)
	{
		cy=1.5;
	}	
	if((spring_counter%2)!=0)
	{
		cy=1.0;
	}

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

void drawrobot(float cx,float cy,float cz)
{

	initialise_tile_with_robo(cx,cy,cz);
	check_boundary();
	position_of_robot(cx,cy,cz);
	check_spring(cx,cy,cz);
//	check_spot_light();
	int ret=check_fire();
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
		     else{
	             glColor3f(1.0f,0.5f,0.0f);}
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
void drawScene()
{
	if(set_flag==0)
	{
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
	drawrobot(cx,cy,cz);
	cv=0;
	for(float j=0.0;j>(-8*1.5);j-=1.5)
	{
		k++;
		int v1;
		int v2=0;
		cl=0;
		v1=rand()%10+2; // missing
		printf("missing tile is %d\n",v1);
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

	}}
//		drawrobot(cx,cy,cz);}
       else if(set_flag==1){		
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
	 
//	drawrobot(cx,cy,cz);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId[1]);
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
	glutSolidCube(2.0);    //0.2
//	glTranslatef(-2*1.5, 0.0, 2*1.5);	
/*	cv=0;
	for(float j=0.0;j>(-8*1.5);j-=1.5)
	{
		k++;
		int v1;
		int v2=0;
		cl=0;
		v1=rand()%10+2; // missing
//		printf("missing tile is %d\n",v1);
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

	}*/


/*			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId[2]);
	// isse upar waale white squares ban rhe hain
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);
//	glColor3f(0.0f,0.0f,0.0f);*/
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
/*	glTexCoord2f(0.0f, 0.0f);   uncomment    
	glVertex3f(-5.0f,-5.0f,0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.0f,-5.0f,0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f,5.0f,0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.0f,5.0f,0.0f);
	glEnd();
uncomment	glDisable(GL_TEXTURE_2D); */
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
       
//	glClearColor(
//	glClearColor(0.50, 0.6, 0.7, 0.5);}
	//glClearColor(1.00, 1.00, 1.00, 0.0);}
	glutSwapBuffers();
}
void handleKeypress2(int key,int x,int y)
{
		if (key == GLUT_KEY_LEFT)
		{
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
		{
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
		{
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
		{
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
	if (fac<0)
	{
		fac=0;
	}
	if (_angle > 360) {

		_angle -= 360;

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
	system("aplay mario.wav &");
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(800,800);
	glutCreateWindow("basic shape");
	initRendering();
	glutFullScreen();
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

