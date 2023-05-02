
#include <iostream>
using namespace std;
#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED   "\033[31m"
#define GREEN "\033[32m"
#define ORANGE "\033[33m"
#define BLUE "\033[34m"

template<typename T>
class TMass {
private:
    int Count;
    T** Item;
    int (*cmp)(T&, T&);
    bool LinkCheck(T& tmp) {
        for (int i = 0; i < Count; i++) {
            if (Item[i] == &tmp) { return 1; }

        }
        return 0;
    }
public:
    T* getItem(int Index) {
        if ((Index >= 0) && (Index < Count)) {
            return (Item[Index]);
        }
        else { throw; }//-----------------------------------------------------
    }
    int getCount() { return Count; }
    void setCmp(int (*_cmp)(T&, T&)) {
        cmp = _cmp;
    }
    bool AddItem(T& tmp, bool AddSame = 1) {
        if (cmp == nullptr) {
            cerr << typeid(*this).name() << "    (cmp) function == nullptr";
            throw logic_error("(cmp) function == nullptr");
        }
        if (AddSame == 0) { if (FaindFirst(tmp) > -1) { return 0; } }
        T** Item_tmp = new T * [Count + 1];
        int i = 0;
        for (i; i < Count; i++) {
            if (cmp(*Item[i], tmp) < 0) { Item_tmp[i] = Item[i]; }
            else break;
        }
        Item_tmp[i] = &tmp;
        for (i; i < Count; i++) { Item_tmp[i + 1] = Item[i]; }
        delete Item;
        Item = Item_tmp;
        Count++;
        return true;
    }
    void Out() {
        if (Count == 0) { cout << "Mass count == 0" << endl; }
        else {
            for (int i = 0; i < Count; i++) {
                cout << "Ilement [" << i << "] = " << *Item[i] << endl;
            }
        }
    }
    void DeleteAllItemByType(T& tmp) {
        TMass<T>Faind = FaindAll(tmp);
        for (int i = 0; i < Faind.Count; i++) {
            DeleteItemByType(*Faind.Item[i]);
        }
    }
    void DeleteItemByType(T& tmp) {
        int Index = FaindFirst(tmp);
        DeleteItemByIndex(Index);
    }
    void DeleteItemByIndex(int Index1) {
        if ((Index1 > -1) && (Index1 < Count) && (Count > 0)) {
            T** Item_tmp = new T * [Count - 1];
            int i = 0;
            for (i; i < Index1; i++) { Item_tmp[i] = Item[i]; }
            for (i; i < Count; i++) { Item_tmp[i] = Item[i + 1]; }
            delete Item;
            Item = Item_tmp;
            Count--;
        }
        else {
            if (Count == 0) {
                throw logic_error("Count == 0, can no deleted");
            }
            if ((Index1 > -1) && (Index1 < Count)) {
                throw logic_error("No index in mass");
            }
        }
    }
    int FaindFirst(T& tmp) {
        int left = 0;
        int right = Count;
        int search = -1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (cmp(*Item[mid], tmp) == 0) {
                search = mid;
                break;
            }
            if (cmp(*Item[mid], tmp) > 0)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return search;
    }
    TMass<T>& FaindAll(T& tmp) {
        int n = FaindFirst(tmp);
        int i = n;
        TMass<T>* out = new TMass<T>;
        out->cmp = cmp;
        while (1) {
            if ((i >= 0) && (i < Count)) {
                if (cmp(*Item[i], tmp) == 0) {
                    out->AddItem(*Item[i], 1);
                    i++;
                }
                else { break; }
            }
            else { break; }
        }
        i = n - 1;
        while (1) {
            if ((i >= 0) && (i < Count)) {
                if (cmp(*Item[i], tmp) == 0) {
                    out->AddItem(*(Item[i]));
                    i--;
                }
                else { break; }
            }
            else { break; }
        }
        return *out;
    }
    void Dispose() {
        delete Item;
        Item = nullptr;
        Count = 0;
    }

    TMass() :cmp(nullptr), Count(0), Item(nullptr) {}
    TMass(int (*_cmp)(T&, T&)) :cmp(nullptr), Count(0), Item(nullptr) {
        cmp = _cmp;

    }
    TMass(TMass& tmp) :cmp(nullptr), Count(tmp.Count), Item(nullptr) {
        Item = new T * [Count];
        for (int i = 0; i < Count; i++) {
            Item[i] = tmp.Item[i];
        }
        cmp = tmp.cmp;
    }
    ~TMass() {
        Dispose();
    }
    template<typename T>
    friend ostream& operator<<(ostream& os, TMass<T>& tmp);
    TMass& operator+=(const TMass& tmp) {
        for (int i = 0; i < tmp.Count; i++)
            AddItem(tmp.Item[i]);
        return *this;
    }
};
template<typename T>
ostream& operator<<(ostream& os, TMass<T>& tmp) {
    if (tmp.Count == 0) { os << ORANGE << "\tMass count == 0" << RESET << endl; }
    else {
        for (int i = 0; i < tmp.Count; i++) {
            os << "\tIlement [" << i << "] = " << *tmp.Item[i] << endl;
        }
    }
    return os;

}

class TProduct {
    string Name;

    TProduct() :Name("NoN name") {}
    TProduct(TProduct& tmp) {
        Name = tmp.Name;
    }
    ~TProduct() {}
    friend ostream& operator<<(ostream& os, TProduct& tmp);
};
ostream& operator<<(ostream& os, TProduct& tmp) {
    os << "Product Name: " << tmp.Name << endl;
    return os;
}

