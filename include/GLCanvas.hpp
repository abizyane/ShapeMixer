#pragma once
#include <wx/glcanvas.h>
#include <wx/image.h>
#include <wx/dc.h>
#include <wx/dcclient.h>
#include <vector>
#include "Shape.hpp"
#include "Constants.hpp"

class GLCanvas : public wxGLCanvas {
private:
    wxGLContext* _context;
    std::vector<Shape*> _shapes;
    std::vector<bool> _shapeStates;
    GLuint _buttonTexture;
    
    void OnPaint(wxPaintEvent& evt);
    void OnMouse(wxMouseEvent& evt);
    void OnSize(wxSizeEvent& evt);
    GLuint LoadTexture(const wxString& filename);

public:
    GLCanvas(wxWindow* parent);
    ~GLCanvas();

    void ToggleShape(int index, bool state);
    void UpdateScale(float scale);
    void UpdatePosition(float x, float y);
    float GetHorizontalPosition() const { return _shapes[0]->GetX(); }
    float GetVerticalPosition() const { return _shapes[0]->GetY(); }

    DECLARE_EVENT_TABLE()
};
