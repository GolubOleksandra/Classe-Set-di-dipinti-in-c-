#include "CustomChartView.h"

// Costruttore della classe CustomChartView
CustomChartView::CustomChartView(QChart *chart, QWidget *parent)
    : QChartView(chart, parent), m_isMousePressed(false) {}

// Gestisce l'evento di rotazione della rotellina del mouse (scroll)
// Questo metodo consente di zoomare in avanti e indietro sul grafico
void CustomChartView::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) {
        // se si ruota la rotellina in avanti, lo zoom avanza
        chart()->zoomIn();
    } else {
        // se si ruota la rotellina all'indietro, lo zoom arretra
        chart()->zoomOut();
    }
}

// Gestisce l'evento di pressione del pulsante del mouse
void CustomChartView::mousePressEvent(QMouseEvent *event) {
    // controlla se il pulsante premuto è il tasto sinistro del mouse
    if (event->button() == Qt::LeftButton) {
        // memorizza la posizione attuale del mouse
        m_lastMousePos = event->pos();
        // true perche il pulsante del mouse è stato premuto
        m_isMousePressed = true;
    }
}

// Gestisce l'evento di movimento del mouse
void CustomChartView::mouseMoveEvent(QMouseEvent *event) {
    // controlla se il pulsante del mouse è premuto
    if (m_isMousePressed) {
        // calcola il cambiamento della posizione del mouse
        auto dPos = event->pos() - m_lastMousePos;
        // sposta il grafico in base al movimento del mouse
        chart()->scroll(-dPos.x(), -dPos.y());
        // aggiorna l'ultima posizione del mouse
        m_lastMousePos = event->pos();
    }
}

// Gestisce l'evento di rilascio del pulsante del mouse
void CustomChartView::mouseReleaseEvent(QMouseEvent *event) {
    // se il pulsante rilasciato è il tasto sinistro del mouse
    if (event->button() == Qt::LeftButton) {
        // false perche il pulsante del mouse è stato rilasciato
        m_isMousePressed = false;
    }
}
