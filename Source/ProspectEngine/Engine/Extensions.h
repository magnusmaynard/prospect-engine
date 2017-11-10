#pragma once
#include <optional>

namespace Prospect
{
   template<typename P, typename I>
   static std::optional<P> MakeOptionalImpl(I impl)
   {
      return impl ? std::optional<P>(impl) : std::nullopt;
   }

   template<typename T>
   static std::optional<T> MakeOptional(T object)
   {
      return object ? std::optional<T>(object) : std::nullopt;
   }
}