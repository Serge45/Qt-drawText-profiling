# Qt-drawText-profiling

## Abstract ##
This application is for text drawing profiling in Qt, it records time for different text drawing strategy:

1. Use `QPainter::drawText` directly.
2. Use `QPainter::drawPath` with prepared `QPainterPath`.
3. Similar to 2., but `QPainterPath` is created while painting.
