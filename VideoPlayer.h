#ifndef VIDEO_PLAYER_H
#define VIDEO_PLAYER_H

#include <wx/wx.h>
#include <wx/mediactrl.h>

class VideoPlayer : public wxFrame {
public:
    VideoPlayer(const wxString& title);

private:
    void OnOpenVideo(wxCommandEvent& event);
    void OnPlay(wxCommandEvent& event);
    void OnPause(wxCommandEvent& event);
    void OnVolumeUp(wxCommandEvent& event);
    void OnVolumeDown(wxCommandEvent& event);

    wxMediaCtrl* m_mediaCtrl;
    double m_volume;
};

#endif