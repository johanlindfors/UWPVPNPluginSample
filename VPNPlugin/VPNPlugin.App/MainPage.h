#pragma once

#include "MainPage.g.h"

namespace winrt::VPNPlugin_App::implementation
{
    enum NotifyType
    {
	    StatusMessage,
    	ErrorMessage
    };
	
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

    private:
        void UpdateStatus(winrt::hstring strMessage, NotifyType type);

        //static MainPage Current;
        void NotifyUser(winrt::hstring strMessage, NotifyType type);
        void Update_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::VPNPlugin_App::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
