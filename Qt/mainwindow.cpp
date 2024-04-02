#include "CustomChartView.h"
#include "set.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QByteArray>
#include <QList>
#include <QTableWidgetItem>
#include <QtCharts>
#include <QMap>
#include <QtCharts/QChartView>
#include <QVBoxLayout>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QDialog>
#include <Qt>

using namespace QtCharts;

QList<QByteArray> parseCSVLine(const QByteArray& line); //Dichiarazione della funzione per l'analisi delle righe di un file CSV

// Costruttore per la classe MainWindow.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // si configura l'interfaccia utente
    ui->setupUi(this);

    QWidget *widget = new QWidget();
    widget->setLayout(ui->verticalLayout);
    setCentralWidget(widget); // si imposta un widget centrale nel MainWindow


    // Verifica se il file esiste e può essere aperto in lettura
    /*if (!f.exists()) {
        QMessageBox::critical(this, "Errore", "Il file dipinti_uffizi.csv non esiste.");
        qDebug() << "Percorso di esecuzione corrente:" << QDir::currentPath();
        return;
    }

    if (!f.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Errore", "Impossibile aprire il file dipinti_uffizi.csv.");
        return;
    }*/



    // si crea un oggetto QFile per leggere il file CSV
    QFile f("dipinti_uffizi.csv");
    // si apre il file in modalità di sola lettura
    f.open(QIODevice::ReadOnly);

    // vengono letti e memorizzati tutti i dati dal file
    QByteArray data = f.readAll();

    // si chiude il file
    f.close();

    // si imposta il numero di righe nella tabella in base al numero di linee nel file
    ui->tableWidget->setRowCount(data.count('\n'));

    // vengono divisi i dati in righe usando il carattere di nuova linea
    QList<QByteArray> lines = data.split('\n');

    // si itera su ogni riga del file CSV
    for (int i = 0; i < lines.size(); ++i) {
        QByteArray line = lines.at(i);

        // si ignora la prima riga del file .csv (quella dove ci sono i titoli delle colonne)
        if (i == 0) {
            continue;
        }

        // si analizza ogni riga del file CSV
        QList<QByteArray> values = parseCSVLine(line);

        // si crea un insieme di set di stringhe
        Set<QString> setDipinti;
        // si conta il numero di valori (colonne) nella riga corrente e lo memorizza in x
        int x = values.count();
        // se il numero di valori nella riga corrente è maggiore del numero di colonne nella tabella
        // si aggiorna il numero di colonne della tabella per adattarsi
        if (x > ui->tableWidget->columnCount())
            ui->tableWidget->setColumnCount(x);

        // si inizia un ciclo che itera su ogni valore (cella) nella riga corrente
        for (int j = 0; j < values.count(); ++j) {
            QByteArray cell = values.at(j);
            // vengono rimossi le virgolette dalle celle
            cell = cell.replace("\"", "");
            // vengono aggiunti elementi al set
            setDipinti.add(QString(cell));
            // si crea il nuovo elemento nella tabella per ogni cella
            QTableWidgetItem *item = new QTableWidgetItem(QString(cell));        
            // cosi gli elementi della tabella saranno non modificabili
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            // l'aggiunta dell'elemento nella tabella
            ui->tableWidget->setItem(i - 1, j, item); // i - 1 perché abbiamo saltato la prima riga
        }
        setsData.append(setDipinti); // viene aggiunto il set di stringhe alla lista
        originalData.append(setDipinti); // vengono conservati i dati originali
    }

    // per alcuni label viene implementata opzione di andare a capo
    ui->label->setWordWrap(true);
    ui->label_2->setWordWrap(true);
    ui->label_3->setWordWrap(true);

    // viene impostata la modalità di ridimensionamento dell'intestazione orizzontale e verticale.
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


// Funzione per analizzare una riga CSV
QList<QByteArray> parseCSVLine(const QByteArray& line) {
    QList<QByteArray> result;
    bool inQuotes = false;
    QByteArray current;

    for (int i = 0; i < line.size(); ++i) {
        if (line[i] == '\"') {
            inQuotes = !inQuotes;
        } else if (line[i] == ',' && !inQuotes) {
            result.append(current.trimmed());
            current.clear();
        } else {
            current.append(line[i]);
        }
    }
    if (!current.isEmpty()) {
        result.append(current.trimmed());
    }

    return result;
}


// Distruttore per MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}


