#include "../include/GLCanvas.hpp"

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

    SetCurrent(*_context);
    glEnable(GL_TEXTURE_2D);
    _buttonTexture = LoadTexture("resources/button.png");
    glDisable(GL_TEXTURE_2D);
}

GLCanvas::~GLCanvas() {
    for (Shape* shape : _shapes)
        delete shape;
    if (_context)
        delete _context;
    if (_buttonTexture)
        glDeleteTextures(1, &_buttonTexture);
}

void GLCanvas::OnSize(wxSizeEvent& evt) {
    int width, height;
    GetClientSize(&width, &height);
    SetCurrent(*_context);
    glViewport(0, 0, width, height);
    Refresh();
    evt.Skip();
}

void GLCanvas::OnPaint(wxPaintEvent&) {
    wxGLCanvas::SetCurrent(*_context);
    wxPaintDC(this);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    for(size_t i = 0; i < _shapes.size(); ++i) {
        if(_shapeStates[i]) {
            _shapes[i]->Draw();
        }
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _buttonTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(0.8f, 0.8f);
    glTexCoord2f(1, 0); glVertex2f(0.9f, 0.8f);
    glTexCoord2f(1, 1); glVertex2f(0.9f, 0.9f);
    glTexCoord2f(0, 1); glVertex2f(0.8f, 0.9f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    SwapBuffers();
}

void GLCanvas::OnMouse(wxMouseEvent& evt) {
    if (evt.LeftDown()) {
        wxSize size = GetSize();
        float x = (2.0f * evt.GetX() / size.x) - 1.0f;
        float y = 1.0f - (2.0f * evt.GetY() / size.y);

        if (x > 0.8f && x < 0.9f && y > 0.8f && y < 0.9f) {
            wxCommandEvent event(wxEVT_BUTTON);
            event.SetId(ID_TOGGLE_PANEL);
            wxPostEvent(GetParent(), event);
        }
    }
}

GLuint GLCanvas::LoadTexture(const wxString& filename) {
    if (!wxFileExists(filename))
        return 0;
    
    wxImage image;
    if (!image.LoadFile(filename))
        return 0;
    
    image = image.Mirror(false);

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.GetWidth(), image.GetHeight(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, image.GetData());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return textureID;
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