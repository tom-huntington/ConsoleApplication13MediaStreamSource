#include "pch.h"

#pragma comment(lib, "Mfuuid.lib")

using namespace winrt;
using namespace Windows::Foundation;
constexpr auto SAMPLE_RATE = 16'000;
constexpr auto BITS_PER_COMPRESSED_SAMPLE = 16;



int main()
{
    using namespace winrt::Windows::Media::MediaProperties;

    auto propsB = MediaEncodingProfile::CreateMp4(VideoEncodingQuality::Auto).Video().Properties();
    auto propsA = VideoEncodingProperties::CreateH264().Properties();
        

    auto fn = [propsB, propsA]<typename T>(GUID const& guid) {
        auto a = propsA.HasKey(guid) ? propsA.Lookup(guid).as<Windows::Foundation::IPropertyValue>() : Windows::Foundation::IPropertyValue{};
        auto b = propsA.HasKey(guid) ? propsB.Lookup(guid).as<Windows::Foundation::IPropertyValue>() : Windows::Foundation::IPropertyValue{};
        if constexpr (std::is_same_v<T, UINT32>)
            return std::array<std::optional<T>, 2> { a ? a.GetUInt32() : std::optional<T>{}, b ? b.GetUInt32() : std::optional<T>{} };
        if constexpr (std::is_same_v<T, GUID>)
            return std::array<std::optional<winrt::guid>, 2> { a ? a.GetGuid() : std::optional<winrt::guid>{}, b ? b.GetGuid() : std::optional<winrt::guid>{} };
        if constexpr (std::is_same_v<T, UINT64>)
            return std::array<std::optional<T>, 2>{ a ? a.GetUInt64() : std::optional<T>{}, b ? b.GetUInt64() : std::optional<T>{} };

        throw std::exception("not reached");
    };
    auto a = MFVideoFormat_MPEG2;
    auto b = MFVideoFormat_H265;
    auto c = MFVideoFormat_H264;
    auto d = MFVideoFormat_HEVC;
    auto [a1, a2] = fn.operator() < GUID > (MF_MT_MAJOR_TYPE);
    auto [b1, b2] = fn.operator() < GUID > (MF_MT_SUBTYPE);
    auto [c1, c2] = fn.operator() < UINT32 > (MF_MT_AVG_BITRATE);
    auto [d1, d2] = fn.operator() < UINT64 > (MF_MT_FRAME_RATE);
    auto [e1, e2] = fn.operator() < UINT64 > (MF_MT_FRAME_SIZE);
    auto [f1, f2] = fn.operator() < UINT32 > (MF_MT_INTERLACE_MODE);
    auto [g1, g2] = fn.operator() < UINT32 > (MF_MT_MPEG2_PROFILE);
    auto [h1, h2] = fn.operator() < UINT32 > (MF_MT_MPEG2_LEVEL);
    auto [i1, i2] = fn.operator()<UINT64>(MF_MT_PIXEL_ASPECT_RATIO);

}
