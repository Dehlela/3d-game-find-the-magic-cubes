#include<math.h>
#include<stdio.h>
#include <windows.h>
#include<string.h>
#include<unistd.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
void land();
void magic_cube(int,int,int,int);
void repeat_scroll();
void guard_snowman();

GLfloat mat_specular[] = {0.2,0.2,0.2};
GLfloat mat_diffuse[]={0,0,0};
GLfloat mat_shininess[] = {30.0};
GLfloat light_position[] = {1.0,1.0,0.0,0.0};
GLfloat light_intensity[]={0,0,0};

int ox0=-3000,ox1=3000,oy0=-3000,oy1=3000,oz0=-50000,oz1=500000;
float scale_x,scale_y,scale_z;
int magic_cube_collected[4],cube_collection,gems_collected[4],start=0,repeat=0;
int w1, w2;
int board_on_resize=0;
int wd,ht;
int w;
int attack=0,movex,movez,move_flag,hits[3];
int fg,rg,sg,congrats_msg;
//float xpos = 150, ypos = 0, zpos = 7500;//main entry
//float xpos = 728, ypos = 0, zpos = -115;//magic cube 1
//float xpos = 5100, ypos = 0, zpos = -11200;//snowy
float xpos = -4100, ypos = 0, zpos = -5100;//rocky
//float xpos = 4278, ypos = 0, zpos = -9342;//magic cube 2
//float xpos = 400, ypos = 0, zpos = -23000;//magic cube 3
float xrot=0,yrot=0,temp_xrot=0,temp_yrot=0;
int level=2;
float cRadius = 10.0f;
float theta,angle=0.0;
GLuint texture;
GLuint texture2,texture3,paper;
struct gem
{
	float color[3];
	float pos[3];
	int flag;
 } gems_main[12],gems_rocky[11],gems_snowy[11];

int gm=12,gr=10,gs=10;
float gcolor[2][3]={{1,0,1},{0.5,0.5,0.5}};

GLuint boardlist,board2list,initlist1,initlist2,initlist3,rockylist,gorilla_list,maze_forestlist,pondlist,snowylist,leaflist,snowforestlist,attack_scroll_list,collect_cube_scroll_list,snow_tex_list,rocky_tex_list,main_tex_list,decorate_list,entrancelist,cavelist,skylist,collectibleslist;

GLuint LoadTexture( const char * filename, int width, int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    data = (unsigned char *)malloc( width * height * 3 );
    fread( data, width * height * 3, 1, file );
    fclose( file );

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
GL_MODULATE );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
GL_LINEAR );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
GL_REPEAT );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
GL_RGB, GL_UNSIGNED_BYTE, data);
    free( data );
    return texture;
}

void FreeTexture( GLuint texture )
{
  glDeleteTextures( 1, &texture );
}

void drawGrass (void) {
main_tex_list=glGenLists(1);
glNewList(main_tex_list,GL_COMPILE);
texture = LoadTexture("texture.raw", 256, 256);
glColor3f(0.486,0.988,0);//lawn green
   for (int i = -50; i < 50; i++)
    {
        for (int j = -50; j < 50; j++)
        {

                glBindTexture( GL_TEXTURE_2D, texture );


            glPushMatrix();
                glTranslatef(j, -5, i+15);
				glRotatef(90,1,0,0);
                glBegin (GL_QUADS);
                    glTexCoord2d(0.0, 0.0);
                    glVertex3f(0.0, 0.0, 0.0);

                    glTexCoord2d(1.0, 0.0);
                    glVertex3f(1.0, 0.0, 0.0);

                    glTexCoord2d(1.0, 1.0);
                    glVertex3f(1.0, 1.0, 0.0);

                    glTexCoord2d(0.0, 1.0);
                    glVertex3f(0.0, 1.0, 0.0);
                glEnd();
            glPopMatrix();
        }
    }
    glEndList();
}
void drawSnow () {

snow_tex_list=glGenLists(1);
glNewList(snow_tex_list,GL_COMPILE);
glColor3f(1,1,1);
texture3 = LoadTexture("snow.bmp", 256, 256);
    for (int i = -60; i < 60; i++)
    {
        for (int j = -50; j < 50; j++)
        {

                glBindTexture( GL_TEXTURE_2D, texture3 );


            glPushMatrix();
                glTranslatef(j, -5, i+15);
				glRotatef(90,1,0,0);
                glBegin (GL_QUADS);
                    glTexCoord2d(0.0, 0.0);
                    glVertex3f(0.0, 0.0, 0.0);

                    glTexCoord2d(1.0, 0.0);
                    glVertex3f(1.0, 0.0, 0.0);

                    glTexCoord2d(1.0, 1.0);
                    glVertex3f(1.0, 1.0, 0.0);

                    glTexCoord2d(0.0, 1.0);
                    glVertex3f(0.0, 1.0, 0.0);
                glEnd();
            glPopMatrix();
        }
    }
glEndList();
}
void drawDirt (void) {
rocky_tex_list=glGenLists(1);
glNewList(rocky_tex_list,GL_COMPILE);
texture2 = LoadTexture("rocky4.bmp", 256,256);
glColor3f(0.824,0.412,0.118);
   for (int i = -20; i < 20; i++)
    {
        for (int j = -50; j < 50; j++)
        {

                glBindTexture( GL_TEXTURE_2D, texture2 );


            glPushMatrix();
                glTranslatef(j, -5, i+15);
				glRotatef(90,1,0,0);
                glBegin (GL_QUADS);
                    glTexCoord2d(0.0, 0.0);
                    glVertex3f(0.0, 0.0, 0.0);

                    glTexCoord2d(1.0, 0.0);
                    glVertex3f(1.0, 0.0, 0.0);

                    glTexCoord2d(1.0, 1.0);
                    glVertex3f(1.0, 1.0, 0.0);

                    glTexCoord2d(0.0, 1.0);
                    glVertex3f(0.0, 1.0, 0.0);
                glEnd();
            glPopMatrix();
        }
    }
    glEndList();
}
void resize1(int w, int h)
{
    glViewport(0, 0, w, h);
    wd=w;
    ht=h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

}
void img2(int * img1,float a,float b,float c )
{
	int i=0;
	glColor3f(a,b,c);
	glBegin(GL_POLYGON);
	while (img1[i]!=-1)
	{
		glVertex2i(img1[i],300-img1[i+1]);
		i=i+2;
	}
	glEnd();
}
void fox()
{
	GLint a1[]={29,250,47,257,46,262,45,266,47,271,47,277,50,281,52,285,55,289,56,295,55,299,52,301,47,301,43,301,39,299,37,295,34,292,31,285,30,
	277,30,271,30,265,29,260,29,254,-1};
	GLint a2[]={30,251,45,264,46,260,47,258,50,255,54,253,59,251,64,250,68,247,73,245,77,244,82,242,84,239,80,239,76,240,75,237,73,233,72,229,70,225,68,220,67,215,
	65,210,63,205,62,200,60,195,60,191,58,188,58,193,56,200,57,205,56,211,54,216,53,222,50,227,47,233,42,239,38,243,34,247,-1};
	GLint a3[]={48,141,49,147,51,154,52,160,53,167,55,173,57,182,59,190,62,198,64,209,68,216,71,227,73,233,75,238,79,239,85,238,90,238,96,238,101,239,
	106,239,109,239,109,233,110,229,110,225,111,220,111,215,112,210,112,204,111,198,113,191,113,186,113,182,113,176,113,171,113,166,113,159,117,155,120,
	151,122,146,124,143,127,141,121,140,116,139,110,138,105,137,99,137,93,137,88,137,84,137,80,137,75,137,71,137,66,137,62,137,55,139,-1};
	GLint a4[]={98,309,109,325,105,327,101,328,98,328,93,328,88,329,84,329,81,327,78,324,79,321,81,317,83,314,84,311,87,310,92,310,-1};
	GLint a5[]={97,309,109,325,110,321,110,316,111,311,113,305,115,299,116,294,119,287,121,283,124,277,127,272,129,267,133,261,136,255,140,252,
	143,247,147,243,151,236,154,235,156,233,110,222,110,231,109,237,108,245,107,254,106,264,105,273,102,282,102,288,101,295,99,304,-1};
	GLint a6[]={157,233,110,232,110,228,110,225,111,220,111,215,112,209,112,203,112,197,113,192,113,183,113,177,113,170,114,164,114,159,116,155,119,152,
	122,147,124,144,126,143,131,143,136,143,140,143,144,144,147,149,149,160,151,166,151,171,151,179,152,187,154,192,155,201,155,209,156,218,157,226,-1};
	GLint a7[]={146,307,145,309,140,309,137,310,133,310,129,310,126,309,124,309,123,307,124,304,125,301,127,297,130,294,133,294,136,294,-1};
	GLint a8[]={137,293,145,307,148,304,151,298,155,294,157,290,160,285,161,283,163,279,167,273,169,269,171,265,172,262,174,257,155,262,153,267
	,150,272,147,279,144,283,140,289,-1};
	GLint b1[]={154,262,174,259,174,256,170,251,170,248,167,240,166,235,165,231,165,224,165,221,165,217,165,214,161,216,158,216,156,216,156,
    220,157,223,158,229,157,234,153,236,150,240,148,244,145,247,143,249,145,253,148,254,151,258,-1};
	GLint b2[]={157,217,161,217,165,214,168,212,167,209,166,206,164,203,161,201,159,199,156,197,155,195,155,200,155,206,156,211,-1};
	GLint b3[]={201,303,216,302,217,307,218,312,217,316,214,317,209,318,204,318,200,317,197,317,194,317,194,314,194,309,194,307,196,304,-1};
	GLint b4[]={199,303,217,307,216,303,215,297,215,293,214,289,214,285,212,280,212,275,210,270,209,265,208,261,208,258,196,264,197,268,198,
	272,200,277,200,284,200,289,201,295,201,300,-1};
   	GLint b5[]={197,267,208,263,208,258,205,252,203,246,201,238,198,230,196,220,193,212,192,204,190,198,187,194,165,206,168,213,171,218,
	173,226,176,233,180,241,183,248,187,254,190,259,194,262,-1};
   GLint b6[]={168,212,188,193,183,191,178,189,171,186,167,182,160,179,155,173,151,163,151,171,152,181,154,187,154,193,157,197,161,
	198,164,201,166,207,-1};
	GLint b7[]={237,157,281,152,279,149,273,145,269,142,263,140,258,137,252,136,247,134,240,133,236,133,232,133,228,132,225,132,221,
	132,217,132,220,136,223,138,229,142,232,146,235,152,-1};
	GLint b8[]={238,158,275,148,281,153,285,156,290,161,293,168,297,176,298,181,299,188,300,195,234,187,235,182,237,175,238,168,238,163,-1};
	GLint e1[]={300,197,303,195,304,191,306,189,307,185,308,183,310,190,312,196,312,202,-1};
	GLint e2[]={312,199,237,176,235,184,232,188,231,192,228,196,223,201,219,203,274,263,279,260,284,257,289,254,292,251,297,246,301,242,305,
	237,308,231,310,225,311,220,312,214,313,208,-1};
	GLint e3[]={220,202,278,261,271,265,265,268,259,268,254,271,249,271,245,271,240,271,235,270,231,269,224,266,220,264,215,260,211,258,208,256,
	206,249,202,241,201,234,199,228,197,222,196,216,193,209,192,205,191,199,194,200,199,203,203,203,209,204,215,203,-1};
	GLint e4[]={135,132,137,136,140,139,140,143,143,142,148,142,153,140,158,140,161,140,165,137,169,137,171,134,174,129,176,
	125,173,125,169,125,164,126,159,127,155,127,150,128,144,128,139,130,-1};
	GLint e5[]={46,109,64,137,71,138,78,138,84,137,89,137,94,137,102,138,108,139,114,141,121,141,127,143,133,143,139,142,139,139,134,
	133,131,129,125,125,121,121,116,115,112,110,107,104,104,98,101,94,98,91,94,88,91,85,86,83,80,83,75,82,71,82,65,85,61,88,56,93,51,98,49,103,48,107,-1};
	GLint e6[]={46,108,63,136,58,138,52,140,47,142,41,145,36,147,34,147,35,143,35,139,32,139,27,141,23,141,25,136,28,126,30,121,33,116,37,113,41,110,-1};
	GLint e7[]={98,65,134,69,132,59,130,53,128,45,126,38,125,33,124,27,121,20,120,14,119,9,117,6,114,11,110,17,107,26,104,36,101,44,100,52,98,59,-1};
	GLint e8[]={84,65,149,71,149,78,149,86,148,95,148,105,151,111,154,115,159,118,165,121,170,122,175,124,172,125,165,125,155,126,147,127,141,129,135,130,129,
	127,125,123,119,119,114,111,107,102,100,93,95,87,90,83,84,82,79,80,-1};
	GLint e9[]={85,66,93,86,86,82,78,81,73,82,68,83,63,86,59,89,55,94,51,101,47,108,42,109,42,104,42,99,44,94,46,88,52,80,58,76,-1};
	GLint e10[]={58,74,84,66,79,57,73,51,67,45,61,41,55,36,46,33,42,29,36,26,29,21,23,18,19,16,13,14,19,18,23,22,28,25,33,30,39,35,43,40,50,45,54,52,56,59,57,69,-1};
	GLint e11[]={43,94,48,87,52,82,57,76,58,70,57,62,57,57,54,50,50,45,45,40,40,35,34,29,28,26,25,23,21,20,17,17,12,15,12,20,15,30,18,39,19,48,22,56,23,66,25,74,27,83,29,88,34,89,39,93,-1};

	glPushMatrix();
	glTranslatef(-100,-150,0);

	 glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(a1,0.545,0.271,0.075);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(a2,0.545,0.271,0.075);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(a3,1,1,1);
	glPopMatrix();

 	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(a4,0.545,0.271,0.075);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(a5,0.545,0.271,0.075);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(a6,0.545,0.271,0.075);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(a7,0.545,0.271,0.075);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(a8,0.545,0.271,0.075);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(b1,0.545,0.271,0.075);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(b2,1,1,1);
	glPopMatrix();

 	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(b3,0.545,0.271,0.075);
	glPopMatrix();


 	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(b4,0.545,0.271,0.075);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(b5,0.545,0.271,0.075);
	glPopMatrix();

 		glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(b6,0.545,0.271,0.075);
	glPopMatrix();


 		glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(b7,0.545,0.271,0.075);
	glPopMatrix();

 		glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(b8,0.545,0.271,0.075);
	glPopMatrix();

			glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(e1,0.545,0.271,0.075);
	glPopMatrix();


			glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(e2,0.545,0.271,0.075);
	glPopMatrix();


			glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(e3,0.545,0.271,0.075);
	glPopMatrix();

				glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(e4,0,0,0);
	glPopMatrix();

				glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(e5,1,1,1);
	glPopMatrix();


				glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(e6,1,1,1);
	glPopMatrix();

			glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(e7,0.545,0.271,0.075);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(e8,0.545,0.271,0.075);
	glPopMatrix();

			glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(e9,0.545,0.271,0.075);
	glPopMatrix();

				glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(e10,0.545,0.271,0.075);
	glPopMatrix();

					glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img2(e11,0.545,0.271,0.075);
	glPopMatrix();

 glPopMatrix();
}
void img(int * img1,float a,float b,float c,int outline )
{
	int i=0;
	if(outline==0)
	{
	glColor3f(a,b,c);
	glBegin(GL_POLYGON);
	while (img1[i]!=-1)
	{
		glVertex2i(img1[i],300-img1[i+1]);
		i=i+2;
	}
	glEnd();
	}
	else if(outline==1)
	{
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	while (img1[i]!=-1)
	{
		glVertex2i(img1[i],300-img1[i+1]);
		i=i+2;
	}
	glEnd();
	}
}

