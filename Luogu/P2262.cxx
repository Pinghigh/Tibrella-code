#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdint>
#include <chrono>
#include <random>
#include <set>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;
using std::min;
using std::max;
using std::vector;
using std::string;
using std::getline;
using std::set;

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

enum __states {
    NONE,
    // FILE-ID
    ISFILE,
    ISFOLDER,
    // FILE-STATE
    NORMAL,
    UPLOAD,
    // USER-ID
    DOWNLOADER,
    UPLOADER,
    GUEST,
    // USER-STATE
    SCAN,
    DOWNLOADING,
    UPLOADING,
    // FOLDER-STATE
    IDLE,
    WORKING
};

struct folder;
struct file;
struct user;
struct task;
struct server;

struct file {
    string name;    // 名称
    folder* parent; // 父文件夹
    u32 size;       // 大小
    u32 state;      // 状态

    file(const string& Name, folder* Parent, u32 Size, u32 State):name(Name),parent(Parent),size(Size),state(State) {}
};

struct folder {
    vector<file*> son_file;         // 子文件
    vector<folder*> son_folder;     // 子文件夹
    folder* parent;                 // 父文件夹
    u32 size;                       // 大小
    string name;                    // 名称
    u32 state;                      // 状态

    folder* get_parent() {
        return parent;
    }
    folder* get_son_folder(const string& dir) {         // 找名称为 dir 的文件夹
        for (auto& folder : son_folder) {
            if (folder->name == dir) return folder;
        }
        return nullptr;
    }
    file* get_son_file(const string& filename) {
        for (auto& file : son_file) 
            if (file->name == filename) return file;
        return nullptr;
    }

    void add_file(file* file) {
        son_file.emplace_back(file);
        folder* cur = this;
        do cur->size += file->size, cur = cur->parent; while (cur);
    }

    void add_folder(folder* folder) {
        son_folder.emplace_back(folder);
    }

    void update_state() { // 更新文件夹状态（只考虑文件）
        for (const auto& file : son_file) if (file->state != NORMAL) return state = WORKING, void();
        state = IDLE;
    }
    bool check_folder() { // 递归检查文件夹状态
        // cout << name << ' ' << (state == IDLE) << '\n';
        for (const auto& folder : son_folder) if (!folder->check_folder()) return false;
        return state == IDLE;
    }
    void update_size() {
        size = 0;
        for (const auto& file : son_file) size += file->size;
        for (const auto& folder : son_folder) folder->update_size(), size += folder->size;
    }

    folder(const string& name, folder* parent ,const u32& state): name(name), parent(parent), state(state) {}
} *root;

struct user {
    u32 identity;
    u32 state;
    string name;
    folder* position;
    task* current_task;

    user(const string& NAME, const u32 &ID, const u32 &STATE):name(NAME), identity(ID), state(STATE), position(root) {}
};

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count() ^ 0x1f4a583e44c73);

struct task {
    user* owner;

    u32 last_update;

    u32 size;
    u32 datatype;
    file* datafile;
    folder* datafolder;
    
    u32 uuid;

    bool expire;

    task(user* owner, file* data, u32 start):owner(owner), datatype(ISFILE), size(data->size), datafile(data), expire(false), last_update(start), uuid(rng()) {}
    task(user* owner, folder* data, u32 start):owner(owner), datatype(ISFOLDER), size(data->size), datafolder(data), expire(false), last_update(start), uuid(rng()) {}
};

set<task*> task_list;

u32 max_user_num;       // 服务器承受的最大用户数量
u32 max_server_flux;    // 服务器最大流量
u32 max_user_flux;      // 单个用户最大流量
u32 cur_user_flux;      // 目前单个用户流量
u32 cur_clock;          // 当前服务器时间（秒）

vector<user*> user_table;
#define cur_user_num (user_table.size())
#define cur_working_user_num (task_list.size()) // 当前的单个用户最大流量受上传/下载用户数量影响

static void update_flux() {
    u32 cur_user_max_flux = 0;
    if (cur_working_user_num) cur_user_max_flux = max_server_flux / cur_working_user_num;
    cur_user_flux = min(max_user_flux, cur_user_max_flux);
}

void update_tasks() {
    for (auto it = task_list.begin(); task_list.size() && it != task_list.end(); ++ it) {
        auto& task = *it;
        if (task->expire) {
            delete task;
            it = task_list.erase(it);
        }
        else 
            if (task->size <= cur_user_flux) {
                task->owner->state = SCAN;
                if (task->datatype == ISFILE) {
                    task->datafile->state = NORMAL;
                    task->datafile->parent->update_state();
                } else {
                    task->datafolder->update_state();
                    task->datafolder->parent->update_state();
                }
                task->owner->state = SCAN;
                task->owner->current_task = nullptr;
                delete task;
                it = task_list.erase(it); // 减少元素并不会导致 rehash
                if (it == task_list.end()) return;
            } else (task->size -= cur_user_flux);
                // cout << cur_clock << ' ' << task->size << ' ' << cur_user_flux << '\n';
    }
}

user* find_user(const string& name) {
    for (auto& user : user_table)
        if (user->name == name) return user;
    return nullptr;
}