// Slot per gestire il click sul pulsante "aggiungi"
void MainWindow::on_pushButton_aggiungi_clicked()
{
    // controlla se tutti i QLineEdit sono riempiti
    if (ui->lineEdit_scuola_aggiungi->text().trimmed().isEmpty() ||
        ui->lineEdit_autore_aggiungi->text().trimmed().isEmpty() ||
        ui->lineEdit_titolo_aggiungi->text().trimmed().isEmpty() ||
        ui->lineEdit_data_aggiungi->text().trimmed().isEmpty() ||
        ui->lineEdit_sala_aggiungi->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Attenzione", "Tutti i campi devono essere riempiti.");
        return;
    }

    // si crea un nuovo set per il dipinto e si aggiungono i dati
    Set<QString> nuovoDipinto;
    nuovoDipinto.add(ui->lineEdit_scuola_aggiungi->text());
    nuovoDipinto.add(ui->lineEdit_autore_aggiungi->text());
    nuovoDipinto.add(ui->lineEdit_titolo_aggiungi->text());
    nuovoDipinto.add(ui->lineEdit_data_aggiungi->text());
    nuovoDipinto.add(ui->lineEdit_sala_aggiungi->text());

    // si aggiunge il nuovo set alla lista di set
    setsData.append(nuovoDipinto);

    // aggiunge una nuova riga alla tabella per visualizzare il nuovo dipinto e popola le celle
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(ui->lineEdit_scuola_aggiungi->text()));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(ui->lineEdit_autore_aggiungi->text()));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(ui->lineEdit_titolo_aggiungi->text()));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(ui->lineEdit_data_aggiungi->text()));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(ui->lineEdit_sala_aggiungi->text()));

    // svuota i campi di input dopo l'inserimento
    ui->lineEdit_scuola_aggiungi->clear();
    ui->lineEdit_autore_aggiungi->clear();
    ui->lineEdit_titolo_aggiungi->clear();
    ui->lineEdit_data_aggiungi->clear();
    ui->lineEdit_sala_aggiungi->clear();
}


// Slot per gestire il click sul pulsante "elimina"
void MainWindow::on_pushButton_elimina_clicked()
{
    // si ottiene la riga selezionata
    int row = ui->tableWidget->currentRow();

    // si controlla se una riga è selezionata
    if (row < 0) {
        QMessageBox::warning(this, "Attenzione", "Seleziona un dipinto da eliminare.");
        return;
    }

    // si rimuove il set corrispondente e la riga dalla tabella
    setsData.removeAt(row);
    ui->tableWidget->removeRow(row);
    // deseleziona qualsiasi riga dopo l'eliminazione
    ui->tableWidget->clearSelection();
    // viene impostata la riga corrente su un indice non valido
    ui->tableWidget->setCurrentCell(-1, -1);

}


// Slot per gestire il click sul pulsante "cerca"
void MainWindow::on_pushButton_cerca_clicked()
{
    // si ottiene il testo di ricerca
    QString ricercaTesto = ui->lineEdit_scelta->text().trimmed();
    // si ottiene l'indice della colonna selezionata
    int colonnaRicerca = ui->comboBox_scelta->currentIndex();

    if (ricercaTesto.isEmpty()) {
        QMessageBox::warning(this, "Attenzione", "Inserisci l'elemento che stai cercando.");
        return;
    }

    // si cerca attraverso le righe della tabella
    bool trovato = false;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
           // Assumendo che il testo cercato si trovi nella colonna selezionata
           QTableWidgetItem *item = ui->tableWidget->item(i, colonnaRicerca);
           if (item && item->text() == ricercaTesto) {
               ui->tableWidget->showRow(i);
               trovato = true;
           } else {
               ui->tableWidget->hideRow(i);
           }
       }

    if (!trovato) {
       QMessageBox::information(this, "Ricerca", "Nessun dipinto trovato con il titolo/soggetto specificato.");
    }

    // svuota il campo di input dopo l'inserimento
    ui->lineEdit_scelta->clear();
}


// Slot per gestire il click sul pulsante "tabella iniziale"
void MainWindow::on_pushButton_iniziale_clicked()
{
    // si cancella la tabella corrente
    ui->tableWidget->setRowCount(0);

    // si ricrea la tabella utilizzando i dati originali
    for (const Set<QString> &row : qAsConst(originalData)) {
        int newRow = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(newRow);

        int j = 0;
        for (const QString &value : row) {
            QTableWidgetItem *item = new QTableWidgetItem(value);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tableWidget->setItem(newRow, j, item);
            ++j;
        }
    }
}


