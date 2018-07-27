#include "pybind11/pybind11.h"
#include "../public/MediaProducer.h"

namespace py = pybind11;

void init_pyProducer(py::module &m) {
    py::class_<MediaIPC::MediaProducer, MediaIPC::MediaBase>(m, "MediaProducer")
        .def(py::init<const std::string &, const MediaIPC::ControlBlock&>())
        .def("submitVideoFrame", &MediaIPC::MediaProducer::submitVideoFrame)
        .def("submitAudioSamples", &MediaIPC::MediaProducer::submitAudioSamples)
        .def("stop", &MediaIPC::MediaProducer::stop);
}