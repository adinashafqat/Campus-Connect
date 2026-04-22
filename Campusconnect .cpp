#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//location
struct place {
    int id;
    string name;
    string type;
    int cap;

    place() {
        this->id = 0;
        this->cap = 0;
    }

    place(int id, string name, string type, int cap) {
        this->id = id;
        this->name = name;
        this->type = type;
        this->cap = cap;
    }
};

//graph edge
struct edge {
    int to;
    int dist;
    edge* nxt;

    edge(int to, int dist) {
        this->to = to;
        this->dist = dist;
        this->nxt = nullptr;
    }
};

//graph node
struct gnode {
    place loc;
    edge* edges;

    gnode() {
        this->edges = nullptr;
    }

    gnode(place loc) {
        this->loc = loc;
        this->edges = nullptr;
    }
};

//student
struct pupil {
    int id;
    string name;
    string mail;
    string dept;
    string subs[10];
    int subcnt;
    string likes[10];
    int likecnt;
    string free;
    int yr;

    pupil() {
        this->id = 0;
        this->subcnt = 0;
        this->likecnt = 0;
        this->yr = 1;
    }

    pupil(int id, string name, string mail, string dept, int yr) {
        this->id = id;
        this->name = name;
        this->mail = mail;
        this->dept = dept;
        this->yr = yr;
        this->subcnt = 0;
        this->likecnt = 0;
    }
};

//booking
struct book {
    int bid;
    int pid;
    int lid;
    string day;
    string when;
    int hrs;
    int prio;

    book() {
        this->bid = 0;
        this->pid = 0;
        this->lid = 0;
        this->hrs = 1;
        this->prio = 3;
    }
};

//event
struct event {
    int eid;
    string title;
    string desc;
    string day;
    string when;
    int lid;
    string org;

    event() {
        this->eid = 0;
        this->lid = 0;
    }
};

//tree node
struct tnode {
    event data;
    tnode* left;
    tnode* right;

    tnode(event data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

//log
struct logentry {
    string time;
    string uid;
    string act;
    string detail;

    logentry() {}

    logentry(string uid, string act, string detail) {
        this->uid = uid;
        this->act = act;
        this->detail = detail;
        this->time = "2024-11-15 10:00:00";
    }
};

//action
struct act {
    string type;
    string desc;

    act(string type, string desc) {
        this->type = type;
        this->desc = desc;
    }
};

//hash node for string keys
struct snode {
    string key;
    pupil* val;
    snode* nxt;

    snode(string key, pupil* val) {
        this->key = key;
        this->val = val;
        this->nxt = nullptr;
    }
};

//hash node for int keys
struct inode {
    int key;
    pupil* val;
    inode* nxt;

    inode(int key, pupil* val) {
        this->key = key;
        this->val = val;
        this->nxt = nullptr;
    }
};

//util
int strtoint(string s) {
    int r = 0;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            r = r * 10 + (c - '0');
        }
    }
    return r;
}

void split(string s, char d, string* out, int& cnt) {
    cnt = 0;
    string cur = "";
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (c == d) {
            if (!cur.empty()) {
                out[cnt++] = cur;
                cur = "";
            }
        }
        else {
            cur += c;
        }
    }
    if (!cur.empty()) {
        out[cnt++] = cur;
    }
}

//graph
class graph {
private:
    gnode* list;
    int cnt;
    int cap;
    int nextid;

    void grow(int newcap) {
        gnode* newlist = new gnode[newcap];
        for (int i = 0; i < this->cnt; i++) {
            newlist[i] = this->list[i];
        }
        delete[] this->list;
        this->list = newlist;
        this->cap = newcap;
    }

public:
    graph() {
        this->cnt = 0;
        this->cap = 10;
        this->nextid = 1;
        this->list = new gnode[this->cap];
        this->add(place(0, "Main Gate", "entrance", 0));
        this->add(place(0, "Library", "library", 200));
        this->add(place(0, "Computer Lab", "lab", 50));
        this->add(place(0, "Cafeteria", "cafeteria", 150));
        this->add(place(0, "CS Dept", "dept", 100));
    }

    ~graph() {
        for (int i = 0; i < this->cnt; i++) {
            edge* e = this->list[i].edges;
            while (e) {
                edge* t = e;
                e = e->nxt;
                delete t;
            }
        }
        delete[] this->list;
    }

