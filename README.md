PROGETTO C++

Riassunto:

Il progetto consiste nell'implementazione di una classe Set in C++, la quale fornisce funzionalità per la gestione di collezioni di elementi generici. 
Il set, come suggerisce il nome, è una struttura dati che rappresenta una collezione di elementi unici (nessun duplicato è permesso). 
Il progetto include anche un file main.cpp per testare le funzionalità della classe Set.

Dettagli:

➢ Classe Set Templata:
La classe Set è implementata come una classe templata, permettendo così la creazione di set di qualsiasi tipo di dato (es: Set<int>, Set<double>, Set<char>, Set<string>, ecc.).

Gestisce la compatibilità tra i tipi attraverso l'uso del cast; infatti, nel file main.cpp ci sono molteplici esempi della creazione di set con diversi tipi di dati 
e delle relative conversioni tra i tipi di dati di diversi set.

➢ Gestione della memoria:

La classe Set gestisce la memoria in modo dinamico; pertanto, la capacità di ogni set viene incrementata esponenzialmente per ridurre il numero 
di riallocazioni necessarie durante l'aggiunta di nuovi elementi.

Per soddisfare questa esigenza, è stato creato un costruttore di default: inizialmente, viene allocata la memoria per l’array che conterrà 
gli elementi del set (inizialmente vuoto), impostando la sua capacità a 1. Quando un nuovo elemento viene aggiunto e il set raggiunge la sua capacità massima, 
la capacità viene raddoppiata. A questo punto, un nuovo array di dimensioni maggiori viene allocato e gli elementi esistenti vengono copiati in esso. 

Dopo la copia, la memoria precedentemente allocata viene liberata.

Inoltre, è stato implementato un costruttore secondario per ottimizzare le prestazioni: anziché utilizzare la tecnica di raddoppio esponenziale, 
la capacità del set viene inizializzata in base alla dimensione dell'array di input. Questo approccio è ottimale per situazioni in cui è previsto 
l'inserimento di un grande numero di elementi nel set e si desidera minimizzare il sovraccarico dovuto a frequenti riallocazioni.

➢ Overloading degli operatori:

Questa tecnica semplifica l’utilizzo degli oggetti della classe Set, controllando meglio il funzionamento di ogni operatore sovrascritto:

a) “Operatore di Assegnamento (operator=)”:

Utilizzato per copiare tutti gli elementi di un set in un altro. Si protegge contro l'auto-assegnazione verificando se l'oggetto sorgente è 
diverso dall'oggetto destinatario prima di procedere con la copia.

b) “Operatore di Accesso di Sola Lettura (operator[])”:

Fornisce un accesso in sola lettura agli elementi del set.

c) ”Operatore di Uguaglianza (operator==)”:

Controlla se due set sono uguali, cioè se contengono gli stessi elementi;

d) ”Operatore di Unione (operator+)”:

Crea un nuovo set che è l'unione di due set. Se un elemento è presente in entrambi i set, viene incluso una sola volta nel set risultante.

e) ”Operatore di Intersezione (operator-)”:

Crea un nuovo set che è l'intersezione di due set. Gli elementi che sono unici per un solo set vengono esclusi dal set risultante.

f) ”Operatore di Stream di Output (operator<<)”:

Utilizzato per stampare il contenuto di un set, inviando un set a uno stream di output (es: std::cout).

➢ Iteratore costante:

La classe const_iterator, definita all'interno della classe Set, serve a gestire le strutture dati in modo sicuro. 

Questa classe permette di accedere agli elementi di un set in sola lettura, senza modificarli, garantendo così la costanza dei dati durante l'iterazione.

Alcuni aspetti interessanti da notare includono:

a) La classe const_iterator utilizza un puntatore di tipo “const T*” che punta all’elemento corrente del set. Questo assicura che gli elementi a cui si accede attraverso l’iteratore non possano essere modificati.

b) La classe const_iterator è progettata per supportare un'iterazione in avanti (forward iteration), ovvero può muoversi solo dal primo all'ultimo elemento del set.

c) La classe Set fornisce i metodi begin() e end() per ottenere iteratori costanti rispettivamente all'inizio e alla fine del set. Questi metodi facilitano l'uso dell'iteratore in loop.

➢ Funzioni Globali:

Le funzioni globali come “filter_out” e “save” offrono operazioni aggiuntive che estendono la funzionalità del set oltre le operazioni standard fornite dalla classe Set. Pur essendo definite al di fuori della classe Set, queste funzioni interagiscono con oggetti di tipo Set:

a) La funzione “filter_out” filtra gli elementi di un set in base a un predicato specificato.

b) La funzione “save” permette di salvare il contenuto di un set in un file.

