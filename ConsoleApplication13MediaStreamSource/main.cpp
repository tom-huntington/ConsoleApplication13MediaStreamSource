#include "pch.h"


#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <codecapi.h>
#include <winrt/Windows.Graphics.h>

#pragma comment(lib, "Mfuuid.lib")
#pragma comment(lib, "Mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "Mf.lib")

using namespace winrt;
using namespace Windows::Foundation;

static constexpr winrt::Windows::Graphics::SizeInt32 size{1922, 1089};
static constexpr UINT32 FRAME_RATE{ 60 };
static constexpr UINT32 BIT_RATE{ 2'000'000 };
DWORD m_videoStreamIndex{ DWORD(-1) };

int main()
{
    winrt::init_apartment(winrt::apartment_type::multi_threaded);
    winrt::check_hresult(MFStartup(MF_VERSION, MFSTARTUP_NOSOCKET));

    winrt::com_ptr<IMFMediaType> m_videoOut;
    winrt::check_hresult(MFCreateMediaType(m_videoOut.put()));
    winrt::check_hresult(m_videoOut->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video));
    winrt::check_hresult(m_videoOut->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_H264));
    winrt::check_hresult(m_videoOut->SetUINT32(MF_MT_AVG_BITRATE, BIT_RATE));
    winrt::check_hresult(MFSetAttributeRatio(m_videoOut.get(), MF_MT_FRAME_RATE, FRAME_RATE, 1));
    winrt::check_hresult(MFSetAttributeSize(m_videoOut.get(), MF_MT_FRAME_SIZE, size.Width, size.Height));
    winrt::check_hresult(m_videoOut->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive));
    winrt::check_hresult(m_videoOut->SetUINT32(MF_MT_MPEG2_PROFILE, eAVEncH264VProfile_Main));

    winrt::com_ptr<IMFMediaType> m_videoIn;
    winrt::check_hresult(MFCreateMediaType(m_videoIn.put()));
    winrt::check_hresult(m_videoOut->CopyAllItems(m_videoIn.get()));
    winrt::check_hresult(m_videoIn->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_ARGB32));
    winrt::check_hresult(m_videoIn->SetUINT32(MF_MT_ALL_SAMPLES_INDEPENDENT, 1));

    winrt::com_ptr<IMFAttributes> m_containter_attributes;
    winrt::check_hresult(MFCreateAttributes(m_containter_attributes.put(), 6));
    //winrt::check_hresult(m_containter_attributes->SetUINT32(MF_LOW_LATENCY, 1));
    //MF_READWRITE_DISABLE_CONVERTERS
    //MF_READWRITE_ENABLE_HARDWARE_TRANSFORMS
    //MF_SINK_WRITER_ASYNC_CALLBACK
    //winrt::check_hresult(m_containter_attributes->SetUINT32(MF_SINK_WRITER_DISABLE_THROTTLING, 1));
    winrt::check_hresult(m_containter_attributes->SetGUID(MF_TRANSCODE_CONTAINERTYPE, MFTranscodeContainerType_MPEG4));
    //MFT_FIELDOFUSE_UNLOCK_Attribute
#if 0
    winrt::com_ptr<IMFDXGIDeviceManager> devManager;
    UINT resetToken;
    winrt::check_hresult(MFCreateDXGIDeviceManager(&resetToken, devManager.put()));
    winrt::check_hresult(devManager->ResetDevice(m_d3DDevice.get(), resetToken));
    winrt::check_hresult(m_containter_attributes->SetUnknown(MF_SINK_WRITER_D3D_MANAGER, devManager.get()));
#endif

    winrt::com_ptr<IMFByteStream> outputStream;
    winrt::check_hresult(MFCreateFile(MF_ACCESSMODE_READWRITE, MF_OPENMODE_DELETE_IF_EXIST, MF_FILEFLAGS_NONE, L"D:\\Documents\\test.mp4", outputStream.put()));
    winrt::com_ptr<IMFMediaSink> mp4StreamSink;
    winrt::check_hresult(MFCreateMPEG4MediaSink(outputStream.get(), m_videoOut.get(), NULL, mp4StreamSink.put()));
    winrt::com_ptr<IMFSinkWriter> sinkWriter;
    winrt::check_hresult(MFCreateSinkWriterFromMediaSink(mp4StreamSink.get(), m_containter_attributes.get(), sinkWriter.put()));
    sinkWriter->SetInputMediaType(0, m_videoIn.get(), nullptr);

    winrt::com_ptr<IMFSinkWriter> pSinkWriterVideo;
    winrt::check_hresult(MFCreateSinkWriterFromURL(L"D:\\Documents\\test2.mp4", NULL, m_containter_attributes.get(), pSinkWriterVideo.put()));
    winrt::check_hresult(pSinkWriterVideo->AddStream(m_videoOut.get(), &m_videoStreamIndex));
    winrt::check_hresult(pSinkWriterVideo->SetInputMediaType(m_videoStreamIndex, m_videoIn.get(), nullptr /*encoder attributes*/));
    
}
