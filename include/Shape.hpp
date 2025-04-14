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

class Julia : public Shape {
private:
    static const int MAX_ITERATIONS = 100;
    
public:
    void Draw() const override {
        glPushMatrix();
        glTranslatef(_posX, _posY, 0.0f);
        
        if (_scale <= 1.0f) {
            glScalef(_scale, _scale, 1.0f);
            glPointSize(1.0f);
            float step = 0.003f;
            
            DrawFractal(step);
        } else {
            glPointSize(_scale);
            float step = 0.003f / _scale;
            
            DrawFractal(step);
        }
        
        glPopMatrix();
    }

private:
    void DrawFractal(float step) const {
        glBegin(GL_POINTS);
        for(float x = -1.5f; x <= 1.5f; x += step) {
            for(float y = -1.5f; y <= 1.5f; y += step) {
                float zx = x;
                float zy = y;
                int i;
                
                float cx = -0.4f;
                float cy = 0.6f;
                
                for(i = 0; i < MAX_ITERATIONS; i++) {
                    float tmp = zx * zx - zy * zy + cx;
                    zy = 2.0f * zx * zy + cy;
                    zx = tmp;
                    
                    if(zx * zx + zy * zy > 4.0f) break;
                }
                
                if(i == MAX_ITERATIONS) {
                    glColor3f(1.0f, 0.0f, 1.0f);
                    glVertex2f(x * 0.5f, y * 0.5f);
                }
            }
        }
        glEnd();
    }
};