    int add(place p) {
        if (this->cnt >= this->cap) {
            this->grow(this->cap * 2);
        }
        place np = p;
        if (np.id == 0) {
            np.id = this->nextid++;
        }
        this->list[this->cnt] = gnode(np);
        this->cnt++;
        return np.id;
    }

    void link(int a, int b, int w) {
        if (a < 0 || a >= this->cnt || b < 0 || b >= this->cnt) return;
        edge* e1 = new edge(b, w);
        e1->nxt = this->list[a].edges;
        this->list[a].edges = e1;
        edge* e2 = new edge(a, w);
        e2->nxt = this->list[b].edges;
        this->list[b].edges = e2;
    }

    place* get(int id) {
        for (int i = 0; i < this->cnt; i++) {
            if (this->list[i].loc.id == id) {
                return &this->list[i].loc;
            }
        }
        return nullptr;
    }

    void show() {
        for (int i = 0; i < this->cnt; i++) {
            cout << this->list[i].loc.id << ". " << this->list[i].loc.name
                << " (" << this->list[i].loc.type << ")" << endl;
        }
    }

    int total() {
        return this->cnt;
    }
};

//string hash
class shash {
private:
    snode** table;
    int size;
    int num;

    int hash(string key) {
        unsigned long h = 5381;
        for (int i = 0; i < key.length(); i++) {
            char c = key[i];
            h = ((h << 5) + h) + c;
        }
        return h % this->size;
    }

public:
    shash(int size = 100) {
        this->size = size;
        this->num = 0;
        this->table = new snode * [this->size];
        for (int i = 0; i < this->size; i++) {
            this->table[i] = nullptr;
        }
    }

    ~shash() {
        this->clear();
        delete[] this->table;
    }

    void put(string key, pupil* val) {
        int idx = this->hash(key);
        snode* cur = this->table[idx];
        while (cur) {
            if (cur->key == key) {
                cur->val = val;
                return;
            }
            cur = cur->nxt;
        }
        snode* nn = new snode(key, val);
        nn->nxt = this->table[idx];
        this->table[idx] = nn;
        this->num++;
    }

    bool get(string key, pupil*& out) {
        int idx = this->hash(key);
        snode* cur = this->table[idx];
        while (cur) {
            if (cur->key == key) {
                out = cur->val;
                return true;
            }
            cur = cur->nxt;
        }
        return false;
    }

    bool has(string key) {
        pupil* t;
        return this->get(key, t);
    }

    void clear() {
        for (int i = 0; i < this->size; i++) {
            snode* cur = this->table[i];
            while (cur) {
                snode* t = cur;
                cur = cur->nxt;
                delete t;
            }
            this->table[i] = nullptr;
        }
        this->num = 0;
    }

    int total() {
        return this->num;
    }

    void all(string* keys, int& cnt) {
        cnt = 0;
        for (int i = 0; i < this->size; i++) {
            snode* cur = this->table[i];
            while (cur) {
                keys[cnt++] = cur->key;
                cur = cur->nxt;
            }
        }
    }
};

//int hash
class ihash {
private:
    inode** table;
    int size;
    int num;

    int hash(int key) {
        return key % this->size;
    }

public:
    ihash(int size = 100) {
        this->size = size;
        this->num = 0;
        this->table = new inode * [this->size];
        for (int i = 0; i < this->size; i++) {
            this->table[i] = nullptr;
        }
    }

    ~ihash() {
        this->clear();
        delete[] this->table;
    }

    void put(int key, pupil* val) {
        int idx = this->hash(key);
        inode* cur = this->table[idx];
        while (cur) {
            if (cur->key == key) {
                cur->val = val;
                return;
            }
            cur = cur->nxt;
        }
        inode* nn = new inode(key, val);
        nn->nxt = this->table[idx];
        this->table[idx] = nn;
        this->num++;
    }

    bool get(int key, pupil*& out) {
        int idx = this->hash(key);
        inode* cur = this->table[idx];
        while (cur) {
            if (cur->key == key) {
                out = cur->val;
                return true;
            }
            cur = cur->nxt;
        }
        return false;
    }

