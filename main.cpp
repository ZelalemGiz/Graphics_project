#include <GL/glut.h>
#include <cmath>

const float PI = 3.1415926535f;


// Transformation variables
float translateX = 0.0f;
float translateY = 0.0f;
float rotateAngle = 0.0f;
float scaleX = 1.0f;
float scaleY = 1.0f;

// Window dimensions
int windowWidth = 1200;
int windowHeight = 800;


// scaled to -1000 to 1000
const int SCALE = 1000;

void drawRectangle(int x1, int y1, int x2, int y2) {
    glBegin(GL_QUADS);
    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glVertex2i(x2, y1);
    glVertex2i(x1, y1);
    glEnd();
}

void drawArc(int cx, int cy, int r_in, int r_out,float start_angle, float end_angle) {
    int segments = 50;
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; i++) {
        float theta  = start_angle + (end_angle - start_angle) * i / segments;
        float rx_in  = r_in,        ry_in  = r_in  * 2.5f;
        float rx_out = r_out,       ry_out = r_out * 2.5f;
        glVertex2i(cx + (int)(rx_in  * cos(theta)), cy + (int)(ry_in  * sin(theta)));
        glVertex2i(cx + (int)(rx_out * cos(theta)), cy + (int)(ry_out * sin(theta)));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    //  transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Calculate the center of the content (midpoint of flag and JS logo)
    int contentCenterX = -400;  
    int contentCenterY = 0;    

    // Apply translation 
    glTranslatef(translateX * SCALE, translateY * SCALE, 0.0f);

    //  rotation 
    glTranslatef(contentCenterX, contentCenterY, 0.0f);
    glRotatef(rotateAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-contentCenterX, -contentCenterY, 0.0f);

    //  scaling
    glTranslatef(contentCenterX, contentCenterY, 0.0f);
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(-contentCenterX, -contentCenterY, 0.0f);

    // Orange  (top of the flag)
    glColor3f(255.0f/255.0f, 153.0f/255.0f, 51.0f/255.0f);
    drawRectangle(-1000, 333, 200, 1000);

    // White (middle of thr flag)
    glColor3f(1.0f, 1.0f, 1.0f);
    drawRectangle(-1000, -333, 200, 333);

    // Green  (bottom part of the flag)
    glColor3f(19.0f/255.0f, 136.0f/255.0f, 8.0f/255.0f);
    drawRectangle(-1000, -1000, 200, -333);

    // Ashoka Chakra(circle that center of the flag)
    int cx = -400, cy = 0;
    int rx  = 120, ry = 300;

    glColor3f(0.0f, 0.0f, 128.0f / 255.0f);

    // Outer ring
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 100; i++) {
        float t1 = 2.0f * PI * i       / 100.0f;
        float t2 = 2.0f * PI * (i + 1) / 100.0f;
        float rx_out = rx,        ry_out = ry;
        float rx_in  = rx * 0.85f, ry_in = ry * 0.85f;

        glVertex2i(cx + (int)(rx_in  * cos(t1)), cy + (int)(ry_in  * sin(t1)));
        glVertex2i(cx + (int)(rx_out * cos(t1)), cy + (int)(ry_out * sin(t1)));
        glVertex2i(cx + (int)(rx_out * cos(t2)), cy + (int)(ry_out * sin(t2)));

        glVertex2i(cx + (int)(rx_in  * cos(t1)), cy + (int)(ry_in  * sin(t1)));
        glVertex2i(cx + (int)(rx_out * cos(t2)), cy + (int)(ry_out * sin(t2)));
        glVertex2i(cx + (int)(rx_in  * cos(t2)), cy + (int)(ry_in  * sin(t2)));
    }
    glEnd();

    // Centre dot
    glBegin(GL_POLYGON);
    for (int i = 0; i < 30; i++) {
        float theta = 2.0f * PI * i / 30.0f;
        float dotRX = rx * 0.15f;
        float dotRY = ry * 0.15f;
        glVertex2i(cx + (int)(dotRX * cos(theta)), cy + (int)(dotRY * sin(theta)));
    }
    glEnd();

    // 24 spokes(draws center point to outer ring)
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 24; i++) {
        float theta = 2.0f * PI * i / 24.0f;
        glVertex2i(cx, cy);
        glVertex2i(cx + (int)(rx * 0.85f * cos(theta)), cy + (int)(ry * 0.85f * sin(theta)));
    }
    glEnd();

    // JavaScript Logo
    glColor3f(0.0f, 0.0f, 0.0f);//background color
    drawRectangle(200, -1000, 1000, 1000);

    glColor3f(1.0f, 1.0f, 1.0f);

    int text_r_in  = 30;
    int text_r_out = 90;

    int j_cx   = 510;
    int s_cx   = 730;
    int cy_top = -165;
    int cy_bot = -615;

    // Letter 'J'
    drawArc(j_cx, cy_bot, text_r_in, text_r_out, PI, 2.0f * PI);
    drawRectangle(j_cx + text_r_in, cy_bot, j_cx + text_r_out, cy_top + 225);
    drawRectangle(j_cx - text_r_out, cy_bot, j_cx - text_r_in, cy_bot + 150);

    // Letter 'S'
    drawArc(s_cx, cy_top, text_r_in, text_r_out, 0.0f, 5.0f * PI / 4.0f);
    drawRectangle(s_cx + text_r_in, cy_top - 120, s_cx + text_r_out, cy_top);

    glBegin(GL_QUADS);
    glVertex2i(s_cx + (int)(text_r_out * cos(5.0f*PI/4.0f)), cy_top + (int)(text_r_out * 2.5f * sin(5.0f*PI/4.0f)));
    glVertex2i(s_cx + (int)(text_r_in  * cos(5.0f*PI/4.0f)), cy_top + (int)(text_r_in  * 2.5f * sin(5.0f*PI/4.0f)));
    glVertex2i(s_cx + (int)(text_r_out * cos(PI/4.0f)),       cy_bot + (int)(text_r_out * 2.5f * sin(PI/4.0f)));
    glVertex2i(s_cx + (int)(text_r_in  * cos(PI/4.0f)),       cy_bot + (int)(text_r_in  * 2.5f * sin(PI/4.0f)));
    glEnd();

    drawArc(s_cx, cy_bot, text_r_in, text_r_out, -PI, PI / 4.0f);
    drawRectangle(s_cx - text_r_out, cy_bot, s_cx - text_r_in, cy_bot + 120);

    glFlush();
}

