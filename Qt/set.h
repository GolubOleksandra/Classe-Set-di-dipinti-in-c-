/**
 * @file set.h
 *
 * @brief File header della classe Set templata
 *
 * File di dichiarazioni/definizioni della classe Set templata
 */

#ifndef SET_H
#define SET_H

#include <iostream>
#include <limits.h>
#include <cassert>
#include <fstream>
#include <string>
#include <exception>

using namespace std;


/**
 * @brief Eccezione personalizzata per indicare che è stato trovato un'elemento duplicato.
 *
 * Questa eccezione viene lanciata quando si trova un'elemento duplicato in un dato set.
 */
class duplicateElementException : public exception {
public:

  /**
   * @brief Fornisce il messaggio di errore per l'eccezione.
   *
   * @return una stringa costante che descrive l'errore.
   */
    const char* what() const noexcept override {
        return "E' stato trovato un'elemento duplicato.";
    }
};


/**
 * @brief Eccezione personalizzata per indicare che un'elemento non è stato trovato.
 *
 * Questa eccezione viene lanciata quando si cerca un'elemento in un dato set e questo non è presente.
 */
class elementNotFoundException : public exception {
public:

  /**
   * @brief Fornisce il messaggio di errore per l'eccezione.
   *
   * @return una stringa costante che descrive l'errore.
   */
    const char* what() const noexcept override {
        return "L'elemento che stai cercando non c'e' in questo set.";
    }
};