    bool has(int key) {
        pupil* t;
        return this->get(key, t);
    }

    void clear() {
        for (int i = 0; i < this->size; i++) {
            inode* cur = this->table[i];
            while (cur) {
                inode* t = cur;
                cur = cur->nxt;
                delete t;
            }
            this->table[i] = nullptr;
        }
        this->num = 0;
    }

    int total() {
        return this->num;
    }
};

//heap for bookings
class heap {
private:
    book* arr;
    int cap;
    int sz;

    void grow(int newcap) {
        book* na = new book[newcap];
        for (int i = 0; i < this->sz; i++) {
            na[i] = this->arr[i];
        }
        delete[] this->arr;
        this->arr = na;
        this->cap = newcap;
    }

    void up(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (this->arr[i].prio < this->arr[p].prio) {
                book t = this->arr[i];
                this->arr[i] = this->arr[p];
                this->arr[p] = t;
                i = p;
            }
            else {
                break;
            }
        }
    }

    void down(int i) {
        int small = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < this->sz && this->arr[l].prio < this->arr[small].prio) {
            small = l;
        }
        if (r < this->sz && this->arr[r].prio < this->arr[small].prio) {
            small = r;
        }
        if (small != i) {
            book t = this->arr[i];
            this->arr[i] = this->arr[small];
            this->arr[small] = t;
            this->down(small);
        }
    }

public:
    heap() {
        this->cap = 10;
        this->sz = 0;
        this->arr = new book[this->cap];
    }

    ~heap() {
        delete[] this->arr;
    }

    void push(book b) {
        if (this->sz >= this->cap) {
            this->grow(this->cap * 2);
        }
        this->arr[this->sz] = b;
        this->up(this->sz);
        this->sz++;
    }

    void pop() {
        if (this->sz > 1) {
            this->arr[0] = this->arr[this->sz - 1];
            this->sz--;
            this->down(0);
        }
        else {
            this->sz = 0;
        }
    }

    book& top() {
        return this->arr[0];
    }

    bool empty() {
        return this->sz == 0;
    }

    int total() {
        return this->sz;
    }

    void clear() {
        this->sz = 0;
    }

    void all(book* out, int& cnt) {
        cnt = 0;
        for (int i = 0; i < this->sz; i++) {
            out[cnt++] = this->arr[i];
        }
    }
};

//event tree
class etree {
private:
    tnode* root;
    int nextid;

    tnode* ins(tnode* n, event e) {
        if (!n) return new tnode(e);
        if (e.day < n->data.day) {
            n->left = this->ins(n->left, e);
        }
        else if (e.day > n->data.day) {
            n->right = this->ins(n->right, e);
        }
        else {
            if (e.when < n->data.when) {
                n->left = this->ins(n->left, e);
            }
            else {
                n->right = this->ins(n->right, e);
            }
        }
        return n;
    }

    void inord(tnode* n, event* out, int& idx, int max) {
        if (!n || idx >= max) return;
        this->inord(n->left, out, idx, max);
        if (idx < max) {
            out[idx++] = n->data;
        }
        this->inord(n->right, out, idx, max);
    }

    void del(tnode* n) {
        if (!n) return;
        this->del(n->left);
        this->del(n->right);
        delete n;
    }

public:
    etree() {
        this->root = nullptr;
        this->nextid = 1;
    }

    ~etree() {
        this->del(this->root);
    }

    void add(event e) {
        event ne = e;
        if (ne.eid == 0) {
            ne.eid = this->nextid++;
        }
        this->root = this->ins(this->root, ne);
    }

    int all(event* out, int max) {
        int idx = 0;
        this->inord(this->root, out, idx, max);
        return idx;
    }

    bool empty() {
        return this->root == nullptr;
    }

    int total() {
        event t[1000];
        return this->all(t, 1000);
    }
};

//stack for undo/redo
class astack {
private:
    struct sn {
        act data;
        sn* nxt;
        sn(act data) {
            this->data = data;
            this->nxt = nullptr;
        }
    };
    sn* topn;
    int sz;

public:
    astack() {
        this->topn = nullptr;
        this->sz = 0;
    }

    ~astack() {
        while (!this->empty()) {
            this->pop();
        }
    }

