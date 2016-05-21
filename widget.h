#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QString>
#include <QPainterPath>

namespace Ui {
class Widget;
}

class QFile;
class QTextStream;
class QElapsedTimer;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void initTextBuffer();

private:
    Ui::Widget *ui;
    QFile *m_logFile;
    QTextStream *m_logStream;
    QElapsedTimer *m_timer;
    QVector<QString> m_textBuffer;
    QVector<QPoint> m_textCoord;
    int m_paintCounter;
    QPainterPath m_textPainterPath;
};

#endif // WIDGET_H
