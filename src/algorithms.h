#pragma once

#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<iostream>

typedef std::pair<int, int> ip;

template<class T1, class T2>
bool in(T1 elem, T2 cont){
    return find(cont.begin(), cont.end(), elem) != cont.end();
}

struct astar_node{
    ip pos;
    ip prev;
    double sdist;
    double ddist;
    bool obs;

    astar_node() = default;

    astar_node(ip pos, ip prev, double sd, double dd, bool obs = false): pos(pos), prev(prev), sdist(sd), ddist(dd), obs(obs) {}
};

template<class T1, class T2>
std::ostream& operator<<(std::ostream& os, std::pair<T1, T2> p){
    os << "[" << p.first << ", " << p.second << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, astar_node& as){
    os << "as(" << as.pos << ", " << as.prev << ", " << as.sdist << ", " << as.ddist << ", " << as.obs << ")";
    return os;
}

bool operator==(const astar_node& l, const astar_node& r){
    return l.pos == r.pos;
}

// takes operator >
struct minheap{
    std::vector<astar_node> vec;
    std::function<bool(astar_node&, astar_node&)> comp;

    minheap(std::vector<astar_node> v, std::function<bool(astar_node&, astar_node&)> comp): comp(comp) {
        vec = v;
        std::make_heap(v.begin(), v.end(), comp);
    }

    astar_node pop(){
        std::pop_heap(vec.begin(), vec.end(), comp);
        auto an = vec.back();
        vec.pop_back();
        return an;
    }

    void insert(astar_node an){
        vec.push_back(an);
        std::make_heap(vec.begin(), vec.end(), comp);
    }

    size_t size(){
        return vec.size();
    }
};

double dist(ip f, ip s){
    return sqrt(pow(f.first - s.first, 2) + pow(f.second - s.second, 2));
}

std::vector<ip> neighbors(ip src, int width, int height){
    auto inbounds = [&](int x, int y){
        return x >= 0 && x < width && y >= 0 && y < height;
    };

    std::vector<ip> retval;

    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            if(!i && !j) continue;

            ip p = {src.first + i, src.second + j};

            // avoid obstacles
            //if(obs.find(p) != obs.end()) continue;

            if(inbounds(p.first, p.second)){
                retval.push_back(p);
            }
        }
    }

    return retval;
}

template<class mp>
std::vector<ip> reconstruct_path(mp& map, ip src, ip dest){
    auto curr = src;

    std::vector<ip> path;

    // TODO possibly include current node in path?
    while(curr != src){
        path.push_back(curr);
        curr = map[curr].prev;
    }

    std::reverse(path.begin(), path.end());

    return path;
}

std::vector<ip> astar(level& lev, ip src, ip dest){
    std::cout << "In A*" << std::endl;

    auto width = lev.width;
    auto height = lev.height;

    //auto comp = [&](ip l, ip r) { return l.first + l.second*height < r.first + r.second*height; };
    //auto heapcomp = [&](astar_node l, astar_node r) { return l.pos.first + l.pos.second*height < r.pos.first + r.pos.second*height; };

    //std::map<ip, astar_node, comp> visited;
    auto visited = std::map<ip, astar_node, std::function<bool(const ip&, const ip&)>>{
        [&](ip l, ip r) { return l.first + l.second*height < r.first + r.second*height; }
    };

    for(auto& obs : lev.obstructions){
        visited[obs] = astar_node(obs, obs, 0, 0, true);
    }

    astar_node first(src, src, 0, dist(src, dest));

    std::cout << "First is " << first << std::endl;

    //minheap(std::vector<astar_node>({first}), heapcomp);
    minheap hp(std::vector<astar_node>({first}), [&](astar_node l, astar_node r) { return l.pos.first + l.pos.second*height < r.pos.first + r.pos.second*height; });

    while(hp.size()){
        auto current = hp.pop();

        std::cout << "Processing " << current << std::endl;

        if(current.pos == dest){
            // construct path and return
            return reconstruct_path(visited, src, dest);
        }

        auto neigh = neighbors(current.pos, width, height);

        for(auto& npos : neigh){
            // initialize if needed
            if(!visited.count(npos)){
                visited[npos] = astar_node(npos, current.pos, current.sdist + 1, dist(npos, dest));
            }

            // skip obstructions
            if(visited[npos].obs) continue;

            // neighbor node
            auto& nnode = visited[npos];

            // update if closer
            if(current.sdist + 1 < nnode.sdist){
                nnode.sdist = current.sdist + 1;
                nnode.prev = current.pos;
            }

            if(!in(nnode, hp.vec)){
                hp.insert(nnode);
            }
        }
    }

    return {};
}