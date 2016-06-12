#include "worddatabase.h"

WordDataBase::WordDataBase()
{
    std::ifstream fin[5];
    for(int i=0;i<5;i++)
    {
        fin[i].open(__wordFiles[i]);
        std::string str;
        while (std::getline(fin[i],str))
        {
            WordData *pt = new WordData(str,i+1);
            worddatal.push_back(pt);
        }
    }
    std::ifstream rest(__restWordFile);
    std::string str;
    while(std::getline(rest,str))
    {
        WordData* pt = new WordData(str,-1);
        worddatal.push_back(pt);
    }
}

WordDataBase :: WordDataBase(std::string fileName)
{
    std::ifstream fin(fileName);
    std::string str;int tp,ts;
    while(std::getline(fin,str))
    {
        fin>>tp>>ts;
        WordData *pt = new WordData(str,tp,ts);
        worddatal.push_back(pt);
        std::getline(fin,str);
    }
}

WordDataBase :: ~WordDataBase()
{

}

std::vector <WordData*> WordDataBase::getAll()
{
    std::vector <WordData*> wd(worddatas);
    return wd;
}

WordData* WordDataBase::findWord(std::string str)
{
    for(auto iter : worddatal)
        if (iter->Name()==str)
        {
            return iter;
        }
    return nullptr;
}

bool WordDataBase::empty()
{
    return worddatas.empty();
}

std::vector<WordData*>::iterator WordDataBase::begin()
{
    return worddatas.begin();
}

std::vector<WordData*>::iterator WordDataBase::end()
{
    return worddatas.end();
}

void WordDataBase::save(const std::string fileName)
{
    Logging log("WordDataBase :: save",true);
    log << "INFO saving to file " << fileName << std::endl;
    std::ofstream fout(fileName);
    for(auto iter=worddatal.begin();iter!=worddatal.end();++iter)
    {
        fout<<(*iter)->Name()<<std::endl;
        fout<<(*iter)->Type()<<" "<<(*iter)->Times()<<std::endl;
    }
    fout.close();
}

void WordDataBase::insert(WordData* ud)
{
    worddatal.push_back(ud);
}

WordData* WordDataBase::getRandom()
{
    int i = rand()%size();
    WordData* toReturn = worddatas[i];
    worddatas.erase(worddatas.begin()+i);
    return toReturn;;
}

int WordDataBase :: size()
{
    return worddatas.size();
}

template <typename T>
void WordDataBase :: select(T chooser)
{
    worddatas.clear();
    for(auto iter = worddatal.begin();iter != worddatal.end();++iter)
        if(chooser((*iter)->Type()))
            worddatas.push_back(*iter);
}
template void WordDataBase :: select(_RANGE chooser);
template void WordDataBase :: select(_MOD chooser);