GLint a1[]={87,318,140,231,136,233,132,240,128,242,122,247,118,251,112,255,107,259,101,262,92,266,88,270,82,273,
	77,275,73,279,68,280,62,283,56,286,50,289,44,289,38,290,43,292,49,294,55,296,61,299,66,302,72,305,77,310,81,312,84,317,-1};
	GLint a2[]={139,229,87,318,91,315,95,314,100,312,105,312,110,311,115,312,118,313,123,316,127,318,131,322,135,328,-1};
	GLint a3[]={139,229,135,327,140,325,145,325,150,325,154,326,158,327,162,329,166,330,169,333,171,334,175,334,179,333,183,331,187,329,189,328,-1};
	GLint a4[]={138,229,171,336,176,334,178,332,182,330,186,329,190,329,188,322,188,315,188,310,189,303,189,297,190,292,191,287,193,281,194,277,196,273,199,271,201,
	267,204,265,197,262,192,262,187,260,182,258,176,256,172,254,166,252,162,249,156,247,153,243,148,239,144,236,141,232,-1};
	GLint a5[]={212,256,207,261,204,264,200,269,198,273,195,278,192,283,190,288,188,294,187,300,186,307,187,312,188,319,189,325,190,333,194,338,197,346,201,
	351,204,356,208,359,213,362,218,365,224,368,230,370,236,371,244,373,251,372,257,373,263,370,270,370,275,368,280,365,286,363,291,360,296,355,297,352,301,
	348,305,342,309,336,310,330,312,323,313,316,313,310,314,304,314,299,313,293,311,289,310,284,309,278,306,274,303,269,299,265,295,261,288,255,285,258,278,
	261,272,263,266,266,259,267,251,268,243,268,235,267,229,264,222,261,217,258,-1};
	GLint a6[]={232,267,224,274,221,277,217,283,214,290,212,298,211,305,211,312,212,321,214,328,217,334,221,339,227,344,233,347,240,350,246,351,252,
351,257,351,263,350,267,347,273,343,278,339,282,334,287,329,287,322,289,315,289,309,289,303,287,297,284,289,282,284,279,279,274,274,273,271,269,267,
264,267,259,268,252,268,247,268,240,267,235,267,-1};
	GLint a7[]={364,229,418,318,420,313,425,309,432,305,438,302,445,299,452,296,458,293,465,292,469,290,462,290,454,288,445,285,435,279,427,275,417,270,
	410,267,402,261,394,254,385,248,378,243,373,238,-1};
	GLint a8[]={365,229,369,327,372,323,375,319,379,316,383,314,388,312,394,311,398,311,402,312,407,313,412,314,416,317,418,319,-1};
	GLint b1[]={364,229,331,336,335,332,339,330,343,328,347,326,352,325,356,325,360,325,364,326,367,326,370,328,-1};
	GLint b2[]={332,335,364,230,360,233,355,239,351,243,345,248,338,253,331,256,325,257,320,260,315,261,310,262,305,264,298,264,301,268,303,274,307,281,
308,288,310,292,311,298,312,305,313,312,313,320,312,328,311,330,316,327,321,329,325,331,329,333,-1};
	GLint b3[]={204,356,200,360,196,364,194,370,196,374,199,379,203,380,208,381,213,380,217,379,222,376,226,373,228,370,223,368,217,366,212,363,207,360,-1};
	GLint b4[]={271,370,277,368,282,365,287,363,290,359,293,355,297,357,300,360,304,364,305,370,305,376,300,380,294,382,287,380,280,376,275,374,-1};
	GLint b5[]={227,137,220,141,213,145,209,151,204,158,199,166,194,173,189,182,185,189,185,195,183,202,186,210,186,218,189,225,192,232,195,237,199,243,205,
249,210,255,216,260,222,263,227,266,233,268,240,270,248,271,256,271,266,269,274,265,281,260,288,256,294,251,299,245,304,237,309,231,312,222,314,216,315,209,315,
201,315,194,313,187,310,181,308,176,306,169,302,163,298,158,295,153,290,148,285,142,279,140,274,138,268,135,262,134,256,133,251,133,246,133,239,133,234,135,-1};
   	GLint b6[]={298,158,301,153,302,149,306,145,310,141,314,138,318,134,323,132,327,129,324,128,318,129,312,130,307,131,302,133,297,136,293,137,289,139,286,141,284,
	   142,288,144,291,148,293,152,-1};
    GLint b7[]={297,155,300,160,303,165,305,171,307,175,310,180,314,184,317,181,319,175,323,169,326,161,328,153,329,144,329,137,330,131,330,127,324,130,318,134,
	313,139,310,142,306,145,301,148,298,151,-1};
	GLint b8[]={186,186,189,181,190,177,193,173,196,167,199,163,201,160,203,157,201,154,196,149,193,145,190,141,186,138,182,135,178,133,175,130,170,127,170,132,
	170,137,171,146,172,152,174,161,178,169,181,176,-1};
	GLint b9[]={203,158,208,154,210,150,213,146,215,143,213,141,209,138,204,135,198,132,192,131,185,130,179,128,175,128,170,128,177,132,181,135,186,138,191,143,
	195,150,199,154,-1};
	GLint e1[]={261,218,264,215,269,210,272,207,274,204,276,202,279,198,281,196,283,194,285,190,288,189,292,191,296,195,297,198,300,202,298,206,296,210,293,212,
	289,216,285,219,279,220,274,221,269,221,263,221,-1};
	GLint e2[]={282,196,279,199,277,201,275,204,272,207,269,211,266,214,269,217,273,218,277,218,280,215,282,213,285,210,286,206,285,203,285,200,284,198,-1};
	GLint e3[]={212,189,210,191,208,193,205,196,204,198,201,202,202,205,206,210,209,215,214,217,219,219,224,221,229,221,233,221,237,221,240,218,237,214,234,211,
	230,207,227,203,220,198,215,192,217,195,-1};
	GLint e4[]={218,195,221,200,224,202,227,204,229,207,232,210,234,212,236,214,233,216,229,218,225,218,222,217,219,214,216,211,213,207,213,202,214,198,-1};
	GLint e5[]={243,236,247,238,252,238,255,238,258,236,257,234,253,233,250,232,246,233,-1};
	GLint e6[]={242,238,245,242,248,244,251,245,255,244,257,241,258,238,254,238,250,239,245,239,-1};
