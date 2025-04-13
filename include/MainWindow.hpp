#pragma once
#include <wx/wx.h>
#include <wx/sizer.h>
#include "GLCanvas.hpp"
#include "Constants.hpp"

class MainWindow : public wxFrame {
private:
    GLCanvas* _canvas;
    wxPanel* _controlPanel;
    bool _isPanelVisible;
    
    void CreateControls();
    void OnTogglePanel(wxCommandEvent& evt);

public:
    MainWindow(const wxString& title, int width, int height);
    ~MainWindow();
};