/**
  @brief classe Set

  La classe implementa un set di elementi generici T.
*/
template <typename T> class Set {
    T* arr; ///< puntatore al primo elemento di un array
    int capacity; ///< il numero totale di elementi che l'array può attualmente contenere
    int currentSize; ///< il numero di elementi attualmente inseriti nel set

public:
    /**
     * @brief Costruttore di default.
     * 
     * Inizializza un nuovo oggetto Set. All'inizio, il set è vuoto con una capacità iniziale 
     * predefinita. L'array `arr` viene inizializzato a nullptr per evitare puntatori appesi,
     * poi viene allocato dinamicamente con la capacità iniziale.
     *
     * @details
     * Il costruttore imposta prima `arr` su nullptr, `capacity` su 1 e `currentSize` su 0.
     * Poi, alloca memoria per l'array `arr` basandosi sulla capacità iniziale. Questo approccio
     * aiuta a prevenire errori in caso di fallimento dell'allocazione di memoria, assicurando
     * che il distruttore non tenti di deallocare un puntatore non inizializzato.
     */
    Set() : arr(nullptr), capacity(1), currentSize(0) {
        arr = new T[capacity];
    }

    /**
     * @brief Costruttore secondario che inizializza un set con un insieme di elementi.
     *
     * Questo costruttore crea un set e lo popola con elementi da un array in input.
     * La capacità iniziale del set è impostata uguale al numero degli elementi in input,
     * ottimizzando così le prestazioni riducendo il numero di riallocazioni necessarie.
     *
     * @param array un puntatore a un array di elementi di tipo T.
     * @param size il numero di elementi nel array.
     *
     * @throw duplicateElementException()
     */
    Set(const T* array, size_t size) : arr(nullptr), capacity(size), currentSize(0) {
        arr = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            if (!contains(array[i])) {
                arr[currentSize++] = array[i];
            } /*else {
                throw duplicateElementException();
            }*/
        }
    }

    /**
     * @brief Costruttore di copia.
     * 
     * Crea una nuova istanza di Set che è una copia profonda di un altro Set.
     * Questo costruttore copia tutti gli elementi dal Set sorgente al nuovo Set,
     * mantenendo la stessa capacità e la dimensione corrente.
     * 
     * @param other reference costante a un altro oggetto Set da cui copiare i dati.
     * 
     * @details
     * Il costruttore inizia inizializzando `arr` a nullptr e impostando `capacity` e `currentSize`
     * ai valori di `other`. Successivamente, alloca memoria per l'array `arr` e copia ogni elemento
     * dall'array `other.arr`. Questo assicura che il nuovo Set sia una copia indipendente di `other`,
     * con i propri dati e risorse.
     * 
     * @throw std::bad_alloc possibile eccezione di allocazione
     */
    Set(const Set<T>& other) : arr(nullptr), capacity(other.capacity), currentSize(other.currentSize) {
        arr = new T[capacity];
        try {
            for (int i = 0; i < currentSize; i++) {
                arr[i] = other.arr[i];
            }
        }catch(...){
            clear(); 
            throw;
        }
    }


    /**
     * @brief Distruttore.
     *
     * Dealloca l'array dinamico utilizzato per memorizzare gli elementi del set.
     */
    ~Set() {
        clear();
    }


    /**
     * @brief Costruttore template che permette di creare un set 
     * da una sequenza di elementi definita da due iteratori generici.
     * 
     * Questo costruttore consente di costruire un set inizializzandolo con gli elementi
     * di un'altra sequenza o container. La sequenza è definita da una coppia di iteratori,
     * che specificano rispettivamente l'inizio e la fine della sequenza da copiare.
     * 
     * Il costruttore alloca inizialmente un array di capacità 1 e poi aggiunge gli elementi
     * nella sequenza uno ad uno, aumentando la capacità del set se necessario.
     *
     * @param begin iteratore generico di inizio sequenza 
     * @param end iteratore generico di fine sequenza
     * 
     * @throw std::bad_alloc possibile eccezione di allocazione 
     */
    template <typename Iterator>
    Set(Iterator begin, Iterator end) {
        capacity = 1;
        currentSize = 0;
        arr = new T[capacity];
        try {
            for (Iterator it = begin; it != end; ++it) {
                add(static_cast<T>(*it));
            } 
        } catch(...) {
            clear(); 
            throw;
        }

    }


    /**
     * @brief Operatore di assegnamento. 
     *
     * Garantisce che, quando si assegna un set a un altro, tutti i dati dell'oggetto 
     * sorgente vengano copiati correttamente nell'oggetto di destinazione
     * 
     * @param other reference costante a un altro oggetto Set da cui copiare i dati
     *
     * @details
     * Se 'other' è diverso da questo set (controllo dell'auto-assegnazione), crea una copia
     * temporanea di 'other' e poi scambia il suo stato con quello di questo set. Ciò consente
     * di gestire correttamente la memoria e altre risorse, evitando potenziali problemi di
     * auto-assegnamento e garantendo la sicurezza delle eccezioni.
     *
     * @return reference a questo set modificato
     */
    Set& operator=(const Set<T>& other) {
        if (this != &other) {   // Controlla l'auto-assegnazione
            Set<T> temp(other); // Crea una copia temporanea di 'other'
            swap(temp);         // Scambia il contenuto di 'this' con quella copia temporanea
        }
        return *this;           // La copia temporanea (che ora contiene lo stato originale di 'this') viene distrutta
    }
 

    /**
     * @brief Scambia il contenuto di questo set con un altro set.
     *
     * @param other reference al set con cui scambiare i dati
     *
     * @details
     * Scambia gli array interni, le capacità e le dimensioni correnti
     * di questo set con quelli del set 'other'. 
     */

    void swap(Set& other) {
        std::swap(arr, other.arr); // Usa std::swap per scambiare i puntatori
        std::swap(capacity, other.capacity);
        std::swap(currentSize, other.currentSize);
    }


    /**
     * @brief Svuota il set.
     *
     * Rimuove tutti gli elementi dal Set e resetta le sue proprietà interne.
     * Dopo l'esecuzione di questo metodo, il Set sarà vuoto, con una capacità e
     * una dimensione corrente impostate a 0.
     *
     * @details
     * Questo metodo dealloca l'array interno che memorizza gli elementi del Set
     * e imposta il puntatore 'arr' su nullptr per evitare puntatori appesi. 
     * Resetta anche 'currentSize' e 'capacity' a 0. Dopo la chiamata a 'clear',
     * il Set non conterrà alcun elemento e non avrà memoria allocata.
     */
    void clear() {
        delete[] arr;  
        arr = nullptr; 
        currentSize = 0; 
        capacity = 0;    
    }

    /**
     * @brief Ritorna il numero di elementi presenti nel set.
     * 
     * @return il numero di elementi presenti nel set
    */
    int size() const {
        return currentSize;
    }


    /**
     * @brief Controlla se un dato elemento è già presente nel set.
     *
     * @param value il valore da controllare
     *
     * @return true o false
    */
    bool contains(const T& value) const {
        for (int i = 0; i < currentSize; ++i) {
            if (arr[i] == value) {
                return true; 
            }
        }
        return false; 
    }


    /**
     * @brief Aggiunge un nuovo elemento nel set.
     *
     * @param value il valore da aggiungere 
    */
    void add(const T& value) {
        // Controlla se l'elemento è già presente
        if (!contains(value)) {
            // Assicurati che ci sia spazio per aggiungere un nuovo elemento
            if (currentSize == capacity) {
                // Raddoppia la capacità se necessario
                capacity *= 2;
                T* temp = new T[capacity];
                for (int i = 0; i < currentSize; i++) {
                    temp[i] = arr[i];
                }
                delete[] arr;
                arr = temp;
            }
            // Aggiungi l'elemento e incrementa la dimensione
            arr[currentSize++] = value;
        }/*else{
            throw duplicateElementException();
        }*/
    }


    /**
     * @brief Elimina un certo elemento dal set.
     *
     * @param value il valore da rimuovere
    */
    void remove(const T& value) {
        for (int i = 0; i < currentSize; ++i) {
            if (arr[i] == value) {
                // Trovato l'elemento da rimuovere
                for (int j = i; j < currentSize - 1; ++j) {
                    arr[j] = arr[j + 1]; // Sposta tutti gli elementi successivi indietro di una posizione
                }
                currentSize--; // Decrementa la dimensione del Set
                return; // Termina il metodo dopo la rimozione
            } 
        } 
        // Se l'elemento non è stato trovato, lancia un'eccezione
        //throw elementNotFoundException();
    }

 
    /**
     * @brief Operatore di accesso in sola lettura.
     * 
     * @param index l'indice dell'elemento nel Set che si desidera accedere
     * 
     * @return reference all'elemento corrispondente nel Set
    */
    const T& operator[](int index) const {
        // Controlla se l'indice è nel range valido
        if (index < 0 || index >= currentSize) {
            throw out_of_range("Indice è fuori dai limiti");
        }
        return arr[index];
    }


    /**
     * @brief Funzione GLOBALE che implementa l'operatore di stream.
     * 
     * La funzione è templata su set ed è messa
     * friend perché accediamo ai dati privati di set.
     * La funzione consente di stampare il contenuto del set, 
     * mostrando il numero di elementi seguito da ogni elemento 
     * racchiuso tra parentesi e separati da spazi.
     * 
     * @param os stream di output
     * @param s set da spedire sullo stream
     * 
     * @return lo stream di output
    */
    friend ostream& operator<<(ostream& os, const Set<T>& s) {
        os << s.currentSize;
        if (s.currentSize > 0) {
            os << " (";
            for (int i = 0; i < s.currentSize; i++) {
                os << s.arr[i];
                if (i < s.currentSize - 1) {
                    os << ") (";
                }
            }
            os << ")";
        }
        return os;
    }


    /**
     * @brief Funzione GLOBALE che implementa l'operatore di ugualianza.
     * 
     * La funzione è templata su set ed è messa
     * friend perché accediamo ai dati privati di set.
     * La funzione verifica l'uguaglianza tra due set 
     * confrontando le loro dimensioni e i loro elementi.
     * 
     * @param a reference al primo set
     * @param b reference al secondo set
     * 
     * @return true o false
    */
    friend bool operator==(const Set<T>& a, const Set<T>& b) {
        if (a.currentSize != b.currentSize) return false;
        for (int i = 0; i < a.currentSize; i++) {
            if (!b.contains(a.arr[i])) return false;
        }
        return true;
    }

        /**
         * @class const_iterator
         * @brief Iteratore costante per la classe Set.
         *
         * La classe const_iterator è un iteratore che permette di attraversare
         * la collezione di elementi di una classe Set in modo costante, cioè senza
         * modificarli. Fornisce accesso in sola lettura agli elementi della classe Set.
         */
        class const_iterator {
            const T* ptr; ///< Puntatore all'elemento corrente

            // La classe container deve essere messa friend dell'iteratore per poter
            // usare il costruttore di inizializzazione.
            friend class Set;

        public:
            typedef forward_iterator_tag      iterator_category; ///< Categoria di iteratore utilizzata per identificare il tipo di iterazione supportato
            typedef T                         value_type; ///<  Tipo di valore a cui l'iteratore fa riferimento
            typedef ptrdiff_t                 difference_type; ///< Tipo utilizzato per rappresentare la differenza tra due iteratori
            typedef const T*                  pointer; ///< Puntatore a un elemento costante
            typedef const T&                  reference; ///< Riferimento a un elemento costante


           /**
            * @brief Costruttore di default.
            *
            * @param p puntatore all'elemento iniziale (default è nullptr)
            */
            const_iterator(const T* p = nullptr) : ptr(p) {}


           /**
            * @brief Costruttore di copia.
            *
            * @param other altro const_iterator da copiare
            */
            const_iterator(const const_iterator& other) : ptr(other.ptr) {}

           /**
            * @brief Operatore di assegnamento.
            *
            * @param other altro const_iterator da assegnare a questo
            *
            * @return reference a questo iteratore dopo l'assegnamento
            */
            const_iterator& operator=(const const_iterator& other) {
                ptr = other.ptr;
                return *this;
            }

           /**
            * @brief Distruttore.
            */
            ~const_iterator() {}


           /**
            * @brief Dereferenzia l'iteratore.
            *
            * Ritorna il dato riferito dall'iteratore (dereferenziamento).
            *
            * @return il dato riferito dall'iteratore
            */
            reference operator*() const {
                return *ptr;
            }

           /**
            * @brief Accesso al membro dell'elemento puntato dall'iteratore.
            *
            * Ritorna il puntatore al dato riferito dall'iteratore.
            *
            * @return puntatore al dato riferito dall'iteratore
            */
            pointer operator->() const {
                return ptr;
            }

           /**
            * @brief Incrementa l'iteratore (pre-incremento).
            *
            * @return riferimento a questo iteratore dopo l'incremento
            */
            const_iterator& operator++() {
                ptr++;
                return *this;
            }

           /**
            * @brief Incrementa l'iteratore (post-incremento).
            *
            * @return iteratore ai valori precedenti l'incremento
            */
            const_iterator operator++(int) {
                const_iterator temp = *this;
                ++(*this);
                return temp;
            }


           /**
            * @brief Confronta due iteratori per uguaglianza.
            *
            * @param other altro iteratore da confrontare
            *
            * @return true se gli iteratori sono uguali, false altrimenti
            */
            bool operator==(const const_iterator& other) const {
                return ptr == other.ptr;
            }

           /**
            * @brief Confronta due iteratori per diversità.
            *
            * @param other altro iteratore da confrontare
            *
            * @return true se gli iteratori sono diversi, false altrimenti
            */
            bool operator!=(const const_iterator& other) const {
                return ptr != other.ptr;
            }
        };

       /**
        * @brief Ritorna un iteratore costante al primo elemento del set.
        *
        * Questa funzione crea e ritorna un const_iterator che punta al primo elemento
        * del set. È utile per iniziare un'iterazione su tutti gli elementi del set.
        *
        * @return const_iterator un iteratore costante che punta al primo elemento del set
        */
        const_iterator begin() const {
            return const_iterator(arr);
        }

        /**
        * @brief Ritorna un iteratore costante che punta appena oltre l'ultimo elemento del set.
        *
        * Questa funzione crea e ritorna un const_iterator che punta alla posizione
        * successiva all'ultimo elemento del set. Questo iteratore funge da "sentinella"
        * per terminare l'iterazione.
        *
        * @return const_iterator un iteratore costante che punta alla posizione dopo l'ultimo elemento del set
        */
        const_iterator end() const {
            return const_iterator(arr + currentSize);
        }
};

   /**
     * @brief Funzione GLOBALE che crea un nuovo set in base ai requisiti del predicato.
     * 
     * Accetta un set e un dato predicato, restituendo il nuovo set, 
     * contenente gli elementi che soddisfano il predicato.
     * 
     * @param s reference al set
     * @param p il predicato da usare
     * 
     * @return result il nuovo set che soddisfa il predicato
    */
    template <typename T, typename Predicate>
    Set<T> filter_out(const Set<T>& s, Predicate p) {
        Set<T> result;
        for (int i = 0; i < s.size(); ++i) {
            if (p(s[i])) {
                result.add(s[i]);
            }
        }
        return result;
    }

   /**
     * @brief Funzione GLOBALE che implementa l'operatore di unione.
     * 
     * La funzione concatena gli elementi dei due set, controllando 
     * se sono già presenti nel nuovo set per evitare i duplicati.
     * 
     * @param a reference al primo set
     * @param b reference al secondo set
     * 
     * @return result, il nuovo set
    */
    template <typename T>
    Set<T> operator+(const Set<T>& a, const Set<T>& b) {
        Set<T> result;
        // Aggiungi tutti gli elementi del primo set al set risultante
        for (int i = 0; i < a.size(); ++i) {
            result.add(a[i]);
        }
        // Aggiungi tutti gli elementi del secondo set al set risultante
        // Controlla se sono già presenti nel set per evitare duplicati
        for (int i = 0; i < b.size(); ++i) {
            if (!result.contains(b[i])) {
                result.add(b[i]);
            }
        }
        return result;
    }


   /**
     * @brief Funzione GLOBALE che implementa l'operatore di intersezione.
     * 
     * La funzione crea l'intersezione di due set, controllando 
     * se sono già presenti nel nuovo set per evitare i duplicati.
     * 
     * @param a reference al primo set
     * @param b reference al secondo set
     * 
     * @return result, il nuovo set
    */
    template <typename T>
    Set<T> operator-(const Set<T>& a, const Set<T>& b) {
        Set<T> result;
        // Itera su tutti gli elementi del primo set
        for (int i = 0; i < a.size(); ++i) {
            // Se un elemento del primo set è presente anche nel secondo set,
            // lo aggiunge al set risultante
            if (b.contains(a[i])) {
                result.add(a[i]);
            }
        }
        return result;
    }

   /**
     * @brief Funzione GLOBALE che salva il contenuto di un set di stringhe in un file.
     * 
     * @param s set di stringhe da salvare
     * @param filename il nome del file in cui salvare il set
    */
    inline void save(const Set<std::string>& s, const std::string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (Set<string>::const_iterator it = s.begin(); it != s.end(); ++it) {
                file << *it << endl;
            }
            file.close();
        }
        else {
            throw runtime_error("Impossibile aprire il file");
        }
    }

    /**
     * @brief Verifica se un numero è pari.

     * @param x il numero intero da controllare
     * @return true se il numero è pari, altrimenti false
     */
    inline bool pari(int x) {
        return x % 2 == 0;
    }

    /**
     * @brief Verifica se un numero è dispari.

     * @param x il numero intero da controllare
     * @return true se il numero è dispari, altrimenti false
     */
    inline bool dispari(int x) {
        return x % 2 != 0;
    }


#endif