void bat()
{
	glPushMatrix();

	   glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(a1,0.545,0,0.545,0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(a2,0.545,0,0.545,0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(a3,0.545,0,0.545,0);
	glPopMatrix();

 	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(a4,0.545,0,0.545,0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,1);
	//glScalef(1,1,0);
	img(a5,0.600,0.196,0.800,0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(a6,0.576,0.439,0.859,0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(a7,0.545,0,0.545,0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(a8,0.545,0,0.545,0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(b1,0.545,0,0.545,0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(b2,0.545,0,0.545,0);
	glPopMatrix();

 	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(b3,0.545,0,0.545,0);
	glPopMatrix();


 	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(b4,0.545,0,0.545,0);
	glPopMatrix();

		glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(b5,0.294,0,0.510,0);
	glPopMatrix();

 		glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(b6,0.294,0,0.510,0);
	glPopMatrix();


 		glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(b7,0.576,0.439,0.859,0);
	glPopMatrix();

 		glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(b8,0.576,0.439,0.859,0);
	glPopMatrix();

			glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(b9,0.294,0,0.510,0);
	glPopMatrix();


			glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(e1,1,1,1,0);
	glPopMatrix();


			glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(e2,0,0,0,0);
	glPopMatrix();

				glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(e3,1,1,1,0);
	glPopMatrix();

				glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(e4,0,0,0,0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(e5,0.902,0.902,0.980,0);
	glPopMatrix();


 	glPushMatrix();
 	glTranslatef(0,200,0);
	//glScalef(1,1,0);
	img(e6,0,0,0,0);
	glPopMatrix();


	//outlines


			glPushMatrix();
	glPushMatrix();
	glTranslatef(0,200,1);
	//glScalef(1,1,0);
	img(a1,0.545,0,0.545,1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,1);
	//glScalef(1,1,0);
	img(a2,0.545,0,0.545,1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,1);
	//glScalef(1,1,0);
	img(a3,0.545,0,0.545,1);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0,200,1);
	//glScalef(1,1,0);
	img(a5,0.600,0.196,0.800,1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,1);
	//glScalef(1,1,0);
	img(a8,0.545,0,0.545,1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,1);
	//glScalef(1,1,0);
	img(b1,0.545,0,0.545,1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,200,1);
	//glScalef(1,1,0);
	img(b2,0.545,0,0.545,1);
	glPopMatrix();

 	glPushMatrix();
	glTranslatef(0,200,1);
	//glScalef(1,1,0);
	img(b3,0.545,0,0.545,1);
	glPopMatrix();


 	glPushMatrix();
	glTranslatef(0,200,1);
	//glScalef(1,1,0);
	img(b4,0.545,0,0.545,1);
	glPopMatrix();


 		glPushMatrix();
	glTranslatef(0,200,1);
	//glScalef(1,1,0);
	img(b7,0.576,0.439,0.859,1);
	glPopMatrix();

 		glPushMatrix();
	glTranslatef(0,200,1);
	//glScalef(1,1,0);
	img(b8,0.576,0.439,0.859,1);
	glPopMatrix();

 	glPopMatrix();
}
float leye_lash[][2]={86,176,309,284,312,289,312,296,310,299,308,305,302,312,296,320,289,326,283,331,277,335,269,340,265,343,260,346,152,345,142,337,135,333,127,323,120,315,114,301,105,287,97,271,90,255,85,238,83,223,81,207,82,191};
float leye_white[][2]={258,345,273,338,285,329,296,318,304,309,311,300,312,295,312,291,311,287,308,284,106,203,101,214,100,225,100,235,100,249,103,265,105,279,111,294,117,309,128,325,137,335,151,345};
float louter_eye_ball[][2]={150,220,145,231,143,243,142,269,144,286,149,300,157,314,166,325,180,335,195,340,208,341,218,338,229,334,238,327,246,320,253,309,258,300,262,290,264,280,265,267};
float linner_eye_ball[][2]={198,240,197,255,198,272,199,287,200,300,201,312,204,326,206,312,208,299,209,285,210,270,210,254,209,244};

float reye_lash[][2]={412,283,635,177,640,196,640,207,640,219,637,232,634,248,627,265,621,278,613,293,604,310,594,324,584,335,570,345,464,346,448,339,434,327,422,316,414,305,410,297,408,292,408,289};
float reye_white[][2]={414,283,614,203,618,215,620,230,621,245,619,261,615,277,610,295,603,311,595,322,587,332,579,340,569,346,465,347,445,336,435,328,425,319,416,308,411,300,409,293,408,289,410,285};
float router_eye_ball[][2]={455,268,457,281,461,294,467,308,476,321,489,332,502,339,514,341,525,341,539,336,553,325,565,312,572,297,577,281,579,265,579,251,577,236,574,227,570,220};
float rinner_eye_ball[][2]={512,244,510,254,511,264,511,276,512,288,513,299,514,309,517,326,520,308,522,295,522,282,523,268,523,258,523,249,522,240};

float mouth[][2]={115,392,104,396,95,413,89,430,83,453,85,476,90,495,98,515,112,537,131,560,151,577,173,594,198,609,224,623,261,638,294,647,314,649,337,650,360,650,383,648,409,645,429,639,448,633,470,626,489,619,505,610,526,598,555,580,582,560,602,531,619,502,628,475,634,449,632,427,625,405,615,392,603,390,589,392,574,398,557,406,534,414,518,420,498,426,478,430,454,435,434,438,415,441,393,442,373,443,350,443,327,441,303,440,283,439,258,434,242,431,225,426,209,420,190,414,171,407,152,400,136,395,123,391};
float mouth_white[][2]={105,412,99,430,93,453,93,468,95,482,104,506,138,547,141,555,182,587,217,607,274,635,293,642,310,644,352,638,381,631,411,621,443,606,465,593,479,586,506,566,529,547,555,520,569,503,586,481,605,447,619,415,616,411,606,411,598,411,577,415,527,430,496,442,443,452,414,456,383,459,369,458,353,458,330,458,302,456,289,453,252,447,224,440,204,436,173,425,148,417,130,413,119,411,111,410};
float teeth_up[][2]={124,396,118,418,115,441,115,462,117,484,121,503,125,520,130,535,139,555,145,537,153,510,160,490,171,467,180,453,189,444,198,434,199,449,198,472,198,496,199,520,201,546,204,568,208,588,215,607,222,584,226,564,233,539,249,504,261,483,270,469,285,453,285,474,286,496,288,520,290,544,293,565,296,585,299,600,303,616,309,633,315,615,319,592,326,562,334,530,341,504,347,486,352,470,359,453,369,475,376,498,383,521,389,544,394,566,399,590,404,611,409,633,418,608,423,583,427,563,429,542,431,523,432,501,434,473,435,451,450,470,463,490,472,504,480,523,490,550,493,566,498,581,502,605,513,578,517,554,520,530,521,507,521,483,521,464,520,447,519,431,540,451,554,477,562,496,569,515,573,529,576,540,580,559,589,537,594,519,600,498,603,476,604,455,603,437,601,421,599,406,595,396,565,406,541,416,516,424,494,430,475,434,457,437,440,440,425,443,410,443,389,445,373,445,353,444,334,445,316,444,290,441,269,437,252,433,227,429,210,423,194,418,178,412,164,406,147,400,126,393};
float shading1[][2]={174,426,160,447,154,466,148,490,144,507,141,522,141,546,154,505,166,479,177,458,189,442,199,432};
float shading2[][2]={254,448,247,459,240,472,235,487,229,504,224,523,221,543,218,560,216,575,216,596,216,604,225,564,232,545,238,528,245,513,252,498,259,485,267,475,272,465,278,458,282,453};
float shading3[][2]={332,459,327,478,322,503,317,529,314,554,311,573,311,592,311,613,312,623,318,593,322,576,327,557,332,536,337,517,341,503,344,491,347,479,350,469,355,459};
float shading4[][2]={414,457,415,475,416,493,417,516,417,543,415,567,414,585,413,604,411,625,422,590,426,565,430,542,431,521,433,501,433,484,434,473,434,455};
float shading5[][2]={495,441,498,456,501,475,503,494,505,513,505,530,506,549,507,563,508,577,506,604,515,573,517,550,520,529,521,506,521,485,521,468,520,454,520,443,519,436};
float shading6[][2]={578,416,580,430,584,450,585,468,586,487,586,500,586,513,586,523,585,532,581,555,597,509,601,485,603,465,604,451,604,433,601,421,600,412,599,408};
float shading7[][2]={119,411,113,426,110,441,106,459,105,476,104,493,105,507,108,525,137,554,128,529,124,512,119,493,116,475,116,462,116,450,116,439,117,430,118,420};
float shading8[][2]={200,433,195,446,191,462,186,481,183,503,181,522,180,542,181,562,182,578,183,593,216,613,206,585,203,564,201,544,199,527,198,513,198,495,199,481,199,465,199,453,199,439};
float shading9[][2]={285,454,281,469,278,482,276,498,274,514,272,530,272,550,272,570,272,588,274,605,275,618,276,629,290,631,307,632,302,614,298,595,295,577,292,559,290,541,288,523,287,507,286,489,286,477,286,463};
float shading10[][2]={362,460,381,635,393,636,402,633,409,632,406,620,402,601,398,586,394,569,390,550,387,536,383,521,379,507,375,493,372,482,368,472};
float shading11[][2]={438,454,447,472,454,487,462,507,467,525,472,545,476,563,479,581,480,595,482,615,503,606,497,581,492,559,487,542,482,528,475,514,469,501,461,489,456,480,449,469};
float shading12[][2]={522,433,530,449,537,465,545,485,552,506,557,524,560,545,561,574,579,560,577,539,571,520,565,505,559,490,554,477,548,465,541,455,534,445};
float mouth_extra[][2]={122,391,602,390,541,427,484,444,399,458,310,457,233,443,155,420};
float reye_brow[][2]={376,226,383,242,402,234,425,223,451,208,473,196,494,184,514,171,537,160,551,152,569,144,585,139,599,134,612,133,624,132,637,134,648,136,659,141,663,134,652,128,628,123,611,123,592,127,574,133,562,137,549,144,533,151,519,160,506,167,491,177,480,184,468,194,454,200,441,209,427,219,413,225,400,229,390,232,381,232};
float leye_brow[][2]={344,228,339,241,327,236,303,225,278,211,252,196,231,183,204,169,178,154,151,143,129,136,110,132,93,131,80,134,63,141,59,134,69,127,83,123,100,122,119,126,137,129,158,139,174,145,195,156,209,165,224,174,237,183,250,191,259,198,273,207,288,215,299,220,309,224,320,230,332,235,337,236};
void scary_face_f()
{
	int i,j;

	glPushMatrix();
	glTranslatef(304,350,5);
	glScalef(0.15,0.15,0.15);
	glRotatef(180,0,0,1);

	glPushMatrix();
	glTranslatef(0,0,3);
	//left eye labrowsh
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(leye_brow)/8;i++)
		glVertex2fv(leye_brow[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,3);
	//right eye labrowsh
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(reye_brow)/8;i++)
		glVertex2fv(reye_brow[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,0);
	//left eye lash
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(leye_lash)/8;i++)
		glVertex2fv(leye_lash[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,0);
	//right eye lash
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(reye_lash)/8;i++)
		glVertex2fv(reye_lash[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	//left eye white
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(leye_white)/8;i++)
		glVertex2fv(leye_white[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	//left eye white
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(reye_white)/8;i++)
		glVertex2fv(reye_white[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,2);
	//left outer eye ball
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(louter_eye_ball)/8;i++)
		glVertex2fv(louter_eye_ball[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,2);
	//right outer eye ball
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(router_eye_ball)/8;i++)
		glVertex2fv(router_eye_ball[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,3);
	//left outer eye ball outine
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(louter_eye_ball)/8;i++)
		glVertex2fv(louter_eye_ball[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,3);
	//right outer eye ball outline
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(router_eye_ball)/8;i++)
		glVertex2fv(router_eye_ball[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,3);
	//left inner eye ball
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(linner_eye_ball)/8;i++)
		glVertex2fv(linner_eye_ball[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,3);
	//right inner eye ball
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(rinner_eye_ball)/8;i++)
		glVertex2fv(rinner_eye_ball[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,0);
	//mouth black
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(mouth)/8;i++)
		glVertex2fv(mouth[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,2);
	//mouth extra (covering up)
	glColor3f(0.294,0.0,0.510);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(mouth_extra)/8;i++)
		glVertex2fv(mouth_extra[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40,70,1);
	glScalef(0.9,0.9,0.9);
	// white
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(mouth)/8;i++)
		glVertex2fv(mouth[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading7)/8;i++)
		glVertex2fv(shading7[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading8)/8;i++)
		glVertex2fv(shading8[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading9)/8;i++)
		glVertex2fv(shading9[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading10)/8;i++)
		glVertex2fv(shading10[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading11)/8;i++)
		glVertex2fv(shading11[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading12)/8;i++)
		glVertex2fv(shading12[i]);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading1)/8;i++)
		glVertex2fv(shading1[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading2)/8;i++)
		glVertex2fv(shading2[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading3)/8;i++)
		glVertex2fv(shading3[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading4)/8;i++)
		glVertex2fv(shading4[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading5)/8;i++)
		glVertex2fv(shading5[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading6)/8;i++)
		glVertex2fv(shading6[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//teeth_up
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(teeth_up)/8;i++)
		glVertex2fv(teeth_up[i]);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}
void scary_face_r()
{
	int i,j;

	glPushMatrix();
	glTranslatef(114,70,10);
	glScalef(0.15,0.15,0.15);
	//glRotatef(-180,0,0,1);

	glPushMatrix();
	glTranslatef(0,0,3);
	//left eye brows
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(leye_brow)/8;i++)
		glVertex2fv(leye_brow[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,3);
	//right eye brows
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(reye_brow)/8;i++)
		glVertex2fv(reye_brow[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,0);
	//left eye lash
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(leye_lash)/8;i++)
		glVertex2fv(leye_lash[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,0);
	//right eye lash
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(reye_lash)/8;i++)
		glVertex2fv(reye_lash[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	//left eye white
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(leye_white)/8;i++)
		glVertex2fv(leye_white[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	//left eye white
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(reye_white)/8;i++)
		glVertex2fv(reye_white[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,2);
	//left outer eye ball
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(louter_eye_ball)/8;i++)
		glVertex2fv(louter_eye_ball[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,2);
	//right outer eye ball
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(router_eye_ball)/8;i++)
		glVertex2fv(router_eye_ball[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,3);
	//left outer eye ball outine
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(louter_eye_ball)/8;i++)
		glVertex2fv(louter_eye_ball[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,3);
	//right outer eye ball outline
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(router_eye_ball)/8;i++)
		glVertex2fv(router_eye_ball[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,3);
	//left inner eye ball
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(linner_eye_ball)/8;i++)
		glVertex2fv(linner_eye_ball[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,3);
	//right inner eye ball
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(rinner_eye_ball)/8;i++)
		glVertex2fv(rinner_eye_ball[i]);
	glEnd();
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(75,55,10);
	glScalef(0.25,0.25,0.15);
	glPushMatrix();
	glTranslatef(0,20,0);
	//mouth black
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(mouth)/8;i++)
		glVertex2fv(mouth[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,2);
	//mouth extra (covering up)
	glColor3f(1.0,0.894,0.769);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(mouth_extra)/8;i++)
		glVertex2fv(mouth_extra[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40,70,1);
	glScalef(0.9,0.9,0.9);
	// white
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(mouth)/8;i++)
		glVertex2fv(mouth[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading7)/8;i++)
		glVertex2fv(shading7[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading8)/8;i++)
		glVertex2fv(shading8[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading9)/8;i++)
		glVertex2fv(shading9[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading10)/8;i++)
		glVertex2fv(shading10[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading11)/8;i++)
		glVertex2fv(shading11[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading12)/8;i++)
		glVertex2fv(shading12[i]);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading1)/8;i++)
		glVertex2fv(shading1[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading2)/8;i++)
		glVertex2fv(shading2[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading3)/8;i++)
		glVertex2fv(shading3[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading4)/8;i++)
		glVertex2fv(shading4[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading5)/8;i++)
		glVertex2fv(shading5[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//shading1
	glColor3f(0.863,0.078,0.235);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(shading6)/8;i++)
		glVertex2fv(shading6[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,20,3);
	//teeth_up
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(teeth_up)/8;i++)
		glVertex2fv(teeth_up[i]);
	glEnd();
	glPopMatrix();


	glPopMatrix();
}
void scary_face_s()
{
	int i,j;

	glPushMatrix();
	glTranslatef(44,275,5);
	glScalef(0.125,0.125,0.125);
	glRotatef(180,0,0,1);

//	glPushMatrix();
//	glTranslatef(0,0,3);
//	//left eye labrowsh
//	glColor3f(0,0,0);
//	glBegin(GL_LINE_LOOP);
//	for(i=0;i<sizeof(leye_brow)/8;i++)
//		glVertex2fv(leye_brow[i]);
//	glEnd();
//	glPopMatrix();
//
	glPushMatrix();
	glTranslatef(0,0,3);
	//right eye labrowsh
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(reye_brow)/8;i++)
		glVertex2fv(reye_brow[i]);
	glEnd();
	glPopMatrix();

//	glPushMatrix();
//	glTranslatef(0,0,0);
//	//left eye lash
//	glColor3f(0,0,0);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(leye_lash)/8;i++)
//		glVertex2fv(leye_lash[i]);
//	glEnd();
//	glPopMatrix();
//
	glPushMatrix();
	glTranslatef(0,0,0);
	//right eye lash
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(reye_lash)/8;i++)
		glVertex2fv(reye_lash[i]);
	glEnd();
	glPopMatrix();

//	glPushMatrix();
//	glTranslatef(0,0,1);
//	//left eye white
//	glColor3f(1,1,1);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(leye_white)/8;i++)
//		glVertex2fv(leye_white[i]);
//	glEnd();
//	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	//right eye white
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(reye_white)/8;i++)
		glVertex2fv(reye_white[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,2);
//	//left outer eye ball
//	glColor3f(1,0,0);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(louter_eye_ball)/8;i++)
//		glVertex2fv(louter_eye_ball[i]);
//	glEnd();
//	glPopMatrix();
//
	glPushMatrix();
	glTranslatef(0,0,2);
	//right outer eye ball
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(router_eye_ball)/8;i++)
		glVertex2fv(router_eye_ball[i]);
	glEnd();
	glPopMatrix();

//	glPushMatrix();
//	glTranslatef(0,0,3);
//	//left outer eye ball outine
//	glColor3f(0,0,0);
//	glBegin(GL_LINE_LOOP);
//	for(i=0;i<sizeof(louter_eye_ball)/8;i++)
//		glVertex2fv(louter_eye_ball[i]);
//	glEnd();
//	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,3);
	//right outer eye ball outline
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(router_eye_ball)/8;i++)
		glVertex2fv(router_eye_ball[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,3);
//	//left inner eye ball
//	glColor3f(0,0,0);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(linner_eye_ball)/8;i++)
//		glVertex2fv(linner_eye_ball[i]);
//	glEnd();
//	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,3);
	//right inner eye ball
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(rinner_eye_ball)/8;i++)
		glVertex2fv(rinner_eye_ball[i]);
	glEnd();
	glPopMatrix();

//	glPushMatrix();
//	glRotatef(10,0,1,0);
//
//	glPushMatrix();
//	glTranslatef(0,20,0);
//	//mouth black
//	glColor3f(0,0,0);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(mouth)/8;i++)
//		glVertex2fv(mouth[i]);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0,20,2);
//	//mouth extra (covering up)
//	glColor3f(0.294,0.0,0.510);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(mouth_extra)/8;i++)
//		glVertex2fv(mouth_extra[i]);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(40,70,1);
//	glScalef(0.9,0.9,0.9);
//	// white
//	glColor3f(1,1,1);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(mouth)/8;i++)
//		glVertex2fv(mouth[i]);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0,20,3);
//	//shading1
//	glColor3f(0.863,0.078,0.235);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(shading7)/8;i++)
//		glVertex2fv(shading7[i]);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0,20,3);
//	//shading1
//	glColor3f(0.863,0.078,0.235);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(shading8)/8;i++)
//		glVertex2fv(shading8[i]);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0,20,3);
//	//shading1
//	glColor3f(0.863,0.078,0.235);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(shading9)/8;i++)
//		glVertex2fv(shading9[i]);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0,20,3);
//	//shading1
//	glColor3f(0.863,0.078,0.235);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(shading10)/8;i++)
//		glVertex2fv(shading10[i]);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0,20,3);
//	//shading1
//	glColor3f(0.863,0.078,0.235);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(shading11)/8;i++)
//		glVertex2fv(shading11[i]);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0,20,3);
//	//shading1
//	glColor3f(0.863,0.078,0.235);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(shading12)/8;i++)
//		glVertex2fv(shading12[i]);
//	glEnd();
//	glPopMatrix();
//
//
//	glPushMatrix();
//	glTranslatef(0,20,3);
//	//shading1
//	glColor3f(0.863,0.078,0.235);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(shading1)/8;i++)
//		glVertex2fv(shading1[i]);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0,20,3);
//	//shading1
//	glColor3f(0.863,0.078,0.235);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(shading2)/8;i++)
//		glVertex2fv(shading2[i]);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0,20,3);
//	//shading1
//	glColor3f(0.863,0.078,0.235);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(shading3)/8;i++)
//		glVertex2fv(shading3[i]);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0,20,3);
//	//shading1
//	glColor3f(0.863,0.078,0.235);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(shading4)/8;i++)
//		glVertex2fv(shading4[i]);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0,20,3);
//	//shading1
//	glColor3f(0.863,0.078,0.235);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(shading5)/8;i++)
//		glVertex2fv(shading5[i]);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0,20,3);
//	//shading1
//	glColor3f(0.863,0.078,0.235);
//	glBegin(GL_POLYGON);
//	for(i=0;i<sizeof(shading6)/8;i++)
//		glVertex2fv(shading6[i]);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0,20,3);
//	//teeth_up
//	glColor3f(0,0,0);
//	glBegin(GL_LINE_LOOP);
//	for(i=0;i<sizeof(teeth_up)/8;i++)
//		glVertex2fv(teeth_up[i]);
//	glEnd();
//	glPopMatrix();
//
//	glPopMatrix();

	glPopMatrix();
}
float out_face[][2]={180,242,199,239,210,237,228,230,240,225,255,212,264,205,269,195,273,182,274,167,271,154,264,142,256,134,250,129,237,120,235,105,233,93,230,79,224,70,215,62,212,58,200,50,192,42,182,37,184,28,179,26,172,32,167,40,163,33,160,27,155,26,149,32,146,43,143,42,139,37,135,32,130,44,128,50,118,57,109,64,103,73,100,81,96,90,92,100,92,109,91,123,85,125,77,129,71,135,66,147,62,154,57,166,55,175,55,182,58,191,65,202,74,212,85,219,96,228,109,235,134,240,152,240,163,245};
float in_face[][2]={113,129,104,137,92,150,83,164,79,174,77,185,77,192,81,201,89,208,100,215,113,220,122,224,136,228,151,229,161,229,180,231,193,231,204,227,221,224,235,214,240,208,250,198,254,185,250,169,247,165,239,153,232,146,226,139,222,134,216,132,216,126,218,115,215,101,209,87,200,77,187,73,176,69,166,67,152,67,143,72,131,76,121,85,114,99,113,115};
float right_hand[][2]={53,181,42,197,38,212,33,228,29,243,26,265,23,279,23,294,25,313,27,330,33,351,40,360,47,377,55,389,61,389,68,381,72,391,80,392,85,379,90,389,97,393,101,376,108,380,116,389,123,383,123,364,117,345,117,331,121,312,120,297,117,278,115,261,112,248,110,237,102,231,88,225,78,216,69,208,61,199};
float left_hand[][2]={221,235,215,255,212,270,212,283,210,295,210,306,210,321,211,333,213,338,212,349,210,357,207,368,207,383,210,386,216,388,222,383,228,375,228,388,233,394,240,388,243,379,246,387,250,390,254,390,260,387,262,380,267,387,271,387,277,386,281,380,287,369,291,357,298,345,300,333,304,318,304,305,305,289,301,270,300,251,296,232,293,221,289,203,284,191,275,181,273,189,270,199,264,206,257,211,251,217,240,223,235,226,225,230};float ear1[][2]={76,129,68,129,61,123,61,116,63,111,67,104,71,97,82,96,90,103,90,112,91,122,85,127};
float ear2[][2]={251,129,262,129,268,123,267,114,263,106,257,100,251,97,245,99,239,104,239,112,237,115,242,126};
float leg1[][2]={139,352,128,349,117,343,121,361,124,380,130,397,130,404,131,410,137,404,140,396,138,377,134,364,134,355,131,352};
float leg2[][2]={190,349,197,355,194,367,190,384,190,400,194,409,198,411,199,401,202,392,206,383,207,374,207,364,209,354,211,349,210,346,200,348};
float fingers1[][2]={50,383,54,399,55,411,49,413,38,421,41,426,53,430,62,433,65,432,67,428,68,423,69,418,69,425,67,434,72,434,75,434,79,434,81,431,84,426,86,418,85,430,83,434,87,435,91,435,95,433,97,431,100,428,100,421,101,417,105,423,102,430,98,435,106,435,112,434,114,430,116,424,117,418,117,427,120,430,122,427,129,421,129,415,128,402,126,391,126,384,121,387,116,388,110,385,108,382,105,378,103,385,102,390,99,390,94,387,90,384,89,380,86,379,85,383,82,389,80,391,76,392,69,388,67,385,66,388,63,389,61,390};
float fingers2[][2]={208,381,203,390,198,407,201,427,208,427,214,429,213,420,215,426,221,433,226,433,232,433,229,425,227,418,231,426,234,432,236,433,239,433,245,433,245,431,244,425,242,417,247,425,249,434,252,434,258,434,261,434,263,433,263,430,260,424,258,417,261,422,262,425,267,434,275,434,279,433,282,429,287,425,288,416,281,407,276,406,273,408,273,404,274,395,275,388,273,388,268,389,263,384,258,385,255,391,249,392,247,386,244,380,241,379,238,385,234,391,229,387,226,384,226,380,224,378,221,382,217,385,212,387,210,383};
float stomach1[][2]={120,331,137,341,168,345,186,344,201,337,210,332,210,316,210,300,211,290,212,281,214,271,214,261,214,254,205,250,200,246,191,243,182,242,171,242,159,244,148,244,137,244,127,248,120,254,115,256,119,286,121,306};
float stomach2[][2]={111,234,130,239,141,242,157,242,177,241,196,240,210,238,217,234,217,244,216,256,212,265,212,282,212,296,210,308,210,327,210,337,210,345,196,349,183,350,166,351,150,351,136,351,120,343,117,337,121,321,119,304,119,285,115,264,114,249};
float nose1[][2]={142,147,142,142,144,139,146,137,150,136,153,137,155,140,157,142,157,144,157,147};
float nose2[][2]={174,148,174,144,174,140,176,138,179,136,182,136,185,137,187,139,188,142,188,144,188,147};
float nose_hole1[][2]={149,148,146,147,144,145,144,143,145,141,147,139,149,139,151,140,153,141,154,143,154,145,152,147};
float nose_hole2[][2]={176,146,175,144,176,142,177,140,179,139,181,140,183,141,185,144,184,146,182,148,180,148,178,148};
void gorilla()
{
	int i;
	gorilla_list=glGenLists(1);
	glNewList(gorilla_list,GL_COMPILE);
		glPushMatrix();
		glTranslatef(200,450,-150);
		glRotatef(180,0,0,1);

	glPushMatrix();
	glTranslatef(0,110,0);
	glColor3f(0.184,0.310,0.310);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(out_face)/8;i++)
	{
	glVertex2fv(out_face[i]);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,1);
	glColor3f(0.184,0.310,0.310);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(out_face)/8;i++)
	{
	glVertex2fv(out_face[i]);
	}
	glEnd();
	glPopMatrix();

	//outline
	glPushMatrix();
	glTranslatef(0,0,3);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(out_face)/8;i++)
	{
	glVertex2fv(out_face[i]);
	}
	glEnd();
	glPushMatrix();

	glPushMatrix();
	glTranslatef(0,0,3);
	glColor3f(1,0.894,0.769);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(in_face)/8;i++)
	{
	glVertex2fv(in_face[i]);
	}
	glEnd();
	glPushMatrix();

	//outline
	glPushMatrix();
	glTranslatef(0,0,3);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(in_face)/8;i++)
	{
	glVertex2fv(in_face[i]);
	}
	glEnd();
	glPushMatrix();

	glPushMatrix();
	glColor3f(0.184,0.310,0.310);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(left_hand)/8;i++)
	{
	glVertex2fv(left_hand[i]);
	}
	glEnd();
	glPushMatrix();

	glPushMatrix();
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(left_hand)/8;i++)
	{
	glVertex2fv(left_hand[i]);
	}
	glEnd();
	glPushMatrix();

	glPushMatrix();
	glColor3f(0.184,0.310,0.310);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(right_hand)/8;i++)
	{
	glVertex2fv(right_hand[i]);
	}
	glEnd();
	glPushMatrix();

	glPushMatrix();
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(right_hand)/8;i++)
	{
	glVertex2fv(right_hand[i]);
	}
	glEnd();
	glPushMatrix();

	glPushMatrix();
	glColor3f(1,0.894,0.769);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(ear1)/8;i++)
	{
	glVertex2fv(ear1[i]);
	}
	glEnd();
	glPushMatrix();

	glPushMatrix();
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(ear1)/8;i++)
	{
	glVertex2fv(ear1[i]);
	}
	glEnd();
	glPushMatrix();

	glPushMatrix();
	glColor3f(1,0.894,0.769);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(ear2)/8;i++)
	{
	glVertex2fv(ear2[i]);
	}
	glEnd();
	glPushMatrix();

	glPushMatrix();
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(ear2)/8;i++)
	{
	glVertex2fv(ear2[i]);
	}
	glEnd();
	glPushMatrix();

	glPushMatrix();
	glColor3f(0.184,0.310,0.310);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(leg1)/8;i++)
	{
	glVertex2fv(leg1[i]);
	}
	glEnd();
	glPushMatrix();

	glPushMatrix();
	glColor3f(0.184,0.310,0.310);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(leg2)/8;i++)
	{
	glVertex2fv(leg2[i]);
	}

	glEnd();
	glPushMatrix();

		glPushMatrix();
	glColor3f(1,0.894,0.769);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(fingers1)/8;i++)
	{
	glVertex2fv(fingers1[i]);
	}
	glEnd();
	glPopMatrix();

		glPushMatrix();
	glColor3f(1,0.894,0.769);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(fingers2)/8;i++)
	{
	glVertex2fv(fingers2[i]);
	}
	glEnd();
	glPopMatrix();


		glPushMatrix();
		glTranslatef(0,0,4);
	glColor3f(0.184,0.310,0.310);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(stomach2)/8;i++)
	{
	glVertex2fv(stomach2[i]);
	}
	glEnd();
	glPopMatrix();



		glPushMatrix();
		glTranslatef(0,0,5);
	glColor3f(1,0.894,0.769);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(stomach1)/8;i++)
	{
	glVertex2fv(stomach1[i]);
	}
	glEnd();
	glPopMatrix();

		glPushMatrix();
		glTranslatef(0,0,4);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(nose1)/8;i++)
	{
	glVertex2fv(nose1[i]);
	}
	glEnd();
	glPopMatrix();

		glPushMatrix();
		glTranslatef(0,0,4);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(nose2)/8;i++)
	{
	glVertex2fv(nose2[i]);
	}
	glEnd();
	glPopMatrix();

		glPushMatrix();
		glTranslatef(0,0,4);
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(nose_hole1)/8;i++)
	{
	glVertex2fv(nose_hole1[i]);
	}
	glEnd();
	glPopMatrix();

		glPushMatrix();
		glTranslatef(0,0,4);
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(nose_hole2)/8;i++)
	{
	glVertex2fv(nose_hole2[i]);
	}
	glEnd();
	glPopMatrix();

	glPopMatrix();
	glEndList();
}
int forest_guard()
{
	//alert();
	attack=1;

	if(movez==200)
	{
		printf("\nYOU DIDNT DEFEAT THE GUARD!");
		attack=0;
		repeat=1;
		hits[level-1]=0;
		movex=0;
		movez=0;
		xpos=150;
		ypos=0;
		zpos=7500;

	return 0;
	}
	else if(hits[level-1]==5)
	{
		printf("\nYou defeated the guard!");
		attack=0;
		xrot=temp_xrot;
		yrot=temp_yrot;
		congrats_msg=1;
		return 1;
	}
	glPushMatrix();
	glTranslatef(xpos+movex-250,-100,zpos-500+movez);
	glDisable(GL_LIGHTING);
	//glScalef(3,4,3);
	bat();
	scary_face_f();
	glEnable(GL_LIGHTING);
	glPopMatrix();

}
int rocky_guard()
{
	//alert();
	attack=1;

	if(movez==200)
	{
		printf("\nYOU DIDNT DEFEAT THE GUARD!");
		attack=0;
		repeat=1;
		hits[level-1]=0;
		movex=0;
		movez=0;
		xpos=-4100;
		ypos=0;
		zpos=-4500;
	return 0;
	}
	else if(hits[level-1]==5)
	{
		printf("\nYou defeated the guard!");
		attack=0;
		xrot=temp_xrot;
		yrot=temp_yrot;
		congrats_msg=1;
		return 1;
	}
	glPushMatrix();
	glTranslatef(xpos+movex,0,zpos-500+movez);
	//glScalef(3,4,3);
	glCallList(gorilla_list);
	scary_face_r();
	glPopMatrix();
}
int snow_guard()
{
	//alert();
	attack=1;

	if(movez==200)
	{
		printf("\nYOU DIDNT DEFEAT THE GUARD!");
		attack=0;
		repeat=1;
		hits[level-1]=0;
		movex=0;
		movez=0;
		xpos=5100;
		ypos=0;
		zpos=-11200;
	return 0;
	}
	else if(hits[level-1]==5)
	{
		printf("\nYou defeated the guard!");
		attack=0;
		xrot=temp_xrot;
		yrot=temp_yrot;
		congrats_msg=1;
		return 1;
	}
	glPushMatrix();
	glTranslatef(xpos+movex,0,zpos-500+movez);
	glDisable(GL_LIGHTING);
	//glScalef(3,4,3);
	//guard_snowman();
	fox();
	scary_face_s();
	glPopMatrix();
	glEnable(GL_LIGHTING);

}


