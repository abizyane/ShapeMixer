#include <wx/wx.h>
#include "MainWindow.hpp"

class Application : public wxApp {
private:
    MainWindow* _mainWindow;

public:
    bool OnInit() override {
        if (!wxApp::OnInit())
            return false;
        
        wxInitAllImageHandlers();
        _mainWindow = new MainWindow("Shape Mixer", 800, 600);
        _mainWindow->Show(true);
        return true;
    }

    ~Application() {
        if (_mainWindow)
            delete _mainWindow;
    }
};

IMPLEMENT_APP(Application)
