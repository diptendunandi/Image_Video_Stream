





#include "ImageSlideshow.h"
#include "VideoPlayer.h"
#include <wx/wx.h>

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString& title)
        : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 200)) {
        // Create buttons
        m_btnImage = new wxButton(this, wxID_ANY, wxT("Open Image Slideshow"), wxPoint(50, 50), wxSize(150, 30));
        m_btnVideo = new wxButton(this, wxID_ANY, wxT("Open Video Player"), wxPoint(200, 50), wxSize(150, 30));

        // Bind button events
        m_btnImage->Bind(wxEVT_BUTTON, &MainFrame::OnOpenImageSlideshow, this);
        m_btnVideo->Bind(wxEVT_BUTTON, &MainFrame::OnOpenVideoPlayer, this);
    }

private:
    void OnOpenImageSlideshow(wxCommandEvent& event) {
        ImageSlideshow* slideshow = new ImageSlideshow("Image Slideshow");
        slideshow->Show(true);
    }

    void OnOpenVideoPlayer(wxCommandEvent& event) {
        VideoPlayer* player = new VideoPlayer("Video Player");
        player->Show(true);
    }

    
    wxButton* m_btnVideo;
    wxButton* m_btnImage;
};

class MyApp : public wxApp {
public:
    virtual bool OnInit() override {
        MainFrame* frame = new MainFrame("Main Frame");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);



