# YololTranslator Core V2
## Description
This is the translation engine, there is a shared library (YololTranslator, the extention is platform dependant) with a C++ API (see the Translator.hpp) and a C API (SharedLibInterface.hpp).
There is also a little command line program named YololTranslatorCmd.

## Requirement to build
* Cmake
* A C++ compiler compatible with C++20

## Todos
* An interface with a YololString composend of a const char*, a size and an id, possible to free with the id or the const char* to avoid the void* trick in the js related projects and a way to keep track of all allocated ressources and delete everything if needed.
* Possibility to load several dictionnaries, and a better API to load them
* Put everything in a namespace
* Use custom exceptions
* Units tests on the part that are easily testable
* Instead of splitting, iterate over the string on delimiters => avoid allocation => faster, also after it will be easier to refactorate the split and tokenize code and remove the duplicate code