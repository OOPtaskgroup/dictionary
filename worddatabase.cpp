#include"worddatabase.h"

WordDataBase::WordDataBase()
{
    std::ifstream fin[5];
    fin[0].open("Easy.txt");fin[1].open("Normal.txt");fin[2].open("Hard.txt");fin[3].open("Lunatic.txt");fin[4].open("Extra.txt");
    for(int i=0;i<5;i++)
    {
        std::string str;
        while (std::getline(fin[i],str))
        {
            WordData *pt = new WordData(str,i+1);
            worddatal.push_back(pt);
        }
    }
    std::ifstream rest("Rest.txt");
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

WordData* WordDataBase::FindWord(std::string str)
{
    for(std::vector<WordData*>::iterator iter=worddatal.begin();iter!=worddatal.end();++iter)
    {
        if ((*iter)->Name()==str)
        {
            return *iter;
        }
    }
    return nullptr;
}

bool WordDataBase::isEmpty()
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

void WordDataBase::reWrite(const std::string& fileName)
{
    std::ofstream fout(fileName);
    for(std::vector<WordData*>::iterator iter=worddatal.begin();iter!=worddatal.end();++iter)
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

WordData* WordDataBase::getrandom()
{
    int i = rand()%size();
    WordData* toReturn = worddatas[i];
    worddatas.erase(worddatas.begin()+i);
    return toReturn;;
}
/*
void WordDataBase::select(int typel, int typer)
{

    worddatas.clear();
    for(std::vector<WordData*>::iterator iter=worddatal.begin();iter!=worddatal.end();++iter)
    {
        if((*iter)->Type() >= typel && (*iter)->Type() <= typer)
        {
            worddatas.push_back(*iter);
        }
    }

    select(_RANGE(typel,typer));
}

void WordDataBase :: select(int type)
{
    select(type,type);
}
*/
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