// Slot per visualizzare un grafico a barre con la percentuale dei dipinti per scuola
void MainWindow::on_actionPercentuale_dipinti_per_Scuola_triggered()
{
    // si crea un nuovo dialog
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Percentuale dipinti per Scuola");

    // si crea una mappa per tenere traccia del conteggio degli elementi (dipinti per scuola)
    QMap<QString, int> itemCount;
    int totalItems = 0;

    // Contaggio di ogni elemento per ogni Scuola
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        QString itemText = ui->tableWidget->item(i, 0)->text();
        itemCount[itemText]++;
        totalItems++;
    }

    // si crea una serie di dati per il grafico a barre
    QBarSeries *series = new QBarSeries();
    // si crea una lista di stringhe per le categorie (scuole)
    QStringList categories;
    // si crea un nuovo set di barre
    QBarSet *set = new QBarSet("");

    // Controlla la percentuale di ogni elemento
    for (auto it = itemCount.constBegin(); it != itemCount.constEnd(); ++it) {
        // si calcola la percentuale di ogni categoria
        double percent = (totalItems > 0) ? (static_cast<double>(it.value()) / totalItems * 100.0) : 0;
        // si aggiunge la percentuale al set di barre
        *set << percent;
        // si aggiunge la categoria (scuola) alla lista delle categorie
        categories << it.key();
    }
    // si aggiunge il set di barre alla serie
    series->append(set);

    // si configura e si crea il grafico
    QChart *chart = new QChart();
    // viene aggiunta la serie di barre al grafico
    chart->addSeries(series);

    // si crea un nuovo asse delle categorie per l'asse X
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    // vengono aggiunte le categorie all'asse X
    axisX->append(categories);
    // viene impostata l'angolazione delle etichette sull'asse X
    axisX->setLabelsAngle(-90);
    // si aggiunge l'asse X al grafico e lo si allinea in basso
    chart->addAxis(axisX, Qt::AlignBottom);
    // si associa la serie di barre all'asse X
    series->attachAxis(axisX);

    // si crea un nuovo asse delle categorie per l'asse Y
    QValueAxis *axisY = new QValueAxis();
    // si imposta l'intervallo di valori per l'asse Y
    axisY->setRange(-100, 100);
    // si imposta il formato delle etichette sull'asse Y
    axisY->setLabelFormat("%.2f%%");
    // si imposta il numero di tacche sull'asse Y
    axisY->setTickCount(21);
    // si aggiunge l'asse Y al grafico e lo allinea a sinistra
    chart->addAxis(axisY, Qt::AlignLeft);
    // si associa la serie di barre all'asse E
    series->attachAxis(axisY);

    // si crea una vista personalizzata per il grafico
    CustomChartView *chartView = new CustomChartView(chart);
    // si imposta il suggerimento di rendering per la vista del grafico
    chartView->setRenderHint(QPainter::Antialiasing);

    // si crea un layout verticale per il dialogo
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    // si aggiunge la vista del grafico al layout
    layout->addWidget(chartView);

    // si imposta il layout sul dialogo
    dialog->setLayout(layout);
    // si impostano le dimensioni del dialogo
    dialog->resize(1200, 1000);
    // si esegue il dialogo
    dialog->exec();
}


// Slot per visualizzare un grafico a barre con il numero di dipinti per data
void MainWindow::on_actionNumero_dipinti_per_Data_triggered()
{
    // si crea un nuovo dialog
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Numero dipinti per Data");

    // si conta il numero totale di ogni elemento della quarta colonna
    QMap<QString, int> itemCount;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        if (ui->tableWidget->item(i, 3) != nullptr) {
            QString itemText = ui->tableWidget->item(i, 3)->text();
            itemCount[itemText]++;
        }
    }

    // si crea una serie di dati per il grafico a barre
    QBarSet *set = new QBarSet("");
    // si crea una lista di stringhe per le categorie (date)
    QStringList categories;
    // si itera attraverso la mappa per popolare il grafico a barre
    for (auto it = itemCount.constBegin(); it != itemCount.constEnd(); ++it) {
        // si aggiunge il conteggio (numero di dipinti) al set di barre
        *set << it.value();
        // si aggiunge la data alla lista delle categorie
        categories.append(it.key());
    }

    // si crea una nuova serie di barre
    QBarSeries *series = new QBarSeries();
    // si aggiunge il set di barre alla serie
    series->append(set);

    // si configura e si crea il grafico
    QChart *chart = new QChart();
    // viene aggiunta la serie di barre al grafico
    chart->addSeries(series);

    // si crea un nuovo asse delle categorie per l'asse X
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    // si aggiunge il set di barre alla serie.
    axisX->append(categories);
    // si imposta l'angolazione delle etichette sull'asse X
    axisX->setLabelsAngle(-90);
    // si aggiunge l'asse X al grafico, allineandolo in basso
    chart->addAxis(axisX, Qt::AlignBottom);
    // si associa la serie di barre all'asse X
    series->attachAxis(axisX);

    // si crea un nuovo asse delle categorie per l'asse Y
    QValueAxis *axisY = new QValueAxis();
    // imposta l'intervallo dell'asse Y
    axisY->setRange(-50, 50);
    // si imposta il numero di tacche sull'asse Y
    axisY->setTickCount(21);
    // si aggiunge l'asse Y al grafico, allineandolo a sinistra
    chart->addAxis(axisY, Qt::AlignLeft);
    // si associa la serie di barre all'asse Y
    series->attachAxis(axisY);

    // si crea una vista personalizzata per il grafico
    CustomChartView *chartView = new CustomChartView(chart);
    // si imposta il suggerimento di rendering per la vista del grafico
    chartView->setRenderHint(QPainter::Antialiasing);

    // si crea un layout verticale per il dialogo
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    // si aggiunge la vista del grafico al layout
    layout->addWidget(chartView);

    // si imposta il layout sul dialogo
    dialog->setLayout(layout);
    // si impostano le dimensioni del dialogo
    dialog->resize(1200, 1000);
    // si esegue il dialogo
    dialog->exec();
}

