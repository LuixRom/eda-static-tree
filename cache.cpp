#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int x):key(x), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node* nodo, int x) {
        if(!nodo) return new Node(x);

        if(x < nodo->key)
            nodo->left = insert(nodo->left, x);
        else
            nodo->right = insert(nodo->right, x);

        return nodo;
    }

    bool search(Node* nodo, int x) const {
        if(!nodo) return false;

        if(nodo->key == x) return true;

        if(x < nodo->key)
            return search(nodo->left, x);

        return search(nodo->right, x);
    }

    void liberar(Node* nodo){
        if (!nodo) return;
        liberar(nodo->left);
        liberar(nodo->right);
        delete nodo;
    }

public:
    BST():root(nullptr) {}

    ~BST() {
        liberar(root);
    }

    void build(const vector<int>& a) {
        for(int x : a)
            root = insert(root, x);
    }

    bool search(int x) const {
        return search(root, x);
    }
};

class staticTree{
    private:
        vector<int> nodos;
        vector<int> ordenado;
    public:

        int altura(int l, int r){
            int n = r-l + 1;
            if( n<=0 ) return 0;
            return (int)floor(log2(n)) + 1;
        }

        void top(const vector<int>& a, int l, int r, int h){
            if(l>r || h ==0) return;

            int mid = (l + r) / 2;

            nodos.push_back(a[mid]);
            top(a, l, mid-1, h-1);
            top(a, mid+1, r, h-1);
        }

        void bottom(const vector<int>& a, int l, int r, int h){
            if(l>r) return;

            if(h == 0){
                veb(a,l,r);
                return;
            }

            int mid= (l + r)/ 2;

            bottom(a, l, mid-1, h-1);
            bottom(a, mid+1, r, h-1);
        }

        void veb(const vector<int>& a, int l, int r){
            if(l>r) return;

            int h = altura(l, r);

            if(h<=2){
                top(a,l,r,h);
                return;
            }

            int topAltura = h/2;

            top(a,l,r,topAltura);
            bottom(a,l,r,topAltura);
        }

        void build(const vector<int>& a){
            nodos.clear();
            ordenado = a;
            veb(a, 0, a.size()-1);
        }

        bool search(int x){ return binary_search(ordenado.begin(), ordenado.end(), x);
}

        void print(){
            for(int i: nodos) cout << i << " ";
            cout << endl;
        }
};


int main() {
    const int N = 1000000;
    const int Q = 1000000;
    const int T = 5;

    vector<int> datos(N);

    for (int i = 0; i < N; i++) {
        datos[i] = i;
    }

    srand(time(0));

    double tiempoTotalStatic= 0;
    double tiempoTotalBST= 0;

    for(int experimento= 0; experimento< T; experimento++) {

        vector<int> consultas(Q);

        for(int i = 0; i < Q; i++) {
            consultas[i]= rand() % N;
        }

        staticTree t;
        t.build(datos);

        vector<int> mezcla= datos;

        for(int i= 0;i< N; i++) {
            int j=rand() % N;
            swap(mezcla[i], mezcla[j]);
        }

        BST bst;
        bst.build(mezcla);

        auto inicio= high_resolution_clock::now();

        for(int i=0; i<Q; i++) {
            t.search(consultas[i]);
        }

        auto fin= high_resolution_clock::now();

        double tiempoStatic = duration_cast<milliseconds>(fin - inicio).count();

        inicio= high_resolution_clock::now();

        for(int i=0; i<Q; i++) {
            bst.search(consultas[i]);
        }

        fin= high_resolution_clock::now();

        double tiempoBST = duration_cast<milliseconds>(fin - inicio).count();

        tiempoTotalStatic+= tiempoStatic;
        tiempoTotalBST+= tiempoBST;

        cout<<"Experimento "<< experimento+1<<endl;
        cout<<"Tiempo static tree: "<<tiempoStatic<<" ms"<< endl;
        cout<<"Tiempo BST: "<< tiempoBST<<" ms"<< endl;
    }

    cout<<endl;
    cout<<"Promedio static tree: "<<tiempoTotalStatic/T<<" ms"<< endl;
    cout<<"Promedio BST: "<<tiempoTotalBST/T<<" ms"<<endl;

    return 0;
}
