#include "pybind11/chrono.h"
#include "../public/MediaBase.h"
#include "../public/ControlBlock.h"
#include "../public/Formats.h"
#include "RingBuffer.h"
#include "IPCUtils.h"

namespace py = pybind11;

void init_pyProducer(py::module &);
void init_pyConsumer(py::module &);

PYBIND11_MODULE(pyMediaIPC, m)
{
    py::class_<MediaIPC::MediaBase>(m, "MediaBase")
        .def(py::init<>());

    py::enum_<MediaIPC::VideoFormat>(m, "VideoFormat")
        #define VIDEO_FORMAT(name, bytes, description) .value(#name , MediaIPC::VideoFormat::name)
	    #include "../public/VideoFormats.inc"
        .value("None", MediaIPC::VideoFormat::None);

    py::enum_<MediaIPC::AudioFormat>(m, "AudioFormat")
        #define AUDIO_FORMAT(name, bytes, description) .value(#name , MediaIPC::AudioFormat::name)
	    #include "../public/AudioFormats.inc"
        .value("None", MediaIPC::AudioFormat::None);

    
    py::class_<MediaIPC::ControlBlock>(m, "ControlBlock")
        .def(py::init<>())
        .def("calculateVideoBufsize", &MediaIPC::ControlBlock::calculateVideoBufsize)
        .def("calculateAudioBufsize", &MediaIPC::ControlBlock::calculateAudioBufsize)
        .def("calculateVideoInterval", &MediaIPC::ControlBlock::calculateVideoInterval)
        .def("calculateAudioInterval", &MediaIPC::ControlBlock::calculateAudioInterval)
        .def_readwrite("width", &MediaIPC::ControlBlock::width)
        .def_readwrite("height", &MediaIPC::ControlBlock::height)
        .def_readwrite("frameRate", &MediaIPC::ControlBlock::frameRate)
        .def_readwrite("videoFormat", &MediaIPC::ControlBlock::videoFormat)
        .def_readwrite("channels", &MediaIPC::ControlBlock::channels)
        .def_readwrite("sampleRate", &MediaIPC::ControlBlock::sampleRate)
        .def_readwrite("samplesPerBuffer", &MediaIPC::ControlBlock::samplesPerBuffer)
        .def_readwrite("audioFormat", &MediaIPC::ControlBlock::audioFormat);
    

    init_pyProducer(m);
    init_pyConsumer(m);
}