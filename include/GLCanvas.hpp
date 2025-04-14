#pragma once
#include <wx/glcanvas.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <vector>
#include "Shape.hpp"

const int ID_TOGGLE_PANEL = wxID_HIGHEST + 1;

class GLCanvas : public wxGLCanvas {
private:
    wxGLContext* _context;
    std::vector<Shape*> _shapes;
    std::vector<bool> _shapeStates;
    wxButton* _toggleButton;
    
    void OnPaint(wxPaintEvent& evt);
    void OnMouse(wxMouseEvent& evt);
    void OnSize(wxSizeEvent& evt);

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
