void asterisk(int x, int y) {
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();

    y += 6;
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y+15);
    glVertex2f(x-7, y+4);
    glVertex2f(x+7, y+11);
    glVertex2f(x-7, y+11);
    glVertex2f(x+7, y+4);
    glEnd();
}

void pluss(int x, int y) {
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();

    y += 6;
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y+14);
    glVertex2f(x-7, y+7);
    glVertex2f(x+7, y+7);
    glEnd();
}

void letterA(int x, int y) {
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();

    y += 6;
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2f(x-5, y+5);
    glVertex2f(x+5, y+5);
    glVertex2f(x, y+15);
    glVertex2f(x-6, y);
    glVertex2f(x, y+15);
    glVertex2f(x+6, y);
    glEnd();
}

void letterB(int x, int y) {
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();

    x += -4;
    y += 6;
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2f(x, y-1);
    glVertex2f(x, y+15);
    glVertex2f(x, y+13);
    glVertex2f(x+9, y+13);
    glVertex2f(x, y+7);
    glVertex2f(x+9, y+7);
    glVertex2f(x, y+1);
    glVertex2f(x+9, y+1);
    glVertex2f(x+9, y+1);
    glVertex2f(x+9, y+6);
    glVertex2f(x+9, y+8);
    glVertex2f(x+9, y+12);
    glEnd();
}

void letterC(int x, int y) {
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();

    x += -4;
    y += 6;
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x+9, y);
    glVertex2f(x, y);
    glVertex2f(x, y+15);
    glVertex2f(x, y+15);
    glVertex2f(x+9, y+15);
    glEnd();
}

void letterD(int x, int y) {
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();

    y += 6;
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2f(x-7, y);
    glVertex2f(x+5, y);
    glVertex2f(x-5, y);
    glVertex2f(x-5, y+15);
    glVertex2f(x-7, y+15);
    glVertex2f(x+5, y+15);
    glVertex2f(x+6, y+1);
    glVertex2f(x+6, y+14);
    glEnd();
}

void letterE(int x, int y) {
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();

    x += -4;
    y += 6;
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2f(x, y-1);
    glVertex2f(x, y+15);
    glVertex2f(x, y+13);
    glVertex2f(x+10, y+13);
    glVertex2f(x, y+7);
    glVertex2f(x+7, y+7);
    glVertex2f(x, y+1);
    glVertex2f(x+10, y+1);
    glEnd();
}

void letterF(int x, int y) {
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
    x += -2;
    y += 5;
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y+15);
    glVertex2f(x, y+13);
    glVertex2f(x+10, y+13);
    glVertex2f(x, y+7);
    glVertex2f(x+7, y+7);
    glEnd();
}

void letterG(int x, int y) {
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();

    y += 6;
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2f(x-6, y);
    glVertex2f(x+6, y);
    glVertex2f(x-6, y+1);
    glVertex2f(x-6, y+14);
    glVertex2f(x-6, y+15);
    glVertex2f(x+6, y+15);
    glVertex2f(x+6, y+1);
    glVertex2f(x+6, y+8);
    glVertex2f(x+6, y+8);
    glVertex2f(x-1, y+8);
    glEnd();
}

void letterH(int x, int y) {
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();

    y += 6;
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2f(x-4, y+8);
    glVertex2f(x+4, y+8);
    glVertex2f(x-4, y);
    glVertex2f(x-4, y+15);
    glVertex2f(x+4, y);
    glVertex2f(x+4, y+15);
    glEnd();
}

void letterI(int x, int y) {
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();

    y += 6;
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x, y+15);
    glVertex2f(x-5, y);
    glVertex2f(x+5, y);
    glVertex2f(x-5, y+15);
    glVertex2f(x+5, y+15);
    glEnd();
}

void letterK(int x, int y) {
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();

    y += 6;
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2f(x-5, y);
    glVertex2f(x-5, y+15);
    glVertex2f(x-5, y+8);
    glVertex2f(x+5, y+13);
    glVertex2f(x-5, y+8);
    glVertex2f(x+5, y+1);
    glEnd();
}

void letterL(int x, int y) {
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();

    y += 6;
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2f(x-5, y);
    glVertex2f(x+5, y);
    glVertex2f(x-4, y-2);
    glVertex2f(x-4, y+14);
    glEnd();
}

void letterM(int x, int y) {
    glPointSize(4.0);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();

    y += 6;
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glVertex2f(x, y+5);
    glVertex2f(x-4, y+15);
    glVertex2f(x, y+5);
    glVertex2f(x+4, y+15);
    glVertex2f(x-6, y);
    glVertex2f(x-6, y+15);
    glVertex2f(x+6, y);
    glVertex2f(x+6, y+15);
    glEnd();
}