void leaves(int a, int b, int c,int flag)
{
//	leaflist=glGenLists(1);
//	glNewList(leaflist,GL_COMPILE);
	glPushMatrix();
	glColor3f(0,0.392,0);

	//1 cone down
	glPushMatrix();
	glTranslatef(a,b+60,c);//(a,b+10,c)
	glScalef(0.5,2.0,0.5);
	glRotatef(270,1,0,0);
	glutSolidCone(100,50,10,10);//200,150,..
	glPopMatrix();

	if(flag==2)//snow
	{glColor3f(1,0.98,0.98);
	glPushMatrix();
	glTranslatef(a,b+80,c);//(a,b+10,c)
	glScalef(0.5,2.0,0.5);
	glRotatef(270,1,0,0);
	glutSolidCone(100,50,10,10);//200,150,..
	glPopMatrix();
	}
	//2cone up
		glPushMatrix();

	glColor3f(0,0.392,0);
	glTranslatef(a,b+105,c);//(a,b+95,c)
	glScalef(0.5,2.0,0.5);
	glRotatef(270,1,0,0);
	glutSolidCone(100,50,10,10);//(200,150,100,100);
	glPopMatrix();

	if(flag==2)//snow
	{glColor3f(1,0.98,0.98);
	glPushMatrix();
	glTranslatef(a,b+65+70,c);//(a,b+95,c)
	glScalef(0.5,2.0,0.5);
	glRotatef(270,1,0,0);
	glutSolidCone(100,50,10,10);//(200,150,100,100);
	glPopMatrix();
	}


	glPopMatrix();
//	glEndList();
}
void tree(int a, int b, int c,int flag)
{
//	treelist=glGenLists(1);
//	glNewList(treelist,GL_COMPILE);
    glPushMatrix();

    if(flag==1)//maze forest
    glColor3f(0.545,0.271,0.075);
    if(flag==2)//snow
    glColor3f(0.663,0.663,0.663);

	glTranslatef(a,b,c);
	glScalef(1,20,1);
	glRotatef(90,1,0,0);
	glutSolidTorus(5,10,100,100);//(38,68,100,100);
	glPopMatrix();


	leaves(a,b,c,flag);
//	glEndList();
}
void mountain(int x_val, int z_val, int b, int h)
{
	glPushMatrix();
	glColor3f(0.545,0.271,0.075);

	glPushMatrix();
	glScalef(0.7,0.7,0.7);
	glRotatef(270,1,0,0);
	glTranslatef(x_val,z_val,0);
	glutSolidCone(b,h,10,10);
	glPopMatrix();

	glPopMatrix();
}

void path(int a, int b)
{
	glPushMatrix();
	glColor3f(0.741,0.718,0.420);//dark khaki
	glTranslatef(a,0,b);
	glScalef(1,0.01,1);
	glutSolidCube(100);
	glPopMatrix();
}
int is_pathway(int a, int b, int flag)//(x,y)
{
	int pathway_mf[12][2]={-150,-170,  -150,30,
	-50,-70,  -50,130,  -50,330,
	50,230,
	150,130,  150,330, 150,-170,
	250,-70,  250,30,  250,230};
	int pathway_sf[17][2]={-700,-900,
	-800,-800, -600,-800,
	-900,-700,
	-800,-600,
	-700,-500,
	-800,-400, -500,-400,
	-700,-300, -600,-300, -400,-300,
	-800,-200, -400,-200, -300,-200,
	-500,-100};
	int i,j;

	if(flag==2)
	for(j=0;j<17;j++)
			if(a==pathway_sf[j][0] && b==pathway_sf[j][1])
				return 1;

	if(flag==1)
	for(i=0;i<12;i++)
			if(a==pathway_mf[i][0] && b==pathway_mf[i][1])
				return 1;


	return 0;
}
void guard_snowman()
{
	glPushMatrix();
	glTranslatef(0,50,0);
	//body
     glPushMatrix();
     glColor3f(1,1,1);
     glTranslatef(0,0,0);
     glScalef(1.5,1,1.5);
     glutSolidSphere(100.0,100,100);
     glPopMatrix();

     //head
     glPushMatrix();
     glColor3f(1,1,1);
     glTranslatef(0,130,0);
     glScalef(1.5,1,1.5);
     glutSolidSphere(50.0,100,100);
     glPopMatrix();

     glPopMatrix();
 }
void normal_snowman()
{
	//body
     glPushMatrix();
     glColor3f(1,1,1);
     glTranslatef(0,0,0);
     glScalef(1.5,1,1.5);
     glutSolidSphere(100.0,100,100);
     glPopMatrix();

     //head
     glPushMatrix();
     glColor3f(1,1,1);
     glTranslatef(0,130,0);
     glScalef(1.5,1,1.5);
     glutSolidSphere(50.0,100,100);
     glPopMatrix();

    //eye1
    glPushMatrix();
     glColor3f(0,0,0);
     glTranslatef(-30,150,65);
     glutSolidSphere(5.0,100,100);
     glPopMatrix();

	//eye2
	 glPushMatrix();
     glColor3f(0,0,0);
     glTranslatef(30,150,65);
     glutSolidSphere(5.0,100,100);
     glPopMatrix();

     //nose
      glPushMatrix();
     glColor3f(1,0,0);
     glTranslatef(0,130,70);
     glScalef(2,2,3);
     glutSolidCone(3.0,15.0,100,100);
     glPopMatrix();
//     //button1
//      glPushMatrix();
//     glColor3f(0,0,0);
//     glTranslatef(0,80,95);
//     glutSolidSphere(5.0,100,100);
//     glPopMatrix();
//     //button2
//       glPushMatrix();
//     glColor3f(0,0,0);
//     glTranslatef(0,40,140);
//     glutSolidSphere(5.0,100,100);
//     glPopMatrix();
//     //button 3
//        glPushMatrix();
//     glColor3f(0,0,0);
//     glTranslatef(0,0,150);
//     glutSolidSphere(5.0,100,100);
//     glPopMatrix();

}
void snow_forest()
{
	snowforestlist=glGenLists(1);
	glNewList(snowforestlist,GL_COMPILE);
	int i,j;
	for(i=-900;i<=-300;i+=100)//z values
		for(j=-600;j<=-100;j+=100)//x values
		{
			if(is_pathway(i,j,2))
			{
				path(j,i);
				continue;
			}
			tree(j,50,i,2);
		}

	for(i=-900;i<=-600;i+=100)//z values
		for(j=-900;j<=-400;j+=100)//x values
		{
			if(is_pathway(i,j,2))
			{
				path(j,i);
				continue;
			}
			tree(j,50,i,2);
		}
	glEndList();
}
void maze_forest()
{
	int i,j;
	maze_forestlist=glGenLists(1);
	glNewList(maze_forestlist,GL_COMPILE);
	for(i=-170;i<=350;i+=100)//z values
		for(j=-250;j<=350;j+=100)//x values
		{
			if(is_pathway(j,i,1))
			{
				path(j,i);
				continue;
			}

			tree(j,50,i,1);
		}
	tree(-300,50,380,1);
	tree(-200,50,380,1);
	tree(300,50,380,1);
	tree(400,50,380,1);

	for(i=-300;i<=400;i+=100)
		tree(i,50,-220,1);
glEndList();
}
//void random_trees()
//{
//	random_treeslist=glGenLists(1);
//	glNewList();
//
//}
void cave()
{
	cavelist=glGenLists(1);
glNewList(cavelist,GL_COMPILE);
	glColor3f(0.412,0.412,0.412);
	glPushMatrix();
	glTranslatef(-850,20,840);
	glScalef(3,2.5,15);
	glutSolidTorus(58,98,10,10);
	glPopMatrix();
glEndList();
}
void processSpecialKeys(int key, int xx, int yy)
{
if(attack==0)
{
 	if (key==GLUT_KEY_UP)
    {
    start=1;
    repeat=0;
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos += 200*float(sin(yrotrad)) ;
    zpos -= 200*float(cos(yrotrad)) ;
    ypos -= 200*float(sin(xrotrad)) ;
    }

    if (key==GLUT_KEY_DOWN)
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * 3.141592654f);
    xrotrad = (xrot / 180 * 3.141592654f);
    xpos -= 200*float(sin(yrotrad));
    zpos += 200*float(cos(yrotrad)) ;
    ypos += 200*float(sin(xrotrad));
    }

    if (key==GLUT_KEY_RIGHT)
    {
    yrot += 10;
    if (yrot >360) yrot -= 360;
    }

    if (key==GLUT_KEY_LEFT)
    {
    yrot -= 10;
    if (yrot < -360)yrot += 360;
    }
}
	glutPostRedisplay();
}

