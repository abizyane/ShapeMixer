#include "../include/MainWindow.hpp"

MainWindow::MainWindow(const wxString& title, int width, int height)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(width, height)),
      _isPanelVisible(false)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
    
    _canvas = new GLCanvas(this);
    CreateControls();

    mainSizer->Add(_canvas, 1, wxEXPAND);
    mainSizer->Add(_controlPanel, 0, wxEXPAND);
    
    SetSizer(mainSizer);
    _controlPanel->Show(false);

    Bind(wxEVT_BUTTON, &MainWindow::OnTogglePanel, this, ID_TOGGLE_PANEL);
}

void MainWindow::CreateControls() {
    _controlPanel = new wxPanel(this);
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    const char* shapeNames[] = {"Triangle", "Square", "Circle"};
    for(int i = 0; i < 3; ++i) {
        wxCheckBox* checkbox = new wxCheckBox(_controlPanel, wxID_ANY, shapeNames[i]);
        checkbox->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent& evt) {
            _canvas->ToggleShape(i, evt.IsChecked());
        });
        sizer->Add(checkbox, 0, wxALL, 5);
    }

    wxSlider* hPosSlider = new wxSlider(_controlPanel, wxID_ANY, 50, 0, 100);
    hPosSlider->Bind(wxEVT_SLIDER, [=](wxCommandEvent& evt) {
        float hPos = (evt.GetInt() - 50) / 50.0f;
        _canvas->UpdatePosition(hPos, _canvas->GetVerticalPosition());
    });
    sizer->Add(new wxStaticText(_controlPanel, wxID_ANY, "Horizontal Position"), 0, wxALL, 5);
    sizer->Add(hPosSlider, 0, wxEXPAND | wxALL, 5);

    wxSlider* vPosSlider = new wxSlider(_controlPanel, wxID_ANY, 50, 0, 100);
    vPosSlider->Bind(wxEVT_SLIDER, [=](wxCommandEvent& evt) {
        float vPos = (evt.GetInt() - 50) / 50.0f;
        _canvas->UpdatePosition(_canvas->GetHorizontalPosition(), vPos);
    });
    sizer->Add(new wxStaticText(_controlPanel, wxID_ANY, "Vertical Position"), 0, wxALL, 5);
    sizer->Add(vPosSlider, 0, wxEXPAND | wxALL, 5);

    wxSlider* scaleSlider = new wxSlider(_controlPanel, wxID_ANY, 50, 10, 100);
    scaleSlider->Bind(wxEVT_SLIDER, [=](wxCommandEvent& evt) {
        _canvas->UpdateScale(evt.GetInt() / 50.0f);
    });
    sizer->Add(new wxStaticText(_controlPanel, wxID_ANY, "Scale"), 0, wxALL, 5);
    sizer->Add(scaleSlider, 0, wxEXPAND | wxALL, 5);

    _controlPanel->SetSizer(sizer);
}

void MainWindow::OnTogglePanel(wxCommandEvent&) {
    _isPanelVisible = !_isPanelVisible;
    _controlPanel->Show(_isPanelVisible);
    GetSizer()->Layout();
}

MainWindow::~MainWindow() {
    delete _canvas;
    delete _controlPanel;
}