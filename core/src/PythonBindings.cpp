#include <Translator.hpp>

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(yolol, m) {
    m.doc() = "Yolol bindings";

    py::class_<Translator>(m, "Translator")
        .def(py::init<std::string_view, std::string_view, std::string_view>(),
            py::arg("word_to_phonem_file"),
            py::arg("phonem_to_chars_file"),
            py::arg("word_to_word_file"))
        .def("translate", &Translator::operator());
}