#include "../include/GLCanvas.hpp"
#include <wx/msgdlg.h>
#include <wx/dcclient.h>

BEGIN_EVENT_TABLE(GLCanvas, wxGLCanvas)
    EVT_PAINT(GLCanvas::OnPaint)
    EVT_MOUSE_EVENTS(GLCanvas::OnMouse)
    EVT_SIZE(GLCanvas::OnSize)
END_EVENT_TABLE()

GLCanvas::GLCanvas(wxWindow* parent)
    : wxGLCanvas(parent, wxID_ANY, nullptr, wxDefaultPosition, wxDefaultSize,
                 wxFULL_REPAINT_ON_RESIZE)
{
    _context = new wxGLContext(this);
    
    _shapes.push_back(new Triangle());
    _shapes.push_back(new Square());
    _shapes.push_back(new Circle());
    _shapeStates = std::vector<bool>(3, false);

    // Create toggle button with scaled PNG image
    wxBitmap buttonBitmap("resources/button.png", wxBITMAP_TYPE_PNG);
    wxImage img = buttonBitmap.ConvertToImage();
    img.Rescale(30, 30, wxIMAGE_QUALITY_HIGH);
    buttonBitmap = wxBitmap(img);
    
    // Position button in top-right corner with 10px padding
    _toggleButton = new wxButton(this, ID_TOGGLE_PANEL, "", 
                               wxPoint(GetSize().x - 40, 10), 
                               wxSize(30, 30));
    _toggleButton->SetBitmap(buttonBitmap);
    _toggleButton->SetWindowStyleFlag(wxBORDER_NONE);  // Remove border
}

GLCanvas::~GLCanvas() {
    for (Shape* shape : _shapes)
        delete shape;
    if (_context)
        delete _context;
}

void GLCanvas::OnSize(wxSizeEvent& evt) {
    int width, height;
    GetClientSize(&width, &height);
    SetCurrent(*_context);
    glViewport(0, 0, width, height);
    
    // Update button position to stay in top-right corner
    if (_toggleButton) {
        _toggleButton->SetPosition(wxPoint(width - 50, 10));
    }
    
    Refresh();
    evt.Skip();
}

void GLCanvas::OnPaint(wxPaintEvent&) {
    wxGLCanvas::SetCurrent(*_context);
    wxPaintDC(this);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw shapes
    for(size_t i = 0; i < _shapes.size(); ++i) {
        if(_shapeStates[i]) {
            _shapes[i]->Draw();
        }
    }

    SwapBuffers();
}

void GLCanvas::OnMouse(wxMouseEvent& evt) {
    if (evt.LeftDown()) {
        wxSize size = GetSize();
        float x = (2.0f * evt.GetX() / size.x) - 1.0f;
        float y = 1.0f - (2.0f * evt.GetY() / size.y);


        if (x > 0.85f && x < 0.95f && y > 0.85f && y < 0.95f) {
            wxCommandEvent event(wxEVT_BUTTON);
            event.SetId(ID_TOGGLE_PANEL);
            wxPostEvent(GetParent(), event);
        }
    }
}

void GLCanvas::ToggleShape(int index, bool state) {
    if (index >= 0 && index < static_cast<int>(_shapeStates.size())) {
        _shapeStates[index] = state;
        Refresh();
    }
}

void GLCanvas::UpdateScale(float scale) {
    for (Shape* shape : _shapes) {
        shape->SetScale(scale);
    }
    Refresh();
}

void GLCanvas::UpdatePosition(float x, float y) {
    for (Shape* shape : _shapes) {
        shape->SetPosition(x, y);
    }
    Refresh();
}
