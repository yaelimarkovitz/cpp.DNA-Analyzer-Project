#include <cstring>
#include <string>
#include <iostream>
#include <exception>
#include <cstdio>
#include "my_exception.h"
#include <vector>
//#include "nucleotide.h"

class DnaSequence{
    
private:
    mutable size_t m_length_dna;
    class Nucleotide{

    public:
        Nucleotide(){}
        Nucleotide(char &c);
        Nucleotide(const Nucleotide &n);
        Nucleotide& operator=(Nucleotide &n);
        bool operator==(const Nucleotide& n)const;
        bool operator!=(const Nucleotide& n)const;
        char getChar()const;

    private:
        void isValid(char &c);
        char m_nuc;
    };
    Nucleotide *m_dna_seq;
    void init( char *seq);
    void copy(const DnaSequence & d);

public:
    DnaSequence(){};
    DnaSequence( char* seq);
    DnaSequence(std::string &seq);
    DnaSequence(const DnaSequence& d);
    const DnaSequence& operator=(const DnaSequence& d);
    const size_t length() const;
    bool compare(const DnaSequence& d) const;
    const Nucleotide& operator[]( size_t index) const ;
    Nucleotide& operator[]( size_t index);
    DnaSequence slice(int start,int end);
    DnaSequence pair() const ;
    int find(const DnaSequence d)const ;
    int count(const DnaSequence d)const ;
    std::vector <int> findAll(const DnaSequence d) const ;
    std::vector <int> findConsensusSequences() const ;
    int input(const char* name_file);
    int output(const char* name_file);
};

inline DnaSequence::DnaSequence( char *seq):m_length_dna(strlen(seq)),m_dna_seq(new Nucleotide[m_length_dna]){
        init(seq);

}
inline DnaSequence::DnaSequence(std::string &seq):m_length_dna(seq.size()),m_dna_seq(new Nucleotide[m_length_dna]) {
        init(const_cast<char*>(seq.c_str()));
}
inline void DnaSequence::copy(const DnaSequence& d ){
    for (unsigned int i = 0; i <m_length_dna ; ++i) {
        Nucleotide n(d[i]);
        m_dna_seq[i]=n;
    }
}
inline DnaSequence::DnaSequence(const DnaSequence &d): m_length_dna(d.length()), m_dna_seq(new Nucleotide [m_length_dna]) {
    copy(d);
}
inline const DnaSequence& DnaSequence:: operator=(const DnaSequence& d){
    Nucleotide * orig = m_dna_seq;
    m_dna_seq = new Nucleotide [d.length()];
    delete [] orig;
    m_length_dna= d.length();
    copy(d);
    return *this;
}
inline std::ostream& operator<<(std::ostream& cout,const DnaSequence &d){
    for (unsigned int i = 0; i < d.length(); ++i) {
        cout<<d[i].getChar()<<"";
    }
    return cout;
}

inline bool operator ==(const DnaSequence &d1,const DnaSequence &d2){
    return (d1.compare(d2));
}
inline bool operator !=(const DnaSequence &d1,const DnaSequence &d2){
    return (d1.compare(d2));
}
inline const size_t DnaSequence:: length() const{
    return m_length_dna;
}
inline DnaSequence::Nucleotide& DnaSequence:: operator[]( size_t index) {
    if (index>m_length_dna )
    {
        throw TooLargIndex();
    }
    return m_dna_seq[index];
}
inline const DnaSequence::Nucleotide& DnaSequence:: operator[]( size_t index) const{
    if (index>m_length_dna )
    {
        throw TooLargIndex();
    }
    return m_dna_seq[index];
}



////////nuclutide class/////////////////////////////
inline char DnaSequence::Nucleotide::getChar() const {
    return m_nuc;
}
inline  bool DnaSequence::Nucleotide::operator==(const Nucleotide &n) const{
    return m_nuc==n.m_nuc;
}
inline  bool DnaSequence::Nucleotide::operator!=(const Nucleotide &n) const{
    return m_nuc!=n.m_nuc;
}
inline DnaSequence::Nucleotide::Nucleotide(char &c):m_nuc(c) {
    isValid(c);
}
inline DnaSequence::Nucleotide::Nucleotide(const Nucleotide &n):m_nuc(n.getChar()) {
}

inline  DnaSequence::Nucleotide& DnaSequence::Nucleotide::operator=(Nucleotide &n) {
    m_nuc=n.getChar();
    return *this;
}
inline void DnaSequence::Nucleotide::isValid(char& c){
    if (c != 'C' && c != 'T' && c != 'G' && c != 'A') {
        throw InVailidNeculeotide();
    }
}