class TData {
public:
    int id;
    string Caption;
    string Category;
    string ContextInfo;
    TData() :id(-1), Caption("No"), Category("No"), ContextInfo("No") {}
    TData(TData& tmp) {
        id = tmp.id;
        Caption = tmp.Caption;
        Category = tmp.Category;
        ContextInfo = tmp.ContextInfo;
    }
    ~TData() {}
    friend ostream& operator<<(ostream& os, TData& tmp);
    friend bool TDataCMP(TData t, string str);
};
ostream& operator<<(ostream& os, TData& tmp) {
    os << "\tid: " << tmp.id << "\n\tCaption: " << tmp.Caption << "\n\tCategory: " << tmp.Category
        << "\n\tContextInfo: " << tmp.ContextInfo <<"  END"<< endl;
    return os;

}
bool TDataCMP(TData& t, string& str) {
    return ((t.Caption == str)||(t.Caption == "No"));
}
int TDataCMP(TData& tmp1, TData& tmp2) {
    //if (tmp1.Caption == tmp2.Caption) { return 0; }
    return (strcmp(tmp1.Caption.c_str(), tmp2.Caption.c_str()));
}
template<typename T>
int TDataCMP(TData& tmp1, T& tmp2) {
    return ((tmp1.Caption == tmp2) || (tmp1.Caption == "No"));
}

int StrCMP(string& t1, string& t2) {
    return strcmp(t1.c_str(), t2.c_str());
}

//T - TProduct, T1 - TData 
template<typename T >
class TNode {
public:
    TMass<TNode> SonMass;
    TMass<T> ItemMass;
    TData Data;
    TNode() {};
    TNode(int (*CmpTNode)(TNode<T>&, TNode<T>&, int (*CmpDate)(TData&, TData&)), int (*CmpItem)(T&, T&)) {
        SonMass.setCmp(TDataCMP);
        ItemMass.setCmp(CmpItem);
    };
    TNode(TNode& tmp) {
        SonMass = tmp.SonMass;
        ItemMass = tmp.ItemMass;
        Data = tmp.Data;
    };
    ~TNode() {}
    template<typename T>
    friend ostream& operator<<(ostream& os, TNode<T>& tmp);
};
template<typename T>
ostream& operator<<(ostream& os, TNode<T>& tmp) {
    os << "----------------------------------------" << endl;
    os << GREEN << "Son Mass:" << RESET << endl;
    os << tmp.SonMass;
    os << GREEN << "Item Mass:" << RESET << endl;
    os << tmp.ItemMass;
    os << GREEN << "Data:" << RESET << endl;
    os << tmp.Data;
    os << "----------------------------------------" << endl;
    return os;
}
template<typename T>
int TNodeCMP(TNode<T>& tmp1, TNode<T>& tmp2) {
    return TDataCMP(tmp1.Data, tmp2.Data);

}

//T - TProduct, T1 - TData //T2 - List Parametrs
template<typename T, typename T1, typename T2>
class TTree {
public:
    TNode<T> Root;
    int NodeCount;
    int (*CmpNode)(TNode<T>&, TNode<T>&);
    int (*CmpDateWithParm)(T1&, T2&);
    int (*CmpItem)(T&, T&);
    //void AddNode() {}
    TMass<TNode<T>>& FaindAll(TMass<T2>& ParmList, TNode<T>& Item, int Index = 0) {
        TNode<T>* tmpNode;
        T2 tmpParm = *(ParmList.getItem(Index));;
        TMass<TNode<T>>* Out = new TMass<TNode<T>>;
        for (int i = 0; i < Item.SonMass.getCount(); i++)
        {
           
            tmpNode = Item.SonMass.getItem(i);
            cout << "\ti = "<<i<<" TP = "<< tmpParm <<endl;
            if (CmpDateWithParm(tmpNode->Data, tmpParm) == 1) {
                cout<<" Faind node<"<< tmpParm <<">: " << tmpNode<<" INDEX = "<<i << endl;
                    
            }
        }

        TMass<TNode<T>>* Out = new TMass<TNode<T>>;
        //Out->setCmp(CmpNode);
        //Out->AddItem(Root);
        return *Out;

    }
    /*TNode<T,T1>& FaindFirst(TMass<T2>& ListParm, bool (*_cmp)(T1&, T2&)) {}
    bool AddNode(TMass<T2>&ListParm, bool (*_cmp)(T1&, T2&)) {}
    void DeleteNode(){}
    void Out() {}*/

    TTree() :NodeCount(0), CmpNode(nullptr), CmpDateWithParm(nullptr), CmpItem(nullptr) {
        //Root.SonMass.setCmp();

    }
    TTree(
        int (*_CmpNode)(TNode<T>&, TNode<T>&),
        int (*_CmpDateWithParm)(TData&, T2&),
        int (*_CmpItem)(T&, T&)) :NodeCount(0)
    {
        CmpDateWithParm = _CmpDateWithParm;
        CmpNode = _CmpNode;
        CmpItem = _CmpItem;
        Root.SonMass.setCmp(_CmpNode);
        Root.ItemMass.setCmp(_CmpItem);

    }
    TTree(TTree& tmp) :NodeCount(tmp.NodeCount) {
        Root = tmp.Root;
    }
    ~TTree() {}
};



int main()
{

    TNode<TProduct> t, t1;
    TTree<TProduct, TData, string> tree(TNodeCMP, TDataCMP, nullptr);
    //tree.Root.SonMass.setCmp(TNodeCMP);
    //tree.CmpDateWithParm = TDataCMP;
    tree.Root.SonMass.AddItem(t);
    tree.Root.SonMass.AddItem(t1);
    TMass<string> Parms;
    Parms.setCmp(StrCMP);
    string s1 = "No", s2 = "No";
    Parms.AddItem(s1);
    Parms.AddItem(s2);

    cout << "---FAIND---"<<endl;
    cout << tree.FaindAll(Parms, tree.Root);



}

