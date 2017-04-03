#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include <GL/glut.h>
#include"rotate.h"


typedef unsigned char BYTE;

void DefineIluminacao();
void teclasup(int key, int x, int y);

int mapa[21][21][21]=
{{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}},
{{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0},{0}}};

GLuint text,text2,text3,text4;
GLfloat xpos=0, xposi=-150;
ypos=70,yposi=0,zpos=500,zposi=0;angle, angle2, angle3, fAspect,sx,sy,sz,scl, vx, vy, vz;
GLfloat cx,cy,cz;
int moving,mr,mid,wi,he,moveup,movedown,moveleft,moveright;

GLuint lertexturabmp( const char * filename, int wrap )
{
    GLuint texture;
    int width, height;
    BYTE * data;
    FILE * file;

    // open texture data
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;

    // allocate buffer
    width = 128;
    height = 128;
    data = malloc( width * height * 3 );

    // read texture data
    fread( data, width * height * 3, 1, file );
    fclose( file );

    // allocate a texture name
    glGenTextures( 1, &texture );

    // select our current texture
    glBindTexture( GL_TEXTURE_2D, texture );

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                     wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                     wrap ? GL_REPEAT : GL_CLAMP );

    // build our texture mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,
                       GL_RGB, GL_UNSIGNED_BYTE, data );

    // free buffer
    free( data );

    return texture;
}


void cubo(int texture, int texture2)
{


    // Face frontal
    glBindTexture( GL_TEXTURE_2D, texture2 );
    glBegin ( GL_QUADS );
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glEnd();

    // Face posterior

    glBindTexture( GL_TEXTURE_2D, texture2 );
    glBegin ( GL_QUADS );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glEnd();

    // Face superior
    glBindTexture( GL_TEXTURE_2D, texture );
    glBegin ( GL_QUADS );
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glEnd();

    // Face inferior
    glBindTexture( GL_TEXTURE_2D, texture2 );
    glBegin ( GL_QUADS );
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glEnd();

    // Face lateral yposeita
    glBindTexture( GL_TEXTURE_2D, texture2 );
    glBegin ( GL_QUADS );
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glEnd();

    // Face lateral esquerda
    glBindTexture( GL_TEXTURE_2D, texture2 );
    glBegin ( GL_QUADS );
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();



}

// Função callback chamada para fazer o desenho
void display()
{
    int i,j,k;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    glPushMatrix();
    for (j=-10; j<=10; j++)
    {
        for(i=-10; i<=10; i++)
        {
            glPushMatrix();
            glScalef(25,25,25);
            glTranslatef(2*i,0,2*j);
            cubo(text,text2);
            glPopMatrix();
        }
    }
    glPopMatrix();

    for(k=-10; k<=10; k++){
        for (j=-10; j<=10; j++)
        {
            for(i=-10; i<=10; i++)
            {
                if(mapa[i+10][j+10][k+10]){
                glPushMatrix();
                glScalef(25,25,25);
                glTranslatef(2*i,2*j,2*k);
                cubo(text,text2);
                glPopMatrix();
                }
            }
        }

    }
    pulainimigo();

    // Executa os comandos OpenGL
    glutSwapBuffers();

}


void EspecificaParametrosVisualizacao()
{
    // Especifica sistema de coordenadas de projeção
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva
    gluPerspective(angle,fAspect,10,5000);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    // Especifica posição do observador e do alvo
    gluLookAt(xpos,ypos,zpos, cx,cy,cz, vx,vy,vz);


    DefineIluminacao();

    glutPostRedisplay();



}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    int i;
    // Para previnir uma divisão por zero
    if ( h == 0 ) h = 1;

    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);

    // Calcula a correção de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    wi=w;
    he=h;

    EspecificaParametrosVisualizacao();

}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON)
    {
        //possibilita moveupr o objeto pelo botão esquerdo
        if (state == GLUT_DOWN)
        {


            // Zoom-in

        }

        //impede o objeto de se movimentar
        else if (state == GLUT_UP)
        {


        }

    }

    //possibilita rotacionar o objeto pelo botão yposeito
    else if (button == GLUT_RIGHT_BUTTON)
    {

        if (state == GLUT_DOWN)
        {



            // Zoom-in

        }
        else if (state == GLUT_UP)
        {


        }

    }

    //possibilita aumentar o objeto pelo botão do meio
    else if(button==GLUT_MIDDLE_BUTTON)
    {
        if (state == GLUT_DOWN)
        {

        }
        else if (state == GLUT_UP)
        {


        }
    }

}

void TeclasEspeciais(int key, int x, int y)
{

    switch (key)
    {

    case GLUT_KEY_UP:

        moveup=1;

        break;

    case GLUT_KEY_DOWN:

        movedown=1;

        break;

    case GLUT_KEY_LEFT:

        moveleft=1;

        break;

    case GLUT_KEY_RIGHT:

        moveright=1;

        break;

    case GLUT_KEY_END:

        exit(0);

    break;


    }

}

