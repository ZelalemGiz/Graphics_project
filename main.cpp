#include <GL/glut.h>
#include <cmath>

const float PI = 3.1415926535f;

float translateX = 0.0f;
float translateY = 0.0f;
float rotateAngle = 0.0f;
float scaleX = 1.0f;
float scaleY = 1.0f;

int windowWidth = 1200;
int windowHeight = 800;

const int SCALE = 1000;

float waveAngle = 0.0f;
const float WAVE_SPEED = 0.1f;
const float WAVE_AMPLITUDE = 35.0f;

float get3DShading(float a) {

    float slope = cos(waveAngle + (a * 0.01f));

    float shade = 10.95f + 0.20f * slope;

    if (shade > 1.0f) shade = 1.0f;
    if (shade < 0.0f) shade = 0.0f;

    return shade;
}

void drawWavingRectangle3D(int x1, int y1, int x2, int y2, float baseR, float baseG, float baseB) {

    int segments = 60;

    float width = x2 - x1;
    float segWidth = width / segments;

    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i <= segments; i++) {

        float currX = x1 + i * segWidth;

        float waveOffset =
            WAVE_AMPLITUDE *
            sin(waveAngle + (currX * 0.005f));

        float shade = get3DShading(currX);

        glColor3f(baseR * shade, baseG * shade, baseB * shade);

        glVertex2f(currX, y2 + waveOffset);
        glVertex2f(currX, y1 + waveOffset);
    }

    glEnd();
}

void drawRectangle(int x1, int y1, int x2, int y2) {

    glBegin(GL_QUADS);

    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glVertex2i(x2, y1);
    glVertex2i(x1, y1);

    glEnd();
}