    void push(act a) {
        sn* nn = new sn(a);
        nn->nxt = this->topn;
        this->topn = nn;
        this->sz++;
    }

    void pop() {
        if (this->topn) {
            sn* t = this->topn;
            this->topn = this->topn->nxt;
            delete t;
            this->sz--;
        }
    }

    act& top() {
        return this->topn->data;
    }

    bool empty() {
        return this->topn == nullptr;
    }

    int total() {
        return this->sz;
    }

    void clear() {
        while (!this->empty()) {
            this->pop();
        }
    }
};

//global
shash mailmap(100);
ihash idmap(100);
graph g;
heap bookq;
etree evtree;
astack undostack;
astack redostack;
logentry logs[1000];
int logcnt = 0;
pupil* user = nullptr;
bool admin = false;
int nextbid = 1;

//file
void logact(string act, string detail) {
    string uid = user ? to_string(user->id) : "system";
    if (logcnt < 1000) {
        logs[logcnt++] = logentry(uid, act, detail);
    }
    ofstream f("log.txt", ios::app);
    if (f.is_open()) {
        f << "2024-11-15 10:00:00 | User: " << uid
            << " | Act: " << act
            << " | Detail: " << detail << endl;
        f.close();
    }
}

void savepupils() {
    ofstream f("pupils.txt");
    if (!f.is_open()) return;
    string keys[1000];
    int kcnt = 0;
    mailmap.all(keys, kcnt);
    for (int i = 0; i < kcnt; i++) {
        pupil* p;
        if (mailmap.get(keys[i], p)) {
            f << p->id << ","
                << p->name << ","
                << p->mail << ","
                << p->dept << ","
                << p->yr << ","
                << p->free << ",";
            f << p->subcnt << ",";
            for (int j = 0; j < p->subcnt; j++) {
                f << p->subs[j];
                if (j < p->subcnt - 1) f << ";";
            }
            f << ",";
            f << p->likecnt << ",";
            for (int j = 0; j < p->likecnt; j++) {
                f << p->likes[j];
                if (j < p->likecnt - 1) f << ";";
            }
            f << endl;
        }
    }
    f.close();
}

void loadpupils() {
    ifstream f("pupils.txt");
    if (!f.is_open()) return;
    string line;
    while (getline(f, line)) {
        string parts[20];
        int pcnt = 0;
        split(line, ',', parts, pcnt);
        if (pcnt >= 6) {
            pupil* p = new pupil();
            p->id = strtoint(parts[0]);
            p->name = parts[1];
            p->mail = parts[2];
            p->dept = parts[3];
            p->yr = strtoint(parts[4]);
            p->free = parts[5];
            if (pcnt > 6) {
                int subcnt = strtoint(parts[6]);
                if (pcnt > 7) {
                    string subs[20];
                    int scnt = 0;
                    split(parts[7], ';', subs, scnt);
                    for (int j = 0; j < scnt && j < subcnt; j++) {
                        p->subs[p->subcnt++] = subs[j];
                    }
                }
            }
            if (pcnt > 8) {
                int likecnt = strtoint(parts[8]);
                if (pcnt > 9) {
                    string likes[20];
                    int lcnt = 0;
                    split(parts[9], ';', likes, lcnt);
                    for (int j = 0; j < lcnt && j < likecnt; j++) {
                        p->likes[p->likecnt++] = likes[j];
                    }
                }
            }
            mailmap.put(p->mail, p);
            idmap.put(p->id, p);
        }
    }
    f.close();
}

void savebooks() {
    ofstream f("books.txt");
    if (!f.is_open()) return;
    book all[1000];
    int cnt = 0;
    bookq.all(all, cnt);
    f << nextbid << endl;
    for (int i = 0; i < cnt; i++) {
        f << all[i].bid << ","
            << all[i].pid << ","
            << all[i].lid << ","
            << all[i].day << ","
            << all[i].when << ","
            << all[i].hrs << ","
            << all[i].prio << endl;
    }
    f.close();
}