➢ Eccezioni:
Sono state implementate due eccezioni personalizzate (”duplicateElementException” e “elementNotFoundException”) per gestire casi specifici come l'aggiunta di un elemento duplicato o la rimozione di un elemento non presente nel set. A tale proposito, nel file main.cpp, ci sono due righe di codice (alla riga 42 e alla riga 53) commentati che servono per testare l’uso di queste eccezioni.

Inoltre, sono state utilizzate diverse eccezioni standard del C++ per gestire situazioni specifiche:

a) “std::bad_alloc”, che viene sollevata in caso di fallimento di una nuova allocazione di memoria.

b) “std::out_of_range”, che viene sollevata quando si tenta di accedere a elementi fuori dai limiti validi.

c) “std::runtime_error” , che viene sollevata in caso di fallimento nell'apertura di un file.

**************

PROGETTO GT

Riassunto:

Il progetto consiste nello sviluppo di un'applicazione con interfaccia grafica utente (GUI) per la gestione dei dipinti presenti nella Galleria degli Uffizi.

Dettagli:

➢ Interfaccia grafica:

L’interfaccia principale include una tabella che mostra i dati caricati da file .csv.

Questi dati non sono modificabili e ogni riga della tabella rappresenta un dipinto distinto, mentre ogni colonna rappresenta gli attributi di ciascun dipinto (scuola, autore, titolo, data e sala).

Funzionalità principali attraverso pulsanti:

a) “Aggiungi (on_pushButton_aggiungi_clicked)“:

Serve per aggiungere un nuovo dipinto alla fine della tabella, basandosi sui dati forniti nei campi di input corrispondenti.

b) “Elimina (on_pushButton_elimina_clicked)“:

Consente di rimuovere un dipinto selezionato dall'utente tramite un clic del mouse.

c) “Cerca (on_pushButton_cerca_clicked)“:

Permette di cercare dipinti specifici basandosi sui criteri selezionati dall'utente (intestazione della colonna e testo dell'oggetto cercato).

d) “Ripristina (on_pushButton_iniziale_clicked)“:

Ripristina la tabella alla sua forma iniziale dopo l'aggiunta o l'eliminazione di righe.

Ulteriori opzioni disponibili nella barra del menu:

a) “Percentuale Dipinti per Scuola (on_actionPercentuale_dipinti_per_Scuola_triggered)“:

Mostra un grafico che riporta la percentuale di dipinti per ciascuna scuola.

b) “Numero Dipinti per Data (on_actionNumero_dipinti_per_Data_triggered)“:

Mostra un grafico che riporta il numero di dipinti in base al campo Data.


➢ Gestione interna dei dati della tabella:

La classe Set viene utilizzata per rappresentare ogni riga, ovvero ogni dipinto, nel modo seguente:

a) Ogni riga della tabella dei dipinti è rappresentata da un oggetto Set<QString>, dove ogni elemento del set rappresenta una proprietà unica del dipinto, come la scuola, l'autore, il titolo, la data e la sala.

b) Questi set sono poi raccolti in una QList<Set<QString>>, dove ogni elemento della lista rappresenta un dipinto diverso.

In pratica, viene implementata una struttura multidimensionale, dove ogni set è una dimensione che contiene vari attributi, e la QList di questi set rappresenta un'altra dimensione che tiene traccia di tutti i dipinti.

Gestione interna dei grafici:

La classe CustomChartView viene utilizzata per migliorare la visualizzazione dei grafici, estendendo QChartView, un widget fornito dal modulo Qt Charts.

a) Si occupa della gestione degli eventi di mouse e zoom:Eventi Mouse:

“mousePressEvent“, “mouseMoveEvent“ e “mouseReleaseEvent“ sono stati ridefiniti per implementare una logica personalizzata, come la gestione di eventi di trascinamento con il mouse per spostare la vista del grafico.

a) Eventi Rotellina:

“wheelEvent“ è utilizzato per implementare lo zoom in e zoom out quando l'utente usa la rotellina del mouse.

➢ MessageBox:

Spesso si ricorre all’’utilizzo di MessageBox per messaggi di avviso o informazioni all'utente, quando certe condizioni non sono state soddisfatte:

a) Nel metodo “on_pushButton_aggiungi_clicked“ viene mostrato un avviso se almeno uno dei cinque campi di input non è stato riempito prima di aggiungere un nuovo dipinto.

b) Nel metodo “on_pushButton_elimina_clicked“ viene mostrato un avviso se nessun dipinto è stato selezionato prima di procedere con la rimozione.

c) Nel metodo “on_pushButton_cerca_clicked“ viene mostrato un avviso se il campo di input è vuoto prima di iniziare la ricerca di un dipinto e un messaggio informativo se la ricerca non restituisce risultati.
