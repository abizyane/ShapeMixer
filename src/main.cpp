#include <wx/wx.h>
#include "../include/MainWindow.hpp"

class Application : public wxApp 
{
private:
    MainWindow* _mainWindow;

public:
    virtual bool OnInit() 
    {
        if (!wxApp::OnInit())
            return false;
        
        wxInitAllImageHandlers();
        _mainWindow = new MainWindow("Shape Mixer", 1400, 900);
        _mainWindow->Show(true);
        return true;
    }

    virtual ~Application() 
    {
        if (_mainWindow)
            delete _mainWindow;
    }
};

DECLARE_APP(Application)
IMPLEMENT_APP(Application)