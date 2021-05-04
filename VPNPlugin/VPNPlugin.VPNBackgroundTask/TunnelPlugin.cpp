#include "pch.h"
#include "TunnelPlugin.h"

using namespace winrt;
using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace Windows::Networking;
using namespace Windows::Networking::Vpn;
using namespace Windows::Networking::Sockets;

namespace VPNPlugin_VPNBackgroundTask
{
    TunnelPlugin::TunnelPlugin(DatagramSocket const& sock)
	    : dSock(sock)
    {
    }

    void TunnelPlugin::Connect(VpnChannel const& channel)
    {
		this->dSock = DatagramSocket();

    	channel.AssociateTransport(this->dSock, nullptr);

		const auto settings = ApplicationData::Current().LocalSettings().Values();
		const auto svcName = unbox_value<hstring>(settings.Lookup(L"LocalTunnelPort"));
		auto tmpStr = unbox_value<hstring>(settings.Lookup(L"LocalTunnelHost"));
		const HostName tunnelV4Addr(tmpStr);
		// auto result = create_task(dSock->BindEndpointAsync(tunnelV4Addr, svcName));
		dSock.BindServiceNameAsync(svcName).get();

		// Connect to the destination tunnel address on UDP socket.
		tmpStr = unbox_value<hstring>(settings.Lookup(L"RemoteTunnelHost"));
		const HostName remoteTunnelIP(tmpStr);
		const auto remoteTunnelPort = unbox_value<hstring>(settings.Lookup(L"RemoteTunnelPort"));
		this->dSock.ConnectAsync(remoteTunnelIP, remoteTunnelPort).get();

		std::vector<HostName> localV4Addrs;
		tmpStr = unbox_value<hstring>(settings.Lookup(L"VPNInterfaceV4Addr"));
		localV4Addrs.push_back(HostName(tmpStr)); // Local host name to be bound.

		// IP subnets to be routed via VPN. Only 1 subnet supported in this code. Change code to add more.
		const VpnRouteAssignment routeScope;
		// The subnet mask must match the IP specified. I.e. there must be zero bits after mask.
		tmpStr = unbox_value<hstring>(settings.Lookup(L"TunnelSubnetIP"));
		const HostName routeHost(tmpStr);
		const auto routeMask = static_cast<uint8_t>(_wtoi(unbox_value<hstring>(settings.Lookup(L"TunnelSubnetMask")).data()));
		routeScope.Ipv4InclusionRoutes().Append(VpnRoute(routeHost, routeMask));

		try
		{
			// Enhance the code if IPv6 traffic tunneling and DNS servers are to be specified.
			channel.StartWithMainTransport(localV4Addrs, nullptr, nullptr, routeScope, nullptr, 1400, 1500, false, this->dSock);
		}
		catch (hresult_error error)
		{
			auto code = error.code();
			auto message = error.message();
		}
    }

    void TunnelPlugin::Disconnect(VpnChannel const& channel)
    {
        channel.Stop(); // TODO: The callback gets called twice on disconnect.
    }

    void TunnelPlugin::GetKeepAlivePayload(VpnChannel const&, VpnPacketBuffer&)
    {

    }

    void TunnelPlugin::Encapsulate(VpnChannel const&, VpnPacketBufferList const& packets, VpnPacketBufferList const& encapulatedPackets)
    {
        // Right now simply forward whatever comes.
        while (packets.Size() > 0)
        {
	        VpnPacketBuffer packet(packets.RemoveAtBegin());
            auto buf = packet.Buffer();
            //auto status = packet.Status();
            encapulatedPackets.Append(packet);
        }
    }

    void TunnelPlugin::Decapsulate(VpnChannel const&, VpnPacketBuffer const& encapBuffer, VpnPacketBufferList const& decapsulatedPackets, winrt::Windows::Networking::Vpn::VpnPacketBufferList const&)
    {
        // Right now simply forward whatever comes.
        while (encapBuffer)
        {
            decapsulatedPackets.Append(encapBuffer);
        }
    }
}
