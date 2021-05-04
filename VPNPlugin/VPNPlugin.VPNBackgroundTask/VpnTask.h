#pragma once
#include "VpnTask.g.h"

namespace winrt::VPNPlugin_VPNBackgroundTask::implementation
{
    struct VpnTask : VpnTaskT<VpnTask>
    {
    	VpnTask() = default;

        void OnCanceled(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance const& taskInstance, winrt::Windows::ApplicationModel::Background::BackgroundTaskCancellationReason const& reason);
        void Run(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance const& taskInstance);

    private:
        winrt::Windows::ApplicationModel::Background::BackgroundTaskCancellationReason CancelReason = Windows::ApplicationModel::Background::BackgroundTaskCancellationReason::Abort;
        volatile bool CancelRequested = false;
        winrt::agile_ref<Windows::ApplicationModel::Background::BackgroundTaskDeferral> TaskDeferral = nullptr;
        winrt::Windows::System::Threading::ThreadPoolTimer PeriodicTimer = nullptr;
        unsigned int Progress = 0;
        winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance TaskInstance{ nullptr };
        static winrt::Windows::Networking::Vpn::IVpnPlugIn plugin;
    };
}
namespace winrt::VPNPlugin_VPNBackgroundTask::factory_implementation
{
    struct VpnTask : VpnTaskT<VpnTask, implementation::VpnTask>
    {
    };
}