void assign_position(struct gem &g, float x, float y, float z)
{
	g.pos[0]=x;
	g.pos[1]=y;
	g.pos[2]=z;
}
void collect(double a, double b,int v)
{
	glPushMatrix();
	glColor3fv(gems_main[v].color);
	glTranslated(a,20,b);
	glScalef(3,4,3);
	glRotatef(theta,0,1,0);
	glutSolidOctahedron();
	glPopMatrix();

}
void collect_r(double a, double b,int v)
{
	glPushMatrix();
	glTranslatef(-2000,30,-1700);
	glScalef(10,1,15);
	glRotatef(-180,1,0,0);

	glPushMatrix();
	glColor3fv(gems_rocky[v].color);
	glTranslatef(a,20,b);
	glScalef(3*2/10.0,4*2,3*2/15.0);
	glRotatef(theta,0,1,0);
	glutSolidOctahedron();
	glPopMatrix();

	glPopMatrix();


}
void collect_s(double a, double b,int v)
{

	glPushMatrix();
	glTranslatef(-1000,0,-8000);
	glScalef(10,1,10);
	glRotatef(-45,0,1,0);

	glPushMatrix();
	glTranslatef(a,20,b);
	glColor3fv(gems_snowy[v].color);
	glScalef(3*2/10.0,4*2,3*2/10.0);
	glRotatef(theta,0,1,0);
	glutSolidOctahedron();
	glPopMatrix();

	glPopMatrix();


}
void collectibles_1()
{
	int i,j,k=0;
	//assigning colours
	for(i=0;i<gm;i++)
	{
		gems_main[i].color[0]=gcolor[gems_main[i].flag][0];
		gems_main[i].color[1]=gcolor[gems_main[i].flag][1];
		gems_main[i].color[2]=gcolor[gems_main[i].flag][2];
	}
	//creating main gems
	for(j=430;j<2530;j+=400,k++)//5
	{
		collect(50,j,k);
	}
	//towards pond
		collect(450,1130,k);k++;
		collect(750,930,k);k++;
	//towards cave
	for(i=-50;i>-950;i-=400,k++)
		collect(i,2030,k);
		collect(-850,1930,k);

	//assigning collect positions
	assign_position(gems_main[0],150,0,1350);
	assign_position(gems_main[1],150,0,2550);
	assign_position(gems_main[2],150,0,3750);
	assign_position(gems_main[3],150,0,4950);
	assign_position(gems_main[4],150,0,6150);
	assign_position(gems_main[5],150,0,7350);
	assign_position(gems_main[6],1300,0,3379);
	assign_position(gems_main[7],2253,0,2805);
	assign_position(gems_main[8],-132,0,6101);
	assign_position(gems_main[9],-1309,0,6043);
	assign_position(gems_main[10],-2475,0,6094);
	assign_position(gems_main[11],-2566,0,5805);
}
void collectibles_2()
{
	int i,j;
	//assigning colours
	for(i=0;i<gr;i++)
	{
		gems_rocky[i].color[0]=gcolor[gems_rocky[i].flag][0];
		gems_rocky[i].color[1]=gcolor[gems_rocky[i].flag][1];
		gems_rocky[i].color[2]=gcolor[gems_rocky[i].flag][2];
	}


	//creating rocky gems
	collect_r((23+56)/2.0,(30+30)/2.0,0);
	collect_r((53+36)/2.0,(75+75)/2.0,1);
	collect_r((92+92)/2.0,(90+120)/2.0,2);
	collect_r((148+148)/2.0,(70+90)/2.0,3);
	collect_r((230+225)/2.0,(60+90)/2.0,4);
	collect_r((276+246)/2.0,(90+120)/2.0,5);
	collect_r((299+322)/2.0,(20+45)/2.0,6);
	collect_r((368+368)/2.0,(0+30)/2.0,7);
	collect_r((424+404)/2.0,(70+65)/2.0,8);
	collect_r((424+404)/2.0,(120+100)/2.0,9);


		//assigning rocky gems' positions
	assign_position(gems_rocky[0],-4714,0,-6341);
	assign_position(gems_rocky[1],-4613,0,-8342);
	assign_position(gems_rocky[2],-3314,0,-9770);
	assign_position(gems_rocky[3],-1659,0,-8755);
	assign_position(gems_rocky[4],688,0,-8418);
	assign_position(gems_rocky[5],1749,0,-9682);
	assign_position(gems_rocky[6],3149,0,-6610);
	assign_position(gems_rocky[7],4915,0,-5801);
	assign_position(gems_rocky[8],6372,0,-8064);
	assign_position(gems_rocky[9],6449,0,-9975);
}
void collectibles_3()
{
	int i,j;
	//assigning colours
	for(i=0;i<gs;i++)
	{
		gems_snowy[i].color[0]=gcolor[gems_snowy[i].flag][0];
		gems_snowy[i].color[1]=gcolor[gems_snowy[i].flag][1];
		gems_snowy[i].color[2]=gcolor[gems_snowy[i].flag][2];
	}

	//creating snowy gems
	collect_s((23+56)/2.0,(30+30)/2.0,0);
	collect_s((53+36)/2.0,(75+75)/2.0,1);
	collect_s((92+92)/2.0,(90+120)/2.0,2);
	collect_s((148+148)/2.0,(70+90)/2.0,3);
	collect_s((230+225)/2.0,(60+90)/2.0,4);
	collect_s((276+246)/2.0,(90+120)/2.0,5);
	collect_s((299+322)/2.0,(20+45)/2.0,6);
	collect_s((368+368)/2.0,(0+30)/2.0,7);
	collect_s((424+404)/2.0,(70+65)/2.0,8);
	collect_s((424+404)/2.0,(120+100)/2.0,9);

	//assign collect positions
	assign_position(gems_snowy[9],3591,0,-12782);
	assign_position(gems_snowy[8],4326,0,-13712);
	assign_position(gems_snowy[7],4535,0,-15700);
	assign_position(gems_snowy[6],3036,0,-16660);
	assign_position(gems_snowy[5],393,0,-16117);
	assign_position(gems_snowy[4],258,0,-17487);
	assign_position(gems_snowy[3],-1506,0,-19104);
	assign_position(gems_snowy[2],-3182,0,-19751);
	assign_position(gems_snowy[1],-3830,0,-21361);
	assign_position(gems_snowy[0],-2864,0,-22513);
}
void entry_path(int a, int b)
{
	glPushMatrix();
	glColor3f(0.741,0.718,0.420);
	glTranslatef(a,0,b);
	glScalef(1,0.01,1);
	glutSolidCube(100);
	glPopMatrix();
}
void entrance()
{
	int i,j;
	entrancelist=glGenLists(1);
glNewList(entrancelist,GL_COMPILE);
	//pathways
	for(j=430;j<2530;j+=100)
		entry_path(50,j);
	for(i=50;i<750;i+=100)
		entry_path(i,1130);
	for(j=930;j<1230;j+=100)
		entry_path(750,j);
	for(i=-50;i>-950;i-=100)
		entry_path(i,2030);
	for(j=1930;j>1530;j-=100)
		entry_path(-850,j);
glEndList();

}
void lotus_leaf(int a, int b, int c)
{
	glPushMatrix();
	glColor3f(0,0.3,0);
	glTranslatef(a+15,b-10,c);
    glScalef(1.5,0.1,1);
    glRotatef(90,0,0,1);
    glutSolidSphere(10.0,100,100);
    glPopMatrix();

    glPushMatrix();
	glColor3f(0,0.3,0);
	glTranslatef(a-15,b-10,c);
    glScalef(1.5,0.1,1);
    glRotatef(90,0,0,1);
    glutSolidSphere(10.0,100,100);
    glPopMatrix();
}

void petal(float scale_x, float scale_y,float scale_z)
{
     glPushMatrix();
     glScalef(scale_x,scale_y,scale_z);
     glutSolidSphere(10.0,100,100);
     glPopMatrix();
}
void flower(int a, int b, int c, char type)
{
	if(type=='f')
	{
		scale_x=0.5;
		scale_y=2;
		scale_z=0.5;
	}
	else if(type=='g')
	{
		scale_x=0.08;
		scale_y=0.5;
		scale_z=0.08;
	}
	//first petal
    glPushMatrix();
    glTranslatef(a,b,c);
    glPushMatrix();
     petal(scale_x,scale_y,scale_z);
    glPopMatrix();
    glPopMatrix();

    //fourth petal
    glPushMatrix();
    glTranslatef(a-5,b,c);
    glRotatef(30,0,0,1);
    petal(scale_x,scale_y,scale_z);
    glPopMatrix();


   //seventh
    glPushMatrix();
    glTranslatef(a+5,b,c);
    glRotatef(-30,0,0,1);
    petal(scale_x,scale_y,scale_z);
    glPopMatrix();
}
void floor()
{
	int j;
	glColor3f(0.486,0.988,0);//lawn green

		glPushMatrix();
		glScalef(0.01,0.01,0.01);
		flower(0,10,1930,'g');
		glPopMatrix();

}
void pond()
{
	pondlist=glGenLists(1);
	glNewList(pondlist,GL_COMPILE);

	glColor3f(1,0,0);
	flower(550,10,-70,'f');
	lotus_leaf(550,10,-70);

	glColor3f(1,0,0);
	flower(650,10,-170,'f');
	lotus_leaf(650,10,-170);

	glColor3f(1,0,0);
	flower(700,10,-100,'f');
	lotus_leaf(700,10,-100);

	glColor3f(1,0,0);
	flower(600,10,-50,'f');
	lotus_leaf(600,10,-50);

	glColor3f(1,0,0);
	flower(700,10,300,'f');
	lotus_leaf(700,10,300);

	glColor3f(1,0,0);
	flower(750,10,350,'f');
	lotus_leaf(750,10,350);

	glColor3f(1,0,0);
	flower(800,10,450,'f');
	lotus_leaf(800,10,450);

	glColor3f(1,0,0);
	flower(850,10,400,'f');
	lotus_leaf(850,10,400);

	glColor3f(1,0,0);
	flower(900,10,380,'f');
	lotus_leaf(900,10,380);

	glEndList();
}
void fence(int a, int b, int c,int flag)
{
	if(flag==1){
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(a,b,c);
	glScalef(0.33,10,3);
	glutSolidCube(10);
	glPopMatrix();
	}
	if(flag==2){
	glPushMatrix();
	glColor3f(1,1,1);
	glTranslatef(a,b,c);
	glRotatef(-270,0,1,0);
	glScalef(0.33,10,2);
	glutSolidCube(10);
	glPopMatrix();
	}
}
void fencing()
{
	int i,j;
	for(j=450;j<750;j+=50)
		fence(420,0,j,1);
	for(i=430;i<800;i+=50)
		fence(i,0,780,2);
}
void rotate_magic_cube(int v)
{
	theta+=20.0;
	if(theta>=360)
		theta=0.0;
	glutTimerFunc(1,rotate_magic_cube,0);
}
void move_guard(int v)
{
	if(move_flag==0)
		movex+=10;
	if(movex>100 && move_flag==0)
	{
		move_flag=1;
		movex-=10;
	}
	if(movex>=-100 && move_flag==1)
	{
		movex-=10;
	}
	if(movex<-100 && move_flag==1)
	{
		move_flag=0;
		movex+=10;
	}
	glutTimerFunc(20,move_guard,0);
}
float cube_vertices[][3]={{-1,-1,1},{1,-1,1},{1,1,1},{-1,1,1},{-1,1,-1},{1,1,-1},{1,-1,-1},{-1,-1,-1}},
cube_colors_before[][3]={{0.863,0.078,0.235},{1,0,0},{1,0.271,0},{1,0.647,0},{1,0.843,0},{1,1,0},{0.98,0.502,0.447},{1,0.498,0.314}},
cube_colors_after[][3]={{0,0,0.545},{0,0,1},{0.118,0.565,1},{0.294,0,0.510},{0.502,0,0.502},{0.729,0.333,0.827},{0.541,0.169,0.886},{0.545,0,0.545}};
void polygon(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glColor3fv(cube_colors_before[a]);
	glVertex3fv(cube_vertices[a]);
	glColor3fv(cube_colors_before[b]);
	glVertex3fv(cube_vertices[b]);
	glColor3fv(cube_colors_before[c]);
	glVertex3fv(cube_vertices[c]);
	glColor3fv(cube_colors_before[d]);
	glVertex3fv(cube_vertices[d]);
	glEnd();
}
void polygon_after(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glColor3fv(cube_colors_after[a]);
	glVertex3fv(cube_vertices[a]);
	glColor3fv(cube_colors_after[b]);
	glVertex3fv(cube_vertices[b]);
	glColor3fv(cube_colors_after[c]);
	glVertex3fv(cube_vertices[c]);
	glColor3fv(cube_colors_after[d]);
	glVertex3fv(cube_vertices[d]);
	glEnd();
}
void magic_cube(int a, int b, int c, int id)
{
	if(magic_cube_collected[id]==0)
	{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(a,b,c);
	glScalef(10,5,10);
	glRotatef(45,0,0,1);
	glRotatef(theta,0,1,0);
//	glutSolidCube(20);
	polygon(0,1,2,3);
	polygon(4,5,6,7);
	polygon(2,3,4,5);
	polygon(0,1,6,7);
	polygon(1,2,5,6);
	polygon(0,3,4,7);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	}
	else
	{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glTranslatef(a,b,c);
	glScalef(10,5,10);
	glRotatef(45,0,0,1);
	glRotatef(theta,0,1,0);
//	glutSolidCube(20);
	polygon_after(0,1,2,3);
	polygon_after(4,5,6,7);
	polygon_after(2,3,4,5);
	polygon_after(0,1,6,7);
	polygon_after(1,2,5,6);
	polygon_after(0,3,4,7);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	}
}
void rocky()
{
	rockylist=glGenLists(1);
glNewList(rockylist,GL_COMPILE);
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(0.545,0.271,0.075);//saddle brown
	glTranslatef(-2000,1,-1700);
	glScalef(10,1,15);
	glRotatef(-180,1,0,0);

	glBegin(GL_TRIANGLE_STRIP);

	glVertex3f(46,0,0);//1
	glVertex3f(92,1,0);
	glVertex3f(23,0,30);
	glVertex3f(56,0,30);

	glColor3f(0.722,0.525,0.043);//dark golden rod

	glVertex3f(56,1,75);//2
	glVertex3f(36,0,75);

	glColor3f(0.722,0.525,0.043);//dark golden rod
	glVertex3f(92,0,90);//3
	glColor3f(0.855,0.647,0.125);//golden rod
	glVertex3f(92,0,120);

	glColor3f(0.545,0.271,0.075);//saddle brown

	glVertex3f(148,0,70);//4
	glVertex3f(148,0,90);

	glColor3f(0.722,0.525,0.043);//dark golden rod

	glVertex3f(230,0,60);//5
	glVertex3f(225,0,90);

	glColor3f(0.722,0.525,0.043);//dark golden rod
	glVertex3f(276,0,90);//6
	glColor3f(0.855,0.647,0.125);//golden rod
	glVertex3f(246,0,120);

	glColor3f(0.545,0.271,0.075);//saddle brown

	glVertex3f(299,0,120);//7

	glColor3f(0.722,0.525,0.043);//dark golden rod

	glVertex3f(299,0,20);//8
	glVertex3f(322,0,45);

	glColor3f(0.722,0.525,0.043);//dark golden rod
	glVertex3f(368,0,0);//9
	glColor3f(0.855,0.647,0.125);//golden rod
	glVertex3f(368,0,30);
	glColor3f(0.545,0.271,0.075);//saddle brown

	glVertex3f(424,0,70);//10
	glVertex3f(404,0,65);

	glVertex3f(424,0,120);//11
	glVertex3f(404,0,100);

	glColor3f(0.741,0.718,0.420);//dark khaki

	glVertex3f(368,0,150);//12
	glVertex3f(332,0,150);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1700,0,-2000);
	glRotatef(40,0,1,0);
	mountain(200,1040,200,400);//left
	mountain(1050,1010,300,600);//right
	mountain(600,1010,400,800);//mid
	glPopMatrix();



	//small mountains
	glPushMatrix();
	glTranslatef(-1700,0,-2000);
	glRotatef(40,0,1,0);
	mountain(200,1040,200,400);//left
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-500,0,-2000);
	glRotatef(40,0,1,0);
	mountain(200,1040,200,400);//left
	glPopMatrix();

	glPushMatrix();
	glTranslatef(300,0,-2700);
	glRotatef(40,0,1,0);
	mountain(200,1040,200,400);//left
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1700,0,-2000);
	glRotatef(40,0,1,0);
	mountain(200,1040,200,400);//left
	glPopMatrix();


	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(500,0,-2000);
	glRotatef(40,0,1,0);
	mountain(200,1040,200,400);//left
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(-500,0,-1500);
	glRotatef(40,0,1,0);
	mountain(600,1010,400,800);//mid
	glPopMatrix();


	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(-1000,0,-2000);
	glRotatef(40,0,1,0);
	mountain(200,1040,200,400);//left
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(950,0,-2000);
	glRotatef(40,0,1,0);
	mountain(200,1040,200,400);//left
	glPopMatrix();


	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(0,1000,-2000);
	glRotatef(40,0,1,0);
	mountain(600,1010,400,800);//mid
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(-1000,2000,-2000);
	glRotatef(40,0,1,0);
	mountain(200,1040,200,400);//left
	glPopMatrix();


glEndList();
}
void snowy()
{
	snowylist=glGenLists(1);
glNewList(snowylist,GL_COMPILE);
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(0.741,0.718,0.420);
	glTranslatef(-1000,1,-8000);
	glScalef(10,1,10);
	glRotatef(-45,0,1,0);
	glBegin(GL_TRIANGLE_STRIP);

	glVertex3f(46,0,0);//1
	glVertex3f(92,0,0);
	glVertex3f(23,0,30);
	glVertex3f(56,0,30);

	glVertex3f(56,0,75);//2
	glVertex3f(36,0,75);

	glVertex3f(92,0,90);//3
	glVertex3f(92,0,120);

	glVertex3f(148,0,70);//4
	glVertex3f(148,0,90);

	glVertex3f(230,0,60);//5
	glVertex3f(225,0,90);

	glVertex3f(276,0,90);//6
	glVertex3f(246,0,120);

	glVertex3f(299,0,120);//7

	glVertex3f(299,0,20);//8
	glVertex3f(322,0,45);

	glVertex3f(368,0,0);//9
	glVertex3f(368,0,30);

	glVertex3f(424,0,70);//10
	glVertex3f(404,0,65);

	glVertex3f(424,0,120);//11
	glVertex3f(404,0,100);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2035,1,-7950);
	glScalef(10,1,10);
	glRotatef(-80,0,1,0);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(424,0,120);//11
	glVertex3f(404,0,100);
	glVertex3f(368,0,150);//12
	glVertex3f(332,0,150);
	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();

