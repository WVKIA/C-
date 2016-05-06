struct idnode
{
    char id[20];
    unsigned int index;
};
class idhash
{
    public:
        idhash(const char *fname);
        struct idnode *find(const char *id);
        struct idnode *find(const unsigned int index);
        bool add(const char *id,const unsigned int index);
        bool del(const char *id);
        bool del(const unsigned int index);
        bool save(void);
        struct idnode *getNext(const char *id);
        ~idhash();
    private:
        std::map<std::string,struct idnode *>idmap;
        std::string fname;
};
using namespace std;
idhash::idhash(const char *fname)
{
    int n = 0;
    struct idnode *pidnode = NULL;
    this->fname = std::string(fname);
    FILE *fp = fopen(fname,"r");
    if(NULL == fp)
    {
        return ;
    }
    std::pair<std::string,struct idnode *>par;
    while(1)
    {
        pidnode = (struct node *)malloc(sizeof(struct idnode));
        if(NULL == pidnode)
        {
            fclose(fp);
            return ;
        }
        n = fread(pidnode,sizeof(struct idnode),1,fp);
        if(0 == n)
        {
            free(pidnode);
            break;
        }
        par = pair<string,struct idnode*>(string(pidnode->id),pidnode);
        idmap.insert(par);
    }
    fclose(fp);
}
struct idnode *idhash::find(const char *id)
{
    map<string,struct idnode *>::iterator it;
    it = idmap.find(string(id));
    if(it == idmap.end())
    {
        return NULL;
    }
    return it->second;
}
struct idnode *idhash::find(const unsigned int index)
{
    map<string,struct idnode *>::iterator it;
    for(it = idmap.begin(); it != idmap.end(); it++)
    {
        if(it->second->index == index)
        {
            break;
        }
    }
    if(it == idmap.end())
    {
        return NULL;
    }
    return it->second;
}
bool idhash::add(const char *id,const unsigned int index)
{
    struct idnode *p = NULL;
    p = (struct node *)malloc(sizeof(struct idnode ));
    if(NULL == p)
    {
        return ;
    }
    strcpy(p->id,id);
    p->index = index;
    std::pair<std::string,struct idnode *>par(string(id),p);
    idmap.insert(par);
    return true;
}
bool idhash::del(const char *id)
{
    struct idnode * p =NULL;
    map<string,struct idnode *>::iterator it;
    it  = idmap.find(string(id));
    if(it != idmap.end())
    {
         p = it->second;
         idmap.erase(it);
         free(p);
    }
    return true;
}
bool idhash::del(const unsigned int index)
{
    struct idnode *p  =NULL;
    map<string,struct idnode *>::iterator it;
    for(it = idmap.begin(); it != idmap.end(); it++)
    {
        if(index == it->second->index)
        {
            break;
        }
    }
    if(it != idmap.end())
    {
        p = it->second;
        free(p);
        idmap.erase(it);
    }
    return true;
}
struct idnode *idhash::getNext(const char *id)
{
    map<stirng,struct idnode *>::iterator it = idmap.end();
    if(strlen(id) == 0)
    {
        it = idmap.begin();
    }
    else
    {
        it = idmap.find(string(id));
        if(it != idmap.end())
        {
            it++;
        }
    }
    if(it == idmap.end())
    {
        return NULL;
    }
    return it->second;
}
bool idhash::save(void)
{
    struct idnode *p = NULL;
    FILE *fp = fopen(fname.c_str(),"w");
    if(NULL == fp)
    {
        return false;
    }
    map<string,struct idnode *>::iterator it;
    for(it == idmap.begin(); it != idmap.end(); it++)
    {
        p = it->second;
        fwrite(p,sizeof(struct idnode ),1,fp);
    }
    fclose(fp);
}
idhash::~idhash()
{
    struct idnode *p = NULL;
    map<string ,struct idnode *>::iterator it;
    map<string,struct idnode *>::iterator it1;
    for(it = idmap.begin(); it != idmap.end(); it = it1)
    {
        it1 = it;
        it1++;
        p = it->second;
        idmap.erase(it);
        free(p);
    }

}
