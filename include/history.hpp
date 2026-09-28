#include <iostream>
#include <utility>
#include <fstream>

template <typename mem>
class queue{
    private:
        struct node{
            double value;
            mem val;
            node* next;
        };
        node* ptr;
        int node_count = 0;

        void prepend(double value, mem val);
    
    public:
        queue();
        queue(const queue<mem>& c); 
        queue(queue<mem>&& c); //TO IMPLEMENT
        ~queue();
        queue<mem>& operator=(queue<mem>& other);
        queue& operator=(queue&& other);
        void add(double n_value, mem n_val);
        void remove_last_node();
        void clear();

        void print() const;
        void save_to_file(const std::string& history_log) const;
        std::pair<double,mem> get_top() const;
};

template <typename mem>
queue<mem>::queue(){
    ptr = nullptr;
}

//copy constructor
template <typename mem>
queue<mem>::queue(const queue<mem>& other){
    //inizializzazione nuovo queue
    this->ptr = nullptr;
    this->node_count = 0;
    
    if(other.ptr == nullptr) return;

    //primo nodo
    node* currOther = other.ptr;
    this->ptr = new node{currOther->value, currOther->val, nullptr};
    this->node_count = 1;

    //resto della lista
    node* pc = this->ptr;
    currOther = currOther->next;

    while(currOther != nullptr){
        pc->next = new node{currOther->value, currOther->val, nullptr};
        
        pc = pc->next;
        currOther = currOther->next;
        this->node_count++;
    }
}

template <typename mem>
queue<mem>::queue(queue<mem>&& c){
    this->ptr = c.ptr;
    this->node_count = c.node_count;

    c.ptr = nullptr;
    c.node_count = 0;
}

template <typename mem>
queue<mem>& queue<mem>::operator=(queue<mem>&& other){
    if(this != &other){
        while(this->ptr != nullptr){
            node* tmp = this->ptr;
            this->ptr = this->ptr->next;
            delete tmp;
        }

        this->ptr = other.ptr;
        this->node_count = other.node_count;

        other.node_count = 0;
        other.ptr = nullptr;
    }

    return *this;
}

template <typename mem>
queue<mem>::~queue(){
    while(ptr != nullptr){
        node* tmp = ptr;
        ptr = ptr->next;
        delete tmp;
    }
}

template <typename mem>
void queue<mem>::prepend(double value, mem val){
    node* tmp = new node{value, val, ptr};
    ptr = tmp;
}

template <typename mem>
void queue<mem>::remove_last_node(){
    if(ptr == nullptr)return;
    if(ptr->next == nullptr){
        delete ptr;
        ptr = nullptr;
        return;
    }
    node* pc = ptr;
    while(pc->next->next != nullptr){
        pc = pc->next;
    }
    delete pc->next;
    pc->next = nullptr;
}

template <typename mem>
void queue<mem>::add(double value, mem val){
    try{
        if(node_count < 10){
            prepend(value, val);
            node_count++;
        }else{
            remove_last_node();
            prepend(value, val);
        }
    }catch(std::bad_alloc& e){
        std::cout<<"[MEM] memory in fully occupied, cannot save history logs"<<std::endl;
    }
}

template <typename mem>
void queue<mem>::print() const{
    if(ptr == nullptr){
        std::cout<<"[MEM] empty"<<std::endl;
    }
    node* curr = ptr;

    while(curr != nullptr){
        std::cout<<"Value: "<<curr->value<<std::endl;
        std::cout<<"type: "<<curr->val<<std::endl;
        curr = curr->next;
    }
    
}

template <typename mem>
void queue<mem>::clear(){
    if(ptr == nullptr){
        std::cout<<"[MEM] history alredy empty"<<std::endl;
    }
    node* curr = ptr;
    while(curr != nullptr){
        node* tmp = curr;
        curr = curr->next;
        delete tmp;
    }
    ptr = nullptr;
    node_count = 0;
}

template <typename mem>
std::pair<double,mem> queue<mem>::get_top() const{
    if(ptr == nullptr){
        std::cout<<"[MEM] history is empty"<<std::endl;
        return std::make_pair(-1.0,mem{});
    }
    return std::make_pair(ptr->value, ptr->val);
}
          
template <typename mem>
void queue<mem>::save_to_file(const std::string& history_log) const{
    std::ofstream file(history_log);

    if(!file.is_open()){
        std::cout<<"[MEM] problem occurred while opening file: "<<history_log<<std::endl;
        throw std::runtime_error("Couldn\' open file " + history_log);
    }

    file << "----CONVERSION HISTORY----"<<std::endl;

    const node* pc = ptr;
    while(pc != nullptr){
        file<<"Value: "<<pc->value<<"- "<<"Unit: "<<pc->val<<std::endl;
        pc = pc->next;
    }

    file.close();
    std::cout<<"Saving successfully occurred"<<std::endl;
}

template <typename mem>
queue<mem>& queue<mem>::operator=(queue<mem>& other) {
    if(this == &other){
        return *this;
    }

    while(this->ptr != nullptr){
        node* tmp = this->ptr;
        this->ptr = this->ptr->next;
        delete tmp;
        this->node_count--;
    }

    if(other.ptr == nullptr){
        return *this;
    }

    //first node
    this->ptr = new node{other.ptr->value, other.ptr->val, nullptr};
    this->node_count++;

    node* pc = this->ptr;
    node* curr = other.ptr->next;

    while(curr != nullptr){
        node* tmp = new node{other.ptr->value, other.ptr->val, nullptr};

        pc->next = tmp;
        curr = curr->next;
        pc = pc->next;
        this->node_count++;
    }
    return *this; 
}
