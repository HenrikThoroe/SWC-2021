#pragma once

#include <array>

namespace Util {

    /// A faster implementation of the stack container. It follows the paradigm first-in last-out.
    template<typename T, int S> class FastStack {
        private:
            /// The underlying array which stores the data.
            std::array<T, S> data {};

            /// The currently active index
            int index {};

        public:
            /// Returns the top-most element of the stack
            const T& top() const {
                return data[index];
            }

            /// Removes the top-most element of the stack
            void pop() {
                index -= 1;
            }

            /// Adds an element on top off the stack
            void push(const T& item) {
                index += 1;
                data[index] = item;
            }
    };

}