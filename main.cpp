/**
 * @file main.cpp
 * @brief File dei test per la classe Set, specializzata per gestire le collezioni degli elementi 
 * 
 * File dei test per la classe Set, specializzata per gestire le collezioni degli elementi.
 */

#include "set.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <list>

using namespace std;
 
/**
 * @brief Tipo definito per un insieme di interi.
 *
 * Typedef della classe Set su interi 
 * 
 */
typedef Set<int> defaultSet;

/**
 * @brief Test della classe Set e delle sue funzioni
 * 
 * Test della classe Set e delle sue funzioni.
*/
void test_set() {
    cout << "------------------------------------------------" << endl;
    cout << "Test della funzione add" << endl;
    cout << "Esempio: primoSet = {1, 6, 4, 9, 7, 10, 12}" << endl;
    // cout << "Esempio l'eccezione: primoSet = {1, 6, 4, 9, 7, 10, 12, 10}" << endl;
    defaultSet primoSet;
    primoSet.add(1);
    primoSet.add(6);
    primoSet.add(4);
    primoSet.add(9);
    primoSet.add(7);
    primoSet.add(10);
    primoSet.add(12);
    // primoSet.add(10); // test eccezione duplicateElementException
    cout << "Stampa del primoSet: " << endl;
    cout << primoSet << endl;
    cout << "Se si vuole testare l'eccezione duplicateElementException, bisogna togliere il commento nel main.cpp a riga 42" << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;

    cout << "Test della funzione remove" << endl;
    cout << "Esempio: viene eliminato il valore 9 dal primoSet" << endl;
    // cout << "Esempio: viene eliminato il valore 0 dal primoSet" << endl;
    primoSet.remove(9);
    // primoSet.remove(0); // test eccezione elementNotFoundException
    cout << "Stampa del primoSet: " << endl;
    cout << primoSet << endl;
    cout << "Da notare, che il valore 9 non compare più nel primoSet" << endl;
    cout << "Se si vuole testare l'eccezione elementNotFoundException, bisogna togliere il commento nel main.cpp a riga 53" << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;

    cout << "Test della funzione add" << endl;
    cout << "Esempio: viene inserito il valore 9 nel primoSet" << endl;
    primoSet.add(9);
    cout << "Stampa del primoSet: " << endl;
    cout << primoSet << endl;
    cout << "Da notare, che il valore 9 di nuovo compare nel primoSet" << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;

    cout << "Test della funzione size" << endl;
    cout << "Esempio: verifica quanti elementi ci sono nel primoSet " << endl;
    cout << "Stampa del primoSet: " << endl;
    cout << primoSet << endl;
    cout << "Nel primoSet ci sono " << primoSet.size()<< " elementi"<< endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;

    cout << "Test della funzione contains" << endl;
    cout << "Esempio: controlla la presenza dell'elemento 6 (che c'è) nel primoSet " << endl;
    cout << "primoSet.contains(6)? -> " << primoSet.contains(6) << endl;
    if (primoSet.contains(6)) {
        cout << "Il primoSet contiene il valore 6." << endl;
    } else {
        cout << "Il primoSet non contiene il valore 6." << endl;
    }
    cout << "Da notare che 0 = false, 1 = true" << std::endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;
    
    cout << "Test della funzione contains" << endl;
    cout << "Esempio: controlla la presenza dell'elemento 5 (che NON c'è) nel primoSet " << endl;
    cout << "primoSet.contains(5)? -> " << primoSet.contains(5) << endl;
    if (primoSet.contains(5)) {
        cout << "Il primoSet contiene il valore 5." << endl;
    } else {
        cout << "Il primoSet non contiene il valore 5." << endl;
    }
    cout << "Da notare che 0 = false, 1 = true" << std::endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;

    cout << "Test dell'operatore di accesso in sola lettura (operator[])" << endl;
    cout << "Esempio: accesso all'elemento in posizione 2 del primoSet " << endl; 
    cout << "Stampa del primoSet: " << endl;
    cout << primoSet << endl;
    const int& elemento = primoSet[2]; 
    cout << "Stampa dell'elemento: " << elemento << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;


    cout << "Test dell'operatore di ugualianza (operator==)" << endl;
    cout << "Esempio: controlla se due set (primoSet e copyPrimoSet) sono uguali " << endl;
    cout << "Stampa del primoSet: " << endl;
    cout << primoSet << endl;
    defaultSet copyPrimoSet = primoSet;
    cout << "Stampa del copyPrimoSet: " << endl;
    cout << copyPrimoSet << endl;
    int result1 = (primoSet == copyPrimoSet) ? 1 : 0;
    cout << "I set sono " << (result1 ? "uguali." : "diversi.") << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;


    cout << "Test dell'operatore di ugualianza (operator==)" << endl;
    cout << "Esempio: controlla se due set (primoSet e secondoSet) sono uguali " << endl;
    cout << "Stampa del primoSet: " << endl;
    cout << primoSet << endl;
    defaultSet secondoSet;
    secondoSet.add(5);
    secondoSet.add(7);
    secondoSet.add(8);
    cout << "Stampa del secondoSet: " << endl;
    cout << secondoSet << endl;
    int result2 = (primoSet == secondoSet) ? 1 : 0;
    cout << "I set sono " << (result2 ? "uguali." : "diversi.") << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;


    cout << "Test dell'operatore di unione (operator+)" << endl;
    cout << "Esempio: si uniscono i due set (primoSet e secondoSet) " << endl;
    cout << "Stampa del primoSet: " << endl;
    cout << primoSet << endl;
    cout << "Stampa del secondoSet: " << endl;
    cout << secondoSet << endl;
    defaultSet unionSet = primoSet + secondoSet;
    cout << "Unione dei due set: " << endl;
    cout << unionSet << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;


    cout << "Test dell'operatore di intersezione (operator-)" << endl;
    cout << "Esempio: si intersecano i due set (primoSet e secondoSet) " << endl;
    cout << "Stampa del primoSet: " << endl;
    cout << primoSet << endl;
    cout << "Stampa del secondoSet: " << endl;
    cout << secondoSet << endl;
    defaultSet intersectionSet = primoSet - secondoSet;
    cout << "Intersezione dei due set: " << endl;
    cout << intersectionSet << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;


    cout << "Test della funzione filter_out con il predicato pari " << endl;
    cout << "Esempio: defaultSet pariSet = filter_out(unionSet, pari) " << endl;
    defaultSet pariSet = filter_out(unionSet, pari);
    cout << "Stampa del unionSet: " << endl;
    cout << unionSet << endl;
    cout << "Filtered Set (numeri pari): " << endl;
    cout << pariSet << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;

    cout << "Test della funzione filter_out con il predicato dispari " << endl;
    cout << "Esempio: defaultSet dispariSet = filter_out(unionSet, dispari) " << endl;
    defaultSet dispariSet = filter_out(unionSet, dispari);
    cout << "Stampa del unionSet: " << endl;
    cout << unionSet << endl;
    cout << "Filtered Set (numeri dispari): " << endl;
    cout << dispariSet << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;

    cout << "Test del costruttore secondario" << endl;
    cout << "Esempio: mySetFromMyArray(myArray, 5) dove '5' è il numero di elementi " << endl;
    int myArray[] = {1, 2, 3, 4, 5};
    Set<int> mySetFromMyArray(myArray, 5); // dove '5' è il numero di elementi
    cout << "Stampa del mySetFromMyArray di 5 elementi: " << endl;
    cout << mySetFromMyArray << endl;
    cout << "Da notare, che la capacità del set viene inizializzata in base alla dimensione"; 
    cout << " dell'array di input, riducendo il bisogno di riallocare e ridimensionare l'array interno"; 
    cout << " man mano che gli elementi vengono aggiunti" << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;


    cout << "Test del costruttore di copia" << endl;
    cout << "Esempio: primoSet2(primoSet) " << endl;
    defaultSet primoSet2(primoSet);
    cout << "Stampa del primoSet: " << endl;
    cout << primoSet << endl;
    cout << "Stampa del primoSet2: " << endl;
    cout << primoSet2 << endl;
    cout << "Da notare, che sono due set identici" << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;
    
    cout << "Test del costruttore Set (conversione: da doubleSet a intSet)" << endl;
    cout << "Esempio: double doubleSet[] = {1.1, 2.2, 3.3, 4.4, 5.5} " << endl;
    double doubleSet[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    Set<int> myIntSetFromDouble(doubleSet, doubleSet + sizeof(doubleSet) / sizeof(doubleSet[0]));
    cout << "Stampa del myIntSetFromDouble: " << endl;
    cout << myIntSetFromDouble << endl;
    cout << "Da notare, che tutti elementi non sono più double, ma sono int" << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;

    cout << "Test del costruttore Set (conversione: da charSet a intSet)" << endl;
    cout << "Esempio: char charSet[] = {'a', 'b', 'c', 'd', 'e'} " << endl;
    char charSet[] = {'a', 'b', 'c', 'd', 'e'};
    Set<int> myIntSetFromChar(charSet, charSet + sizeof(charSet) / sizeof(charSet[0]));
    cout << "Stampa del myIntSetFromChar: " << endl;
    cout << myIntSetFromChar << endl;
    cout << "Da notare, che tutti elementi non sono più char, ma sono int" << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;

    cout << "Test del costruttore Set (conversione: da floatSet a doubleSet)" << endl;
    cout << "Esempio: float floatSet[] = {1.5f, 2.5f, 3.5f, 4.5f, 5.5f} " << endl;
    float floatSet[] = {1.5f, 2.5f, 3.5f, 4.5f, 5.5f};
    Set<double> myDoubleSetFromFloat(floatSet, floatSet + sizeof(floatSet) / sizeof(floatSet[0]));
    cout << "Stampa del myDoubleSetFromFloat: " << endl;
    cout << myDoubleSetFromFloat << endl;
    cout << "Da notare, che tutti elementi non sono più float, ma sono double" << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;


    cout << "Test del costruttore Set (conversione: da doubleVector a intSet)" << endl;
    cout << "Esempio: vector<double> doubleVector = {1.1, 2.2, 3.3, 4.4, 5.5} " << endl;
    vector<double> doubleVector = {1.1, 2.2, 3.3, 4.4, 5.5};
    Set<int> myIntSetFromDoubleVector(doubleVector.begin(), doubleVector.end());
    cout << "Stampa del myIntSetFromDoubleVector: " << endl;
    cout << myIntSetFromDoubleVector << endl;
    cout << "Da notare, che tutti elementi non sono più double, ma sono int" << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;

    cout << "Test del costruttore Set (conversione: da charList a intSet)" << endl;
    cout << "Esempio: list<char> charList = {'a', 'b', 'c', 'd', 'e'} " << endl;
    list<char> charList = {'a', 'b', 'c', 'd', 'e'};
    Set<int> myIntSetFromCharList(charList.begin(), charList.end());
    cout << "Stampa del myIntSetFromCharList: " << endl;
    cout << myIntSetFromCharList << endl;
    cout << "Da notare, che tutti elementi non sono più char, ma sono int" << endl;
    cout << "------------------------------------------------" << endl;
    //cout << endl;

    cout << "Test della funzione save" << endl;
    Set<string> myStringSet;
    myStringSet.add("Ciao");
    myStringSet.add("Mondo");
    myStringSet.add("Test");
    string filename = "test_set_output.txt";
    save(myStringSet, filename);
    cout << "Il set è stato salvato in " << filename << endl;
    cout << "------------------------------------------------" << endl;
}


/**
 * @brief Funzione principale
 *
 * Testa le funzionalità della classe Set e gestisce le eccezioni.
 *
 */
int main() {
    try {
        test_set();
    } catch (const duplicateElementException& e) {
        cerr << "######################################################" << std::endl;
        cerr << "Exception: " << e.what() << endl;
        cerr << "######################################################" << std::endl;
    } catch (const elementNotFoundException& e) {
        cerr << "######################################################" << std::endl;
        cerr << "Exception: " << e.what() << endl;
        cerr << "######################################################" << std::endl;
    }

    return 0;
}