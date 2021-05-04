#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Storage;
using namespace Windows::UI::Core;

namespace winrt::VPNPlugin_App::implementation
{
	MainPage::MainPage()
	{
		InitializeComponent();

		Update().Click(RoutedEventHandler(this, &MainPage::Update_Click));

		ApplicationData::Current().LocalSettings().Values().Insert(L"RemoteTunnelHost", box_value(RemoteTunnelHost().Text()));
		ApplicationData::Current().LocalSettings().Values().Insert(L"RemoteTunnelPort", box_value(RemoteTunnelPort().Text()));
		ApplicationData::Current().LocalSettings().Values().Insert(L"LocalTunnelHost", box_value(LocalTunnelHost().Text()));
		ApplicationData::Current().LocalSettings().Values().Insert(L"LocalTunnelPort", box_value(LocalTunnelPort().Text()));
		ApplicationData::Current().LocalSettings().Values().Insert(L"VPNInterfaceV4Addr", box_value(VPNInterfaceV4Addr().Text()));
		// Only 1 single route configuration supported for now. 
		ApplicationData::Current().LocalSettings().Values().Insert(L"TunnelSubnetIP", box_value(TunnelSubnetIP().Text()));

	}

	void MainPage::UpdateStatus(hstring strMessage, NotifyType type)
	{
		switch (type)
		{
		case NotifyType::StatusMessage:
			//StatusBorder->Background = ref new SolidColorBrush(Windows::UI::Colors::Green);
			break;
		case NotifyType::ErrorMessage:
			//StatusBorder->Background = ref new SolidColorBrush(Windows::UI::Colors::Red);
			break;
		default:
			break;
		}
	}

	void MainPage::NotifyUser(hstring strMessage, NotifyType type)
	{
		if (Dispatcher().HasThreadAccess())
		{
			UpdateStatus(strMessage, type);
		}
		else
		{
			Dispatcher().RunAsync(CoreDispatcherPriority::Normal, DispatchedHandler([strMessage, type, this]()
				{
					UpdateStatus(strMessage, type);
				}));
		}
	}

	void MainPage::Update_Click(IInspectable const&, RoutedEventArgs const&)
	{
		ApplicationData::Current().LocalSettings().Values().Insert(L"RemoteTunnelHost", box_value(RemoteTunnelHost().Text()));
		ApplicationData::Current().LocalSettings().Values().Insert(L"RemoteTunnelPort", box_value(RemoteTunnelPort().Text()));
		ApplicationData::Current().LocalSettings().Values().Insert(L"LocalTunnelHost", box_value(LocalTunnelHost().Text()));
		ApplicationData::Current().LocalSettings().Values().Insert(L"LocalTunnelPort", box_value(LocalTunnelPort().Text()));
		ApplicationData::Current().LocalSettings().Values().Insert(L"VPNInterfaceV4Addr", box_value(VPNInterfaceV4Addr().Text()));
		// Only 1 single route configuration supported for now. 
		ApplicationData::Current().LocalSettings().Values().Insert(L"TunnelSubnetIP", box_value(TunnelSubnetIP().Text()));
		ApplicationData::Current().LocalSettings().Values().Insert(L"TunnelSubnetMask", box_value(TunnelSubnetMask().Text()));
	}

}
