#include "pybind11/pybind11.h"
#include "RingBuffer.h"
#include "../public/MediaConsumer.h"

namespace py = pybind11;

void init_pyConsumer(py::module &m) {
    py::class_<MediaIPC::MediaConsumer, MediaIPC::MediaBase>(m, "MediaConsumer")
        .def(py::init<const std::string &, std::unique_ptr<MediaIPC::ConsumerDelegate> &&>());
    /*
		.def("streamIsActive", &MediaIPC::MediaConsumer::streamIsActive)
		.def("videoLoop", &MediaIPC::MediaConsumer::videoLoop)
		.def("audioLoop", &MediaIPC::MediaConsumer::audioLoop)
		.def("delegate", &MediaIPC::MediaConsumer::delegate)
        */

    py::class_<MediaIPC::RingBuffer>(m, "RingBuffer")
        .def(py::init<uint8_t *, uint32_t, uint32_t *>())
        .def("read", &MediaIPC::RingBuffer::read)
        .def("write", &MediaIPC::RingBuffer::write);

    class PyConsumerDelegate : public MediaIPC::ConsumerDelegate
    {
      public:
        /* Inherit the constructors */
        using MediaIPC::ConsumerDelegate::ConsumerDelegate;

        /* Trampoline (need one for each virtual function) */
        void controlBlockReceived(const MediaIPC::ControlBlock &cb) override
        {
            PYBIND11_OVERLOAD_PURE(
                void,                       /* Return type */
                MediaIPC::ConsumerDelegate, /* Parent class */
                controlBlockReceived,       /* Name of function in C++ (must match Python name) */
                cb                          /* Argument(s) */
            );
        }

        /* Trampoline (need one for each virtual function) */
        void videoFrameReceived(const uint8_t *buffer, uint64_t length) override
        {
            PYBIND11_OVERLOAD_PURE(
                void,                       /* Return type */
                MediaIPC::ConsumerDelegate, /* Parent class */
                videoFrameReceived,         /* Name of function in C++ (must match Python name) */
                buffer,                     /* Argument */
                length                      /* Argument */
            );
        }

        /* Trampoline (need one for each virtual function) */
        void audioSamplesReceived(const uint8_t *buffer, uint64_t length) override
        {
            PYBIND11_OVERLOAD_PURE(
                void,                       /* Return type */
                MediaIPC::ConsumerDelegate, /* Parent class */
                videoFrameReceived,         /* Name of function in C++ (must match Python name) */
                buffer,                     /* Argument */
                length                      /* Argument */
            );
        }
    };

    py::class_<MediaIPC::ConsumerDelegate, PyConsumerDelegate>(m, "ConsumerDelegate")
        .def(py::init<>())
        .def("controlBlockReceived", &MediaIPC::ConsumerDelegate::controlBlockReceived)
        .def("videoFrameReceived", &MediaIPC::ConsumerDelegate::videoFrameReceived)
        .def("audioSampleReceived", &MediaIPC::ConsumerDelegate::audioSamplesReceived);

    py::class_<MediaIPC::FunctionConsumerDelegate, MediaIPC::ConsumerDelegate>(m, "FunctionConsumerDelegate")
        .def(py::init<>())
        .def("setControlBlockHandler", &MediaIPC::FunctionConsumerDelegate::setControlBlockHandler)
        .def("setVideoHandler", &MediaIPC::FunctionConsumerDelegate::setVideoHandler)
        .def("setAudioHandler", &MediaIPC::FunctionConsumerDelegate::setAudioHandler);
    /*
        .def("controlBlockReceived", &MediaIPC::FunctionConsumerDelegate::controlBlockReceived)
        .def("videoFrameReceived", &MediaIPC::FunctionConsumerDelegate::videoFrameReceived)
        .def("audioSampleReceived", &MediaIPC::FunctionConsumerDelegate::audioSamplesReceived);
                
        .def("cbHandler", &MediaIPC::FunctionConsumerDelegate::cbHandler)
        .def("videoHandler", &MediaIPC::FunctionConsumerDelegate::videoHandler)
        .def("audioHandler", &MediaIPC::FunctionConsumerDelegate::audioHandler)        
        */
}