glEndList();
}
float layer_1[][2]={1,85,3,86,6,88,9,87,11,86,15,85,20,82,23,80,26,78,29,74,33,70,36,65,39,63,42,59,47,55,50,51,54,49,58,46,63,42,66,44,69,47,71,51,72,53,75,58,78,61,82,66,83,70,87,73,89,77,92,80,95,81,98,82,101,81,103,79,110,80,114,76,118,77,121,73,127,75,129,71,135,70,137,67,141,64,144,62,149,59,150,57,151,54,155,51,160,47,164,45,170,42,173,44,175,44,201,73,214,74,215,72,216,74,220,73,222,69,224,66,227,63,233,57,242,74,245,71,247,70,249,67,252,64,254,61,257,60,262,64,266,71,272,79,276,75,279,77,279,75,282,78,287,78,292,78,296,78,300,79,299,166,1,166};
float layer_1s[][2]={1,85,3,88,8,89,10,87,12,87,16,84,19,84,23,80,26,79,28,77,31,74,32,71,32,68,36,65,39,62,40,60,43,56,45,54,49,51,52,49,55,47,57,45,59,44,62,43,65,45,68,48,69,50,71,56,72,61,73,64,74,66,75,69,77,72,78,74,80,76,85,80,88,82,91,82,94,81,96,79,99,83,103,79,107,81,110,79,111,76,113,75,116,77,118,77,119,75,120,73,122,74,124,74,126,74,128,71,132,71,134,71,136,68,138,66,140,65,143,64,147,61,150,58,151,55,152,53,154,49,158,47,161,46,165,43,167,42,169,41,171,42,175,45,177,51,177,55,179,60,180,62,183,63,186,66,190,71,194,72,197,72,201,75,204,75,210,76,214,73,216,74,218,74,221,73,221,70,222,67,224,65,226,63,228,61,230,59,232,57,235,63,236,68,238,73,240,76,242,77,243,75,244,73,246,71,248,70,250,67,253,65,256,62,259,61,259,63,261,67,261,69,263,71,264,73,265,75,268,78,272,80,274,80,277,76,280,78,282,76,284,77,288,77,290,79,296,81,299,80,299,167,0,164};
float layer_2[][2]={1,91,6,94,11,94,23,97,27,91,29,96,31,93,34,93,38,89,43,88,43,85,45,86,46,83,48,85,50,82,52,85,60,92,60,89,62,92,65,90,67,93,72,93,72,90,74,93,77,91,78,87,81,92,83,95,85,90,88,98,90,89,91,97,95,97,97,90,99,96,101,89,103,95,109,89,113,87,121,87,129,89,132,91,136,89,139,86,139,82,143,86,145,84,145,81,147,88,150,88,154,89,155,81,157,87,160,88,163,83,164,88,168,82,170,88,172,90,174,86,175,90,179,89,181,83,184,89,186,83,188,87,191,87,191,85,194,87,198,87,204,85,208,83,212,81,216,82,218,83,223,86,224,83,226,86,229,85,232,82,235,82,235,80,238,83,240,85,244,86,244,83,246,82,247,86,252,89,254,88,254,84,257,89,262,89,264,85,266,89,267,84,269,88,273,90,280,90,287,92,294,93,299,93,299,166,1,166};
float layer_3[][2]={0,118,3,108,8,119,11,114,25,109,29,98,31,107,33,104,37,95,38,99,41,102,43,97,44,92,45,96,49,102,49,96,50,91,52,98,55,100,57,100,58,95,60,98,63,99,64,95,65,90,67,98,67,100,72,100,73,97,73,93,75,100,78,99,81,97,82,93,84,89,87,94,88,104,91,102,95,102,98,102,102,102,106,102,109,100,111,96,112,100,114,104,118,104,122,102,123,96,125,103,127,105,131,105,134,101,134,98,136,100,140,98,143,95,149,92,153,93,157,94,161,94,163,90,165,88,166,92,170,94,172,94,172,90,174,96,176,97,179,97,183,96,186,94,189,95,193,97,195,99,197,100,201,100,204,100,208,103,211,104,215,105,220,102,223,96,226,100,229,100,231,101,234,101,235,98,236,102,237,105,246,108,248,109,249,112,300,134,298,166,3,166};
float layer_4[][2]={0,140,30,129,38,123,48,121,53,121,57,121,59,118,60,112,63,106,65,113,69,112,73,112,75,113,77,112,80,101,82,105,83,108,86,111,87,108,89,105,90,109,92,109,92,105,95,105,97,110,100,111,100,107,101,101,102,106,103,110,105,112,106,114,108,116,111,118,114,119,116,108,118,120,120,122,123,124,125,126,128,127,131,129,134,131,140,133,150,135,168,136,173,131,174,123,179,135,182,138,299,160,299,165,1,166};
float layer_5[][2]={2,159,12,149,35,135,43,140,52,141,58,143,61,142,65,125,70,141,78,139,82,129,87,142,89,138,93,117,95,122,97,129,97,134,103,135,104,138,105,141,107,137,110,118,112,128,115,139,115,141,118,141,120,141,122,130,123,133,125,140,130,140,134,140,139,135,139,130,141,125,143,120,144,118,146,122,147,127,150,135,151,138,156,142,165,144,170,145,177,140,179,138,182,139,184,136,185,131,189,138,190,142,193,146,194,140,196,133,197,128,199,133,200,137,202,130,203,132,205,136,207,139,213,138,219,138,220,130,222,113,228,137,232,139,298,164,4,167};
float layer_6[][2]={2,164,2,147,3,137,4,122,7,115,9,111,10,104,11,98,14,86,18,86,20,93,22,104,24,114,26,119,28,126,32,140,34,147,37,161,39,166,66,166,66,159,70,146,71,144,73,130,77,145,79,156,83,162,88,164,122,166,123,159,124,154,127,146,128,138,129,132,130,129,131,139,134,151,139,158,142,161,144,157,147,151,149,144,151,134,153,127,155,116,158,113,161,120,163,127,166,138,166,144,168,151,170,155,171,158,171,161,201,164,202,158,203,154,203,147,204,139,204,132,209,113,212,120,215,132,217,136,218,139,220,143,221,145,224,147,226,145,228,143,229,136,232,124,233,120,234,117,238,128,239,131,241,132,243,123,245,125,247,129,250,130,253,112,254,110,260,122,262,126,265,124,270,118,271,112,273,105,277,115,280,111,282,110,289,93,291,87,293,82,294,80,297,71,298,68,299,166,2,167};
void sky()
{
skylist=glGenLists(1);
glNewList(skylist,GL_COMPILE);


glPushMatrix();
int i;
glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(-3500,1500,-9000);//top
	glRotatef(180,0,0,1);
	glRotatef(180,0,1,0);
	glScalef(0.6,2.5,1);
	//far mountains layer 1
	glPushMatrix();
	glTranslatef(0,0,0);
	glScalef(40,5,1);
	glColor3f(0.941,1.0,1.0);//azure
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_1)/8;i++)
		glVertex2fv(layer_1[i]);
	glEnd();
	glPopMatrix();
	//far mountains layer 1 shading
	glPushMatrix();
	glTranslatef(0,0,-40);
	glScalef(40,5,1);
	glColor3f(0.392,0.584,0.929);//cornlower blue
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_1s)/8;i++)
		glVertex2fv(layer_1s[i]);
	glEnd();
	glPopMatrix();
	//far mountains layer 3
	glPushMatrix();
	glTranslatef(0,0,-80);
	glScalef(40,5,1);
	glColor3f(0.255,0.412,0.882);//royal blue
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_3)/8;i++)
	glVertex2fv(layer_3[i]);
	glEnd();
	glPopMatrix();
glPopMatrix();

	glPushMatrix();//left
	glTranslatef(-3500,1500,4200);
	glRotatef(180,0,0,1);
	glRotatef(90,0,1,0);
	glScalef(0.6,2.5,1);
	//far mountains layer 1
	glPushMatrix();
	glTranslatef(0,0,0);
	glScalef(40,5,1);
	glColor3f(0.941,1.0,1.0);//azure
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_1)/8;i++)
		glVertex2fv(layer_1[i]);
	glEnd();
	glPopMatrix();
	//far mountains layer 1 shading
	glPushMatrix();
	glTranslatef(0,0,-40);
	glScalef(40,5,1);
	glColor3f(0.392,0.584,0.929);//cornlower blue
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_1s)/8;i++)
		glVertex2fv(layer_1s[i]);
	glEnd();
	glPopMatrix();
	//far mountains layer 3
	glPushMatrix();
	glTranslatef(0,0,-80);
	glScalef(40,5,1);
	glColor3f(0.255,0.412,0.882);//royal blue
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_3)/8;i++)
		glVertex2fv(layer_3[i]);
	glEnd();
	glPopMatrix();
glPopMatrix();

	glPushMatrix();//left
	glTranslatef(-3500,1500,-1800);
	glRotatef(180,0,0,1);
	glRotatef(90,0,1,0);
	glScalef(0.6,2.5,1);
	//far mountains layer 1
	glPushMatrix();
	glTranslatef(0,0,0);
	glScalef(40,5,1);
	glColor3f(0.941,1.0,1.0);//azure
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_1)/8;i++)
		glVertex2fv(layer_1[i]);
	glEnd();
	glPopMatrix();
	//far mountains layer 1 shading
	glPushMatrix();
	glTranslatef(0,0,-40);
	glScalef(40,5,1);
	glColor3f(0.392,0.584,0.929);//cornlower blue
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_1s)/8;i++)
		glVertex2fv(layer_1s[i]);
	glEnd();
	glPopMatrix();
	//far mountains layer 3
	glPushMatrix();
	glTranslatef(0,0,-80);
	glScalef(40,5,1);
	glColor3f(0.255,0.412,0.882);//royal blue
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_3)/8;i++)
		glVertex2fv(layer_3[i]);
	glEnd();
	glPopMatrix();
glPopMatrix();

	glPushMatrix();//right
	glTranslatef(3800,1500,4450);
	glRotatef(180,0,0,1);
	glRotatef(90,0,1,0);
	glScalef(0.6,2.5,1);
	//far mountains layer 1
	glPushMatrix();
	glTranslatef(0,0,-120);
	glScalef(40,5,1);
	glColor3f(0.941,1.0,1.0);//azure
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_1)/8;i++)
		glVertex2fv(layer_1[i]);
	glEnd();
	glPopMatrix();
	//far mountains layer 1 shading
	glPushMatrix();
	glTranslatef(0,0,-80);
	glScalef(40,5,1);
	glColor3f(0.392,0.584,0.929);//cornlower blue
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_1s)/8;i++)
		glVertex2fv(layer_1s[i]);
	glEnd();
	glPopMatrix();
	//far mountains layer 3
	glPushMatrix();
	glTranslatef(0,0,-40);
	glScalef(40,5,1);
	glColor3f(0.255,0.412,0.882);//royal blue
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_3)/8;i++)
		glVertex2fv(layer_3[i]);
	glEnd();
	glPopMatrix();
glPopMatrix();

	glPushMatrix();//right
	glTranslatef(3800,1500,-2500);
	glRotatef(180,0,0,1);
	glRotatef(90,0,1,0);
	glScalef(0.6,2.5,1);
	//far mountains layer 1
	glPushMatrix();
	glTranslatef(0,0,-120);
	glScalef(40,5,1);
	glColor3f(0.941,1.0,1.0);//azure
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_1)/8;i++)
		glVertex2fv(layer_1[i]);
	glEnd();
	glPopMatrix();
	//far mountains layer 1 shading
	glPushMatrix();
	glTranslatef(0,0,-80);
	glScalef(40,5,1);
	glColor3f(0.392,0.584,0.929);//cornlower blue
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_1s)/8;i++)
		glVertex2fv(layer_1s[i]);
	glEnd();
	glPopMatrix();
	//far mountains layer 3
	glPushMatrix();
	glTranslatef(0,0,-40);
	glScalef(40,5,1);
	glColor3f(0.255,0.412,0.882);//royal blue
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_3)/8;i++)
		glVertex2fv(layer_3[i]);
	glEnd();
	glPopMatrix();
glPopMatrix();

glPushMatrix();//bottom
	glTranslatef(-3500,1500,4000);
	glRotatef(180,0,0,1);
	glRotatef(180,0,1,0);
	glScalef(0.6,2.5,1);
	//far mountains layer 1
	glPushMatrix();
	glTranslatef(0,0,-120);
	glScalef(40,5,1);
	glColor3f(0.941,1.0,1.0);//azure
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_1)/8;i++)
		glVertex2fv(layer_1[i]);
	glEnd();
	glPopMatrix();
	//far mountains layer 1 shading
	glPushMatrix();
	glTranslatef(0,0,-80);
	glScalef(40,5,1);
	glColor3f(0.392,0.584,0.929);//cornlower blue
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_1s)/8;i++)
		glVertex2fv(layer_1s[i]);
	glEnd();
	glPopMatrix();
	//far mountains layer 3
	glPushMatrix();
	glTranslatef(0,0,-40);
	glScalef(40,5,1);
	glColor3f(0.255,0.412,0.882);//royal blue
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(layer_3)/8;i++)
		glVertex2fv(layer_3[i]);
	glEnd();
	glPopMatrix();
glPopMatrix();

glEnable(GL_LIGHTING);
glPopMatrix();

