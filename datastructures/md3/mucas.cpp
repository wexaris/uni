#include <iostream>
#include <fstream>

const char* INPUT_FILE = "mucas.dat";
const char* OUTPUT_FILE = "mucas.rez";

class Barrel {
public:
    Barrel(size_t id, size_t max_conn) :
        m_ID(id),
        m_MaxConnections(max_conn),
        m_Content(0)
    {
        m_Connections = new bool[m_MaxConnections];
        memset(m_Connections, 0, m_MaxConnections * sizeof(m_Connections[0]));
    }

    ~Barrel() {
        delete[] m_Connections;
    }

    ///
    void fill(Barrel* list, long double amount) {
        bool* visited = new bool[m_MaxConnections];
        memset(visited, 0, m_MaxConnections * sizeof(visited[0]));

        long double total = 0;
        size_t count = 0;

        visit_connected(list, visited, &total, &count);

        memset(visited, 0, m_MaxConnections * sizeof(visited[0]));
        long double amount_per = (total + amount) / count;

        set_connected_amount(list, visited, amount_per);

        delete[] visited;
    }

    ///
    void toggle_connection(Barrel* list, Barrel& other) {
        m_Connections[other.m_ID] = !m_Connections[other.m_ID];
        other.m_Connections[m_ID] = m_Connections[other.m_ID];

        fill(list, 0);
    }

    long double amount() const { return m_Content; }

private:
    size_t m_ID;
    size_t m_MaxConnections;

    long double m_Content;
    bool* m_Connections;

    void visit_connected(Barrel* list, bool* visited, long double* total, size_t* count) const {
        if (visited[m_ID])
            return;

        visited[m_ID] = true;
        (*total) += m_Content;
        (*count)++;

        for (size_t i = 0; i < m_MaxConnections; i++)
            if (m_Connections[i])
                list[i].visit_connected(list, visited, total, count);
    }

    void set_connected_amount(Barrel* list, bool* visited, long double amount) {
        if (visited[m_ID])
            return;

        visited[m_ID] = true;
        m_Content = amount;

        for (size_t i = 0; i < m_MaxConnections; i++)
            if (m_Connections[i])
                list[i].set_connected_amount(list, visited, amount);
    }
};

int main() {
    int overflow_idx = 0;

    std::ifstream in(INPUT_FILE);
    if (in.is_open()) {
        size_t N, K;
        in >> N >> K;

        void* barrel_mem = operator new[](N * sizeof(Barrel));
        Barrel* barrels = static_cast<Barrel*>(barrel_mem);
        for (size_t i = 0; i < N; ++i)
            new(&barrels[i]) Barrel(i, N);

        while (in.good() && K--) {
            overflow_idx++;

            char op;
            size_t arg1, arg2;
            in >> op >> arg1 >> arg2;

            switch (op)
            {
            case 'P':
                barrels[arg1 - 1].fill(barrels, arg2);
                break;

            case 'V':
                barrels[arg1 - 1].toggle_connection(barrels, barrels[arg2 - 1]);
                break;

            default:
                break;
            }

            if (barrels[arg1 - 1].amount() > 100)
                break;
        }

        for (size_t i = 0; i < N; i++)
            barrels[i].~Barrel();
        operator delete[](barrel_mem);

        in.close();
    }

    std::ofstream out(OUTPUT_FILE);
    if (out.is_open()) {
        out << overflow_idx << std::endl;
        out.close();
    }
}
