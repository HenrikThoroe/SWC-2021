#pragma once 

namespace Util {

    /// Data container to work with geometric rectangles
    struct Rect {

        /// The minimum x value
        int minX;

        /// The maximum x value
        int maxX;

        /// The minimum y value
        int minY;

        /// The maximum y value
        int maxY;

        Rect(int minX, int maxX, int minY, int maxY);
        Rect(Rect* other) = delete;
        Rect(Rect& other) = delete;

        /// Returns the width of the rect
        int width() const;

        /// Returns the height of the rect
        int height() const;

        /// The length of the diagonal line between two opposite corners of the rectangle
        float diagonal() const;

        /**
         * Combines two rects 
         * 
         * @param other The rect which should be merged
         * @returns A new `Rect` instance which contains both parent rects
         */
        Rect join(const Rect& other) const;

        /// The occupied area of the rectangle
        int size() const;

        /// Returns the size of the intersected area of two rects
        int intersection(const Rect& other) const;
        
    };

}