void motion(int x, int y)
{
    static float sx=0;
    static float sy=0;
    static float ang=0;
    static float ang1=0;
    float ang0;
    float x0,z0,x1,y1,z1,md;
    float ** rotationMatrix;
    float ** inputMatrix=alocarMatriz(4,1);
    float ** outputMatrix;

    ang=-1.5*(x - sx)/(180.0*M_PI);
    ang1=2.5*(y - sy)/(180.0*M_PI);

    cx=(cx*cos(ang)-xpos)+(cz*sin(ang)-zpos);
    cz=(cx*-sin(ang)-xpos)+(cz*cos(ang)-zpos);

    ang0=M_PI/2.0-atan((cx-xpos)==0?M_PI/2.0:(cz-zpos)/(cx-xpos));

    x0=cx-xpos;
    z0=cz-zpos;
    x1=z0;
    z1=x0*(-1);
    md=sqrt(x1*x1+z1*z1);
    x1=(x1)/md;
    z1=(z1)/md;


    rotationMatrix=setUpRotationMatrix(ang1, x1, 0, z1);
    inputMatrix[0][0]=cx;
    inputMatrix[1][0]=cy;
    inputMatrix[2][0]=cz;
    inputMatrix[3][0]=1.0;

    outputMatrix=multiplyMatrix(rotationMatrix,inputMatrix);

    cx=outputMatrix[0][0]-xpos;
    cy=outputMatrix[1][0]-ypos;
    cz=outputMatrix[2][0]-zpos;

    sx = (float)x;
    sy = (float)y;


    EspecificaParametrosVisualizacao();

}

void DefineIluminacao()
{
    GLfloat luzAmbiente[4]= {0.5,0.5,0.5,1.0};
    GLfloat luzDifusa[4]= {0.7,0.7,0.7,1.0};	  // "cor"
    GLfloat luzEspecular[4]= {1.0, 1.0, 1.0, 1.0}; // "brilho"
    GLfloat posicaoLuz[4]= {0.0, 40.0, 0.0, 1.0};

    // Capacidade de brilho do material
    GLfloat especularidade[4]= {1.0,1.0,1.0,1.0};
    GLint especMaterial = 60;

    // Define a refletância do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
    // Define a concentração do brilho
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);
}

//os valores de inicio
void init(void)
{
    glClearColor(0,0.7,1,0);
    angle=50;
    angle3=45;
    scl=100;
    cx=5000;
    cy=75;
    cz=5000;
    vx=0;
    vy=1;
    vz=0;
    mapa[0+10][1+10][0+10]=1;
    mapa[4+10][1+10][4+10]=1;

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHTING);
    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);

    glEnable(GL_TEXTURE_2D);

    text4 = lertexturabmp( "texture4.bmp", 1 );
    text3 = lertexturabmp( "texture3.bmp", 1 );
    text2 = lertexturabmp( "texture2.bmp", 1 );
    text = lertexturabmp( "texture.bmp", 1 );

}

void inimigo(){


        //corpo
        glPushMatrix();
        glTranslatef(0,53,0);
        glScalef(10,25,10);
        cubo(text4,text4);
        glPopMatrix();

        //cabeça
        glPushMatrix();
        glTranslatef(0,93,0);
        glScalef(15,15,15);
        cubo(text3,text3);
        glPopMatrix();

}

void pulainimigo(){
static float t=0;
static float t2=0;

    glTranslatef(-150-70*cos(t2),abs(50*cos(t+15)),0);
    glScalef(1,0.65,1);
    glPushMatrix();
    inimigo();
    glPopMatrix();

    t+=0.1;

    xposi=(GLfloat)-150-70*cos(t2);
    t2+=0.02;
}

int posmapa(int x,int y, int z){
    return (mapa[x+10][y+10][z+10]);
}



void Timer(int value)
{
float ang=M_PI-atan((cx-xpos)==0?M_PI:(cz-zpos)/(cx-xpos));
int cdx=(int)xpos/50;
int cdy=(int)ypos/50;
int cdz=(int)zpos/50;
float z=((cz-zpos)>0?1:-1)*abs(5*sin(ang));
float x=((cx-xpos)>0?1:-1)*abs(5*cos(ang));


    if((moveup)&& !(posmapa(cdx+x/10,cdy,cdz+z/10)))
    {
        zpos+=z;
        xpos+=x;
        cz+=z;
        cx+=x;

    }

    if((movedown)&& !(posmapa(cdx-x/5,cdy,cdz-z/5)))
    {
        zpos-=z;
        xpos-=x;
        cz-=z;
        cx-=x;
    }

    if((moveleft)&& !(posmapa(cdx+z/5,cdy,cdz-x/5)))
    {

        xpos+=z;
        cx+=z;
        zpos+=x*(-1);
        cz+=x*(-1);

    }

    if((moveright)&& !(posmapa(cdx-z/5,cdy,cdz+x/5)))
    {
        xpos-=z;
        cx-=z;
        zpos-=x*(-1);
        cz-=x*(-1);


    }

    //condicao para o inimigo "matar"
    if(((round2(xpos)<=xposi+10)&&(round2(xpos)>=round2(xposi)-10))&&((round2(zpos)>=round2(zposi)-10)&&(round2(zpos)<=round2(zposi)+10)))
    exit(0);

    EspecificaParametrosVisualizacao();


    glutTimerFunc(10,Timer, 0);
}

void teclasup(int key, int x, int y)
{

    switch (key)
    {

    case GLUT_KEY_UP:

        moveup=0;

        break;

    case GLUT_KEY_DOWN:

        movedown=0;

        break;

    case GLUT_KEY_LEFT:

        moveleft=0;

        break;

    case GLUT_KEY_RIGHT:

        moveright=0;

        break;


    }

}

// Programa Principal
int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH| GLUT_MULTISAMPLE);
    glutInitWindowSize(800,800);
    glutCreateWindow("mine");
    glutFullScreen();
    glutDisplayFunc(display);

    glutSpecialFunc(TeclasEspeciais);
    glutSpecialUpFunc(teclasup);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutMouseFunc(GerenciaMouse);
    glutPassiveMotionFunc(motion);
    glutTimerFunc(10, Timer, 0);
    init();


    glutMainLoop();
}
