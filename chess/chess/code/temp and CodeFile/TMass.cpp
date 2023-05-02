template<typename T>
class TMass{
private:
    int Count;
    T** Item;
    int (*cmp)(T&, T&);
    bool LinkCheck(T&tmp) {
        for (int i = 0; i < Count; i++) {
            if (Item[i] == &tmp) { return 1; }

        }
        return 0;
    }
public:
    T* getItem(int Index) {
        if ((Index >= 0) && (Index < Count)) {
            return (*Item[Index]);
        }
        else { throw; }//-----------------------------------------------------
    }
    int getCount() { return Count; }
    void setCmp(int (*_cmp)(T&, T&)) {
        cmp = _cmp;
    }
    bool AddItem(T& tmp,bool AddSame = 1) {
        if (cmp == nullptr) { 
            cerr << typeid(*this).name()<<"    (cmp) function == nullptr";
            throw logic_error("(cmp) function == nullptr"); 
        }
        if (AddSame == 0) { if (FaindFirst(tmp)>-1) { return 0; } }
        T** Item_tmp = new T * [Count + 1];
        int i = 0;
        for (i; i < Count; i++) {
            if (cmp(*Item[i],tmp)<0) { Item_tmp[i] = Item[i]; }
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
        if ((Index1 >-1)&&(Index1<Count)&&(Count>0)) {
            T** Item_tmp = new T * [Count -1];
            int i = 0;
            for (i; i < Index1; i++) { Item_tmp[i] = Item[i]; }
            for (i; i < Count; i++) { Item_tmp[i] = Item[i+1]; }
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
    int FaindFirst(T&tmp) {
        int left = 0; 
        int right = Count;
        int search = -1; 
        while (left <= right) 
        {
            int mid = (left + right) / 2; 
            if (cmp(*Item[mid],tmp) == 0) {  
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
                    out->AddItem(*Item[i],1);
                    i++;
                }
                else { break; }
            }
            else { break; }
        }
        i = n-1;
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

    TMass():cmp(nullptr), Count(0), Item(nullptr){}
    TMass(int (*_cmp)(T&, T&)) :cmp(nullptr), Count(0), Item(nullptr) {
        cmp = _cmp;
        
    }
    TMass(TMass&tmp) :cmp(nullptr),Count(tmp.Count), Item(nullptr) {
        Item = new T* [Count];
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
    if (tmp.Count == 0) { os << ORANGE << "\tMass count == 0" <<RESET<< endl; }
    else {
        for (int i = 0; i < tmp.Count; i++) {
            os << "\tIlement [" << i << "] = " << *tmp.Item[i] << endl;
        }
    }
    return os;

}
