#ifndef NO_HPP
#define NO_HPP

class No{
    private:
        int id;
        char tipo;
    public:
        No();
        No(int id, char tipo);
        
        int get_id() const;
        char get_tipo() const;

        void set_id(int id);
        void set_tipo(char tipo);

};

#endif