// Keyboard controls for transformations
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Translation
        case 'w': translateY += 0.05f; break;
        case 's': translateY -= 0.05f; break;
        case 'a': translateX -= 0.05f; break;
        case 'd': translateX += 0.05f; break;

        // Rotation
        case 'q': rotateAngle += 5.0f; break;
        case 'e': rotateAngle -= 5.0f; break;

        // Scaling
        case 'r': scaleX += 0.1f; scaleY += 0.1f; break;
        case 'f': scaleX -= 0.1f; scaleY -= 0.1f; break;

        // Reset to original
        case '0':
            translateX = 0.0f;
            translateY = 0.0f;
            rotateAngle = 0.0f;
            scaleX = 1.0f;
            scaleY = 1.0f;
            break;

        case 27: exit(0); break;  // ESC key
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: translateY += 0.05f; break;
        case GLUT_KEY_DOWN: translateY -= 0.05f; break;
        case GLUT_KEY_LEFT: translateX -= 0.05f; break;
        case GLUT_KEY_RIGHT: translateX += 0.05f; break;
    }
    glutPostRedisplay();
}

void reshape(int w,int h) {
    windowWidth = w;
    windowHeight = h;
    
//image width and hieght
    int vw = 1000;
    int vh = 400;

    int x = (w - vw) / 2;
    int y = (h - vh) / 2;

    // Ensure  doesn't go negative
    if (x < 0) x = 0;
    if (y < 0) y = 0;

    glViewport(x, y, 1000, 400);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1000, 1000, -1000, 1000);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Indian Flag & JS Logo - With Transformations (Integer Coords)");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}
