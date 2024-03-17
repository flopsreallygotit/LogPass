#include <algorithm> //TODO: clangd says: "Included header is not used directly"
#include <iostream>
#include <vector>
#include <set>

namespace {
    class Item { // TODO: poor class name, no `final` keyword / virtual dtor
    public:
        Item(const std::string &name, unsigned weight, unsigned price): _name(name), _weight(weight), _price(price) {}

        const std::string &get_name() const { return _name; }

        unsigned get_weight() const { return _weight; }

        unsigned get_price() const { return _price; }

        // TODO Maybe it's better to overload `operator<<`?
        void print(std::ostream &os) const { os << ": " << _name << " " << _weight << " " << _price << std::endl; } 

    private:
        std::string _name;
        unsigned    _weight, _price;
    };

    class Inventory { // TODO Poor class name, no `final` keyword / virtual dtor
    public:
        explicit Inventory(unsigned size): _size(size) {}

        bool put(const Item &item) {
            unsigned weight = item.get_weight();

            if (weight > _size)
                return false;

            _size -= weight; // TODO: It's bad practice to start your variable name with `_`, bc., for example, leading undersore before capital is reserved.
                             //       If you want to show that variable is a field, use `m_`, or any other field prefix.
            _items.push_back(item);

            return true;
        }

        void print(std::ostream &os) const {
            for (const auto item : _items)  // TODO use of unnececcary copy-ctor. 
                                            // explanation: https://cppinsights.io/s/9c59bbac, clcik "Run" then check right view, line 78
                                            // try to change to `const auto& item : _items` and check whats changed in right view
                item.print(os);
        }

    private:
        unsigned          _size;
        std::vector<Item> _items;
    };

    class Player {
    public:
        Player(const std::string &name, unsigned strength): _name(name), _strength(strength), _inventory(Inventory(strength)) {}

        const std::string &get_name() const { return _name; }

        bool take(const Item &item) { return _inventory.put(item); }

        void print(std::ostream &os) const {
            os << _name << "\n";

            _inventory.print(os);
        }

        bool operator<(const Player &player) const { return _name < player._name; } // TODO Why?...
                                                                                    // It's always better to overload starship operator (<=>)
                                                                                    // for comparasion
    private:
        std::string _name;
        unsigned    _strength;
        Inventory   _inventory;
    };

    class Party {
    public:
        bool add(const Player &player) {
            auto result = _players.insert(player);

            return result.second;
        }

        bool give(const std::string &player_name, const Item &item) {
            for (auto player : _players) // TODO unnessesary copy ctor
                if (player.get_name() == player_name)
                    return player.take(item);

            return false;
        }

        void print(std::ostream &os) const {
            for (const auto &player : _players)
                player.print(os);
        }

    private:
        std::set<Player> _players;
    };
}  // namespace

int main() {
    Item sword("Sword", 10, 128); // TODO: E2E tests are cool, but you should add unit tests.
                                  // TODO: Use google tests for that. They are easy to use.
    Item bow("Bow", 20, 256);

    Player flops("Flops", 100);
    Player serg("Serg", 200);

    flops.take(sword);
    serg.take(bow);

    Party party = {};
    party.add(flops);
    party.add(serg);

    bool second_insert = party.add(flops);
    std::cout << "Second insert value = " << second_insert << std::endl;

    party.print(std::cout);

    return 0;
}