void drawArc(int cx, int cy, int r_in, int r_out,
             float start_angle, float end_angle) {

    int segments = 50;

    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i <= segments; i++) {

        float theta =
            start_angle +
            (end_angle - start_angle) * i / segments;

        float rx_in = r_in;
        float ry_in = r_in * 2.5f;

        float rx_out = r_out;
        float ry_out = r_out * 2.5f;

        glVertex2i(
            cx + (int)(rx_in * cos(theta)),
            cy + (int)(ry_in * sin(theta))
        );

        glVertex2i(
            cx + (int)(rx_out * cos(theta)),
            cy + (int)(ry_out * sin(theta))
        );
    }

    glEnd();
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    int contentCenterX = -400;
    int contentCenterY = 0;

    glTranslatef(
        translateX * SCALE,
        translateY * SCALE,
        0.0f
    );

    glTranslatef(contentCenterX, contentCenterY, 0.0f);

    glRotatef(
        rotateAngle,
        0.0f,
        0.0f,
        1.0f
    );

    glTranslatef(
        -contentCenterX,
        -contentCenterY,
        0.0f
    );

    glTranslatef(contentCenterX, contentCenterY, 0.0f);

    glScalef(scaleX, scaleY, 1.0f);

    glTranslatef(
        -contentCenterX,
        -contentCenterY,
        0.0f
    );

    drawWavingRectangle3D(
        -1000, 333,
        200, 1000,
        255.0f/255.0f,
        153.0f/255.0f,
        51.0f/255.0f
    );

    drawWavingRectangle3D(
        -1000, -333,
        200, 333,
        1.0f,
        1.0f,
        1.0f
    );

    drawWavingRectangle3D(
        -1000, -1000,
        200, -333,
        19.0f/255.0f,
        136.0f/255.0f,
        8.0f/255.0f
    );

    int cx = -400;
    int cy = 0;

    int rx = 120;
    int ry = 300;

    float chkR = 0.0f;
    float chkG = 0.0f;
    float chkB = 128.0f / 255.0f;

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < 100; i++) {

        float t1 = 2.0f * PI * i / 100.0f;
        float t2 = 2.0f * PI * (i + 1) / 100.0f;

        float rx_out = rx;
        float ry_out = ry;

        float rx_in = rx * 0.85f;
        float ry_in = ry * 0.85f;

        float xA = cx + rx_in * cos(t1);
        float xB = cx + rx_out * cos(t1);
        float xC = cx + rx_out * cos(t2);
        float xD = cx + rx_in * cos(t2);

        float shadeA = get3DShading(xA);
        float shadeB = get3DShading(xB);
        float shadeC = get3DShading(xC);
        float shadeD = get3DShading(xD);

        glColor3f(chkR * shadeA,
                  chkG * shadeA,
                  chkB * shadeA);

        glVertex2f(
            xA,
            cy + ry_in * sin(t1) +
            WAVE_AMPLITUDE *
            sin(waveAngle + (xA * 0.005f))
        );

        glColor3f(chkR * shadeB,
                  chkG * shadeB,
                  chkB * shadeB);

        glVertex2f(
            xB,
            cy + ry_out * sin(t1) +
            WAVE_AMPLITUDE *
            sin(waveAngle + (xB * 0.005f))
        );

        glColor3f(chkR * shadeC,
                  chkG * shadeC,
                  chkB * shadeC);

        glVertex2f(
            xC,
            cy + ry_out * sin(t2) +
            WAVE_AMPLITUDE *
            sin(waveAngle + (xC * 0.005f))
        );

        glColor3f(chkR * shadeA,
                  chkG * shadeA,
                  chkB * shadeA);

        glVertex2f(
            xA,
            cy + ry_in * sin(t1) +
            WAVE_AMPLITUDE *
            sin(waveAngle + (xA * 0.005f))
        );

        glColor3f(chkR * shadeC,
                  chkG * shadeC,
                  chkB * shadeC);

        glVertex2f(
            xC,
            cy + ry_out * sin(t2) +
            WAVE_AMPLITUDE *
            sin(waveAngle + (xC * 0.005f))
        );

        glColor3f(chkR * shadeD,
                  chkG * shadeD,
                  chkB * shadeD);

        glVertex2f(
            xD,
            cy + ry_in * sin(t2) +
            WAVE_AMPLITUDE *
            sin(waveAngle + (xD * 0.005f))
        );
    }

    glEnd();

    glBegin(GL_POLYGON);

    for (int i = 0; i < 30; i++) {

        float theta = 2.0f * PI * i / 30.0f;

        float dotRX = rx * 0.15f;
        float dotRY = ry * 0.15f;

        float pX = cx + dotRX * cos(theta);

        float shade = get3DShading(pX);

        glColor3f(chkR * shade,
                  chkG * shade,
                  chkB * shade);

        glVertex2f(
            pX,
            cy + dotRY * sin(theta) +
            WAVE_AMPLITUDE *
            sin(waveAngle + (pX * 0.005f))
        );
    }

    glEnd();

    glLineWidth(2.0f);

    glBegin(GL_LINES);

    for (int i = 0; i < 24; i++) {

        float theta = 2.0f * PI * i / 24.0f;

        float pX2 = cx + rx * 0.85f * cos(theta);

        float shadeCenter = get3DShading(cx);

        glColor3f(chkR * shadeCenter,
                  chkG * shadeCenter,
                  chkB * shadeCenter);

        glVertex2f(
            cx,
            cy + WAVE_AMPLITUDE *
            sin(waveAngle + (cx * 0.005f))
        );

        float shadeOuter = get3DShading(pX2);

        glColor3f(chkR * shadeOuter,
                  chkG * shadeOuter,
                  chkB * shadeOuter);

        glVertex2f(
            pX2,
            cy + ry * 0.85f * sin(theta) +
            WAVE_AMPLITUDE *
            sin(waveAngle + (pX2 * 0.005f))
        );
    }

    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);

    drawRectangle(200, -1000, 1000, 1000);

    glColor3f(1.0f, 1.0f, 1.0f);

    int text_r_in = 50;
    int text_r_out = 100;

    int j_cx = 510;
    int s_cx = 730;

    int cy_top = -165;
    int cy_bot = -615;

    drawArc(
        j_cx,
        cy_bot,
        text_r_in,
        text_r_out,
        PI,
        2.0f * PI
    );

    drawRectangle(
        j_cx + text_r_in,
        cy_bot,
        j_cx + text_r_out,
        cy_top + 225
    );

    drawRectangle(
        j_cx - text_r_out,
        cy_bot,
        j_cx - text_r_in,
        cy_bot + 150
    );

    drawArc(
        s_cx,
        cy_top,
        text_r_in,
        text_r_out,
        0.0f,
        5.0f * PI / 4.0f
    );

    drawRectangle(
        s_cx + text_r_in,
        cy_top - 120,
        s_cx + text_r_out,
        cy_top
    );

    glBegin(GL_QUADS);

    glVertex2i(
        s_cx + (int)(text_r_out * cos(5.0f*PI/4.0f)),
        cy_top + (int)(text_r_out * 2.5f * sin(5.0f*PI/4.0f))
    );

    glVertex2i(
        s_cx + (int)(text_r_in * cos(5.0f*PI/4.0f)),
        cy_top + (int)(text_r_in * 2.5f * sin(5.0f*PI/4.0f))
    );

    glVertex2i(
        s_cx + (int)(text_r_out * cos(PI/4.0f)),
        cy_bot + (int)(text_r_out * 2.5f * sin(PI/4.0f))
    );

    glVertex2i(
        s_cx + (int)(text_r_in * cos(PI/4.0f)),
        cy_bot + (int)(text_r_in * 2.5f * sin(PI/4.0f))
    );

    glEnd();

    drawArc(
        s_cx,
        cy_bot,
        text_r_in,
        text_r_out,
        -PI,
        PI / 4.0f
    );

    drawRectangle(
        s_cx - text_r_out,
        cy_bot,
        s_cx - text_r_in,
        cy_bot + 120
    );

    glFlush();
}

