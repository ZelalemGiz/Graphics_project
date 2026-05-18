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

float t = 0.0f;

void drawRectangle(int x1, int y1, int x2, int y2) {
    glBegin(GL_QUADS);
    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glVertex2i(x2, y1);
    glVertex2i(x1, y1);
    glEnd();
}

void drawWavyBand(float x_start, float x_end, float y_bottom, float y_top, float time, float r, float g, float b) {
    glColor3f(r, g, b);

    int num_segments = 100;
    float segment_width = (x_end - x_start) / num_segments;

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= num_segments; ++i) {
        float current_x = x_start + i * segment_width;

        float wave_amplitude = 60.0f;
        float wave_frequency = 0.005f;
        float speed = 3.0f;

        float dampening = (current_x - x_start) / (x_end - x_start);

        float y_offset = sin(current_x * wave_frequency - time * speed) * wave_amplitude * dampening;

        glVertex2f(current_x, y_bottom + y_offset);
        glVertex2f(current_x, y_top + y_offset);
    }
    glEnd();
}

void drawSpokes(float cx, float cy, float radius, float time) {
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 24; i++) {
        float theta = 2.0f * PI * i / 24.0f;
        glVertex2f(cx, cy);
        glVertex2f(cx + radius * cos(theta), cy + radius * sin(theta));
    }
    glEnd();
}

void drawChakra(float base_cx, float base_cy, float rx, float ry, float time, float x_start, float x_end) {
    glColor3f(0.0f, 0.0f, 128.0f / 255.0f);

    float wave_amplitude = 60.0f;
    float wave_frequency = 0.005f;
    float speed = 3.0f;
    float dampening = (base_cx - x_start) / (x_end - x_start);
    float y_offset = sin(base_cx * wave_frequency - time * speed) * wave_amplitude * dampening;

    float cx = base_cx;
    float cy = base_cy + y_offset;

    float radius = rx;

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 100; i++) {
        float t1 = 2.0f * PI * i       / 100.0f;
        float t2 = 2.0f * PI * (i + 1) / 100.0f;
        float rx_out = radius;
        float rx_in  = radius * 0.85f;

        glVertex2f(cx + rx_in  * cos(t1), cy + rx_in  * sin(t1));
        glVertex2f(cx + rx_out * cos(t1), cy + rx_out * sin(t1));
        glVertex2f(cx + rx_out * cos(t2), cy + rx_out * sin(t2));

        glVertex2f(cx + rx_in  * cos(t1), cy + rx_in  * sin(t1));
        glVertex2f(cx + rx_out * cos(t2), cy + rx_out * sin(t2));
        glVertex2f(cx + rx_in  * cos(t2), cy + rx_in  * sin(t2));
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < 30; i++) {
        float theta = 2.0f * PI * i / 30.0f;
        float dotR = radius * 0.15f;
        glVertex2f(cx + dotR * cos(theta), cy + dotR * sin(theta));
    }
    glEnd();

    drawSpokes(cx, cy, radius * 0.85f, time);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    int contentCenterX = 100;
    int contentCenterY = 0;

    glTranslatef(translateX * SCALE, translateY * SCALE, 0.0f);

    glTranslatef(contentCenterX, contentCenterY, 0.0f);
    glRotatef(rotateAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-contentCenterX, -contentCenterY, 0.0f);

    glTranslatef(contentCenterX, contentCenterY, 0.0f);
    glScalef(scaleX, scaleY, 1.0f);
    glTranslatef(-contentCenterX, -contentCenterY, 0.0f);

    float flag_left = -1100.0f;
    float flag_right = 1300.0f;

    drawWavyBand(flag_left, flag_right, 333.0f, 1000.0f, t, 255.0f/255.0f, 153.0f/255.0f, 51.0f/255.0f);
    drawWavyBand(flag_left, flag_right, -333.0f, 333.0f, t, 1.0f, 1.0f, 1.0f);
    drawWavyBand(flag_left, flag_right, -1000.0f, -333.0f, t, 19.0f/255.0f, 136.0f/255.0f, 8.0f/255.0f);

    float chakra_base_cx = 100.0f;
    float chakra_base_cy = 0.0f;
    float chakra_radius = 280.0f;
    drawChakra(chakra_base_cx, chakra_base_cy, chakra_radius, chakra_radius, t, flag_left, flag_right);

    glColor3f(0.5f, 0.5f, 0.5f);
    drawRectangle(-1140, -1500, -1100, 1050);

    glutSwapBuffers();
}
void idle() {
    t += 0.01f;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': translateY += 0.05f; break;
        case 's': translateY -= 0.05f; break;
        case 'a': translateX -= 0.05f; break;
        case 'd': translateX += 0.05f; break;

        case 'q': rotateAngle += 5.0f; break;
        case 'e': rotateAngle -= 5.0f; break;

        case 'r': scaleX += 0.1f; scaleY += 0.1f; break;
        case 'f': scaleX -= 0.1f; scaleY -= 0.1f; break;

        case '0':
            translateX = 0.0f;
            translateY = 0.0f;
            rotateAngle = 0.0f;
            scaleX = 1.0f;
            scaleY = 1.0f;
            break;

        case 27: exit(0); break;
    }
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP: translateY += 0.05f; break;
        case GLUT_KEY_DOWN: translateY -= 0.05f; break;
        case GLUT_KEY_LEFT: translateX -= 0.05f; break;
        case GLUT_KEY_RIGHT: translateX += 0.05f; break;
    }
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)w / (float)h;
    if (w >= h) {
        gluOrtho2D(-1300 * aspect, 1300 * aspect, -1300, 1300);
    } else {
        gluOrtho2D(-1300, 1300, -1300 / aspect, 1300 / aspect);
    }

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Animated Indian Flag");

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
