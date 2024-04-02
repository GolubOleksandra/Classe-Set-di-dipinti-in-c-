/**
 * @file mainwindow.h
 *
 * @brief File header della classe MainWindow
 *
 * File di dichiarazioni/definizioni della classe MainWindow
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "set.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_pushButton_aggiungi_clicked();

    void on_pushButton_elimina_clicked();

    void on_pushButton_cerca_clicked();

    void on_pushButton_iniziale_clicked();

    void on_actionPercentuale_dipinti_per_Scuola_triggered();

    void on_actionNumero_dipinti_per_Data_triggered();

private:
    Ui::MainWindow *ui;
    QList<Set<QString>> originalData; // Lista di set per conservare ogni riga come un set distinto (tabella iniziale di copia)
    QList<Set<QString>> setsData; // Lista di set per conservare ogni riga come un set distinto

};
#endif // MAINWINDOW_H
