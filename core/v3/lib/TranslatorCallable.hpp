#pragma once

#include <functional>
#include <string_view>

namespace YololTranslator
{

using TranslatorCallable = std::function<std::string_view()>;

} // namespace YololTranslator
