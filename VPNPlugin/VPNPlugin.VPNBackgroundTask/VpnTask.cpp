#include "pch.h"
#include "VpnTask.h"
#include "VpnTask.g.cpp"
#include "TunnelPlugin.h"

using namespace winrt;
using namespace Windows::Networking::Vpn;
using namespace Windows::ApplicationModel::Background;

namespace winrt::VPNPlugin_VPNBackgroundTask::implementation
{
    Windows::Networking::Vpn::IVpnPlugIn VpnTask::plugin = nullptr;
    	
    void VpnTask::Run(IBackgroundTaskInstance const& taskInstance)
    {
        // Create VPN Plugin and start the channel.
        if (this->plugin == nullptr)
        {
            this->plugin = make<::VPNPlugin_VPNBackgroundTask::TunnelPlugin>(nullptr);
        }

        VpnChannel::ProcessEventAsync(this->plugin, taskInstance.TriggerDetails());
    }

	void VpnTask::OnCanceled(IBackgroundTaskInstance const&, BackgroundTaskCancellationReason const& reason)
    {
        //
		// Indicate that the background task is canceled.
		//
        CancelRequested = true;
        CancelReason = reason;
    }
}
