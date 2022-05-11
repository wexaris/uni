#include <iostream>
#include <fstream>

#ifndef SIZE_MAX
#define SIZE_MAX 0xffffffff
#endif

const char* INPUT_FILE = "salas.in";
const char* OUTPUT_FILE = "salas.out";

class Island {
    struct Route {
        Island* Destination;
        size_t TravelTime;

        Route() : Destination(NULL), TravelTime(0) {}

        void set(Island* dest, size_t travel_time) {
            Destination = dest;
            TravelTime = travel_time;
        }

        operator bool() const { return Destination != NULL; }
    };

public:
    Island(size_t id, size_t island_count) :
        m_ID(id),
        m_IslandCount(island_count)
    {
        m_Routes = new Route[m_IslandCount];
    }

    ~Island() {
        delete[] m_Routes;
    }

    void add_route(Island* other, size_t time) {
        m_Routes[other->m_ID].set(other, time);
        other->m_Routes[m_ID].set(this, time);
    }

    const Route& route(size_t idx) const {
        return m_Routes[idx];
    }

private:
    size_t m_ID;
    size_t m_IslandCount;
    Route* m_Routes;
};

/// Find shortest one of distances
/// Return its index
size_t min_dist(size_t* min_dist, size_t count, bool* visited) { // finding minimum distance
    size_t idx = 0;
    size_t minimum = SIZE_MAX;

    for (size_t i = 0; i < count; i++) {
        if (!visited[i] && min_dist[i] <= minimum) {
            minimum = min_dist[i];
            idx = i;
        }
    }
    return idx;
}

/// Find shortest paths to all islands from the source island
/// Uses Dijkstra's algorithm
size_t* calc_shortest_paths(Island* islands, size_t count, size_t src = 0) {
    size_t* dist = new size_t[count]; // minimum distance for each node
    bool* visited = new bool[count];  // visited or unvisited for each node

    for (size_t i = 0; i < count; i++) {
        dist[i] = SIZE_MAX;
        visited[i] = false;
    }

    dist[src] = 0; // Source vertex distance should be 0

    for (size_t i = 0; i < count; i++) {
        size_t m = min_dist(dist, count, visited);
        visited[m] = true;
        for (size_t j = 0; j < count; j++) {
            // Save shortest distance
            if (!visited[j] && islands[m].route(j) && dist[m] != SIZE_MAX && dist[m] + islands[m].route(j).TravelTime < dist[j])
                dist[j] = dist[m] + islands[m].route(j).TravelTime;
        }
    }

    return dist;
}

int main() {
    std::ifstream in(INPUT_FILE);
    if (in.is_open()) {
        size_t N, K;
        in >> N >> K;

        // Construct Island array using in-place constructors
        void* island_mem = operator new[](N * sizeof(Island));
        Island* islands = static_cast<Island*>(island_mem);
        for (size_t i = 0; i < N; ++i)
            new(&islands[i]) Island(i, N);

        // Collect island routes
        while (in.good() && K--) {
            size_t x, y, t;
            in >> x >> y >> t;

            islands[x - 1].add_route(&islands[y - 1], t);
        }

        std::ofstream out(OUTPUT_FILE);
        if (out.is_open()) {
            for (size_t i = 0; i < N; i++) {
                size_t* dist = calc_shortest_paths(islands, N, i);

                for (size_t j = 0; j < N; j++) {
                    out << dist[j] << " ";
                }
                out << std::endl;
            }
            out.close();
        }

        // Destruct Island array
        for (size_t i = 0; i < N; i++)
            islands[i].~Island();
        operator delete[](island_mem);

        in.close();
    }
}
