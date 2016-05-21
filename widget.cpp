#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QElapsedTimer>
#include <QFile>
#include <QTextStream>

#define _USE_DRAW_TEXT
//#define _LOCAL_PAINTER_PATH

namespace {
#ifdef _USE_DRAW_TEXT
QString logFileName("log_draw_text.txt");
#else
#ifdef _LOCAL_PAINTER_PATH
QString logFileName("log_painter_path.txt");
#else
QString logFileName("log_painter_path_prepend_path.txt");
#endif
#endif
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_logFile(new QFile(this)),
    m_logStream(0),
    m_timer(new QElapsedTimer()),
    m_paintCounter(0)
{
    ui->setupUi(this);
    initTextBuffer();
    m_logFile->setFileName(logFileName);

    if (m_logFile->open(QFile::WriteOnly | QFile::Truncate)) {
        m_logStream = new QTextStream(m_logFile);
    }

    m_timer->start();
    startTimer(100);
}

Widget::~Widget()
{
    delete ui;
    delete m_timer;

    m_logFile->close();

    if (m_logStream) {
        delete m_logStream;
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter p(this);

    m_timer->restart();
    int idx = 0;
#ifdef _USE_DRAW_TEXT
    foreach (const QString &s, m_textBuffer) {
        p.drawText(m_textCoord[idx], s);
        ++idx;
    }
#else
#ifdef _LOCAL_PAINTER_PATH
    QPainterPath path;
    QFont font;

    foreach (const QString &s, m_textBuffer) {
        path.addText(m_textCoord[idx], font, s);
        ++idx;
    }
    p.drawPath(path);
#else
    p.drawPath(m_textPainterPath);
#endif
#endif
    *m_logStream << m_timer->elapsed()
                 << "\n";
}

void Widget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    repaint();
    ++m_paintCounter;

    if (m_paintCounter >= 1000) {
        close();
    }
}

void Widget::initTextBuffer()
{
    const int testSize = 1000;
    m_textBuffer.reserve(testSize);
    int x = 0;
    int y = 0;

    for (int i = 0; i < testSize; ++i) {
        m_textCoord.append(QPoint(x, y));
        m_textBuffer.append("QQ!!AABBCC");
        m_textPainterPath.addText(x, y, QFont(), QString("QQ!!AABBCC"));
        x += 10;
        y += 10;
        x = x % 256;
    }
}
