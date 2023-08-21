#include "pch.h"

using namespace winrt;
using namespace Windows::Foundation;
constexpr auto SAMPLE_RATE = 16'000;
constexpr auto BITS_PER_COMPRESSED_SAMPLE = 16;

int main()
{
    using namespace winrt::Windows::Media::Audio;
    AudioGraphSettings settings{ winrt::Windows::Media::Render::AudioRenderCategory::Media };
    auto encoding = winrt::Windows::Media::MediaProperties::AudioEncodingProperties{};
    encoding.BitsPerSample(32);
    encoding.ChannelCount(1);
    encoding.SampleRate(48'000);
    encoding.Bitrate(encoding.BitsPerSample() * encoding.ChannelCount() * encoding.SampleRate());
    encoding.Subtype(L"Float");
    //encoding.Type(encodingInput.Type());

    settings.EncodingProperties(encoding);
    settings.PrimaryRenderDevice(nullptr);
    auto codec_settings = settings.EncodingProperties();
    CreateAudioGraphResult result0 = AudioGraph::CreateAsync(settings).get();
    WINRT_ASSERT(result0.Status() == AudioGraphCreationStatus::Success);

    encoding.BitsPerSample(32);
    encoding.ChannelCount(2);
    encoding.SampleRate(48'000);
    encoding.Bitrate(encoding.BitsPerSample() * encoding.ChannelCount() * encoding.SampleRate());
    CreateAudioGraphResult result = AudioGraph::CreateAsync(settings).get();
    auto status = result.Status();
    auto error = result.ExtendedError();
    WINRT_ASSERT(result.Status() == AudioGraphCreationStatus::Success);

    //auto webcam_filename = std::format(L"WebCam{:0>3}", 1);
    //auto name = std::format(L"Speech School Recordings\\{:%y-%m-%d} Video", std::chrono::system_clock::now());
    //auto folder = winrt::Windows::Storage::KnownFolders::VideosLibrary().CreateFolderAsync(
    //    name
    //    , winrt::Windows::Storage::CreationCollisionOption::GenerateUniqueName).get();

    //auto quality = winrt::Windows::Media::MediaProperties::AudioEncodingQuality::Auto;
    //auto mediaEncodingProfile = Windows::Media::MediaProperties::MediaEncodingProfile::CreateMp3(quality);
    //auto container = mediaEncodingProfile.Container();
    //auto encodingOut = Windows::Media::MediaProperties::AudioEncodingProperties::CreateMp3(SAMPLE_RATE, 1, SAMPLE_RATE * BITS_PER_COMPRESSED_SAMPLE);
    //mediaEncodingProfile.Audio(encodingOut);

    //auto encodingIn = Windows::Media::MediaProperties::AudioEncodingProperties::CreatePcm(SAMPLE_RATE, 1, 32);
    ///*auto props = audioEncodingPropities.Properties();
    //for (auto p : props)
    //{
    //    auto a = p.Key();
    //    auto b = p.Value();
    //}*/
    //encodingIn.Subtype(Windows::Media::MediaProperties::MediaEncodingSubtypes::Float());
    ////audioEncodingPropities.BitsPerSample(32);
    ////audioEncodingPropities.ChannelCount(1);
    ////audioEncodingPropities.SampleRate(SAMPLE_RATE);
    ////audioEncodingPropities.Bitrate(audioEncodingPropities.BitsPerSample() * audioEncodingPropities.ChannelCount() * audioEncodingPropities.SampleRate())

    //auto descriptor = Windows::Media::Core::AudioStreamDescriptor(encodingIn);
    //auto mediaStreamSource = Windows::Media::Core::MediaStreamSource(descriptor);
    //auto canSeek = mediaStreamSource.CanSeek();
    //mediaStreamSource.CanSeek(true);
    //auto canSeek2 = mediaStreamSource.CanSeek();


    //mediaStreamSource.Starting([](auto a, auto b) {

    //    });
}
