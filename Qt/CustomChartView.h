/**
 * @file CustomChartView.h
 *
 * @brief File header della classe CustomChartView
 *
 * File di dichiarazioni/definizioni della classe CustomChartView, utilizzata per migliorare
 * la visualizzazione dei grafici, estendendo QChartView, un widget fornito dal modulo Qt Charts
 */

#ifndef CUSTOMCHARTVIEW_H
#define CUSTOMCHARTVIEW_H

#include <QtCharts/QChartView>
#include <QMouseEvent>

using namespace QtCharts;

class CustomChartView : public QChartView {
    Q_OBJECT

public:
    explicit CustomChartView(QChart *chart, QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QPoint m_lastMousePos;
    bool m_isMousePressed;
};

#endif // CUSTOMCHARTVIEW_H