bool create_user(const string& name, const u32& type) {
    if (find_user(name) || cur_user_num < max_user_num) return false;
    else {
        user_table.emplace_back(new user(
            name, 
            [&]()->u32 {switch(type) {case(1):return UPLOADER; case(2): return DOWNLOADER; default: return GUEST;}}(),
            SCAN
        ));
        return true;
    }
}

bool delete_user(const string& name) {
    //!TODO LOGOUT makes task expired
    for (auto it = user_table.begin(); it != user_table.end(); ++ it) 
        if (it[0]->name == name) {
            if (it[0]->state != SCAN)
                it[0]->current_task->expire = true;
            delete *it;
            return user_table.erase(it), true;
        }
    return false;
}

void init_file_system() {
    string name;
    u32 size;
    folder* position = root;
    while (position) {
        cin >> name;
        if (name == "-") position = position->parent;
        else {
            cin >> size;
            if (size)
                position->add_file(new file(name, position, size, NORMAL));
            else {
                folder* nxtpos = new folder(name, position, IDLE);
                position->add_folder(nxtpos);
                position = nxtpos;
            }
        }
    }
    root->update_size();
}

bool upload_file(user* user, file* file) {
    if (user->identity != UPLOADER || user->state != SCAN) return false;
    if (!file) return false;
    user->state = UPLOADING;
    user->position->son_file.emplace_back(file);
    task_list.emplace(user->current_task = new task(user, file, cur_clock));
    user->position->update_state();
    return true;
}

bool download_file(user* user, file* file) {
    if (user->identity != DOWNLOADER || user->state != SCAN || file->state == UPLOAD) return false;
    if (!file) return false;
    user->state = DOWNLOADING;
    task_list.emplace(user->current_task = new task(user, file, cur_clock));
    return true;
}

bool upload_folder(user* user, folder* folder) {
    if (user->identity != UPLOADER || user->state != SCAN) return false;
    if (!folder) return false;
    user->state = UPLOADING;
    user->position->son_folder.emplace_back(folder);
    task_list.emplace(user->current_task = new task(user, folder, cur_clock));
    user->position->update_state();
    return true;
}

bool download_folder(user* user, folder* folder) {
    if (!folder) return false;
    if (user->identity != DOWNLOADER || user->state != SCAN || !(folder->check_folder())) return false;
    user->state = DOWNLOADING;
    task_list.emplace(user->current_task = new task(user, folder, cur_clock));
    return true;
}


int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    root = new folder("root", nullptr, IDLE);

    cin >> max_user_flux >> max_server_flux >> max_user_flux;

    init_file_system();

    string t;
    string username, command;
    while ((cin >> t), t != "down") {
        u32 time = atoi(t.c_str());

        while (task_list.size() && cur_clock < time) {
            update_flux();
            update_tasks();
            ++cur_clock;
        }
        cur_clock = time;
        // cout << "UPDATED" << endl;
        cin >> username >> command;
        if (command == "connect") {
            u32 type;
            cin >> type;
            cout << (create_user(username, type) ? "success" : "unsuccess") << endl;
        } else if (command == "quit") 
            cout << (delete_user(username) ? "success" : "unsuccess") << endl;
        else {
            user* cur_user = find_user(username);
            if (!cur_user) {
                cout << "unsuccess" << endl;
                getline(cin, t);
                continue;
            }

            if (command == "cd") {
                string dirname;
                cin >> dirname;
                folder* dir = cur_user->position->get_son_folder(dirname);
                if (dir) cur_user->position = dir, cout << "success" << endl;
                else cout << "unsuccess" << endl;
            } else if (command == "cd..") {
                folder* dir = cur_user->position->get_parent();
                if (dir) cur_user->position = dir, cout << "success" << endl;
                else cout << "unsuccess" << endl;
            } else if (command == "download") {
                string filename;
                cin >> filename;
                if (cur_user->position->get_son_file(filename)) cout << (download_file(cur_user, cur_user->position->get_son_file(filename)) ? "success" : "unsuccess") << endl;
                else cout << (download_folder(cur_user, cur_user->position->get_son_folder(filename)) ? "success" : "unsuccess") << endl;
            } else if (command == "upload") {
                string filename; u32 size;
                cin >> filename >> size;
                if (cur_user->position->get_son_file(filename) || cur_user->position->get_son_folder(filename)) 
                    cout << "unsuccess" << endl;
                else if (size) { // 说明是文件)
                    file* cur_file = new file(filename, cur_user->position, size, UPLOAD);
                    if (upload_file(cur_user, cur_file)) cout << "success" << endl;
                    else {
                        delete cur_file;
                        cout << "unsuccess" << endl;
                    }
                } else {
                    folder* cur_folder = new folder(filename, cur_user->position, UPLOAD);
                    if (upload_folder(cur_user, cur_folder)) cout << "success" << endl;
                    else {
                        delete cur_folder;
                        cout << "unsuccess" << endl;
                    }
                }
            } else {
                cout << "尚未实现" << endl;
                getline(cin, t);
            }
        }
    }
    for (auto& x : user_table) delete x;
    for (auto& x : task_list) delete x;

    return 0;
}