void timer(int value) {

    waveAngle += WAVE_SPEED;

    glutPostRedisplay();

    glutTimerFunc(16, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {

        case 'u':
            translateY += 0.05f;
            break;

        case 'd':
            translateY -= 0.05f;
            break;

        case 'l':
            translateX -= 0.05f;
            break;

        case 'r':
            translateX += 0.05f;
            break;

        case 'q':
            rotateAngle += 5.0f;
            break;

        case 'e':
            rotateAngle -= 5.0f;
            break;

        case 'h':
            scaleX += 0.1f;
            scaleY += 0.1f;
            break;

        case 'f':
            scaleX -= 0.1f;
            scaleY -= 0.1f;
            break;

        case '0':

            translateX = 0.0f;
            translateY = 0.0f;

            rotateAngle = 0.0f;

            scaleX = 1.0f;
            scaleY = 1.0f;

            break;

        case '2':
            exit(0);
            break;
    }

    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {

    switch (key) {

        case GLUT_KEY_UP:
            translateY += 0.5f;
            break;

        case GLUT_KEY_DOWN:
            translateY -= 0.05f;
            break;

        case GLUT_KEY_LEFT:
            translateX -= 0.05f;
            break;

        case GLUT_KEY_RIGHT:
            translateX += 0.05f;
            break;
    }

    glutPostRedisplay();
}

void reshape(int w, int h) {

    windowWidth = w;
    windowHeight = h;

    int vw = 1000;
    int vh = 400;

    int x = (w - vw) / 2;
    int y = (h - vh) / 2;

    if (x < 0)
        x = 0;

    if (y < 0)
        y = 0;

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

    glutCreateWindow("3D Waving Indian Flag & Untouched JS Logo");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glutDisplayFunc(display);

    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);

    glutSpecialFunc(specialKeys);

    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return 0;
}
