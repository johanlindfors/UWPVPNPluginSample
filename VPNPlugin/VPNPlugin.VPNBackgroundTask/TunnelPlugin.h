#pragma once
#include <winrt/base.h>
#include <winrt/Windows.Networking.Vpn.h>
#include <winrt/Windows.Networking.Sockets.h>

namespace VPNPlugin_VPNBackgroundTask
{
    struct TunnelPlugin : winrt::implements<TunnelPlugin, winrt::Windows::Networking::Vpn::IVpnPlugIn>
    {
		TunnelPlugin(winrt::Windows::Networking::Sockets::DatagramSocket const& sock);

        void Connect(winrt::Windows::Networking::Vpn::VpnChannel const& channel);
        void Disconnect(winrt::Windows::Networking::Vpn::VpnChannel const& channel);
        void GetKeepAlivePayload(winrt::Windows::Networking::Vpn::VpnChannel const& channel, winrt::Windows::Networking::Vpn::VpnPacketBuffer& keepAlivePacket);
        void Encapsulate(winrt::Windows::Networking::Vpn::VpnChannel const& channel, winrt::Windows::Networking::Vpn::VpnPacketBufferList const& packets, winrt::Windows::Networking::Vpn::VpnPacketBufferList const& encapulatedPackets);
        void Decapsulate(winrt::Windows::Networking::Vpn::VpnChannel const& channel, winrt::Windows::Networking::Vpn::VpnPacketBuffer const& encapBuffer, winrt::Windows::Networking::Vpn::VpnPacketBufferList const& decapsulatedPackets, winrt::Windows::Networking::Vpn::VpnPacketBufferList const& controlPacketsToSend);

	    private:
	        void ReadMessage(winrt::Windows::Networking::Sockets::DatagramSocketMessageReceivedEventArgs const& eventArguments);
	        winrt::Windows::Storage::Streams::IOutputStream oStream { nullptr };
	        winrt::Windows::Networking::Sockets::DatagramSocket dSock{ nullptr };
	        //CRITICAL_SECTION lock;
    };
}