void loadbooks() {
    ifstream f("books.txt");
    if (!f.is_open()) return;
    string line;
    getline(f, line);
    nextbid = strtoint(line);
    while (getline(f, line)) {
        string parts[10];
        int pcnt = 0;
        split(line, ',', parts, pcnt);
        if (pcnt >= 7) {
            book b;
            b.bid = strtoint(parts[0]);
            b.pid = strtoint(parts[1]);
            b.lid = strtoint(parts[2]);
            b.day = parts[3];
            b.when = parts[4];
            b.hrs = strtoint(parts[5]);
            b.prio = strtoint(parts[6]);
            bookq.push(b);
        }
    }
    f.close();
}

void saveevents() {
    ofstream f("events.txt");
    if (!f.is_open()) return;
    event all[1000];
    int cnt = evtree.all(all, 1000);
    for (int i = 0; i < cnt; i++) {
        f << all[i].eid << ","
            << all[i].title << ","
            << all[i].desc << ","
            << all[i].day << ","
            << all[i].when << ","
            << all[i].lid << ","
            << all[i].org << endl;
    }
    f.close();
}

void loadevents() {
    ifstream f("events.txt");
    if (!f.is_open()) return;
    string line;
    while (getline(f, line)) {
        string parts[10];
        int pcnt = 0;
        split(line, ',', parts, pcnt);
        if (pcnt >= 7) {
            event e;
            e.eid = strtoint(parts[0]);
            e.title = parts[1];
            e.desc = parts[2];
            e.day = parts[3];
            e.when = parts[4];
            e.lid = strtoint(parts[5]);
            e.org = parts[6];
            evtree.add(e);
        }
    }
    f.close();
}

void loadall() {
    loadpupils();
    loadbooks();
    loadevents();
    logact("start", "loaded");
}

void saveall() {
    savepupils();
    savebooks();
    saveevents();
    logact("exit", "saved");
}

//ui
void clearscr() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void wait() {
    cout << "\npress enter...";
    cin.ignore();
    cin.get();
}

void menu() {
    clearscr();
    cout << "CAMPUS SYSTEM\n";
    cout << "1. login student\n";
    cout << "2. login admin\n";
    cout << "3. new student\n";
    cout << "4. view map\n";
    cout << "5. book room\n";
    cout << "6. find partners\n";
    cout << "7. view events\n";
    cout << "8. my bookings\n";
    cout << "9. stats\n";
    cout << "10. exit\n";
    cout << "choice: ";
}

void login() {
    clearscr();
    cout << "STUDENT LOGIN\n";
    string mail;
    cout << "mail: ";
    cin >> mail;
    pupil* p;
    if (mailmap.get(mail, p)) {
        user = p;
        admin = false;
        cout << "\nwelcome " << p->name << endl;
        logact("login", "student: " + mail);
        wait();
    }
    else {
        cout << "\nnot found\n";
        wait();
    }
}

void adminlogin() {
    clearscr();
    cout << "ADMIN LOGIN\n";
    string name, pass;
    cout << "name: ";
    cin >> name;
    cout << "pass: ";
    cin >> pass;
    if (name == "admin" && pass == "admin123") {
        admin = true;
        user = nullptr;
        cout << "\nadmin ok\n";
        logact("admin", "login");
        wait();
    }
    else {
        cout << "\nbad\n";
        wait();
    }
}

void reg() {
    clearscr();
    cout << "NEW STUDENT\n";
    pupil* p = new pupil();
    cout << "id: ";
    string sid;
    cin >> sid;
    p->id = strtoint(sid);
    if (idmap.has(p->id)) {
        cout << "\nid exists\n";
        delete p;
        wait();
        return;
    }
    cin.ignore();
    cout << "name: ";
    getline(cin, p->name);
    cout << "mail: ";
    getline(cin, p->mail);
    cout << "dept: ";
    getline(cin, p->dept);
    cout << "year: ";
    string y;
    getline(cin, y);
    p->yr = strtoint(y);
    cout << "free time: ";
    getline(cin, p->free);
    p->subs[p->subcnt++] = "data struct";
    p->subs[p->subcnt++] = "algo";
    p->subs[p->subcnt++] = "db";
    p->likes[p->likecnt++] = "code";
    p->likes[p->likecnt++] = "study";
    p->likes[p->likecnt++] = "group";
    mailmap.put(p->mail, p);
    idmap.put(p->id, p);
    cout << "\nregistered\n";
    logact("reg", "new: " + p->mail);
    wait();
}

