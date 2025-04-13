#pragma once
#include <GL/gl.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Shape {
protected:
    float _scale;
    float _posX;
    float _posY;

public:
    Shape() : _scale(1.0f), _posX(0.0f), _posY(0.0f) {}
    virtual void Draw() const = 0;
    void SetScale(float scale) { _scale = scale; }
    void SetPosition(float x, float y) { _posX = x; _posY = y; }
    float GetX() const { return _posX; }
    float GetY() const { return _posY; }
    virtual ~Shape() {}
};

class Triangle : public Shape {
public:
    void Draw() const override {
        glPushMatrix();
        glTranslatef(_posX, _posY, 0.0f);
        glScalef(_scale, _scale, 1.0f);
        
        glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.3f, -0.225f);
        glVertex2f(0.3f, -0.225f);
        glVertex2f(0.0f, 0.35f);
        glEnd();
        
        glPopMatrix();
    }
};

class Square : public Shape {
public:
    void Draw() const override {
        glPushMatrix();
        glTranslatef(_posX, _posY, 0.0f);
        glScalef(_scale, _scale, 1.0f);
        
        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.225f, -0.225f);
        glVertex2f(0.225f, -0.225f);
        glVertex2f(0.225f, 0.225f);
        glVertex2f(-0.225f, 0.225f);
        glEnd();
        
        glPopMatrix();
    }
};

class Circle : public Shape {
public:
    void Draw() const override {
        glPushMatrix();
        glTranslatef(_posX, _posY, 0.0f);
        glScalef(_scale, _scale, 1.0f);
        
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        for(int i = 0; i <= 32; i++) {
            float angle = 2.0f * M_PI * i / 32;
            glVertex2f(0.25f * cos(angle), 0.25f * sin(angle));
        }
        glEnd();
        
        glPopMatrix();
    }
};