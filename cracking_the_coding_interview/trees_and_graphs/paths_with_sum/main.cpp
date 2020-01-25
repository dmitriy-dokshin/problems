#include <functional>
#include <iostream>
#include <memory>
#include <random>

using namespace std;

template <class T>
class TNode {
public:
    shared_ptr<TNode> Left;
    shared_ptr<TNode> Right;
    T Value = {};
    size_t Index = 0;
};

function<bool()> make_node_rand(const float threshold) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(0.0f, 1.0f);
    auto result =
        [threshold, gen = move(gen), dis = move(dis)]() mutable {
            return dis(gen) < threshold;
        };
    return result;
}

template <class T>
function<T()> make_value_rand(const T min, const T max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<T> dis(min, max);
    return [gen = move(gen), dis = move(dis)]() mutable { return dis(gen); };
}

template <class T>
void build_random_tree(
    shared_ptr<TNode<T>> node,
    vector<shared_ptr<TNode<T>>>& nodes,
    function<bool()>& left_rand,
    function<bool()>& right_rand,
    function<T()>& value_rand,
    const size_t max_size) {
    nodes.emplace_back(node);

    node->Value = value_rand();
    node->Index = nodes.size() - 1;

    if (nodes.size() < max_size && left_rand()) {
        node->Left = make_shared<TNode<T>>();
        build_random_tree(node->Left, nodes, left_rand, right_rand, value_rand, max_size);
    }

    if (nodes.size() < max_size && right_rand()) {
        node->Right = make_shared<TNode<T>>();
        build_random_tree(node->Right, nodes, left_rand, right_rand, value_rand, max_size);
    }
}

template <class T>
vector<shared_ptr<TNode<T>>> build_random_tree(const float threshold, const float min, const float max, const size_t max_size) {
    auto left_rand = make_node_rand(threshold);
    auto right_rand = make_node_rand(threshold);
    auto value_rand = make_value_rand<T>(min, max);

    vector<shared_ptr<TNode<T>>> nodes;
    if (max_size > 0) {
        build_random_tree(make_shared<TNode<T>>(), nodes, left_rand, right_rand, value_rand, max_size);
    }
    return nodes;
}

template <class T>
void count_paths_with_sum(const TNode<T>& node, const T target_sum, size_t& count, T sum = 0) {
    sum += node.Value;
    if (sum == target_sum) {
        count++;
    }

    if (node.Left) {
        count_paths_with_sum(*node.Left, target_sum, count, sum);
    }

    if (node.Right) {
        count_paths_with_sum(*node.Right, target_sum, count, sum);
    }
}

template <class T>
void traverse(const TNode<T>& node, function<void(const TNode<T>&)> f) {
    f(node);

    if (node.Left) {
        traverse(*node.Left, f);
    }

    if (node.Right) {
        traverse(*node.Right, f);
    }
}

int main() {
    vector<shared_ptr<TNode<int>>> nodes;

    /*
    for (size_t i = 0; i < 10; i++) {
        nodes.emplace_back(make_shared<TNode<int>>());
        nodes[i]->Index = i;
    }

    nodes[0]->Left = nodes[1];
    nodes[0]->Right = nodes[7];
    nodes[1]->Left = nodes[2];
    nodes[2]->Left = nodes[3];
    nodes[2]->Right = nodes[6];
    nodes[3]->Left = nodes[4];
    nodes[4]->Left = nodes[5];
    nodes[7]->Right = nodes[8];
    nodes[8]->Left = nodes[9];

    nodes[0]->Value = -1;
    nodes[1]->Value = 4;
    nodes[2]->Value = 1;
    nodes[3]->Value = -5;
    nodes[4]->Value = 3;
    nodes[5]->Value = -4;
    nodes[6]->Value = -5;
    nodes[7]->Value = -8;
    nodes[8]->Value = 7;
    nodes[9]->Value = -10;
    */

    nodes = build_random_tree<int>(0.5f, -10, 10, 10);

    for (size_t i = 0; i < nodes.size(); i++) {
        const auto& node = *nodes[i];
        pair<size_t, size_t> lr;
        if (node.Left) {
            lr.first = node.Left->Index;
        }
        if (node.Right) {
            lr.second = node.Right->Index;
        }
        cerr << i << "\t{" << lr.first << ", " << lr.second << "}\t" << node.Value << endl;
    }

    int target_sum;
    cin >> target_sum;

    {
        size_t count = 0;
        traverse<int>(*nodes[0], [target_sum, &count](const auto& node) { return count_paths_with_sum(node, target_sum, count); });
        cerr << count << endl;
    }
}
