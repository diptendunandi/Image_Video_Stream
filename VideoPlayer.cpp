#include "VideoPlayer.h"
#include<wx/wx.h>

VideoPlayer::VideoPlayer(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)),
      m_volume(0.75) { // Initial volume set to 75%
    // Create a panel to hold the media control and buttons
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    // Create media control for video playback
    m_mediaCtrl = new wxMediaCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);

    // Check if the media control is created successfully
    if (!m_mediaCtrl) {
        wxLogError("Failed to create media control.");
        return;
    }

    // Create buttons
    wxButton* btnOpen = new wxButton(panel, wxID_ANY, wxT("Open"));
    wxButton* btnPlay = new wxButton(panel, wxID_ANY, wxT("Play"));
    wxButton* btnPause = new wxButton(panel, wxID_ANY, wxT("Pause"));
    wxButton* btnVolUp = new wxButton(panel, wxID_ANY, wxT("Volume +"));
    wxButton* btnVolDown = new wxButton(panel, wxID_ANY, wxT("Volume -"));

    // Bind button events
    btnOpen->Bind(wxEVT_BUTTON, &VideoPlayer::OnOpenVideo, this);
    btnPlay->Bind(wxEVT_BUTTON, &VideoPlayer::OnPlay, this);
    btnPause->Bind(wxEVT_BUTTON, &VideoPlayer::OnPause, this);
    btnVolUp->Bind(wxEVT_BUTTON, &VideoPlayer::OnVolumeUp, this);
    btnVolDown->Bind(wxEVT_BUTTON, &VideoPlayer::OnVolumeDown, this);

    // Create a horizontal box sizer for buttons
    wxBoxSizer* horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
    horizontalSizer->Add(btnOpen, 0, wxALIGN_CENTER | wxALL, 5);
    horizontalSizer->Add(btnPlay, 0, wxALIGN_CENTER | wxALL, 5);
    horizontalSizer->Add(btnPause, 0, wxALIGN_CENTER | wxALL, 5);
    horizontalSizer->Add(btnVolUp, 0, wxALIGN_CENTER | wxALL, 5);
    horizontalSizer->Add(btnVolDown, 0, wxALIGN_CENTER | wxALL, 5);

    // Create a vertical box sizer for the media control and buttons
    wxBoxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);
    verticalSizer->Add(m_mediaCtrl, 1, wxEXPAND | wxALL, 5);
    verticalSizer->Add(horizontalSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    panel->SetSizerAndFit(verticalSizer);
}

void VideoPlayer::OnOpenVideo(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, _("Open Video File"), "", "", 
                                 "Video files (*.mp4;*.avi)|*.mp4;*.avi", 
                                 wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString path = openFileDialog.GetPath();
    m_mediaCtrl->Load(path);
}

void VideoPlayer::OnPlay(wxCommandEvent& event) {
    m_mediaCtrl->Play();
}

void VideoPlayer::OnPause(wxCommandEvent& event) {
    m_mediaCtrl->Pause();
}

void VideoPlayer::OnVolumeUp(wxCommandEvent& event) {
    if (m_volume < 1.0) {
        m_volume += 0.1;
        m_mediaCtrl->SetVolume(m_volume);
    }
}

void VideoPlayer::OnVolumeDown(wxCommandEvent& event) {
    if (m_volume > 0.0) {
        m_volume -= 0.1;
        m_mediaCtrl->SetVolume(m_volume);
    }
}