glEndList();
}
void initial_1()
{
	initlist1=glGenLists(1);
	glNewList(initlist1,GL_COMPILE);
	glPushMatrix();
	glTranslatef(0,0,-3000);

	glPopMatrix();
	glPushMatrix();
	glScalef(3,4,3);


	glPushMatrix();//right water
	glColor3f(0.392,0.584,0.929);//cornlower blue
	glTranslatef(705,-2,220);
	glScalef(2.75,0.01,5);
	glutSolidCube(200);
	glPopMatrix();

	glEndList();
}
void initial_2()
{
	initlist2=glGenLists(1);
	glNewList(initlist2,GL_COMPILE);
	glPushMatrix();
	glTranslatef(0,0,-3000);

	glPopMatrix();
	glPushMatrix();
	glScalef(3,4,3);

	glPushMatrix();//snow forest
	glDisable(GL_LIGHTING);
	glColor3f(1,0.98,0.98);//white
	glTranslatef(10,-10,-6730);
	glScalef(3.33,0.01,3);
	glutSolidCube(2000);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glEndList();
}
void initial_3()
{
	initlist3=glGenLists(1);
	glNewList(initlist3,GL_COMPILE);
	glPushMatrix();
	glTranslatef(0,0,-3000);

	glPopMatrix();
	glPushMatrix();
	glScalef(3,4,3);


	glEndList();
}
float score_board[][2]={728,113,795,112,820,99,834,82,839,61,832,33,816,15,794,4,730,5,184,3,159,5,139,14,126,24,119,37,114,70,115,137,115,869,109,896,94,914,79,924,71,927,147,926,683,924,710,911,720,898,725,888,728,872};
float score_board_extra1[][2]={113,818,62,816,30,825,18,834,13,841,8,851,4,864,3,876,5,887,11,899,19,910,29,918,44,923,55,927,70,926,85,920,100,909,110,897,115,881};
float score_board_extra2[][2]={113,817,67,816,81,827,87,836,87,846,86,855,80,862,70,867,60,872,116,871};
float score_board_extra3[][2]={17,901,26,910,36,918,48,922,58,923,70,922,677,923,697,917,707,910,714,900};
float score_board_extra4[][2]={169,2,193,9,209,19,221,34,227,57,222,81,209,99,194,109,180,114,171,115,789,113,815,102,827,93,833,81,839,68,839,53,832,35,823,20,808,11,795,6,778,3};
float score_board_extra5[][2]={167,59,840,60,835,82,826,95,815,104,806,110,794,112,167,115,158,110,149,104,145,93,143,82,146,71,154,64};
void board()
{
	int i,j;

	//drawing score board
	boardlist=glGenLists(1);
	glNewList(boardlist,GL_COMPILE);

	glPushMatrix();
	glDisable(GL_LIGHTING);
	glPointSize(20);
	glPushMatrix();
	glTranslatef(80,90,-101);
	glScalef(0.051,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0.941,0.902,0.549);//khaki
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(score_board)/8;i++)
		glVertex2fv(score_board[i]);
	glEnd();
	glPopMatrix();
	//shading polygon-lower
	glPushMatrix();
	glTranslatef(80,90,-100.5);
	glScalef(0.051,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0.741,0.718,0.420);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(score_board_extra3)/8;i++)
		glVertex2fv(score_board_extra3[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(79,89.5,-100);
	glScalef(0.05,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(score_board)/8;i++)
		glVertex2fv(score_board[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80,90,-101);
	glScalef(0.051,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0.741,0.718,0.420);//dark khaki
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(score_board_extra1)/8;i++)
		glVertex2fv(score_board_extra1[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80,90,-101);
	glScalef(0.051,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0.941,0.902,0.549);//khaki
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(score_board_extra1)/8;i++)
		glVertex2fv(score_board_extra1[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(79,89.5,-100);
	glScalef(0.05,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(score_board_extra1)/8;i++)
		glVertex2fv(score_board_extra1[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(79,89.5,-100);
	glScalef(0.05,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(score_board_extra2)/8;i++)
		glVertex2fv(score_board_extra2[i]);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(79,89.5,-100);
	glScalef(0.05,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(score_board_extra4)/8;i++)
		glVertex2fv(score_board_extra4[i]);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(76.5,89.5,-100.3);
	glScalef(0.03,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0.741,0.718,0.420);//dark khaki
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(score_board_extra5)/8;i++)
		glVertex2fv(score_board_extra5[i]);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(40,104,-100);
	glScalef(1.03,2.03,1);
	glColor3f(0,0,0);
	glutSolidOctahedron();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40,104,-99.98);
	glScalef(1,2,1);
	glColor3f(0.8,0,0.8);
	glutSolidOctahedron();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40,98,-100);
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
	//glScalef(1,2,1);
	//glColor3f(0.863,0.078,0.235);
	glVertex2f(-1,-1);
	//glColor3f(1,0,0);
	glVertex2f(1,-1);
	//glColor3f(1,1,0);
	glVertex2f(1,1);
	//glColor3f(1,0.843,0);
	glVertex2f(-1,1);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(40,98,-99.98);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	//glScalef(1,2,1);
	//glColor3f(0.863,0.078,0.235);
	glVertex2f(-1,-1);
	//glColor3f(1,0,0);
	glVertex2f(1,-1);
	//glColor3f(1,1,0);
	glVertex2f(1,1);
	//glColor3f(1,0.843,0);
	glVertex2f(-1,1);
	glEnd();
	glPopMatrix();

	glEndList();

	glEnable(GL_LIGHTING);
	glPopMatrix();
}
void board2()
{
//drawing score board
	board2list=glGenLists(1);
	glNewList(board2list,GL_COMPILE);
	int i,j;
	glPointSize(20);

	glPushMatrix();
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glTranslatef(80,90,-101);
	glScalef(0.051,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0.941,0.902,0.549);//khaki
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(score_board)/8;i++)
		glVertex2fv(score_board[i]);
	glEnd();
	glPopMatrix();
	//shading polygon-lower
	glPushMatrix();
	glTranslatef(80,90,-100.5);
	glScalef(0.051,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0.741,0.718,0.420);
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(score_board_extra3)/8;i++)
		glVertex2fv(score_board_extra3[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(79,89.5,-100);
	glScalef(0.05,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(score_board)/8;i++)
		glVertex2fv(score_board[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80,90,-101);
	glScalef(0.051,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0.741,0.718,0.420);//dark khaki
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(score_board_extra1)/8;i++)
		glVertex2fv(score_board_extra1[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80,90,-101);
	glScalef(0.051,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0.941,0.902,0.549);//khaki
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(score_board_extra1)/8;i++)
		glVertex2fv(score_board_extra1[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(79,89.5,-100);
	glScalef(0.05,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(score_board_extra1)/8;i++)
		glVertex2fv(score_board_extra1[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(79,89.5,-100);
	glScalef(0.05,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(score_board_extra2)/8;i++)
		glVertex2fv(score_board_extra2[i]);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(79,89.5,-100);
	glScalef(0.05,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(score_board_extra4)/8;i++)
		glVertex2fv(score_board_extra4[i]);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(76.5,89.5,-100.3);
	glScalef(0.03,0.0251,0);
	glRotatef(90,0,0,1);
	glColor3f(0.741,0.718,0.420);//dark khaki
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(score_board_extra5)/8;i++)
		glVertex2fv(score_board_extra5[i]);
	glEnd();
	glPopMatrix();

	glEndList();
}
void attack_scroll()
{
	int i,j;
	attack_scroll_list=glGenLists(1);
	glNewList(attack_scroll_list,GL_COMPILE);
	glDisable(GL_LIGHTING);
	for(i=0;i<=100;i+=20)
	{
	glPushMatrix();
	glTranslatef(-55+i,-5,-100.4);
	glColor3f(0.941,0.902,0.549);//khaki
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(20,0,0);
	glVertex3f(20,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();
	}
	//shading
	glPushMatrix();
	glTranslatef(-55,-5,-100.2);
	glColor3f(0.741,0.718,0.420);//dark khaki
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(2,0,0);
	glVertex3f(2,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();
	//right scroll outline
	glPushMatrix();
	glTranslatef(-55+115,-5,-100);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0,0,0);
	glVertex3f(5,0,0);
	glVertex3f(5,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();
	//right scroll shading
	glPushMatrix();
	glTranslatef(-55+115,-5,-100.2);
	glColor3f(0.741,0.718,0.420);//dark khaki
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(2,0,0);
	glVertex3f(2,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();
	//outline
	glPushMatrix();
	glTranslatef(-55,-5,-100);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0,0,0);
	glVertex3f(120,0,0);
	glVertex3f(120,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();

	//writing
	char writing1[]="Oops! Looks like you have awakened the Cube Guard!";
	char writing2[]="Use Space Bar to attack the guard.                ";
	char writing3[]="Attack when he reaches the centre.                ";
	char writing4[]="Make 5 hits to defeat the guard.                  ";
	char writing5[]="But beware, if you miss the shot, he comes closer!";
	glColor3f(0,0,0);
	for(i=0,j=0;writing1[i]!='\0';i++,j+=2)
	{
	glPushMatrix();
		glRasterPos3f(-50+j,10,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing1[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-50+j,7,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing2[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-50+j,4,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing3[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-50+j,1,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing4[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-50+j,-2,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing5[i]);
	glPopMatrix();
	}

	glEnable(GL_LIGHTING);
	glPopMatrix();
	glEndList();

}
void welcome_scroll()
{
	int i,j;
	glDisable(GL_LIGHTING);
	for(i=0;i<=100;i+=20)
	{
	glPushMatrix();
	glTranslatef(-55+i,-5,-100.4);
	glColor3f(0.941,0.902,0.549);//khaki
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(20,0,0);
	glVertex3f(20,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();
	}
	//shading
	glPushMatrix();
	glTranslatef(-55,-5,-100.2);
	glColor3f(0.741,0.718,0.420);//dark khaki
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(2,0,0);
	glVertex3f(2,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();
	//right scroll outline
	glPushMatrix();
	glTranslatef(-55+115,-5,-100);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0,0,0);
	glVertex3f(5,0,0);
	glVertex3f(5,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();
	//right scroll shading
	glPushMatrix();
	glTranslatef(-55+115,-5,-100.2);
	glColor3f(0.741,0.718,0.420);//dark khaki
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(2,0,0);
	glVertex3f(2,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();
	//outline
	glPushMatrix();
	glTranslatef(-55,-5,-100);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0,0,0);
	glVertex3f(120,0,0);
	glVertex3f(120,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();

	//writing
	char writing1[]="Welcome to FIND THE MAGIC CUBES!                     ";
	char writing2[]="Use arrow keys to navigate through the game.         ";
	char writing3[]="Press Enter key to collect Gems.                     ";
	char writing4[]="Collect all Gems and Magic Cubes to win the game.    ";
	char writing5[]="And beware of the angry Magic Cube guards! Good Luck!";
	glColor3f(0,0,0);
	for(i=0,j=0;writing5[i]!='\0';i++,j+=2)
	{
	glPushMatrix();
		glRasterPos3f(-50+j,10,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing1[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-50+j,7,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing2[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-50+j,4,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing3[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-50+j,1,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing4[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-50+j,-2,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing5[i]);
	glPopMatrix();
	}

	glEnable(GL_LIGHTING);
	glPopMatrix();

}
void repeat_scroll()
{
	int i,j;
	glDisable(GL_LIGHTING);
	for(i=0;i<=100;i+=20)
	{
	glPushMatrix();
	glTranslatef(-55+i,-5,-100.4);
	glColor3f(0.941,0.902,0.549);//khaki
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(20,0,0);
	glVertex3f(20,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();
	}
	//shading
	glPushMatrix();
	glTranslatef(-55,-5,-100.2);
	glColor3f(0.741,0.718,0.420);//dark khaki
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(2,0,0);
	glVertex3f(2,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();
	//right scroll outline
	glPushMatrix();
	glTranslatef(-55+115,-5,-100);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0,0,0);
	glVertex3f(5,0,0);
	glVertex3f(5,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();
	//right scroll shading
	glPushMatrix();
	glTranslatef(-55+115,-5,-100.2);
	glColor3f(0.741,0.718,0.420);//dark khaki
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(2,0,0);
	glVertex3f(2,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();
	//outline
	glPushMatrix();
	glTranslatef(-55,-5,-100);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0,0,0);
	glVertex3f(120,0,0);
	glVertex3f(120,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();

	//writing
	char writing1[]="You failed to defeat the Magic Cube Guard!           ";
	char writing2[]="You have been moved back to the start of this level. ";
	char writing3[]="Good Luck fighting the guard this time!              ";
	glColor3f(0,0,0);
	for(i=0,j=0;writing2[i]!='\0';i++,j+=2)
	{
	glPushMatrix();
		glRasterPos3f(-50+j,10,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing1[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-50+j,7,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing2[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-50+j,4,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing3[i]);
	glPopMatrix();
	}

	glEnable(GL_LIGHTING);
	glPopMatrix();

}
void collect_cube_scroll()
{
	int i,j;
	collect_cube_scroll_list=glGenLists(1);
	glNewList(collect_cube_scroll_list,GL_COMPILE);
	glDisable(GL_LIGHTING);
	for(i=0;i<=100;i+=20)
	{
	glPushMatrix();
	glTranslatef(-55+i,-5,-100.4);
	glColor3f(0.941,0.902,0.549);//khaki
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(20,0,0);
	glVertex3f(20,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();
	}
	//shading
	glPushMatrix();
	glTranslatef(-55,-5,-100.2);
	glColor3f(0.741,0.718,0.420);//dark khaki
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(2,0,0);
	glVertex3f(2,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();
	//right scroll outline
	glPushMatrix();
	glTranslatef(-55+115,-5,-100);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0,0,0);
	glVertex3f(5,0,0);
	glVertex3f(5,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();
	//right scroll shading
	glPushMatrix();
	glTranslatef(-55+115,-5,-100.2);
	glColor3f(0.741,0.718,0.420);//dark khaki
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(2,0,0);
	glVertex3f(2,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();
	//outline
	glPushMatrix();
	glTranslatef(-55,-5,-100);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0,0,0);
	glVertex3f(120,0,0);
	glVertex3f(120,20,0);
	glVertex3f(0,20,0);
	glEnd();
	glPopMatrix();

	//writing
	char writing1[]="             Congratulations!                 ";
	char writing2[]="You have defeated the Magic Cube guard!       ";
	char writing3[]="Press the Enter key to collect the Magic Cube.";
	char writing4[]="You have cleared this level!                  ";
	char writing5[]="Press key n to enter the next level.          ";
	glColor3f(0,0,0);
	for(i=0,j=0;writing3[i]!='\0';i++,j+=2)
	{
	glPushMatrix();
		glRasterPos3f(-50+j,10,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing1[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-50+j,7,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing2[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-50+j,4,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing3[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-50+j,1,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing4[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-50+j,-2,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing5[i]);
	glPopMatrix();
	}

	glEnable(GL_LIGHTING);
	glPopMatrix();
	glEndList();
}
void score_board_draw()
{
	int i;
	glPushMatrix();
	glDisable(GL_LIGHTING);
	//printf("\ngems collected in level %d = %d",level,gems_collected[level-1]);
	char g[3],lvl[4],c[3];

	int j=0;
	itoa(gems_collected[level-1],g,10);
	itoa(level,lvl,10);
	itoa(cube_collection,c,10);
	for(i=0,j=0;g[i]!='\0';i++)
	{
	glPushMatrix();
		glColor3f(0,0,0);
		glRasterPos3f(45+j,103,-100);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,g[i]);
		j+=2;
	glPopMatrix();
	}
	for(i=0,j=0;c[i]!='\0';i++)
	{
	glPushMatrix();
		glColor3f(0,0,0);
		glRasterPos3f(45+j,97.5,-100);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c[i]);
		j+=2;
	glPopMatrix();
	}
	char l[]="LEVEL: ",e[]="END";

	if(level<4)
	{
	for(i=0,j=0;l[i]!='\0';i++)
	{
	glPushMatrix();
		glColor3f(0,0,0);
		glRasterPos3f(55+j,103,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,l[i]);
		j+=2;
	glPopMatrix();
	}
	for(i=0,j=0;lvl[i]!='\0';i++)
	{
	glPushMatrix();
		glColor3f(0,0,0);
		glRasterPos3f(69+j,103,-100);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,lvl[i]);
		j+=2;
	glPopMatrix();
	}
	}
	else if(level==4)
	{
	for(i=0,j=0;e[i]!='\0';i++)
	{
	glPushMatrix();
		glColor3f(0,0,0);
		glRasterPos3f(55+j,103,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,e[i]);
		j+=2;
	glPopMatrix();
	}
	}
	glEnable(GL_LIGHTING);
	glPopMatrix();

}
void score_board2_draw()
{
	int i;
	glPushMatrix();
	glDisable(GL_LIGHTING);
	//printf("\ngems collected in level %d = %d",level,gems_collected[level-1]);

	char hits_count[4];
	int j=0;
	itoa(hits[level-1],hits_count,10);

	char h[]="HITS: ";

	for(i=0,j=0;h[i]!='\0';i++)
	{
	glPushMatrix();
		glColor3f(0,0,0);
		glRasterPos3f(48+j,100,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,h[i]);
		j+=2;
	glPopMatrix();
	}
	for(i=0,j=0;hits_count[i]!='\0';i++)
	{
	glPushMatrix();
		glColor3f(0,0,0);
		glRasterPos3f(62+j,100,-100);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,hits_count[i]);
		j+=2;
	glPopMatrix();
	}


	glEnable(GL_LIGHTING);
	glPopMatrix();

}
void decorate()
{
	decorate_list=glGenLists(1);
	glNewList(decorate_list,GL_COMPILE);

	glPushMatrix();
	glTranslatef(1200,10,-3900);
	glScalef(0.35,0.35,0.35);
	normal_snowman();
	glPopMatrix();

		glPushMatrix();
	glTranslatef(1600,10,-4700);
	glScalef(0.35,0.35,0.35);
	normal_snowman();
	glPopMatrix();

		glPushMatrix();
	glTranslatef(1500,10,-5500);
	glScalef(0.35,0.35,0.35);
	normal_snowman();
	glPopMatrix();

		glPushMatrix();
	glTranslatef(500,10,-5700);
	glScalef(0.35,0.35,0.35);
	normal_snowman();
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-750,10,-6300);
	glScalef(0.35,0.35,0.35);
	normal_snowman();
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-1200,10,-7300);
	glScalef(0.35,0.35,0.35);
	normal_snowman();
	glPopMatrix();

		glPushMatrix();
	glTranslatef(-750,10,-7350);
	glScalef(0.35,0.35,0.35);
	normal_snowman();
	glPopMatrix();

	glEndList();
}
void End()
{
	int i,j,k;
	glPushMatrix();
	glTranslatef(-150,70,0);
	glRotatef(-90,0,0,1);

	glDisable(GL_LIGHTING);
	glPointSize(20);
	glPushMatrix();
	glTranslatef(80,90,-101);
	//glScalef(0.051,0.0251,0);
	glScalef(0.13,0.13,0);
	glRotatef(90,0,0,1);
	glColor3f(0.941,0.902,0.549);//khaki
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(score_board)/8;i++)
		glVertex2fv(score_board[i]);
	glEnd();
	glPopMatrix();
	//shading polygon-lower
	glPushMatrix();
	glTranslatef(80-2,90,-100.5);
	glScalef(0.13,0.13,0);
	glRotatef(90,0,0,1);
	glColor3f(0.741,0.718,0.420);//dark khaki
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(score_board_extra3)/8;i++)
		glVertex2fv(score_board_extra3[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(79,89.5,-100);
	glScalef(0.13,0.13,0);
	glRotatef(90,0,0,1);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(score_board)/8;i++)
		glVertex2fv(score_board[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80-1,90-0.5,-101);
	glScalef(0.13,0.13,0);
	glRotatef(90,0,0,1);
	glColor3f(0.741,0.718,0.420);//dark khaki
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(score_board_extra1)/8;i++)
		glVertex2fv(score_board_extra1[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(80-1,90,-101);
	glScalef(0.13,0.13,0);
	glRotatef(90,0,0,1);
	glColor3f(0.941,0.902,0.549);//khaki
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(score_board_extra1)/8;i++)
		glVertex2fv(score_board_extra1[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(79,89.5,-100);
	glScalef(0.13,0.13,0);
	glRotatef(90,0,0,1);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(score_board_extra1)/8;i++)
		glVertex2fv(score_board_extra1[i]);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(79,89.5,-100);
	glScalef(0.13,0.13,0);
	glRotatef(90,0,0,1);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(score_board_extra2)/8;i++)
		glVertex2fv(score_board_extra2[i]);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(79,89.5,-100);
	glScalef(0.13,0.13,0);
	glRotatef(90,0,0,1);
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	for(i=0;i<sizeof(score_board_extra4)/8;i++)
		glVertex2fv(score_board_extra4[i]);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(76.5+2,89.5,-100.3);
	glScalef(0.13,0.13,0);
	glRotatef(90,0,0,1);
	glColor3f(0.741,0.718,0.420);//dark khaki
	glBegin(GL_POLYGON);
	for(i=0;i<sizeof(score_board_extra5)/8;i++)
		glVertex2fv(score_board_extra5[i]);
	glEnd();
	glPopMatrix();

glPopMatrix();
	//writing
	char writing1[]="                 SCORE                ";
	char writing2[]="Each Gem gets you a score of 2.       ";
	char writing3[]="Each Magic Cube gets you a score of 5.";
	char writing4[]="            Gems Collected:           ";
	char writing5[]="Level 1:";
	char writing6[]="Level 2:";
	char writing7[]="Level 3:";
	char writing8[]="Total:  ";
	char writing9[]="              Your score:";
	char writing10[]="Gems:                   ";
	char writing11[]="Magic Cubes:            ";
	char writing12[]="Total:                  ";

	glPushMatrix();
	glColor3f(0,0,0);
	for(i=0,j=0,k=0;writing3[i]!='\0';i++,j+=2,k+=4)
	{
	glPushMatrix();
	glColor3f(1,0,0);
		glRasterPos3f(-80+k,100,-100);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,writing1[i]);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0,0,0);
		glRasterPos3f(-42+j,85,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing2[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-42+j,80,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing3[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-42+j,65,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing4[i]);
	glPopMatrix();
	}
	for(i=0,j=0;writing5[i]!='\0';i++,j+=2)
	{
	glPushMatrix();
		glRasterPos3f(-42+j,60,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing5[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-42+j,55,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing6[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-42+j,50,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing7[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-42+j,45,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing8[i]);
	glPopMatrix();
	}
	for(i=0,j=0;writing9[i]!='\0';i++,j+=2)
	{
	glPushMatrix();
		glRasterPos3f(-42+j,30,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing9[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-42+j,25,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing10[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-42+j,20,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing11[i]);
	glPopMatrix();
	glPushMatrix();
		glRasterPos3f(-42+j,13,-100);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,writing12[i]);
	glPopMatrix();
	}
	glPopMatrix();

	int total_gems=gems_collected[0]+gems_collected[1]+gems_collected[2];
	int gems=total_gems*2;
	int cubes=cube_collection*5;
	int score=gems+cubes;
	char g_1[4],g_2[4],g_3[4],tot[4],s[4],gm[4],cb[4];
	itoa(gems_collected[0],g_1,10);
	itoa(gems_collected[1],g_2,10);
	itoa(gems_collected[2],g_3,10);
	itoa(total_gems,tot,10);
	itoa(gems,gm,10);
	itoa(cubes,cb,10);
	itoa(score,s,10);
	for(i=0,j=0;g_1[i]!='\0';i++)
	{
	glPushMatrix();
		glColor3f(0,0,0);
		glRasterPos3f(-24+j,60,-100);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,g_1[i]);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0,0,0);
		glRasterPos3f(-24+j,55,-100);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,g_2[i]);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0,0,0);
		glRasterPos3f(-24+j,50,-100);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,g_3[i]);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0,0,0);
		glRasterPos3f(-24+j,45,-100);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,tot[i]);
	glPopMatrix();
		j+=2;
	}
	for(i=0,j=0;s[i]!='\0';i++)
	{
	glPushMatrix();
		glColor3f(0,0,0);
		glRasterPos3f(-16+j,25,-100);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,gm[i]);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0,0,0);
		glRasterPos3f(-16+j,20,-100);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,cb[i]);
	glPopMatrix();
	glPushMatrix();
		glColor3f(1,0,0);
		glRasterPos3f(-16+j,12,-100);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s[i]);
	glPopMatrix();
		j+=2;
	}
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
void land(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluPerspective (60, (GLfloat)wd / (GLfloat)ht, 1.0, 100000.0);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(attack==0)
	{


	if(level==1)
	{
		glRotatef(xrot,1.0,0.0,0.0);
    glTranslatef(0.0f, -50.0f, -cRadius);
    if(start==0)
    	welcome_scroll();
    if(repeat==1)
    	repeat_scroll();
    glCallList(boardlist);
        score_board_draw();
    if(congrats_msg)
	glCallList(collect_cube_scroll_list);

    glRotatef(yrot,0.0,1.0,0.0);
    glTranslated(-xpos,-50.0f,-zpos);

	glEnable( GL_TEXTURE_2D );
	glDisable(GL_LIGHTING);
	glPushMatrix();
 	glScalef(200,1,150);
	glCallList(main_tex_list);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable( GL_TEXTURE_2D );

	glEnable( GL_TEXTURE_2D );
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(0,0,-10500);
 	glScalef(200,1,150);
	glCallList(rocky_tex_list);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable( GL_TEXTURE_2D );

	glCallList(initlist1);
	glCallList(skylist);
//	glCallList(random_treeslist);
	glCallList(maze_forestlist);
	glCallList(entrancelist);
	glCallList(pondlist);
//	fencing();
	glCallList(cavelist);
	collectibles_1();
	magic_cube(150,50,-170,0);

	}
	if(level==2)
	{
		glRotatef(xrot,1.0,0.0,0.0);
    glTranslatef(0.0f, -50.0f, -cRadius);
    if(repeat==1)
    	repeat_scroll();
    glCallList(boardlist);
    score_board_draw();
    if(congrats_msg)
	glCallList(collect_cube_scroll_list);

    glRotatef(yrot,0.0,1.0,0.0);
    glTranslated(-xpos,-50.0f,-zpos);

	glEnable( GL_TEXTURE_2D );
	glDisable(GL_LIGHTING);
	glPushMatrix();
 	glScalef(200,1,150);
	glCallList(main_tex_list);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable( GL_TEXTURE_2D );

	glEnable( GL_TEXTURE_2D );
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(0,0,-10500);
 	glScalef(200,1,150);
	glCallList(rocky_tex_list);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable( GL_TEXTURE_2D );

    glEnable( GL_TEXTURE_2D );
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(-100,0,-22500);
 	glScalef(200,1,150);
	glCallList(snow_tex_list);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable( GL_TEXTURE_2D );

	glCallList(initlist2);
	glCallList(skylist);
	glCallList(rockylist);
	collectibles_2();
	magic_cube(1500,50,-3100,1);


	}
	if(level==3 || level==4)
	{

	glRotatef(xrot,1.0,0.0,0.0);
    glTranslatef(0.0f, -50.0f, -cRadius);

    if(level==3)
    {
	if(repeat==1)
    	repeat_scroll();
    glCallList(boardlist);
    score_board_draw();
    if(congrats_msg)
	glCallList(collect_cube_scroll_list);
	}
	if(level==4)
    	End();

    glRotatef(yrot,0.0,1.0,0.0);
    glTranslated(-xpos,-50.0f,-zpos);

	glEnable( GL_TEXTURE_2D );
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(0,0,-10500);
 	glScalef(200,1,150);
	glCallList(rocky_tex_list);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable( GL_TEXTURE_2D );

    glEnable( GL_TEXTURE_2D );
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(-100,0,-22500);
 	glScalef(200,1,150);
	glCallList(snow_tex_list);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable( GL_TEXTURE_2D );


	glCallList(initlist3);
	glCallList(skylist);
	//glCallList(snowylist);


	glPushMatrix();
	glTranslatef(500,0,-7000);
	glCallList(snowforestlist);
	glPopMatrix();

	glCallList(decorate_list);
	collectibles_3();
	magic_cube(200,50,-7655,2);

	}

}
	else
	{
    	xrot=0;yrot=0;

    glRotatef(xrot,1.0,0.0,0.0);
    glTranslatef(0.0f, -50.0f, -cRadius);
    glCallList(board2list);
    score_board2_draw();
    	glCallList(attack_scroll_list);
    glRotatef(yrot,0.0,1.0,0.0);
    glTranslatef(-xpos,-50.0f,-zpos);

		glPushMatrix();
		glDisable(GL_LIGHTING);

		glColor3f(1,0,1);
		if(level==1)
		{
	glEnable( GL_TEXTURE_2D );
	glDisable(GL_LIGHTING);
	glPushMatrix();
 	glScalef(200,1,150);
	glCallList(main_tex_list);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable( GL_TEXTURE_2D );

	glEnable( GL_TEXTURE_2D );
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(0,0,-10500);
 	glScalef(200,1,150);
	glCallList(rocky_tex_list);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable( GL_TEXTURE_2D );

		glPushMatrix();
			forest_guard();
		glPopMatrix();
			glCallList(initlist1);
			glCallList(skylist);

		}
		if(level==2)
		{
	glEnable( GL_TEXTURE_2D );
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(0,0,-10500);
 	glScalef(200,1,150);
	glCallList(rocky_tex_list);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable( GL_TEXTURE_2D );

		glPushMatrix();
			rocky_guard();
		glPopMatrix();


			glCallList(initlist1);
			glCallList(skylist);
		}
		if(level==3)
		{
	glEnable( GL_TEXTURE_2D );
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(-100,0,-22500);
 	glScalef(200,1,150);
	glCallList(snow_tex_list);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable( GL_TEXTURE_2D );

		glPushMatrix();
			snow_guard();
		glPopMatrix();
			glCallList(initlist1);
			glCallList(skylist);

		}
		glEnable(GL_LIGHTING);
		glPopMatrix();

	}
	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
	angle++;
}

void light_init()
{

    glClearColor(0.529,0.808,0.980,1);

    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_INTENSITY,light_intensity);

	glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}
void createLists()
{
	board();
	board2();
	gorilla();
	initial_1();
	initial_2();
	initial_3();
	drawGrass();
	rocky();
	//random_trees();
	collect_cube_scroll();
	attack_scroll();
	maze_forest();
	pond();
	//snowy();
	drawGrass();
	drawDirt();
	drawSnow();
	snow_forest();
	decorate();
	entrance();
	//collectibles();
	cave();
	sky();
}
void keyboard(unsigned char key, int xx, int yy)
{
if(attack==0)
{
	if(key=='p')
	{
		printf("\n\nxpos=%f, ypos=%f, zpos=%f\nxrot=%f, yrot=%f",xpos,ypos,zpos,xrot,yrot);
	}
	if(key=='s')
	{
		xrot += 1;
    	if (xrot >360) xrot -= 360;
	}
	if(key=='w')
	{
		xrot -= 1;
    	if (xrot < -360) xrot += 360;
	}
	if(key=='n')
	{
		congrats_msg=0;
		level++;
		if(level==2)
		{
		xpos=-4100;
		ypos=0;
		zpos=-5100;
		yrot=-30;
		}
		if(level==3)
		{
		xpos=5100;
		ypos=0;
		zpos=-11200;
		yrot=-50;
		}
		if(level==4)
		{
			xpos=323;
			ypos=0;
			zpos=-23262;
			yrot=110;
			int total_gems=gems_collected[0]+gems_collected[1]+gems_collected[2];
			int score=2*total_gems+5*cube_collection;
			printf("\nThe End\n");
			printf("\nGems collected:\nLevel 1: %d\nLevel 2: %d\nLevel 3: %d\nTotal: %d\n",gems_collected[0],gems_collected[1],gems_collected[2],total_gems);
			printf("\nMagic Cubes collected: %d\n",cube_collection);
			printf("\nEach gem gets you a score of 2.\nEach magic cube gets you a score of 5.");
			printf("\n\nYour Score: %d for gems + %d for cubes = %d",2*total_gems,5*cube_collection,score);

		}
	}
	if(key==13)
	{
		int i,j;

			printf("\nEnter key pressed");

		if(level==1)
		{
			//gems
			for(i=0;i<gm;i++)
				{

					if(gems_main[i].flag==0)
					if((xpos>=((gems_main[i].pos[0])-100)) && (xpos<=((gems_main[i].pos[0])+100)))
					{
						//printf("\nxpos is within the range");
						if(zpos>=(gems_main[i].pos[2]-100) && zpos<=(gems_main[i].pos[2]+100))
						{
								printf("\n\nCollecting gem %d!",i);
								gems_collected[level-1]++;
								gems_main[i].flag=1;
								break;
						}

					}
				}
			//cube

			if(xpos>=400 && xpos<=800)//magic cube
			{
				printf("\nX is in the range.");
				if(zpos>=-400 && zpos<=-100)
				{
					if(fg==0)
					{
						temp_xrot=xrot;
						temp_yrot=yrot;
						fg=forest_guard();
					}
					if(fg==1)
					{
					magic_cube_collected[level-1]=1;
					cube_collection++;
					}
				}
			}
		}
		if(level==2)
		{

			//printf("\nYes, I am in level 2");
			//printf("\ngems_rocky[0]:\nxpos=%2f, ypos=%2f, zpos=%2f",gems_rocky[0].pos[0],gems_rocky[0].pos[1],gems_rocky[0].pos[2]);
			//gems
			for(i=0;i<gr;i++)
				{
					if(gems_rocky[i].flag==0)
					if((xpos>=((gems_rocky[i].pos[0])-200)) && (xpos<=((gems_rocky[i].pos[0])+200)))
					{
						//printf("\nxpos is within the range");
						if(zpos>=(gems_rocky[i].pos[2]-200) && zpos<=(gems_rocky[i].pos[2]+200))
						{
								printf("\n\nCollecting gem %d!",i);
								gems_collected[level-1]++;
								gems_rocky[i].flag=1;
								break;
						}

					}
				}
			//cube
			if(xpos>=4100 && xpos<=4400)//magic cube
			{
				printf("\nX is in the range.");
				if(zpos>=-9500 && zpos<=-9200)
				{
					if(rg==0)
					{
						temp_xrot=xrot;
						temp_yrot=yrot;
						rg=rocky_guard();
					}
					if(rg==1)
					{

					magic_cube_collected[level-1]=1;
					cube_collection++;
					}
				}
			}
		}
		if(level==3)
		{
			//gems
			for(i=0;i<gs;i++)
				{

					if(gems_snowy[i].flag==0)
					if((xpos>=((gems_snowy[i].pos[0])-200)) && (xpos<=((gems_snowy[i].pos[0])+200)))
					{
						//printf("\nxpos is within the range");
						if(zpos>=(gems_snowy[i].pos[2]-200) && zpos<=(gems_snowy[i].pos[2]+200))
						{
								printf("\n\nCollecting gem %d!",i);
								gems_collected[level-1]++;
								gems_snowy[i].flag=1;
								break;
						}

					}
				}
			//cube

			if(xpos>=300 && xpos<=600)//magic cube
			{
				printf("\nX is in the range.");
				if(zpos>=-24000 && zpos<=-22000)
				{	printf("\nz is in the range.");
					if(sg==0)
					{
						temp_xrot=xrot;
						temp_yrot=yrot;
						sg=snow_guard();
					}
					if(sg==1)
					{
					magic_cube_collected[level-1]=1;
					cube_collection++;
					}
				}
			}

		}
	}
}
else if(attack==1)
{
	if(key==32)//hit 5 times, for every wrong hit, guard comes closer; 10 chances
	{
		if(movex>=-20 && movex<=20)
		{
		hits[level-1]++;

		printf("\nHits in level%d =%d",level,hits[level-1]);
		}
		else
		{
			hits[level-1]--;
			movez+=20;
			printf("\nOH NO! Hits in level%d =%d",level,hits[level-1]);
		}
	}
}
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(905, 700);
    glutInitWindowPosition(455,0);
    w1 = glutCreateWindow (argv[0]);
    glutSetWindowTitle("Find the Magic Cubes!");
    light_init();
    glutReshapeFunc(resize1);
    glutDisplayFunc(land);
    glutIdleFunc (land);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(processSpecialKeys);

    createLists();

    rotate_magic_cube(0);
    move_guard(0);
    glutMainLoop ();
    FreeTexture(texture);
    FreeTexture(texture2);
    return 0;
}