void nav() {
    clearscr();
    cout << "CAMPUS MAP\n";
    g.show();
    cout << "\n(demo)\n";
    logact("map", "viewed");
    wait();
}

void bookroom() {
    if (!user && !admin) {
        cout << "login first\n";
        wait();
        return;
    }
    clearscr();
    cout << "BOOK ROOM\n";
    g.show();
    book b;
    b.bid = nextbid++;
    b.pid = user ? user->id : 0;
    cout << "\nlocation id: ";
    string ls;
    cin >> ls;
    b.lid = strtoint(ls);
    cout << "date: ";
    cin >> b.day;
    cout << "time: ";
    cin >> b.when;
    cout << "hours: ";
    string hs;
    cin >> hs;
    b.hrs = strtoint(hs);
    cout << "prio (1-5): ";
    string ps;
    cin >> ps;
    b.prio = strtoint(ps);
    bookq.push(b);
    cout << "\nbooked id: " << b.bid << endl;
    logact("book", "by " + to_string(b.pid));
    act a("book", "room at " + to_string(b.lid));
    undostack.push(a);
    wait();
}

void findpart() {
    if (!user) {
        cout << "login first\n";
        wait();
        return;
    }
    clearscr();
    cout << "FIND PARTNERS\n";
    cout << "for: " << user->name << endl;
    string keys[1000];
    int kcnt = 0;
    mailmap.all(keys, kcnt);
    struct match {
        int score;
        pupil* p;
    } matches[1000];
    int mcnt = 0;
    for (int i = 0; i < kcnt; i++) {
        pupil* p;
        if (mailmap.get(keys[i], p)) {
            if (p->id == user->id) continue;
            int sc = 0;
            if (p->dept == user->dept) sc += 30;
            if (p->yr == user->yr) sc += 20;
            if (p->free == user->free) sc += 25;
            for (int j = 0; j < user->subcnt; j++) {
                for (int k = 0; k < p->subcnt; k++) {
                    if (user->subs[j] == p->subs[k]) {
                        sc += 10;
                        break;
                    }
                }
            }
            for (int j = 0; j < user->likecnt; j++) {
                for (int k = 0; k < p->likecnt; k++) {
                    if (user->likes[j] == p->likes[k]) {
                        sc += 5;
                        break;
                    }
                }
            }
            if (sc > 0) {
                matches[mcnt].score = sc;
                matches[mcnt].p = p;
                mcnt++;
            }
        }
    }
    for (int i = 0; i < mcnt; i++) {
        for (int j = i + 1; j < mcnt; j++) {
            if (matches[j].score > matches[i].score) {
                match t = matches[i];
                matches[i] = matches[j];
                matches[j] = t;
            }
        }
    }
    cout << "\n=== top matches ===\n";
    int show = mcnt < 5 ? mcnt : 5;
    for (int i = 0; i < show; i++) {
        cout << "\n" << (i + 1) << ". " << matches[i].p->name << endl;
        cout << "   score: " << matches[i].score << "%" << endl;
        cout << "   dept: " << matches[i].p->dept << endl;
        cout << "   year: " << matches[i].p->yr << endl;
        cout << "   free: " << matches[i].p->free << endl;
    }
    if (show == 0) {
        cout << "\nnone\n";
    }
    logact("partner", "search by " + to_string(user->id));
    wait();
}

void viewevents() {
    clearscr();
    cout << "EVENTS\n";
    event all[1000];
    int cnt = evtree.all(all, 1000);
    if (cnt == 0) {
        cout << "none\n";
    }
    else {
        for (int i = 0; i < cnt; i++) {
            cout << "\nevent #" << all[i].eid << endl;
            cout << "title: " << all[i].title << endl;
            cout << "date: " << all[i].day << endl;
            cout << "time: " << all[i].when << endl;
            cout << "org: " << all[i].org << endl;
            cout << "desc: " << all[i].desc << endl;
            cout << "---" << endl;
        }
    }
    if (admin) {
        cout << "\n1. add event\n";
        cout << "2. back\n";
        cout << "choice: ";
        string cs;
        cin >> cs;
        int c = strtoint(cs);
        if (c == 1) {
            event e;
            e.eid = 0;
            cin.ignore();
            cout << "title: ";
            getline(cin, e.title);
            cout << "desc: ";
            getline(cin, e.desc);
            cout << "date: ";
            getline(cin, e.day);
            cout << "time: ";
            getline(cin, e.when);
            cout << "loc id: ";
            string ls;
            getline(cin, ls);
            e.lid = strtoint(ls);
            cout << "org: ";
            getline(cin, e.org);
            evtree.add(e);
            cout << "added\n";
            logact("addevent", e.title);
        }
    }
    wait();
}

