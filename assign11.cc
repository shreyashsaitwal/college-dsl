#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Member {
    unsigned int id;
    string name;
    string phone;
    string email;
};

class ClubDatabase {
   private:
    string DB_FILE;

    vector<string> tokens(string str) {
        std::istringstream iss(str);
        std::vector<std::string> tokens;

        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        for (const auto &t : tokens) {
            std::cout << t << std::endl;
        }

        return tokens;
    }

    Member toksToMember(vector<string> toks) {
        Member m;
        m.id = stoi(toks.at(0));
        m.name = toks.at(1);
        m.phone = toks.at(2);
        m.email = toks.at(3);
        return m;
    }

    string memberToStr(Member m) {
        return to_string(m.id) + " " + m.name + " " + m.phone + " " + m.email + "\n";
    }

    void writeToDb() {
        fstream fs(DB_FILE, std::ios::out | ios::trunc);
        if (!fs.is_open()) {
            std::cerr << "Failed to open file for writing: " << DB_FILE << std::endl;
            return;
        }
        for (const Member &m : members) {
            string line = memberToStr(m);
            fs << line;
        }
        fs.close();
    }

   public:
    vector<Member> members;
    
    ClubDatabase(string file) : DB_FILE(file) {
        fstream fs(DB_FILE);
        string line;
        while (getline(fs, line)) {
            vector<string> toks = tokens(line);
            if (toks.size() < 4) continue;
            members.push_back(toksToMember(toks));
        }
        fs.close();
    }

    ~ClubDatabase() {
        writeToDb();
    }

    void addMember(Member m) {
        // try {
        //     auto mm = searchMember(m.id);
        //     throw runtime_error("Member with ID " + to_string(m.id) + " already exist");
        // } catch (runtime_error e) {
        //     //
        // }
        members.push_back(m);
        writeToDb();
    }

    vector<Member>::iterator searchMember(unsigned int id) {
        auto it = find_if(members.begin(), members.end(), [&id](const Member &m) { return m.id == id; });
        if (it != members.end()) {
            return it;
        }
        throw runtime_error("Member with ID " + to_string(id) + " does not exist");
    }

    void deleteMember(unsigned int id) {
        members.erase(
            remove_if(members.begin(), members.end(), [&id](const Member &m) { return m.id == id; }),
            members.end()
        );
        writeToDb();
    }

    void updateMember(vector<Member>::iterator it, string newName, string newPhone, string newEmail) {
        Member m;
        m.id = (*it).id;
        m.name = newName;
        m.phone = newPhone;
        m.email = newEmail;
        *it = m;
        writeToDb();
    }
};

int main() {
    ClubDatabase db("./club.db.txt");
    while(true) {
        cout << "1. Add new member\n";
        cout << "2. Search member\n";
        cout << "3. Delete member\n";
        cout << "4. Update member\n";
        cout << "0. Exit\n";
        cout << "> Enter your choice: ";

        int ch;
        cin >> ch;

        if (ch == 0) break;

        switch(ch) {
            case 1: {
                Member m;
                cout << "  > Member ID: ";
                cin >> m.id;
                cout << "  > Member name: ";
                cin >> m.name;
                cout << "  > Member phone: ";
                cin >> m.phone;
                cout << "  > Member email: ";
                cin >> m.email;
                db.addMember(m);
                cout << "  !! Success" << endl;
                break;
            }
            case 2: {
                cout << "  > Member ID: ";
                unsigned int id;
                cin >> id;
                try {
                    auto m = *db.searchMember(id);
                    cout << "  - Member name: " << m.name << "\n";
                    cout << "  - Member phone: " << m.phone << "\n";
                    cout << "  - Member email: " << m.email << "\n";
                } catch (runtime_error e) {
                    cerr << e.what() << endl;
                }
            }
            case 3: {
                cout << "  > Member ID: ";
                unsigned int id;
                cin >> id;
                db.deleteMember(id);
                cout << "  !! Success" << endl;
            }
            case 4: {
                cout << "  > Member ID: ";
                unsigned int id;
                cin >> id;
                auto it = db.searchMember(id);
                if (it == db.members.end()) {
                    throw runtime_error("Member with ID " + to_string(id) + " does not exist");
                }

                cout << "  > Updated name: ";
                string name;
                cin >> name;
                cout << "  > Updated phone: ";
                string phone;
                cin >> phone;
                cout << "  > Updated email: ";
                string email;
                cin >> email;

                db.updateMember(it, name, phone, email);
                cout << "  !! Success" << endl;
            }
        }
    }
}