void mybooks() {
    if (!user && !admin) {
        cout << "login first\n";
        wait();
        return;
    }
    clearscr();
    cout << "MY BOOKINGS\n";
    book all[1000];
    int cnt = 0;
    bookq.all(all, cnt);
    bool found = false;
    for (int i = 0; i < cnt; i++) {
        if (admin || all[i].pid == user->id) {
            found = true;
            cout << "\nid: " << all[i].bid << endl;
            cout << "loc: " << all[i].lid << endl;
            cout << "date: " << all[i].day << endl;
            cout << "time: " << all[i].when << endl;
            cout << "hours: " << all[i].hrs << endl;
            cout << "prio: " << all[i].prio << endl;
            cout << "pending" << endl;
            cout << "---" << endl;
        }
    }
    if (!found) {
        cout << "none\n";
    }
    wait();
}

void stats() {
    clearscr();
    cout << "STATS\n";
    cout << "\nSTUDENTS\n";
    cout << "total: " << mailmap.total() << endl;
    string depts[100][2];
    int dcnt = 0;
    string keys[1000];
    int kcnt = 0;
    mailmap.all(keys, kcnt);
    for (int i = 0; i < kcnt; i++) {
        pupil* p;
        if (mailmap.get(keys[i], p)) {
            bool got = false;
            for (int j = 0; j < dcnt; j++) {
                if (depts[j][0] == p->dept) {
                    int n = strtoint(depts[j][1]);
                    n++;
                    depts[j][1] = to_string(n);
                    got = true;
                    break;
                }
            }
            if (!got) {
                depts[dcnt][0] = p->dept;
                depts[dcnt][1] = "1";
                dcnt++;
            }
        }
    }
    cout << "\ndepts:\n";
    for (int i = 0; i < dcnt; i++) {
        cout << "  " << depts[i][0] << ": " << depts[i][1] << endl;
    }
    cout << "\nBOOKINGS\n";
    cout << "total: " << bookq.total() << endl;
    book all[1000];
    int cnt = 0;
    bookq.all(all, cnt);
    int priocnt[6] = { 0 };
    for (int i = 0; i < cnt; i++) {
        if (all[i].prio >= 1 && all[i].prio <= 5) {
            priocnt[all[i].prio]++;
        }
    }
    cout << "\nprio:\n";
    for (int i = 1; i <= 5; i++) {
        cout << "  prio " << i << ": " << priocnt[i] << endl;
    }
    cout << "\nEVENTS\n";
    cout << "total: " << evtree.total() << endl;
    event evs[1000];
    int ecnt = evtree.all(evs, 1000);
    if (ecnt > 0) {
        cout << "next:\n";
        int show = ecnt < 3 ? ecnt : 3;
        for (int i = 0; i < show; i++) {
            cout << "  " << evs[i].title << " on " << evs[i].day << endl;
        }
    }
    cout << "\nCAMPUS\n";
    cout << "locs: " << g.total() << endl;
    logact("stats", "viewed");
    wait();
}

int main() {
    cout << "loading...\n";
    loadall();
    string cs;
    int c;
    do {
        menu();
        cin >> cs;
        c = strtoint(cs);
        switch (c) {
        case 1: login(); break;
        case 2: adminlogin(); break;
        case 3: reg(); break;
        case 4: nav(); break;
        case 5: bookroom(); break;
        case 6: findpart(); break;
        case 7: viewevents(); break;
        case 8: mybooks(); break;
        case 9: stats(); break;
        case 10:
            cout << "saving...\n";
            saveall();
            cout << "bye\n";
            break;
        default:
            cout << "bad\n";
            wait();
        }
    } while (c != 10);
    cout << "\npress enter to exit...";
    cin.ignore();
    cin.get();
    return 0;
}
```